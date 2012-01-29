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
	processResult = buildResult(false, errorMsg, true);
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
			emit authenticationRequired();
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
	processResult = buildResult(false, errorMsg, isFatal);
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

	switch (authIssue) {
		case AUTHORIZED:
			break;

		case DENIED:
			break;

		case RATE_LIMITED:
			break;

		case TWITTER_DOWN:
			break;

		case TOKENS_NOT_AUTHORIZED:
			break;

		case NO_TOKENS:
			break;

		case PARSE_ERROR:
			break;

		case UNKNOWN_PROBLEM:
			break;

		default:
			break;
	}
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
	QString errorMsg = "";

	switch (saveRes) {
		case SAVE_SUCCESSFUL:
			// The application was saved correctly.
			processResult = buildResult(true);
			emit processEnded();
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
	processResult = buildResult(false, errorMsg, true);
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
