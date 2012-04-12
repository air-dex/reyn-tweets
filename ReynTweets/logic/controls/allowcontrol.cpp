/// @file allowcontrol.cpp
/// @brief Implementation of AllowControl
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

#include "allowcontrol.hpp"
#include <QtDeclarative>

// Constructor
AllowControl::AllowControl() :
	QObject(),
	reyn(this),
	control()
{}

// Declaring to the QML components
void AllowControl::declareQML() {
	qmlRegisterType<AllowControl>("ReynTweetsControls",
								  0, 1,
								  "AllowControl");
}


/////////////////////////
// Property management //
/////////////////////////

LoginControl * AllowControl::getLoginControl() {
	return &control;
}

void AllowControl::setLoginControl(LoginControl * ctrl) {
	control = (ctrl == 0) ? LoginControl() : *ctrl;
}



//////////////////////////////
// Execution of the process //
//////////////////////////////

// Allowing Reyn Tweets to use a Twitter Account
void AllowControl::allowReynTweets() {
	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(allowOK(ProcessWrapper)));

	allowWiring();
	reyn.allowReynTweets();
}

// After an authentication, if needed.
void AllowControl::allowOK(ProcessWrapper res) {
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
			emit allowEnded(true, QString(), false);
			break;

		case DENIED:
			// Process successful but Reyn Tweets was denied :(
			displayMessage = AllowControl::trUtf8("Reyn Tweets was denied.");

		// Problems that can be solved trying later
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
			emit allowEnded(false, displayMessage, false);
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
			emit allowEnded(false, displayMessage, false);
			break;
	}
}


///////////////////////////////
// Wiring for authentication //
///////////////////////////////

// Wiring
void AllowControl::allowWiring() {
	// Telling the user that its credentials are required
	connect(&reyn, SIGNAL(userCredentialsNeeded()),
			this, SLOT(credentialsNeeded()));

	// Authorizing (or denying) Reyn Tweets
	connect(&control, SIGNAL(authorize(QString,QString)),
			&reyn, SLOT(authorizeReynTweets(QString,QString)));
	connect(&control, SIGNAL(deny(QString,QString)),
			&reyn, SLOT(denyReynTweets(QString,QString)));

	// When credentials given by the user are right or wrong
	connect(&reyn, SIGNAL(credentialsValid(bool)),
			this, SLOT(validCredentials(bool)));
}

// Unwiring
void AllowControl::allowUnwiring() {
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


////////////////////////////////////////
// Slots to communicate with the View //
////////////////////////////////////////

// Credentials OK ?
void AllowControl::validCredentials(bool valid) {
	if (valid) {
		// Hiding the login popup
		emit showLoginPopup(false);
	} else {
		// Informing the user that the credentials are wrong
		control.wrongCredentials();
	}
}

// Reyn needs credentials
void AllowControl::credentialsNeeded() {
	// Displaying the popup to enter credentials
	emit showLoginPopup(true);
}
