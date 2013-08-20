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
#include <QtQml>

// Constructor
LaunchingControl::LaunchingControl() :
	GenericControl()
{}

// Declaring to the QML components
void LaunchingControl::declareQML() {
	// @uri ReynTweetsComponents
	qmlRegisterType<LaunchingControl>(ReynTweets::QML_LIBRARY_NAME.toLatin1().constData(),
									  ReynTweets::MAJOR_VERSION, ReynTweets::MINOR_VERSION,
									  "LaunchingControl");
}

////////////////////////////////////////////////
// Starting ReynTweets by a launching process //
////////////////////////////////////////////////

void LaunchingControl::launchReynTweets() {
	if (processing) {
		return;
	}

	// Connection for the end of the launch process
	connect(&reyn, &ReynCore::sendResult,
			this, &LaunchingControl::launchOK);

	// Message not necessary
	processing = true;
	reyn.launchReynTweets();
}

// After launching
void LaunchingControl::launchOK(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (ReynTweets::INVALID_END == result.processEnd) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, &ReynCore::sendResult,
			   this, &LaunchingControl::launchOK);

	switch (result.processEnd) {
		case ReynTweets::LAUNCH_SUCCESSFUL:
			// Process successful
			emit actionEnded(true,
							 LaunchingControl::trUtf8("Reyn Tweets launched."),
							 false);
			break;

		case ReynTweets::AUTHENTICATION_REQUIRED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;

		// Problems that can be solved trying later
		case ReynTweets::NO_MORE_DATA:
		case ReynTweets::BAD_REQUEST:
		case ReynTweets::REFUSED_REQUEST:
		case ReynTweets::REINIT_SUCCESSFUL:
		case ReynTweets::RATE_LIMITED:	// The user reached rates.
		case ReynTweets::TWITTER_DOWN:	// Twitter does not respond.
		case ReynTweets::NETWORK_CALL:
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Problems with configuration file
		case ReynTweets::CONFIGURATION_FILE_UNKNOWN:
		case ReynTweets::CONFIGURATION_FILE_NOT_OPEN:
		case ReynTweets::LOADING_CONFIGURATION_ERROR:
		case ReynTweets::EXPECTED_KEY:

		// Unknown ends
		case ReynTweets::UNKNOWN_PROBLEM:

		default:
			emit actionEnded(false, result.errorMsg, true);
			break;
	}
}
