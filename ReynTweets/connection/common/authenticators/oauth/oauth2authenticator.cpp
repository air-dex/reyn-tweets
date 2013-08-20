/// @file oauth2authenticator.cpp
/// @brief Implementation of OAuth2Authenticator
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2013 Romain Ducher
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

#include "oauth2authenticator.hpp"

#include <QUrl>
#include "../../utils/librtconstants.hpp"

// Constructor
OAuth2Authenticator::OAuth2Authenticator() :
	OAuthAuthenticator("2.0"),
	bearerToken(LibRT::FAKE_TOKEN)
{}

// Destructor
OAuth2Authenticator::~OAuth2Authenticator() {}

/////////////////////////////
// Bearer token management //
/////////////////////////////

void OAuth2Authenticator::setBearerToken(QByteArray newBearer) {
	bearerToken = newBearer;
}

void OAuth2Authenticator::resetTokens() {
	bearerToken = LibRT::FAKE_TOKEN;
}


///////////////////////////////////////
// OAuth 2 Authentication management //
///////////////////////////////////////

QByteArray OAuth2Authenticator::getBasicHeader() {
	QByteArray bearerCredentials = "";

	bearerCredentials.append(QUrl::toPercentEncoding(consumerTokens.first))
			.append(':')
			.append(QUrl::toPercentEncoding(consumerTokens.second));

	QByteArray basicHeader = "Basic ";

	basicHeader.append(bearerCredentials.toBase64());

	return basicHeader;
}

QByteArray OAuth2Authenticator::getBearerHeader() {
	QByteArray bearerHeader = "Bearer ";

	bearerHeader.append(bearerToken.toBase64());

	return bearerHeader;
}
