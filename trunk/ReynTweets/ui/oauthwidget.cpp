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
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <QMessageBox>
#include <QWebHistory>
#include "oauthwidget.hpp"

// Constructor
OAuthWidget::OAuthWidget(QWidget * parent) :
	QWidget(parent),
	authorizePage(),
	oauthAuthenticationFlow(0),
	layout(),
	authPageButton("Retourner à la page d'authentification")
{
	// Wiring of the widget

	// Disable the button when you go back to the Authentication Page
	connect(&authorizePage, SIGNAL(loadStarted()),
			this, SLOT(enableAuthPageButton()));

	// Go to the Authentication Page when you click on authPageButton
	connect(&authPageButton, SIGNAL(clicked()),
			this, SLOT(goToAuthPage()));


	// Building the UI

	// authPageButton
	authPageButton.setEnabled(false);
	layout.addWidget(&authPageButton);

	// authorizePage
	layout.addWidget(&authorizePage);
	authorizePage.hide();

	setLayout(&layout);
}

// Destructor
OAuthWidget::~OAuthWidget() {
	if (oauthAuthenticationFlow != 0) {
		killOAuthProcess();
	}
}

// Show or hide the browser
void OAuthWidget::browserVisible(bool visible) {
	authorizePage.setVisible(visible);
}

// Got to the authentication page
void OAuthWidget::goToAuthPage() {
	QWebHistory * history = authorizePage.history();
	history->goToItem(history->itemAt(0));
	authPageButton.setEnabled(false);
}

// Enable authPageButton when a new Wed page is loaded
void OAuthWidget::enableAuthPageButton() {
	authPageButton.setEnabled(true);
}


/////////////////////////
// Authentication flow //
/////////////////////////

// Allowing Reyn Tweets to use your Twitter account
void OAuthWidget::allowReynTweets() {
	oauthAuthenticationFlow = new OAuthProcess(authorizePage, this);

	if (oauthAuthenticationFlow) {
		connect(oauthAuthenticationFlow, SIGNAL(browserVisible(bool)),
				this, SLOT(browserVisible(bool)));
		connect(oauthAuthenticationFlow, SIGNAL(authenticationProcessFinished(bool)),
				this, SLOT(endAuthentication(bool)));
		connect(oauthAuthenticationFlow, SIGNAL(errorProcess(QString,bool)),
				this, SLOT(errorProcess(QString,bool)));
		oauthAuthenticationFlow->startAuthentication();
	} else {
		// Critical error -> Abort the process.
		QMessageBox::critical(this,
							  "Erreur dans le processus d'authentification",
							  "Erreur au lancement de l'authentification. Authentification terminée.");
		emit authenticationFinished(false);
	}
}

// Signal emitted when an error occurs during the process
void OAuthWidget::errorProcess(QString errorMsg, bool fatalError) {
	if (fatalError) {
		// Critical error -> Abort the process.
		QMessageBox::critical(this,
							  "Erreur dans le processus d'authentification",
							  errorMsg);
		emit authenticationFinished(false);
	} else {
		// The error is not critical. The process can be resumed.
		QMessageBox::StandardButton userResponse = QMessageBox::warning(this,
																		"Imprévu dans le processus d'authentification",
																		errorMsg,
																		QMessageBox::Yes | QMessageBox::No,
																		QMessageBox::Yes);
		if (QMessageBox::Yes == userResponse) {
			// Resume the process
			oauthAuthenticationFlow->resetTokens();
			killOAuthProcess();
			startAuthentication();
		} else {
			// Abort the process
			QMessageBox::information(this,
									 "Fin du processus d'authentification",
									 "Fin du processus d'authentification");
			endAuthentication(false);
		}
	}
}

// Killing the OAuth Authentication Flow
void OAuthWidget::killOAuthProcess() {
	// Killing the process
	disconnect(oauthAuthenticationFlow, SIGNAL(browserVisible(bool)),
			   this, SLOT(browserVisible(bool)));
	disconnect(oauthAuthenticationFlow, SIGNAL(authenticationProcessFinished(bool)),
			   this, SLOT(endAuthentication(bool)));
	disconnect(oauthAuthenticationFlow, SIGNAL(errorProcess(QString,bool)),
			   this, SLOT(errorProcess(QString,bool)));
	delete oauthAuthenticationFlow;
	oauthAuthenticationFlow = 0;
}

// End of authentication
void OAuthWidget::endAuthentication(bool authOK) {
	killOAuthProcess();
	qDebug("fin de l'OAuth Authentication Flow");

	// Transmitting the result
	emit authenticationFinished(authOK);
}
