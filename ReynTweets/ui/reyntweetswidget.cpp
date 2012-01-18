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
			this, SLOT(launchOK(LaunchResult)));
	connect(&reyn, SIGNAL(saveConfEnded(SaveConfResult)),
			this, SLOT(saveOK(SaveConfResult)));
	connect(&authenticationWidget, SIGNAL(authenticationFinished(OAuthProcessResult,
																 QByteArray,QByteArray,
																 long,QString)),
			this, SLOT(endOAuthAuthenticationFlow(OAuthProcessResult,
												  QByteArray,QByteArray,
												  long,QString))
			);

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
	disconnect(&authenticationWidget, SIGNAL(authenticationFinished(OAuthProcessResult,
																	QByteArray,QByteArray,
																	long,QString)),
			   this, SLOT(endOAuthAuthenticationFlow(OAuthProcessResult,
													 QByteArray,QByteArray,
													 long,QString))
			   );
}

// Displaying a QMessageBox announcing a critical problem
void ReynTweetsWidget::criticalPopup(QString title,
									 QString announce,
									 QString problem)
{
	// Building the message displayed in the popup
	QString displayedMessage = announce;

	displayedMessage.append('\n');
	displayedMessage.append(problem);
	displayedMessage.append('\n');
	displayedMessage.append(ReynTweetsWidget::trUtf8("Reyn Tweets will quit."));

	// Displaying the error
	QMessageBox::critical(this,
						  title,
						  displayedMessage);
	qApp->quit();
}

// Displaying a QMessageBox for asking a question
QMessageBox::StandardButton ReynTweetsWidget::questionPopup(QString title,
															QString announce,
															QString question)
{
	// Building the message displayed in the popup
	QString displayedMessage = announce;
	displayedMessage.append('\n');
	displayedMessage.append(question);

	// Displaying the error
	return QMessageBox::question(this,
								 title,
								 displayedMessage,
								 QMessageBox::Yes | QMessageBox::No);
}


///////////////////////////////
// Authentication management //
///////////////////////////////

// An authentication to Twitter is required for the application
void ReynTweetsWidget::authenticationRequired() {
	authenticationWidget.allowReynTweets();
}


// End of authentication
void ReynTweetsWidget::endOAuthAuthenticationFlow(OAuthProcessResult processResult,
												  QByteArray accessToken,
												  QByteArray tokenSecret,
												  long userID,
												  QString screenName)
{
	QMessageBox::StandardButton questionButton;
	QString welcomeMessage;

	switch (processResult) {
		case AUTHORIZED:
			// Reyn Tweets is authorized. Welcome the user and upload the account with him.
			welcomeMessage = "@";
			welcomeMessage.append(screenName);
			welcomeMessage.append(ReynTweetsWidget::trUtf8(" can go to Twitter with Reyn Tweets now. Have fun with Reyn Tweets!"));

			QMessageBox::information(this,
									 ReynTweetsWidget::trUtf8("Welcome to Reyn Tweets"),
									 welcomeMessage);
			reyn.updateConfAfterAuth(accessToken, tokenSecret,
									 userID, screenName);
			return;

		case DENIED:
			// Reyn Tweets was not authorized.
			questionButton = questionPopup(ReynTweetsWidget::trUtf8("End of the authentication process"),
										   ReynTweetsWidget::trUtf8("Reyn Tweets was not authorized. You will not be able to use the application correctly."),
										   ReynTweetsWidget::trUtf8("Would you like to authorize the application again ?"));

			if (QMessageBox::Yes == questionButton) {
				authenticationWidget.allowReynTweets();
			}
			return;

		case ERROR_PROCESS:
			// Want to restart ?
			questionButton = questionPopup(ReynTweetsWidget::trUtf8("Error during the authentication process"),
										   ReynTweetsWidget::trUtf8("An error occured during the authentication process."),
										   ReynTweetsWidget::trUtf8("Would you like to try to authorize the application again ?"));

			if (QMessageBox::Yes == questionButton) {
				authenticationWidget.allowReynTweets();
			}
			return;

		default:
			// Unknown problem. Abort.
			return criticalPopup(ReynTweetsWidget::trUtf8("Error while authorizing the application"),
								 ReynTweetsWidget::trUtf8("A problem occured during authentication:"),
								 ReynTweetsWidget::trUtf8("Unknown problem"));
	}

	// Asking what to do
}


//////////////////////////////
// Configuration management //
//////////////////////////////

// End of launch process
void ReynTweetsWidget::launchOK(LaunchResult launchOK) {
	QString errorMsg = "";

	switch (launchOK) {
		case LAUNCH_SUCCESSFUL:
			// The application was launched correctly. You can tweet now.
			reyn.checkTokens();

			// Removing the launching screen
			launchingScreen.hide();
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

	criticalPopup(ReynTweetsWidget::trUtf8("Error while launching the application"),
				  ReynTweetsWidget::trUtf8("A problem occured while launching the application:"),
				  errorMsg);
}

// After saving the configuration
void ReynTweetsWidget::saveOK(SaveConfResult saveOK) {
	QString errorMsg = "";

	switch (saveOK) {
		case SAVE_SUCCESSFUL:
			// The application was saved correctly
			return;

		case CONFIGURATION_BACKUP_FILE_UNKNOWN:
			errorMsg = ReynTweetsWidget::trUtf8("Configuration file does not exist.");
			break;

		case CONFIGURATION_BACKUP_FILE_NOT_OPEN:
			errorMsg = ReynTweetsWidget::trUtf8("Configuration file cannot be opened.");
			break;

		default:
			errorMsg = ReynTweetsWidget::trUtf8("Unknown problem");
			break;
	}

	criticalPopup(ReynTweetsWidget::trUtf8("Error while saving the parameters"),
				  ReynTweetsWidget::trUtf8("A problem occured while saving the parameters of Reyn Tweets:"),
				  errorMsg);
}
