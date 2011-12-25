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

#include "oauthwidget.hpp"

// Constructor
OAuthWidget::OAuthWidget(QWidget *parent) :
	QWidget(parent),
	authorizePage(),
	oauthAuthenticationFlow(0)
{}

// Destructor
OAuthWidget::~OAuthWidget() {
	if (oauthAuthenticationFlow != 0) {
		delete oauthAuthenticationFlow;
	}
}

// Treatments after the request for Request Tokens
void OAuthWidget::browserVisible(bool visible) {
	if (visible) {
		// Displaying authorizePage
	} else {
		// Hiding authorizePage
	}
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
		oauthAuthenticationFlow->startAuthentication();
	} else {
		// Erreur à l'initialisation du process
	}
}

// End of authentication
void OAuthWidget::endAuthentication(bool authOK) {
	// Killing the process
	disconnect(oauthAuthenticationFlow, SIGNAL(browserVisible(bool)),
			this, SLOT(browserVisible(bool)));
	disconnect(oauthAuthenticationFlow, SIGNAL(authenticationProcessFinished(bool)),
			this, SLOT(endAuthentication(bool)));
	delete oauthAuthenticationFlow;
	oauthAuthenticationFlow = 0;

	// Transmitting the result
	emit authenticationFinished(authOK);
}
