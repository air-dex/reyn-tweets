/// @file launchingcontrol.cpp
/// @brief Implementation of LaunchingControl
///
/// Revisions of the file older than r204 are in /trunk/ReynTweets/controls
/// r204 is in /trunk/ReynTweets/logic
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
///
/// This file is part of Reyn Tweets.
///
/// Reyn Tweets is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Lesser General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// Reyn Tweets is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU Lesser General Public License for more details.
///
/// You should have received a copy of the GNU Lesser General Public License
/// along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.

#include "launchingcontrol.hpp"
#include <QtDeclarative>

// Constructor
LaunchingControl::LaunchingControl() :
	QObject(),
	reyn(this),
	control(0)
{
	allowWiring();
}

// Declaring to the QML components
void LaunchingControl::declareQML() {
	qmlRegisterType<LaunchingControl>("ReynTweetsControls",
									  0, 1,
									  "LaunchingControl");
}


/////////////////////////
// Property management //
/////////////////////////

LoginControl * LaunchingControl::getLoginControl() {
	return control;
}

void LaunchingControl::setLoginControl(LoginControl * ctrl) {
	control = ctrl;
}


//////////////////////////////
// Execution of the process //
//////////////////////////////

/////////////////////////////////////////////////////////
// Step 1 : starting ReynTweets by a launching process //
/////////////////////////////////////////////////////////

void LaunchingControl::launchReynTweets() {
	// Connection for the end of the launch process
	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(launchOK(ProcessWrapper)));

	reyn.launchReynTweets();
}

// After launching
void LaunchingControl::launchOK(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return;
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(launchOK(ProcessWrapper)));

	CoreResult issue = result.processIssue;

	switch (issue) {
		case LAUNCH_SUCCESSFUL:
			// Process successful
			emit launchEnded(true, QString(), false);
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

///////////////////////////////////////////////////
// Step 2 : authenticating Reyn Tweets if needed //
///////////////////////////////////////////////////

// Allowing Reyn Tweets to use a Twitter Account
void LaunchingControl::allowReynTweets() {
	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(allowOK(ProcessWrapper)));

	allowWiring();
	reyn.allowReynTweets();
}

// After an authentication, if needed.
void LaunchingControl::allowOK(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return;
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(allowOK(ProcessWrapper)));

	allowUnwiring();

	QString displayMessage = result.errorMsg;
	CoreResult issue = result.processIssue;

	switch (issue) {
		case ALLOW_SUCCESSFUL:
			// Process successful
			emit launchEnded(true, QString(), false);
			break;

		case DENIED:
			// Process successful but Reyn Tweets was denied :(
			displayMessage = LaunchingControl::trUtf8("Reyn Tweets was denied.");

		// Problems that can be solved trying later
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
			emit launchEnded(false, displayMessage, false);
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
			emit launchEnded(false, displayMessage, false);
			break;
	}
}


///////////////////////////////
// Wiring for authentication //
///////////////////////////////

// Wiring
void LaunchingControl::allowWiring() {
	if (!control) {
		return;
	}

	// Telling the user that its credentials are required
	connect(&reyn, SIGNAL(userCredentialsNeeded()),
			this, SLOT(credentialsNeeded()));

	// Authorizing (or denying) Reyn Tweets
	connect(control, SIGNAL(authorize(QString,QString)),
			&reyn, SLOT(authorizeReynTweets(QString,QString)));
	connect(control, SIGNAL(deny(QString,QString)),
			&reyn, SLOT(denyReynTweets(QString,QString)));

	// When credentials given by the user are right or wrong
	connect(&reyn, SIGNAL(credentialsValid(bool)),
			this, SLOT(validCredentials(bool)));
}

// Unwiring
void LaunchingControl::allowUnwiring() {
	if (!control) {
		return;
	}

	// Telling the user that its credentials are required
	disconnect(&reyn, SIGNAL(userCredentialsNeeded()),
			   this, SLOT(credentialsNeeded()));

	// Authorizing (or denying) Reyn Tweets
	disconnect(control, SIGNAL(authorize(QString,QString)),
			   &reyn, SLOT(authorizeReynTweets(QString,QString)));
	disconnect(control, SIGNAL(deny(QString,QString)),
			   &reyn, SLOT(denyReynTweets(QString,QString)));

	// When credentials given by the user are right or wrong
	disconnect(&reyn, SIGNAL(credentialsValid(bool)),
			   this, SLOT(validCredentials(bool)));
}


////////////////////////////////////////
// Slots to communicate with the View //
////////////////////////////////////////

// Credentials OK ?
void LaunchingControl::validCredentials(bool valid) {
	if (valid) {
		// Hiding the login popup
		emit showLoginPopup(false);
	} else {
		// Informing the user that the credentials are wrong
		control->wrongCredentials();
	}
}

// Reyn needs credentials
void LaunchingControl::credentialsNeeded() {
	// Displaying the popup to enter credentials
	emit showLoginPopup(true);
}
