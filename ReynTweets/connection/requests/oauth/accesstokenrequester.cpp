/// @file accesstokenrequester.cpp
/// @brief Implementation of AccessTokenRequester
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
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#include "accesstokenrequester.hpp"
#include "../../parsers/oauthparser.hpp"

// Constructor
AccessTokenRequester::AccessTokenRequester(OAuthManager &authManager) :
	OAuthRequester(POST,
				   TwitterURL::ACCESS_TOKEN_URL,
				   authManager,
				   OAUTH_PARSING,
				   true,
				   false,
				   true)
{}

// Building POST Parameters
void AccessTokenRequester::buildPOSTParameters() {
	postParameters.insert("oauth_verifier", oauthManager.getVerifier());
}

// Parse the raw results of the request.
QVariant AccessTokenRequester::parseResult(bool & parseOK, QVariantMap & parsingErrors) {
	OAuthParser parser;
	QByteArray rawResponse = communicator->getResponseBuffer();
	QString errorMsg = "";

	// For treatments
	QVariant extractedCredential;
	bool treatmentOK;
	QString treatmentErrorMsg = "";


	// Parsing
	QVariantMap resultMap = parser.parse(rawResponse, parseOK, errorMsg);
	errorMsg.append(treatmentErrorMsg);


	// Extracting the "oauth_token" parameter
	extractedCredential = parser.extractParameter(resultMap,
												  "oauth_token",
												  treatmentOK,
												  treatmentErrorMsg);
	parseOK = parseOK && treatmentOK;
	errorMsg.append(treatmentErrorMsg);
	oauthManager.setOAuthToken(extractedCredential.toString());


	// Extracting the "oauth_token_secret" parameter
	extractedCredential = parser.extractParameter(resultMap,
												  "oauth_token_secret",
												  treatmentOK,
												  treatmentErrorMsg);
	parseOK = parseOK && treatmentOK;
	errorMsg.append(treatmentErrorMsg);
	oauthManager.setOAuthSecret(extractedCredential.toString());


	// Ensures that the two remaining arguments are "user_id" and "screen_name"
	treatmentOK = resultMap.size() == 2
			&& resultMap.contains("user_id")
			&& resultMap.contains("screen_name");
	parseOK = parseOK && treatmentOK;

	// Listing all the unexpected parameters
	if (!treatmentOK) {
		QList<QString> argNames = resultMap.keys();
		argNames.removeOne("user_id");
		argNames.removeOne("screen_name");
		foreach (QString argName, argNames) {
			errorMsg.append("Unexpected parameter '")
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

