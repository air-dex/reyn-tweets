/// @file authenticationrequester.cpp
/// @brief Implementation of AuthenticationRequester
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011 Romain Ducher
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

#include "authenticationrequester.hpp"

// Constructor
AuthenticationRequester::AuthenticationRequester(RequestType type,
												 QString url,
												 OAuthManager &authManager,
												 ErrorType parseError,
												 bool tokenNeeded,
												 bool callbackURLNeeded,
												 bool verifierNeeded) :
	TwitterRequester(type, url, parseError),
	oauthManager(authManager),
	oauthTokenNeeded(tokenNeeded),
	oauthCallbackUrlNeeded(callbackURLNeeded),
	oauthVerifierNeeded(verifierNeeded)
{}

// Building HTTP Headers
void AuthenticationRequester::buildHTTPHeaders() {
	// For the Content-Type
	TwitterRequester::buildHTTPHeaders();

	// OAuth header
	// Building the header
	QByteArray authHeader = oauthManager.getAuthorizationHeader(requestType,
																requestURL,
																getParameters,
																postParameters,
																oauthTokenNeeded,
																oauthCallbackUrlNeeded,
																oauthVerifierNeeded);

	headers.insert("Authorization", authHeader);
}
