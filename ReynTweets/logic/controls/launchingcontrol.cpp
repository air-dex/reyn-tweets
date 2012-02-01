#include "launchingcontrol.hpp"
#include <QtDeclarative>

// Constructor
LaunchingControl::LaunchingControl() :
	QObject(),
	reyn(),
	control()
{
	allowWiring();
}

// Declaring to the QML components
void LaunchingControl::declareQML() {
	qmlRegisterType<LaunchingControl>("ReynTweetsControls",
									  0, 1,
									  "LaunchingControl");
}

// Starting ReynTweets
void LaunchingControl::launchReynTweets() {
	// Connection for the end of the launch process
	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(launchOK(ProcessWrapper)));

	reyn.loadConfiguration();
}

// Allowing Reyn Tweets to use a Twitter Account
void LaunchingControl::allowReynTweets() {
	allowWiring();
	reyn.allowReynTweets();
}


LoginControl LaunchingControl::getLoginControl() {
	return control;
}

void LaunchingControl::setLoginControl(LoginControl ctrl) {
	unwiring();
	control = ctrl;
	allowWiring();
}

void LaunchingControl::allowWiring() {
	// Telling the user that its credentials are required
	connect(&reyn, SIGNAL(userCredentialsNeeded()),
			&control, SLOT(credentialsNeeded()));

	// Authorizing (or denying) Reyn Tweets
	connect(&control, SIGNAL(authorize(QString,QString)),
			&reyn, SLOT(authorizeReynTweets(QString,QString)));
	connect(&control, SIGNAL(deny(QString,QString)),
			&reyn, SLOT(denyReynTweets(QString,QString)));

	// When credentials given by the user are right or wrong
	connect(&reyn, SIGNAL(credentialsValid(bool)),
			&control, SLOT(validCredentials(bool)));
}

void LaunchingControl::unwiring() {
	// Telling the user that its credentials are required
	disconnect(&reyn, SIGNAL(userCredentialsNeeded()),
			   &control, SLOT(credentialsNeeded()));

	// Authorizing (or denying) Reyn Tweets
	disconnect(&control, SIGNAL(authorize(QString,QString)),
			   &reyn, SLOT(authorizeReynTweets(QString,QString)));
	disconnect(&control, SIGNAL(deny(QString,QString)),
			   &reyn, SLOT(denyReynTweets(QString,QString)));

	// When credentials given by the user are right or wrong
	disconnect(&reyn, SIGNAL(credentialsValid(bool)),
			   &control, SLOT(validCredentials(bool)));
}

//////////////////////////////
// Configuration management //
//////////////////////////////

// After loading configuration
void LaunchingControl::launchOK(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (WRONG_PROCESS_RESULT == result) {
		return;
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(launchOK(ProcessWrapper)));

	CoreResult issue = result.processIssue;

	switch (issue) {
		case LAUNCH_SUCCESSFUL:
			// Process successful
			break;

		// Problems that can be solved trying later
		case RATE_LIMITED:
			// The user reached rates.
			break;

		case TWITTER_DOWN:
			// Twitter does not respond.
			break;

		// An authentication is needed
		case TOKENS_NOT_AUTHORIZED:
			break;

		case WRONG_USER:
			// Expected user for the tokens is not in the configuration
			break;

		// Problems with configuration file
		case CONFIGURATION_FILE_UNKNOWN:
			break;

		case CONFIGURATION_FILE_NOT_OPEN:
			break;

		case LOADING_CONFIGURATION_ERROR:
			break;

		// Unknown ends
		case UNKNOWN_PROBLEM:
			break;

		default:
			break;
	}
}

// After an authentication, if needed.
void LaunchingControl::allowOK(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (WRONG_PROCESS_RESULT == result) {
		return;
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(launchOK(ProcessWrapper)));

	CoreResult issue = result.processIssue;

	switch (issue) {
		case LAUNCH_SUCCESSFUL:
			// Process successful
			break;

		// Problems that can be solved trying later
		case RATE_LIMITED:
			// The user reached rates.
			break;

		case TWITTER_DOWN:
			// Twitter does not respond.
			break;

		// An authentication is needed
		case TOKENS_NOT_AUTHORIZED:
			break;

		case WRONG_USER:
			// Expected user for the tokens is not in the configuration
			break;

		// Problems with configuration file
		case CONFIGURATION_FILE_UNKNOWN:
			break;

		case CONFIGURATION_FILE_NOT_OPEN:
			break;

		case LOADING_CONFIGURATION_ERROR:
			break;

		// Unknown ends
		case UNKNOWN_PROBLEM:
			break;

		default:
			break;
	}
}
