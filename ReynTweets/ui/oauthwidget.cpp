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
	twitterCalls(ReynTwitterCalls::getInstance()),
	authorizePage()
{}


/////////////////////////
// Authentication flow //
/////////////////////////

// Allowing Reyn Tweets to use your Twitter account
void OAuthWidget::allowReynTweets() {
	requestToken();
}

// Demanding a Request Token
void OAuthWidget::requestToken() {
	connect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(requestTokenDemanded(ResultWrapper)));
	twitterCalls.requestToken(this);
}

// Treatments after the request for Request Tokens
void OAuthWidget::requestTokenDemanded(ResultWrapper res) {
	disconnect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(requestTokenDemanded(ResultWrapper)));

	// Treatments on res for continuing the authentication process

	authorize();	// If that's ok
}

// Authorizing Reyn Tweets by displaying the Twitter
void OAuthWidget::authorize() {
	// Put on the browser

	connect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(authorizeDemanded(ResultWrapper)));
	twitterCalls.requestToken(this);
}

// Treatments after the request for authorizing Request Tokens
void OAuthWidget::authorizeDemanded(ResultWrapper res) {
	disconnect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(authorizeDemanded(ResultWrapper)));

	// Put off the browser

	// Treatments on res for continuing the authentication process

	accessToken();	// If that's ok
}

// Demanding an Access Token
void OAuthWidget::accessToken() {
	connect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(accessTokenDemanded(ResultWrapper)));
	twitterCalls.accessToken(this);
}

// Treatments after the request for Access Tokens
void OAuthWidget::accessTokenDemanded(ResultWrapper res) {
	disconnect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(accessTokenDemanded(ResultWrapper)));

	bool accessTokenOK;

	// Treatments on res

	emit authenticationFinished(accessTokenOK);
}
