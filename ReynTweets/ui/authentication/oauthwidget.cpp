/// @file oauthwidget.cpp
/// @brief Implementation of OAuthWidget
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

#include <QMessageBox>
#include "oauthwidget.hpp"

// Constructor
OAuthWidget::OAuthWidget(QWidget *parent) :
	QWidget(parent),
	authenticationFlow(0),
	loginWidget()
{
	loginWidget.setVisible(false);

	// Wiring

	// Between the login panel and the launching slots
	connect(&loginWidget, SIGNAL(authorize()),
			this, SLOT(launchAuthorize()));
	connect(&loginWidget, SIGNAL(deny()),
			this, SLOT(launchDeny()));

	// Showing or hiding the error message for credentials
	connect(this, SIGNAL(credentialsOK(bool)),
			&loginWidget, SLOT(showCredentialsErrorMessage(bool)));
}

// Destructor
OAuthWidget::~OAuthWidget() {
	if (authenticationFlow) {
		killOAuthProcess();
	}

	// Unwiring

	// Launching slots
	disconnect(&loginWidget, SIGNAL(authorize()),
			   this, SLOT(launchAuthorize()));
	disconnect(&loginWidget, SIGNAL(deny()),
			   this, SLOT(launchDeny()));

	// Error message for credentials
	disconnect(this, SIGNAL(credentialsOK(bool)),
			   &loginWidget, SLOT(showCredentialsErrorMessage(bool)));
}


//////////////////////////
// Visual notifications //
//////////////////////////

// Slot executing to show (or to hide) the login panel
void OAuthWidget::loginPanelVisible(bool visible) {
	loginWidget.setVisible(visible);
}

// Showing or hidding an error message about the validity of credentials.
void OAuthWidget::rightCredentials(bool ok) {
	emit credentialsOK(ok);
}


///////////////////
// OAuth process //
///////////////////

// Allowing Reyn Tweets to use your Twitter account
void OAuthWidget::allowReynTweets() {
	authenticationFlow = new OAuthProcess();

	if (authenticationFlow) {
		// Wiring connection beetween the widget and the process

		// Visual changes
		connect(authenticationFlow, SIGNAL(loginPanelVisible(bool)),
				this, SLOT(loginPanelVisible(bool)));
		connect(authenticationFlow, SIGNAL(credentialsOK(bool)),
				this, SLOT(rightCredentials(bool)));

		// Process notifications
		connect(this, SIGNAL(authorizeReynTweets(QString,QString)),
				authenticationFlow, SLOT(authorizeReynTweets(QString,QString)));
		connect(this, SIGNAL(denyReynTweets(QString,QString)),
				authenticationFlow, SLOT(denyReynTweets(QString,QString)));
		connect(authenticationFlow, SIGNAL(authenticationProcessFinished(OAuthProcessResult,
																		 QByteArray,QByteArray,
																		 long,QString)),
				this, SLOT(endAuthentication(OAuthProcessResult,
											 QByteArray,QByteArray,
											 long,QString))
				);
		connect(authenticationFlow, SIGNAL(errorProcess(bool,QString)),
				this, SLOT(errorProcess(bool,QString)));

		authenticationFlow->startAuthentication();
	} else {
		// Critical error -> Abort the process.
		QMessageBox::critical(this,
							  OAuthWidget::trUtf8("Error during the authentication process"),
							  OAuthWidget::trUtf8("Error while launching the authentication process. Authentication ended."));
		emit authenticationFinished(ERROR_PROCESS);
	}
}

// Signal emitted when an error occurs during the process
void OAuthWidget::errorProcess(bool fatalError, QString errorMsg) {
	QString message = errorMsg;

	if (fatalError) {
		// Critical error -> Abort the process.
		message.append(OAuthWidget::trUtf8("\nEnd of the authentication process."));

		QMessageBox::critical(this,
							  OAuthWidget::trUtf8("Error during the authentication process"),
							  OAuthWidget::trUtf8(message.toUtf8().data()));
		endAuthentication(ERROR_PROCESS);
	} else {
		// The error is not critical. The process can be resumed.
		message.append(OAuthWidget::trUtf8("\nWould you like to resume the authentication process ?"));

		QMessageBox::StandardButton userResponse = QMessageBox::warning(this,
																		OAuthWidget::trUtf8("Hitch in the authentication process"),
																		OAuthWidget::trUtf8(message.toUtf8().data()),
																		QMessageBox::Yes | QMessageBox::No,
																		QMessageBox::Yes);
		if (QMessageBox::Yes == userResponse) {
			// Resume the process
			authenticationFlow->resetTokens();
			killOAuthProcess();
			allowReynTweets();
		} else {
			// Abort the process
			QMessageBox::information(this,
									 OAuthWidget::trUtf8("End of the authentication process"),
									 OAuthWidget::trUtf8("Authentication ended"));
			endAuthentication(ERROR_PROCESS);
		}
	}
}

// Killing the OAuth Authentication Flow
void OAuthWidget::killOAuthProcess() {
	// Unwiring connection beetween the widget and the process

	// Visual changes
	disconnect(authenticationFlow, SIGNAL(loginPanelVisible(bool)),
			   this, SLOT(loginPanelVisible(bool)));
	disconnect(authenticationFlow, SIGNAL(credentialsOK(bool)),
			   this, SLOT(rightCredentials(bool)));

	// Process notifications
	disconnect(this, SIGNAL(authorizeReynTweets(QString,QString)),
			   authenticationFlow, SLOT(authorizeReynTweets(QString,QString)));
	disconnect(this, SIGNAL(denyReynTweets(QString,QString)),
			   authenticationFlow, SLOT(denyReynTweets(QString,QString)));
	disconnect(authenticationFlow, SIGNAL(authenticationProcessFinished(OAuthProcessResult,
																		QByteArray,QByteArray,
																		long,QString)),
			   this, SLOT(endAuthentication(OAuthProcessResult,
											QByteArray,QByteArray,
											long,QString))
			   );
	disconnect(authenticationFlow, SIGNAL(errorProcess(bool,QString)),
			   this, SLOT(errorProcess(bool,QString)));

	delete authenticationFlow;
	authenticationFlow = 0;
}

// End of authentication
void OAuthWidget::endAuthentication(OAuthProcessResult processResult,
									QByteArray accessToken,
									QByteArray tokenSecret,
									long userID,
									QString screenName)
{
	killOAuthProcess();
	qDebug("Fin de l'OAuth Authentication Flow");

	// Transmitting the result
	emit authenticationFinished(processResult,
								accessToken,
								tokenSecret,
								userID,
								screenName);
}


/////////////////////
// Launching Slots //
/////////////////////

// Internal Slot used to send the authorizeReynTweets signal.
void OAuthWidget::launchAuthorize() {
	emit authorizeReynTweets(loginWidget.getLogin(),
							 loginWidget.getPassword());
}

// Internal Slot used to send the denyReynTweets signal.
void OAuthWidget::launchDeny() {
	emit denyReynTweets(loginWidget.getLogin(),
						loginWidget.getPassword());
}
