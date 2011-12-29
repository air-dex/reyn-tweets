/// @file postauthorizerequester.cpp
/// @brief Implementation of PostAuthorizeRequester
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
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#include "postauthorizerequester.hpp"

// Constructor
PostAuthorizeRequester::PostAuthorizeRequester(QObject * requester,
											   OAuthManager & authManager,
											   QString pseudo,
											   QString pwd,
											   bool deny) :
	OAuthRequester(requester,
				   POST,
				   TwitterURL::AUTHORIZE_URL,
				   authManager,
				   HTML_PARSING),
	login(pseudo),
	password(pwd),
	denyReynTweets(deny)
{}

// Building postParameters
void PostAuthorizeRequester::buildPOSTParameters() {
	postParameters.insert("authenticity_token", oauthManager.getAuthenticityToken());
	postParameters.insert("oauth_token", oauthManager.getOAuthToken());

	postParameters.insert("session[username_or_email]", login);
	postParameters.insert("session[password]", password);

	if (denyReynTweets) {
		postParameters.insert("deny", oauthManager.getDeny());
	}
}

// Parsing the raw results of the request.
QVariant PostAuthorizeRequester::parseResult(bool & parseOK, QVariantMap & parsingErrors) {
	// Looking at the URL

	// If it is URL callback, OK ! denied=false then retrieve oauth_token and oauth_verfier

	// If it is TwitterURL::AUTHORIZE_URL, looking at the body class if denied, pas de chance

	return QVariant();
}
