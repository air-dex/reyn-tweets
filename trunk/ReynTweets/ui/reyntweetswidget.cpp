/// @file reyntweetswidget.cpp
/// @brief Implementation of ReynTweetsWidget
/// @author Romain Ducher

/*
Copyright 2011 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QApplication>
#include <QMessageBox>
#include "reyntweetswidget.hpp"

// Constructor
ReynTweetsWidget::ReynTweetsWidget() :
	QWidget(),
	reyn(),
	layout(),
	authenticationWidget(),
	launchingScreen(authenticationWidget),
	mock("Yeah ! It's Reyn time !")
{
	// UI design
	layout.addWidget(&launchingScreen);
	setLayout(&layout);

	// Wiring
	connect(&reyn, SIGNAL(authenticationRequired()),
			this, SLOT(authenticationRequired()));
	connect(&reyn, SIGNAL(launchEnded(LaunchResult)),
			this, SLOT(launchEnded(LaunchResult)));
	connect(&reyn, SIGNAL(saveConfEnded(SaveConfResult)),
			this, SLOT(saveOK(SaveConfResult)));

	// Loading configuration
	reyn.loadConfiguration();
}

// Destructor
ReynTweetsWidget::~ReynTweetsWidget() {
	// Unwiring
	disconnect(&reyn, SIGNAL(authenticationRequired()),
			   this, SLOT(authenticationRequired()));
	disconnect(&reyn, SIGNAL(launchEnded(LaunchResult)),
			   this, SLOT(launchEnded(LaunchResult)));
	disconnect(&reyn, SIGNAL(saveConfEnded(SaveConfResult)),
			   this, SLOT(saveOK(SaveConfResult)));
}


///////////////////////////////
// Authentication management //
///////////////////////////////

// An authentication to Twitter is required for the application
void ReynTweetsWidget::authenticationRequired() {
	authenticationWidget.allowReynTweets();
}

// End of launch process
void ReynTweetsWidget::launchOK(LaunchResult launchOK) {
	QString errorMsg = "";

	switch (launchOK) {
		case LAUNCH_SUCCESSFUL:
			// The application was launched correctly. You can tweet now.

			// Removing the launching screen
			layout.removeWidget(&launchingScreen);

			// Inserting the panel to tweet (mocked for the moment)
			layout.addWidget(&mock);
			return;

		case CONFIGURATION_FILE_UNKNOWN:
			errorMsg = ReynTweetsWidget::trUtf8("Configuration file does not exist.");
			break;

		case CONFIGURATION_FILE_NOT_OPEN:
			errorMsg = ReynTweetsWidget::trUtf8("Configuration file cannot be opened.");
			break;

		case LOADING_CONFIGURATION_ERROR:
			errorMsg = ReynTweetsWidget::trUtf8("Configuration cannot be loaded.");
			break;

		default:
			errorMsg = ReynTweetsWidget::trUtf8("Unknown problem");
			break;
	}

	QString displayedMessage = ReynTweetsWidget::trUtf8("A problem occured while launching the application:");

	displayedMessage.append('\n');
	displayedMessage.append(errorMsg);
	displayedMessage.append('\n');
	displayedMessage.append(ReynTweetsWidget::trUtf8("Reyn Tweets will quit."));

	// Error while launching the app. Abort
	QMessageBox::critical(this,
						  ReynTweetsWidget::trUtf8("Error while launching the application"),
						  displayedMessage);
	qApp->quit();
}

// After saving the configuration
void ReynTweetsWidget::saveOK(SaveConfResult saveOK) {
	QString errorMsg = "";

	switch (saveOK) {
		case SAVE_SUCCESSFUL:
			// The application was saved correctly
			return;

		case CONFIGURATION_FILE_UNKNOWN:
			errorMsg = ReynTweetsWidget::trUtf8("Configuration file does not exist.");
			break;

		case CONFIGURATION_FILE_NOT_OPEN:
			errorMsg = ReynTweetsWidget::trUtf8("Configuration file cannot be opened.");
			break;

		default:
			errorMsg = ReynTweetsWidget::trUtf8("Unknown problem");
			break;
	}

	QString displayedMessage = ReynTweetsWidget::trUtf8("A problem occured while saving the application:");

	displayedMessage.append('\n');
	displayedMessage.append(errorMsg);
	displayedMessage.append('\n');
	displayedMessage.append(ReynTweetsWidget::trUtf8("Reyn Tweets will quit."));

	// Error while saving the app. Abort
	QMessageBox::critical(this,
						  ReynTweetsWidget::trUtf8("Error while saving the application"),
						  displayedMessage);
	qApp->quit();
}
