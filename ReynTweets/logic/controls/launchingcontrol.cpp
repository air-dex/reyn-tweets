#include "launchingcontrol.hpp"
#include <QtDeclarative>

// Constructor
LaunchingControl::LaunchingControl() :
	QObject(),
	reyn()
{
	// Wiring with the core

	// Loading configuration
	connect(&reyn, SIGNAL(loadConfigurationEnded(CoreResult)),
			this, SLOT(loadOK(CoreResult)));

	// Verifying tokens
	connect(&reyn, SIGNAL(verifyTokensEnded(CoreResult)),
			this, SLOT(verifyTokensEnded(CoreResult)));

	// Saving configuration
	connect(&reyn, SIGNAL(saveConfEnded(CoreResult)),
			this, SLOT(saveOK(CoreResult)));
}

// Declaring to the QML components
void LaunchingControl::declareQML() {
	qmlRegisterType<LaunchingControl>("ReynTweetsControls",
									  0, 1,
									  "LaunchingControl");
}

// Starting ReynTweets
void LaunchingControl::launchReynTweets() {
	reyn.loadConfiguration();
}


//////////////////////////////
// Configuration management //
//////////////////////////////

// After loading configuration
void LaunchingControl::loadOK(CoreResult launchOK) {
	QString errorMsg = "";

	switch (launchOK) {
		case LOAD_CONFIGURATION_SUCCESSFUL:
			// The configuration was loaded correctly. Let's check the credentials
			reyn.checkTokens();
			return;

		case CONFIGURATION_FILE_UNKNOWN:
			errorMsg = LaunchingControl::trUtf8("Configuration file does not exist.");
			break;

		case CONFIGURATION_FILE_NOT_OPEN:
			errorMsg = LaunchingControl::trUtf8("Configuration file cannot be opened.");
			break;

		case LOADING_CONFIGURATION_ERROR:
			errorMsg = LaunchingControl::trUtf8("Configuration cannot be loaded.");
			break;

		default:
			// Unknown problem.
			errorMsg = LaunchingControl::trUtf8("Unknown problem");
			break;
	}

	// Telling the component that the launching process has ended fatally.
	emit launchEnded(false, errorMsg, true);
}


// After verifying credentials
void LaunchingControl::verifyTokensEnded(CoreResult verifyOK) {
	QString errorMsg = "";
	bool isFatal = false;

	switch (verifyOK) {
		case TOKENS_OK:
			// Credentials were right.
			reyn.saveConfiguration();
			return;

		case WRONG_USER:
			// User of the configuration and user of credentials do not match.
			// Getting tokens for the user of the configuration
			errorMsg = LaunchingControl::trUtf8("The user was not the right one.");
			break;

		case TOKENS_NOT_AUTHORIZED:
			// Credentials were wrong for the user.
			// Getting tokens for the user of the configuration.
			errorMsg = LaunchingControl::trUtf8("Tokens for authentication to Twitter were wrong.");
			break;

		case RATE_LIMITED:
			// Rate limited. Asking the user to try later.
			errorMsg = LaunchingControl::trUtf8("You reach the authentication rate.");
			break;

		case TWITTER_DOWN:
			// Twitter problem Asking the user to try later.
			errorMsg = LaunchingControl::trUtf8("Twitter is down.");
			break;

		case UNKNOWN_PROBLEM:
			// Unknown problem. Abort ?
			errorMsg = LaunchingControl::trUtf8("Unknown prolem");
			isFatal = true;
			break;

		default:
			// Unexpected result. Abort.
			errorMsg = LaunchingControl::trUtf8("Unexpected result");
			isFatal = true;
			break;
	}

	// Telling the component wat happens
	emit launchEnded(false, errorMsg, isFatal);
}

// After saving the configuration
void LaunchingControl::saveOK(CoreResult saveOK) {
	QString errorMsg = "";

	switch (saveOK) {
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



/*
///////////////////////////////
// Authentication management //
///////////////////////////////

// An authentication to Twitter is required for the application
void LaunchingControl::authenticationRequired() {
	authenticationWidget.allowReynTweets();
}


// End of authentication
void LaunchingControl::endOAuthAuthenticationFlow(OAuthProcessResult processResult,
												  QByteArray accessToken,
												  QByteArray tokenSecret,
												  qlonglong userID,
												  QString screenName)
{
	QMessageBox::StandardButton questionButton;
	QString welcomeMessage;

	switch (processResult) {
		case AUTHORIZED:
			// Reyn Tweets is authorized. Welcome the user and upload the account with him.
			welcomeMessage = "@";
			welcomeMessage.append(screenName);
			welcomeMessage.append(LaunchingControl::trUtf8(" can go to Twitter with Reyn Tweets now. Have fun with Reyn Tweets!"));

			QMessageBox::information(this,
									 LaunchingControl::trUtf8("Welcome to Reyn Tweets"),
									 welcomeMessage);
			reyn.updateConfAfterAuth(accessToken, tokenSecret,
									 userID, screenName);
			return;

		case DENIED:
			// Reyn Tweets was not authorized.
			questionButton = questionPopup(LaunchingControl::trUtf8("End of the authentication process"),
										   LaunchingControl::trUtf8("Reyn Tweets was not authorized. You will not be able to use the application correctly."),
										   LaunchingControl::trUtf8("Would you like to authorize the application again ?"));

			if (QMessageBox::Yes == questionButton) {
				authenticationWidget.allowReynTweets();
			}
			return;

		case ERROR_PROCESS:
			// Want to restart ?
			questionButton = questionPopup(LaunchingControl::trUtf8("Error during the authentication process"),
										   LaunchingControl::trUtf8("An error occured during the authentication process."),
										   LaunchingControl::trUtf8("Would you like to try to authorize the application again ?"));

			if (QMessageBox::Yes == questionButton) {
				authenticationWidget.allowReynTweets();
			}
			return;

		default:
			// Unknown problem. Abort.
			return criticalPopup(LaunchingControl::trUtf8("Error while authorizing the application"),
								 LaunchingControl::trUtf8("A problem occured during authentication:"),
								 LaunchingControl::trUtf8("Unknown problem"));
	}

	// Asking what to do
}
//*/
/*
// After saving the configuration
void LaunchingControl::saveOK(SaveConfResult saveOK) {
	QString errorMsg = "";

	switch (saveOK) {
		case SAVE_SUCCESSFUL:
			// The application was saved correctly
			return;

		case CONFIGURATION_BACKUP_FILE_UNKNOWN:
			errorMsg = LaunchingControl::trUtf8("Configuration file does not exist.");
			break;

		case CONFIGURATION_BACKUP_FILE_NOT_OPEN:
			errorMsg = LaunchingControl::trUtf8("Configuration file cannot be opened.");
			break;

		default:
			errorMsg = LaunchingControl::trUtf8("Unknown problem");
			break;
	}

	criticalPopup(LaunchingControl::trUtf8("Error while saving the parameters"),
				  LaunchingControl::trUtf8("A problem occured while saving the parameters of Reyn Tweets:"),
				  errorMsg);
}
//*/
