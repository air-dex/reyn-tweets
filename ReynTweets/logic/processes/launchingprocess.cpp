#include <QFile>
#include "launchingprocess.hpp"

LaunchingProcess::LaunchingProcess(ReynTweetsConfiguration & conf) :
	GenericProcess(),
	twitter(this),
	configuration(conf)
{
	// Wiring between the different steps of the process
	connect(this, SIGNAL(loadConfigurationEnded(CoreResult)),
			this, SLOT(loadOK(CoreResult)));
	connect(this, SIGNAL(verifyTokensEnded(CoreResult)),
			this, SLOT(verifyOK(CoreResult)));
	connect(this, SIGNAL(saveConfEnded(CoreResult)),
			this, SLOT(saveOK(CoreResult)));
}

// Starting the process
void LaunchingProcess::startProcess() {
	loadConfiguration();
}


////////////////////////////////////////
// Step 1 : loading the configuration //
////////////////////////////////////////

// Loading the configuartion from the configuration file
void LaunchingProcess::loadConfiguration() {
	emit loadConfigurationEnded(loadConfigurationPrivate());
}

// Loading the configuartion from the configuration file
CoreResult LaunchingProcess::loadConfigurationPrivate() {
	// Opening the configuration file
	QFile confFile("conf/ReynTweets.conf");

	if (!confFile.exists()) {
		return CONFIGURATION_FILE_UNKNOWN;
	}

	bool openOK = confFile.open(QFile::ReadOnly);
	if (!openOK) {
		return CONFIGURATION_FILE_NOT_OPEN;
	}

	// Launching the configuration
	QDataStream readStream(&confFile);
	QVariant confVariant;

	readStream >> confVariant;
	confFile.close();

	if (!qVariantCanConvert<ReynTweetsConfiguration>(confVariant)) {
		// The content of the file cannot be converted into a configuration.
		return LOADING_CONFIGURATION_ERROR;
	}

	configuration = qVariantValue<ReynTweetsConfiguration>(confVariant);
	fillOAuthManager();
	return LOAD_CONFIGURATION_SUCCESSFUL;
}

void LaunchingProcess::loadOK(CoreResult loadRes) {
	QString errorMsg = "";

	switch (loadRes) {
		case LOAD_CONFIGURATION_SUCCESSFUL:
			// The configuration was loaded correctly. Let's check the credentials
			return checkTokens();

		case CONFIGURATION_FILE_UNKNOWN:
			errorMsg = LaunchingProcess::trUtf8("Configuration file does not exist.");
			break;

		case CONFIGURATION_FILE_NOT_OPEN:
			errorMsg = LaunchingProcess::trUtf8("Configuration file cannot be opened.");
			break;

		case LOADING_CONFIGURATION_ERROR:
			errorMsg = LaunchingProcess::trUtf8("Configuration cannot be loaded.");
			break;

		default:
			// Unknown problem.
			errorMsg = LaunchingProcess::trUtf8("Unknown problem");
			loadRes = UNKNOWN_PROBLEM;
			break;
	}

	// Telling the component that the launching process has ended fatally.
	buildResult(false, loadRes, errorMsg, true);
	emit processEnded();
}


////////////////////////////////////////
// Step 2 : verifying the credentials //
////////////////////////////////////////

// Checks if the access tokens seem legit.
void LaunchingProcess::checkTokens() {
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(verifyCredentialsEnded(ResultWrapper)));
	twitter.verifyCredentials(true, true);
}

// Slot executed after verifying credentials.
void LaunchingProcess::verifyCredentialsEnded(ResultWrapper res) {
	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(verifyCredentialsEnded(ResultWrapper)));

	RequestResult result = res.accessResult(this);
	int httpCode = result.getHttpCode();

	switch (httpCode) {
		case 200: {
			// Credentials were right a priori. Ensures that the user is the right one.
			QVariantMap userMap = result.getParsedResult().toMap();
			User userOfCredentials;
			userOfCredentials.fillWithVariant(userMap);
			UserAccount & account = configuration.getUserAccount();
			User confUser = account.getUser();
			bool rightUser = confUser.getID() == userOfCredentials.getID();
			CoreResult res = rightUser ?
						TOKENS_OK
					  : WRONG_USER;
			if (rightUser) {
				account.setUser(userOfCredentials);
			}
			emit verifyTokensEnded(res);
		}break;

		case 401:
			// Credentials were wrong
			emit verifyTokensEnded(TOKENS_NOT_AUTHORIZED);
			break;

		case 420:
			// Rate limited
			emit verifyTokensEnded(RATE_LIMITED);
			break;

		default:
			if (httpCode / 100 == 5) {
				// Return code is 5xx -> Twitter problem
				emit verifyTokensEnded(TWITTER_DOWN);
			} else {
				// Unknown problem
				emit verifyTokensEnded(UNKNOWN_PROBLEM);
			}
			break;
	}
}

void LaunchingProcess::verifyOK(CoreResult verifyRes) {
	QString errorMsg = "";
	bool isFatal = false;

	switch (verifyRes) {
		case TOKENS_OK:
			// Credentials were right.
			return saveConfiguration();

		case WRONG_USER:
			// User of the configuration and user of credentials do not match.
			// Getting tokens for the user of the configuration
			errorMsg = LaunchingProcess::trUtf8("The user was not the right one.");
			emit authenticationRequired();
			return;

		case TOKENS_NOT_AUTHORIZED:
			// Credentials were wrong for the user.
			// Getting tokens for the user of the configuration.
			errorMsg = LaunchingProcess::trUtf8("Tokens for authentication to Twitter were wrong.");
			emit authenticationRequired();
			return;

		case RATE_LIMITED:
			// Rate limited. Asking the user to try later.
			errorMsg = LaunchingProcess::trUtf8("You reach the authentication rate.");
			break;

		case TWITTER_DOWN:
			// Twitter problem Asking the user to try later.
			errorMsg = LaunchingProcess::trUtf8("Twitter is down.");
			break;

		case UNKNOWN_PROBLEM:
			// Unknown problem. Abort ?
			errorMsg = LaunchingProcess::trUtf8("Unknown prolem.");
			isFatal = true;
			break;

		default:
			// Unexpected result. Abort.
			errorMsg = LaunchingProcess::trUtf8("Unexpected result.");
			isFatal = true;
			verifyRes = UNKNOWN_PROBLEM;
			break;
	}

	// Telling the component wat happens
	buildResult(false, verifyRes, errorMsg, isFatal);
	emit processEnded();
}


////////////////////////////////////////////////
// Step 2bis : authenticating the application //
////////////////////////////////////////////////

// What happened while authorizing Reyn Tweets
void LaunchingProcess::authenticationIssue(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	if (result == WRONG_PROCESS_RESULT) {
		return;
	}

	CoreResult authIssue = result.processIssue;
	QString errorMsg = "";
	bool isFatal;
	bool processOK;

	switch (authIssue) {
		case AUTHORIZED: {
			// Download the user then save

			// Extract the different values
			QVariantMap resultMap = result.results;
			QByteArray accessToken = resultMap.value("access_token").toByteArray();
			QByteArray tokenSecret = resultMap.value("token_secret").toByteArray();
			qlonglong userID = resultMap.value("user_id").toLongLong();
			QString screenName = resultMap.value("screen_name").toString();

			updateConfiguration(accessToken, tokenSecret, userID, screenName);
		}return;

		case DENIED:
			// Try again later or quit
			processOK = true;
			errorMsg = LaunchingProcess::trUtf8("Reyn Tweets was not authorized to use your Twitter account.");
			isFatal = false;
			break;

		case RATE_LIMITED:
			// Try again later
			processOK = false;
			errorMsg = LaunchingProcess::trUtf8("You reach the Twitter rate.");
			isFatal = false;
			break;

		case TWITTER_DOWN:
			// Try again later
			processOK = false;
			errorMsg = LaunchingProcess::trUtf8("Twitter seems down.");
			isFatal = false;
			break;

		case TOKENS_NOT_AUTHORIZED:
			// Quit
			processOK = false;
			errorMsg = LaunchingProcess::trUtf8("Tokens seem wrong.");
			isFatal = true;
			break;

		case NO_TOKENS:
			// Quit
			processOK = false;
			errorMsg = LaunchingProcess::trUtf8("Twitter did not give any token.");
			isFatal = true;
			break;

		case PARSE_ERROR:
			// Quit
			processOK = false;
			errorMsg = LaunchingProcess::trUtf8("Internal error while parsing Twitter results.");
			isFatal = true;
			break;

		case UNKNOWN_PROBLEM:
			// Quit
			processOK = false;
			errorMsg = LaunchingProcess::trUtf8("Problem unknown");
			isFatal = true;
			break;

		default:
			// Quit
			processOK = false;
			errorMsg = LaunchingProcess::trUtf8("Unexpected end.");
			isFatal = true;
			authIssue = UNKNOWN_PROBLEM;
			break;
	}

	// Failed end
	buildResult(processOK, authIssue, errorMsg, isFatal);
	emit processEnded();
}

// Uploading the configuration with the authentified user after an authentication process
void LaunchingProcess::updateConfiguration(QByteArray accessToken,
										   QByteArray tokenSecret,
										   qlonglong id, QString)
{
	// Updating the tokens
	UserAccount & account = configuration.getUserAccount();
	account.setAccessToken(accessToken.toBase64());
	account.setTokenSecret(tokenSecret.toBase64());

	// Getting informations about the user behind the account
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(retrieveUserEnded(ResultWrapper)));
	twitter.showUser(id);
}

// Updating a user after requesting it to Twitter
void LaunchingProcess::retrieveUserEnded(ResultWrapper res) {
	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(retrieveUserEnded(ResultWrapper)));

	RequestResult result = res.accessResult(this);
	ErrorType errorType = result.getErrorType();

	CoreResult issue;
	QString errorMsg = "";
	bool isFatal = true;

	switch (errorType) {
		case NO_ERROR: {
			// Get user, put it in the conf and save
			QVariantMap parsedResults = result.getParsedResult().toMap();
			User u;
			u.fillWithVariant(parsedResults);
			UserAccount & account = configuration.getUserAccount();
			account.setUser(u);
			saveConfiguration();
		}return;

		case API_CALL: {
			// Retrieving network informations
			int httpCode = result.getHttpCode();
			QString httpReason = result.getHttpReason();

			// Building error message
			errorMsg = LaunchingProcess::trUtf8("Network error ");
			errorMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(httpReason)
					.append(" :\n")
					.append(result.getErrorMessage())
					.append(".\n");

			// Looking for specific value of the return code
			if (httpCode / 100 == 5) {
				issue = TWITTER_DOWN;
			} else if (httpCode == 420) {
				issue = RATE_LIMITED;
			} else {
				issue = NO_TOKENS;
			}

			isFatal = false;
		}break;

		case OAUTH_PARSING:
			// Building error message
			errorMsg = LaunchingProcess::trUtf8("Parsing error :\n");
			errorMsg.append(result.getParsingErrorMessage());
			issue = PARSE_ERROR;
			break;

		default:
			// Unexpected problem. Abort.
			errorMsg = LaunchingProcess::trUtf8("Unexpected problem :\n");
			errorMsg.append(result.getErrorMessage()).append(".\n");
			issue = UNKNOWN_PROBLEM;
			break;
	}

	// Failed end
	buildResult(false, issue, errorMsg, isFatal);
	emit processEnded();
}


////////////////////////////////////////////////////
// Step 3 : updating and saving the configuration //
////////////////////////////////////////////////////

// Saving the configuartion in the configuration file
void LaunchingProcess::saveConfiguration() {
	emit saveConfEnded(saveConfigurationPrivate());
}

// Saving the configuartion in the configuration file
CoreResult LaunchingProcess::saveConfigurationPrivate() {
	// Opening the configuration file
	QFile confFile("conf/ReynTweets.conf");

	if (!confFile.exists()) {
		return CONFIGURATION_FILE_UNKNOWN;
	}

	bool openOK = confFile.open(QFile::WriteOnly);
	if (!openOK) {
		return CONFIGURATION_FILE_NOT_OPEN;
	}

	// Launching the configuration
	QDataStream readStream(&confFile);
	QVariant confVariant = qVariantFromValue(configuration);

	readStream << confVariant;
	confFile.close();

	return SAVE_SUCCESSFUL;
}

void LaunchingProcess::saveOK(CoreResult saveRes) {
	bool processOK = false;
	CoreResult finalIssue = saveRes;
	QString errorMsg = "";
	bool isFatal = true;

	switch (saveRes) {
		case SAVE_SUCCESSFUL:
			// The application was saved correctly.
			processOK = true;
			finalIssue = PROCESS_OK;
			isFatal = false;
			break;

		case CONFIGURATION_FILE_UNKNOWN:
			errorMsg = LaunchingProcess::trUtf8("Configuration file does not exist.");
			break;

		case CONFIGURATION_FILE_NOT_OPEN:
			errorMsg = LaunchingProcess::trUtf8("Configuration file cannot be opened.");
			break;

		default:
			finalIssue = UNKNOWN_PROBLEM;
			errorMsg = LaunchingProcess::trUtf8("Unknown problem");
			break;
	}

	// Ending the process
	buildResult(processOK, finalIssue, errorMsg, isFatal);
	emit processEnded();
}


//////////
// Misc //
//////////

// Filling the OAuth manager of the ReynTwitterCalls with right credentials
void LaunchingProcess::fillOAuthManager() {
	ReynTwitterCalls::setNewTokens(configuration.getUserAccount().getAccessToken(),
								   configuration.getUserAccount().getTokenSecret(),
								   ReynTweetsConfiguration::getConsumerKey(),
								   ReynTweetsConfiguration::getConsumerSecret());
}

// Building the process results
void LaunchingProcess::buildResult(bool processOK,
								   CoreResult issue,
								   QString errMsg,
								   bool isFatal)
{
	processResult.processOK = processOK;
	processResult.processIssue = issue;
	processResult.errorMsg = errMsg;
	processResult.fatalError = isFatal;
	processResult.results = QVariantMap();
}

