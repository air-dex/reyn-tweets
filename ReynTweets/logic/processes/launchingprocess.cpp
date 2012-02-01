#include <QFile>
#include "launchingprocess.hpp"

LaunchingProcess::LaunchingProcess(ReynTweetsConfiguration & conf) :
	GenericProcess(),
	twitter(this),
	configuration(conf)
{}

// Starting the process
void LaunchingProcess::startProcess() {
	loadConfiguration();
}


////////////////////////////////////////
// Step 1 : loading the configuration //
////////////////////////////////////////

// Loading the configuartion from the configuration file
void LaunchingProcess::loadConfiguration() {
	CoreResult loadIssue = configuration.load();

	QString errorMsg = "";

	switch (loadIssue) {
		case LOAD_CONFIGURATION_SUCCESSFUL:
			// The configuration was loaded correctly. Let's check the credentials
			fillOAuthManager();
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
			loadIssue = UNKNOWN_PROBLEM;
			break;
	}

	// Telling the component that the launching process has ended fatally.
	buildResult(false, loadIssue, errorMsg, true);
	endProcess();
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

	// Analysing the Twitter request
	RequestResult result = res.accessResult(this);
	int httpCode = result.getHttpCode();
	CoreResult verifyIssue;

	switch (httpCode) {
		case 200: {
			// Credentials were right a priori. Ensures that the user is the right one.
			QVariantMap userMap = result.getParsedResult().toMap();
			User userOfCredentials;
			userOfCredentials.fillWithVariant(userMap);
			UserAccount & account = configuration.getUserAccount();
			User confUser = account.getUser();
			bool rightUser = confUser.getID() == userOfCredentials.getID();
			verifyIssue = rightUser ? TOKENS_OK : WRONG_USER;
			if (rightUser) {
				account.setUser(userOfCredentials);
			}
			emit verifyTokensEnded(verifyIssue);
		}break;

		case 401:
			// Credentials were wrong
			verifyIssue = TOKENS_NOT_AUTHORIZED;
			break;

		case 420:
			// Rate limited
			verifyIssue = RATE_LIMITED;
			break;

		default:
			// Return == 5xx -> Twitter problem. Unknown problem otherwise.
			verifyIssue = (httpCode / 100 == 5) ?
						TWITTER_DOWN
					  : UNKNOWN_PROBLEM;
			break;
	}


	// Keeping on launching Reyn Tweets
	bool processOK;
	QString errorMsg = "";
	bool isFatal;

	switch (verifyIssue) {
		case TOKENS_OK:
			// Credentials were right. You can save configuration now.
			return saveConfiguration();

		case WRONG_USER:
			// User of the configuration and user of credentials do not match.
			// Getting tokens for the user of the configuration
			processOK = true;
			verifyIssue = AUTHENTICATION_REQUIRED;
			errorMsg = LaunchingProcess::trUtf8("The user was not the right one.");
			isFatal = false;
			emit authenticationRequired();
			break;

		case TOKENS_NOT_AUTHORIZED:
			// Credentials were wrong for the user.
			// Getting tokens for the user of the configuration.
			processOK = true;
			verifyIssue = AUTHENTICATION_REQUIRED;
			errorMsg = LaunchingProcess::trUtf8("Tokens for authentication to Twitter were wrong.");
			isFatal = false;
			emit authenticationRequired();
			break;

		case RATE_LIMITED:
			// Rate limited. Asking the user to try later.
			processOK = false;
			errorMsg = LaunchingProcess::trUtf8("You reach the authentication rate.");
			isFatal = false;
			break;

		case TWITTER_DOWN:
			// Twitter problem Asking the user to try later.
			processOK = false;
			errorMsg = LaunchingProcess::trUtf8("Twitter is down.");
			isFatal = false;
			break;

		case UNKNOWN_PROBLEM:
			// Unknown problem. Abort ?
			processOK = false;
			errorMsg = LaunchingProcess::trUtf8("Unknown prolem.");
			isFatal = true;
			break;

		default:
			// Unexpected result. Abort.
			processOK = false;
			errorMsg = LaunchingProcess::trUtf8("Unexpected result.");
			isFatal = true;
			break;
	}

	// Telling the component wat happens
	buildResult(processOK, verifyIssue, errorMsg, isFatal);
	endProcess();
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
			break;
	}

	// Failed end
	buildResult(processOK, authIssue, errorMsg, isFatal);
	emit processEnded();
}


////////////////////////////////////////////////////
// Step 3 : updating and saving the configuration //
////////////////////////////////////////////////////

// Saving the configuartion in the configuration file
void LaunchingProcess::saveConfiguration() {
	CoreResult saveIssue = configuration.save();
	bool processOK = false;
	QString errorMsg = "";
	bool isFatal = true;

	switch (saveIssue) {
		case SAVE_SUCCESSFUL:
			// The application was saved correctly.
			processOK = true;
			saveIssue = LAUNCH_SUCCESSFUL;
			isFatal = false;
			break;

		case CONFIGURATION_FILE_UNKNOWN:
			errorMsg = LaunchingProcess::trUtf8("Configuration file does not exist.");
			break;

		case CONFIGURATION_FILE_NOT_OPEN:
			errorMsg = LaunchingProcess::trUtf8("Configuration file cannot be opened.");
			break;

		default:
			saveIssue = UNKNOWN_PROBLEM;
			errorMsg = LaunchingProcess::trUtf8("Unknown problem");
			break;
	}

	// Ending the process
	buildResult(processOK, saveIssue, errorMsg, isFatal);
	endProcess();
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

