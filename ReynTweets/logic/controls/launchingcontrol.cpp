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
	reyn(this)
{}

// Declaring to the QML components
void LaunchingControl::declareQML() {
	qmlRegisterType<LaunchingControl>("ReynTweetsControls",
									  0, 1,
									  "LaunchingControl");
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
            emit launchEnded(true,
                             LaunchingControl::trUtf8("Reyn Tweets launched"),
                             false);
			break;

		case AUTHENTICATION_REQUIRED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;

		// Problems that can be solved trying later
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
		case NETWORK_CALL:
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
