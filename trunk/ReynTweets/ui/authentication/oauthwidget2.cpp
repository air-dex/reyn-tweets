/// @file loginwidget.hpp
/// @brief Header of LoginWidget
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
#include "oauthwidget2.hpp"

// Constructor
OAuthWidget2::OAuthWidget2(QWidget *parent) :
	QWidget(parent),
	authenticationFlow(0),
	loginWidget(),
	layout()
{
	loginWidget.setVisible(false);

	// Wiring the login panel and the launching slots
	connect(&loginWidget, SIGNAL(authorize()),
			this, SLOT(launchAuthorize()));
	connect(&loginWidget, SIGNAL(deny()),
			this, SLOT(launchDeny()));
}

// Destructor
OAuthWidget2::~OAuthWidget2() {
	if (authenticationFlow) {
		killOAuthProcess();
	}

	// Unwiring the login panel and the launching slots
	disconnect(&loginWidget, SIGNAL(authorize()),
			   this, SLOT(launchAuthorize()));
	disconnect(&loginWidget, SIGNAL(deny()),
			   this, SLOT(launchDeny()));
}

// Allowing Reyn Tweets to use your Twitter account
void OAuthWidget2::allowReynTweets() {
	authenticationFlow = new OAuthProcess2(this);

	if (authenticationFlow) {
		// Wiring connection beetween the widget and the process
		connect(authenticationFlow, SIGNAL(loginPanelVisible(bool)),
				this, SLOT(loginPanelVisible(bool)));
		connect(authenticationFlow, SIGNAL(authenticationProcessFinished(bool)),
				this, SLOT(endAuthentication(bool)));
		connect(authenticationFlow, SIGNAL(errorProcess(bool,QString)),
				this, SLOT(errorProcess(bool,QString)));
		connect(this, SIGNAL(authorizeReynTweets(QString,QString)),
				authenticationFlow, SLOT(authorizeReynTweets(QString,QString)));
		connect(this, SIGNAL(denyReynTweets(QString,QString)),
				authenticationFlow, SLOT(denyReynTweets(QString,QString)));

		authenticationFlow->startAuthentication();
	} else {
		// Critical error -> Abort the process.
		QMessageBox::critical(this,
							  QObject::tr("Erreur dans le processus d'authentification"),
							  QObject::tr("Erreur au lancement de l'authentification. Authentification terminée."));
		emit authenticationFinished(false);
	}
}

// Slot executing to show (or to hide) the login panel
void OAuthWidget2::loginPanelVisible(bool visible) {
	loginWidget.setVisible(visible);
}

// Signal emitted when an error occurs during the process
void OAuthWidget2::errorProcess(bool fatalError, QString errorMsg) {
	QString message = errorMsg;

	if (fatalError) {
		// Critical error -> Abort the process.
		message.append("\nFin de l'authentification.");

		QMessageBox::critical(this,
							  QObject::tr("Erreur dans le processus d'authentification"),
							  QObject::tr(message.toUtf8().data()));
		endAuthentication(false);
	} else {
		// The error is not critical. The process can be resumed.
		message.append("\nVoulez-vous recommencer l'authentification ?");

		QMessageBox::StandardButton userResponse = QMessageBox::warning(this,
																		QObject::tr("Imprévu dans le processus d'authentification"),
																		QObject::tr(message.toUtf8().data()),
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
									 QObject::tr("Fin du processus d'authentification"),
									 QObject::tr("Authentification terminée"));
			endAuthentication(false);
		}
	}
}

// Killing the OAuth Authentication Flow
void OAuthWidget2::killOAuthProcess() {
	// Unwiring connection beetween the widget and the process
	disconnect(authenticationFlow, SIGNAL(loginPanelVisible(bool)),
			   this, SLOT(loginPanelVisible(bool)));
	disconnect(authenticationFlow, SIGNAL(authenticationProcessFinished(bool)),
			   this, SLOT(endAuthentication(bool)));
	disconnect(authenticationFlow, SIGNAL(errorProcess(bool,QString)),
			   this, SLOT(errorProcess(bool,QString)));
	disconnect(this, SIGNAL(authorizeReynTweets(QString,QString)),
			   authenticationFlow, SLOT(authorizeReynTweets(QString,QString)));
	disconnect(this, SIGNAL(denyReynTweets(QString,QString)),
			   authenticationFlow, SLOT(denyReynTweets(QString,QString)));

	delete authenticationFlow;
	authenticationFlow = 0;
}

// End of authentication
void OAuthWidget2::endAuthentication(bool authOK) {
	killOAuthProcess();
	qDebug("fin de l'OAuth Authentication Flow");

	// Transmitting the result
	emit authenticationFinished(authOK);
}


/////////////////////
// Launching Slots //
/////////////////////

// Internal Slot used to send the authorizeReynTweets signal.
void OAuthWidget2::launchAuthorize() {
	emit authorizeReynTweets(loginWidget.getLogin(),
							 loginWidget.getPassword());
}

// Internal Slot used to send the denyReynTweets signal.
void OAuthWidget2::launchDeny() {
	emit denyReynTweets(loginWidget.getLogin(),
						loginWidget.getPassword());
}
