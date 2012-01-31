#include "launchingcontrol.hpp"
#include <QtDeclarative>

// Constructor
LaunchingControl::LaunchingControl() :
	QObject(),
	reyn(),
	control()
{
	wiring();
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

LoginControl LaunchingControl::getLoginControl() {
	return control;
}

void LaunchingControl::setLoginControl(LoginControl ctrl) {
	unwiring();
	control = ctrl;
	wiring();
}

void LaunchingControl::wiring() {
	// Connection for the end of the launch process
	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(launchOK(ProcessWrapper)));

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
	// Connection for the end of the launch process
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(launchOK(ProcessWrapper)));

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

	CoreResult issue = result.processIssue;

	switch (issue) {
		case PROCESS_OK:
			// Process successful
			break;

		// Problems that can be solved trying later
		case RATE_LIMITED:
			// The user reached rates.
			break;

		case TWITTER_DOWN:
			// Twitter does not respond.
			break;

		// Problems with configuration file
		case CONFIGURATION_FILE_UNKNOWN:
			break;

		case CONFIGURATION_FILE_NOT_OPEN:
			break;

		case PARSE_ERROR:
			// Error while parsing Twitter results
			break;

		case DENIED:
			break;

		case TOKENS_NOT_AUTHORIZED:
			break;

		case LOADING_CONFIGURATION_ERROR:
			break;

		case NO_TOKENS:
			break;

		case UNKNOWN_PROBLEM:
			break;

		default:
			break;
	}
}
