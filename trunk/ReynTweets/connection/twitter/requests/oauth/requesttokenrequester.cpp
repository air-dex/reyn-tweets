/// @file requesttokenrequester.cpp
/// @brief Implementation of RequestTokenRequester
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

#include "requesttokenrequester.hpp"
#include "../../../../tools/parsers/oauthparser.hpp"

// Constructor
RequestTokenRequester::RequestTokenRequester(OAuthManager &authManager) :
	OAuthRequester(Network::POST,
				   TwitterURL::REQUEST_TOKEN_URL,
				   authManager,
				   Network::OAUTH_PARSING,
				   false, true, false)
{}

// Parse the raw results of the request.
QVariant RequestTokenRequester::parseResult(NetworkResponse results,
											bool & parseOK,
											QVariantMap & parsingErrors)
{
	// Key names
	const QString OAUTH_TOKEN_KEY = "oauth_token";
	const QString OAUTH_TOKEN_SECRET_KEY = "oauth_token_secret";
	const QString OAUTH_CALLBACK_CONFIRMED_KEY = "oauth_callback_confirmed";

	// Parsing
	OAuthParser parser;
	QVariantMap resultMap = parser.parse(results.getResponseBody());

	// For treatments
	QString errorMsg = "";
	QVariant extractedCredential;
	bool treatmentOK;
	QString treatmentErrorMsg = "";
	QList<QString> missingArgs;

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

	// oauth_callback_confirmed
	if (resultMap.contains(OAUTH_CALLBACK_CONFIRMED_KEY)) {
		// Rewriting the "oauth_callback_confirmed" parameter as a boolean
		parser.rewriteAsBool(resultMap,
							 OAUTH_CALLBACK_CONFIRMED_KEY,
							 treatmentOK,
							 treatmentErrorMsg);
		parseOK = parseOK && treatmentOK;
		errorMsg.append(treatmentErrorMsg);
	} else {
		// Add it to the missing arguments
		missingArgs.append(OAUTH_CALLBACK_CONFIRMED_KEY);
	}

	parseOK = missingArgs.isEmpty();

	// Listing all the expected parameters
	if (!missingArgs.isEmpty()) {
		foreach (QString argName, missingArgs) {
			errorMsg.append(RequestTokenRequester::trUtf8("Unexpected parameter '"))
					.append(argName)
					.append("'.\n");
		}
	}


	// There was a problem while parsing -> fill the parsingErrors map !
	if (!parseOK) {
		parsingErrors.insert("errorMsg", QVariant(errorMsg));
	}

	return QVariant(resultMap);
}
