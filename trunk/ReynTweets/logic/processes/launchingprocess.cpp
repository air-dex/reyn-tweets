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
			checkTokens();
			return;

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
			break;
	}

	// Telling the component that the launching process has ended fatally.
	// TODO
	emit launchEnded(false, errorMsg, true);
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

// Determining if a token seems legit
bool LaunchingProcess::isValidToken(QByteArray token) {
	// Right tokens == Tokens not empty

	// Step 1 : Base 64 form not null or empty
	if (token.isNull() || token.isEmpty()) {
		return false;
	}

	// Step 2 : Clear form not null or empty
	QByteArray clearToken = QByteArray::fromBase64(token);

	return !(clearToken.isNull() || clearToken.isEmpty());
}

void LaunchingProcess::verifyOK(CoreResult verifyRes) {
	QString errorMsg = "";
	bool isFatal = false;

	switch (verifyRes) {
		case TOKENS_OK:
			// Credentials were right.
			saveConfiguration();
			return;

		case WRONG_USER:
			// User of the configuration and user of credentials do not match.
			// Getting tokens for the user of the configuration
			errorMsg = LaunchingProcess::trUtf8("The user was not the right one.");
			break;

		case TOKENS_NOT_AUTHORIZED:
			// Credentials were wrong for the user.
			// Getting tokens for the user of the configuration.
			errorMsg = LaunchingProcess::trUtf8("Tokens for authentication to Twitter were wrong.");
			break;

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
			errorMsg = LaunchingProcess::trUtf8("Unknown prolem");
			isFatal = true;
			break;

		default:
			// Unexpected result. Abort.
			errorMsg = LaunchingProcess::trUtf8("Unexpected result");
			isFatal = true;
			break;
	}

	// Telling the component wat happens
	// TODO
	emit launchEnded(false, errorMsg, isFatal);
}


/////////////////////////////////////////////////////
// Step 3 : verifying if the user is the right one //
/////////////////////////////////////////////////////


////////////////////////////////////////////////////
// Step 4 : updating and saving the configuration //
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

	// Choix dans la date
	ReynTweetsDateTime userdate = configuration.getUserAccount().getUser().getCreatedAt();
	qDebug("Choix dans la date :");
	qDebug(userdate.toString().toAscii());

	// Launching the configuration
	QDataStream readStream(&confFile);
	QVariant confVariant = qVariantFromValue(configuration);

	readStream << confVariant;
	confFile.close();

	return SAVE_SUCCESSFUL;
}

void LaunchingProcess::saveOK(CoreResult saveRes) {
	// TODO
	QString errorMsg = "";

	switch (saveRes) {
		case SAVE_SUCCESSFUL:
			// The application was saved correctly.
			emit launchEnded(true);
			return;

		case CONFIGURATION_FILE_UNKNOWN:
			errorMsg = LaunchingControl::trUtf8("Configuration file does not exist.");
			break;

		case CONFIGURATION_FILE_NOT_OPEN:
			errorMsg = LaunchingControl::trUtf8("Configuration file cannot be opened.");
			break;

		default:
			errorMsg = LaunchingControl::trUtf8("Unknown problem");
			break;
	}

	// Telling the component that there were a problem
	emit launchEnded(false, errorMsg, true);
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

// Uploading the configuration after an authentication process
void LaunchingProcess::updateConfAfterAuth(QByteArray accessToken, QByteArray tokenSecret, qlonglong id, QString) {
	// Updating the tokens
	UserAccount account = configuration.getUserAccount();
	account.setAccessToken(accessToken.toBase64());
	account.setTokenSecret(tokenSecret.toBase64());
	configuration.setUserAccount(account);

	// Getting informations about the user behind the account
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(getUser(ResultWrapper)));
	twitter.showUser(id);
}

// Getting a user after requesting it to Twitter
void LaunchingProcess::getUser(ResultWrapper res) {
	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(getUser(ResultWrapper)));

	RequestResult result = res.accessResult(this);
	ErrorType errorType = result.getErrorType();

	switch (errorType) {
		case NO_ERROR: {
			// Get user, put it in the conf and save
			QVariantMap parsedResults = result.getParsedResult().toMap();
			User u;
			u.fillWithVariant(parsedResults);
			UserAccount & account = configuration.getUserAccount();
			account.setUser(u);
			configuration.setUserAccount(account);
			saveConfiguration();
		}break;

		case API_CALL: {
			// Retrieving network informations
			int httpCode = result.getHttpCode();
			QString httpReason = result.getHttpReason();

			// Building error message
			QString errorMsg = "Network error ";
			errorMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(httpReason)
					.append(" :\n")
					.append(result.getErrorMessage())
					.append(".\n");
//			emit errorProcess(false, errorMsg);
		}break;

		case OAUTH_PARSING: {
			// Building error message
			QString errorMsg = "Parsing error :\n";
			errorMsg.append(result.getParsingErrorMessage());
//			emit errorProcess(false, errorMsg);
		}break;

		default: {
			// Unexpected problem. Abort.
			QString errorMessage = "Unexpected problem :\n";
			errorMessage.append(result.getErrorMessage()).append(".\n");
//			emit errorProcess(true, errorMessage);
		}break;
	}
}


///////////////////////////////
// Authentication management //
///////////////////////////////

void LaunchingProcess::allowReynTweets() {
	//
}
