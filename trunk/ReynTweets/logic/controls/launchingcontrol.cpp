#include "launchingcontrol.hpp"
#include <QtDeclarative>

// Constructor
LaunchingControl::LaunchingControl() :
	QObject(),
	reyn(this),
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

	reyn.launchReynTweets();
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
	allowUnwiring();
	control = ctrl;
	allowWiring();
}

void LaunchingControl::allowWiring() {
	// Telling the user that its credentials are required
	connect(&reyn, SIGNAL(userCredentialsNeeded()),
			this, SLOT(credentialsNeeded()));

	// Authorizing (or denying) Reyn Tweets
	connect(&control, SIGNAL(authorize(QString,QString)),
			&reyn, SLOT(authorizeReynTweets(QString,QString)));
	connect(&control, SIGNAL(deny(QString,QString)),
			this, SLOT(denyReynTweets(QString,QString)));

	// When credentials given by the user are right or wrong
	connect(&reyn, SIGNAL(credentialsValid(bool)),
			this, SLOT(validCredentials(bool)));
}

void LaunchingControl::allowUnwiring() {
	// Telling the user that its credentials are required
	disconnect(&reyn, SIGNAL(userCredentialsNeeded()),
			   this, SLOT(credentialsNeeded()));

	// Authorizing (or denying) Reyn Tweets
	disconnect(&control, SIGNAL(authorize(QString,QString)),
			   &reyn, SLOT(authorizeReynTweets(QString,QString)));
	disconnect(&control, SIGNAL(deny(QString,QString)),
			   &reyn, SLOT(denyReynTweets(QString,QString)));

	// When credentials given by the user are right or wrong
	disconnect(&reyn, SIGNAL(credentialsValid(bool)),
			   this, SLOT(validCredentials(bool)));
}

//////////////////////////////
// Configuration management //
//////////////////////////////

// After loading configuration
void LaunchingControl::launchOK(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if ("Invalid asker" == result.errorMsg) {
		return;
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(launchOK(ProcessWrapper)));

	CoreResult issue = result.processIssue;

	switch (issue) {
		case LAUNCH_SUCCESSFUL:
			// Process successful
			emit launchEnded(true);
			break;

		case AUTHENTICATION_REQUIRED:
			// An authentication is needed. So let's do it!
			return allowReynTweets();

		// Problems that can be solved trying later
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
			emit launchEnded(false, result.errorMsg, false);
			break;

		// Problems with configuration file
		case CONFIGURATION_FILE_UNKNOWN:
		case CONFIGURATION_FILE_NOT_OPEN:
		case LOADING_CONFIGURATION_ERROR:

		// Unknown ends
		case UNKNOWN_PROBLEM:

		default:
			emit launchEnded(false, result.errorMsg, true);
			break;
	}
}

// After an authentication, if needed.
void LaunchingControl::allowOK(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if ("Invalid asker" == result.errorMsg) {
		return;
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(launchOK(ProcessWrapper)));

	CoreResult issue = result.processIssue;

	switch (issue) {
		case ALLOW_SUCCESSFUL:
			// Process successful
			emit launchEnded(true);
			break;

		case DENIED:	// Process successful but Reyn Tweets was denied :(

		// Problems that can be solved trying later
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
			emit launchEnded(false, result.errorMsg, false);
			break;

		// Problems during process
		case TOKENS_NOT_AUTHORIZED:
		case PARSE_ERROR:
		case POST_AUTHORIZING_FAILED:
		case NO_TOKENS:

		// Problems with configuration file
		case CONFIGURATION_FILE_UNKNOWN:
		case CONFIGURATION_FILE_NOT_OPEN:

		// Unknown ends
		case UNKNOWN_PROBLEM:

		default:
			emit launchEnded(false, result.errorMsg, true);
			break;
	}
}

void LaunchingControl::validCredentials(bool valid) {
	if (valid) {
		// Hiding the login popup
		emit showLoginPopup(false);
	} else {
		// Informing the user that the credentials are wrong
		control.wrongCredentials();
	}
}

void LaunchingControl::credentialsNeeded() {
	// Displaying the popup to enter credentials
	emit showLoginPopup(true);
}
