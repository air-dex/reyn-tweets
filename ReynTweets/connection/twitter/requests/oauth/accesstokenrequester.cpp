/// @file accesstokenrequester.cpp
/// @brief Implementation of AccessTokenRequester
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011, 2013 Romain Ducher
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

#include "accesstokenrequester.hpp"

#include <QStringList>
#include "../../../common/utils/parsers/oauthparser.hpp"

// Constructor
AccessTokenRequester::AccessTokenRequester(TwitterAuthenticator &authManager,
										   QByteArray verifier) :
	OAuthRequester(LibRT::POST,
				   Twitter::ACCESS_TOKEN_URL,
				   authManager,
				   LibRT::OAUTH_PARSING,
				   true, false, true)
{
	oauthManager.setVerifier(verifier);
}

// Building POST Parameters
void AccessTokenRequester::buildPOSTParameters() {
	postParameters.insert("oauth_verifier",
						  QString::fromLatin1(oauthManager.getVerifier()));
}

// Parse the raw results of the request.
QVariant AccessTokenRequester::parseResult(NetworkResponse results,
										   bool & parseOK,
										   QVariantMap & parsingErrors)
{
	// Key names
	const QString OAUTH_TOKEN_KEY = "oauth_token";
	const QString OAUTH_TOKEN_SECRET_KEY = "oauth_token_secret";
	const QString USER_ID_KEY = "user_id";
	const QString SCREEN_NAME_KEY = "screen_name";

	// Parsing
	OAuthParser parser;
	QVariantMap resultMap = parser.parse(results.getResponseBody());

	// For treatments
	QVariant extractedCredential;
	QStringList missingArgs;

	// oauth_token
	if (resultMap.contains(OAUTH_TOKEN_KEY)) {
		// Extracting the "oauth_token" parameter
		extractedCredential = resultMap.value(OAUTH_TOKEN_KEY);
		oauthManager.setOAuthToken(extractedCredential.toByteArray());
	} else {
		// Add it to the missing arguments
		missingArgs.append(OAUTH_TOKEN_KEY);
	}

	// oauth_token_secret
	if (resultMap.contains(OAUTH_TOKEN_SECRET_KEY)) {
		// Extracting the "oauth_token_secret" parameter
		extractedCredential = resultMap.value(OAUTH_TOKEN_SECRET_KEY);
		oauthManager.setOAuthSecret(extractedCredential.toByteArray());
	} else {
		// Add it to the missing arguments
		missingArgs.append(OAUTH_TOKEN_SECRET_KEY);
	}

	// user_id
	if (!resultMap.contains(USER_ID_KEY)) {
		// Add it to the missing arguments
		missingArgs.append(USER_ID_KEY);
	}

	// screen_name
	if (!resultMap.contains(SCREEN_NAME_KEY)) {
		// Add it to the missing arguments
		missingArgs.append(SCREEN_NAME_KEY);
	}

	parseOK = missingArgs.isEmpty();

	// Listing all the expected parameters
	if (!missingArgs.isEmpty()) {
		QString errorMsg = "";

		errorMsg.append(AccessTokenRequester::trUtf8("The following parameters were expected:"))
				.append(' ')
				.append(missingArgs.join(", "))
				.append('.');

		// Fill the parsingErrors map !
		parsingErrors.insert("errorMsg", QVariant::fromValue(errorMsg));
	}

	return QVariant::fromValue(resultMap);
}
