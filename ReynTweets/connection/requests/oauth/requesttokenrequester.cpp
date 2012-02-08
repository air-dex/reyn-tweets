/// @file requesttokenrequester.cpp
/// @brief Implementation of RequestTokenRequester
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

#include "requesttokenrequester.hpp"
#include "../../../tools/parsers/oauthparser.hpp"

RequestTokenRequester::RequestTokenRequester(OAuthManager &authManager) :
	OAuthRequester(POST,
				   TwitterURL::REQUEST_TOKEN_URL,
				   authManager,
				   OAUTH_PARSING,
				   false,
				   true)
{}

// Parse the raw results of the request.
QVariant RequestTokenRequester::parseResult(bool & parseOK, QVariantMap & parsingErrors) {
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
	oauthManager.setOAuthToken(extractedCredential.toByteArray());


	// Extracting the "oauth_token_secret" parameter
	extractedCredential = parser.extractParameter(resultMap,
												  "oauth_token_secret",
												  treatmentOK,
												  treatmentErrorMsg);
	parseOK = parseOK && treatmentOK;
	errorMsg.append(treatmentErrorMsg);
	oauthManager.setOAuthSecret(extractedCredential.toByteArray());


	// Rewriting the "oauth_callback_confirmed" parameter as a boolean
	parser.rewriteAsBool(resultMap,
						 "oauth_callback_confirmed",
						 treatmentOK,
						 treatmentErrorMsg);
	parseOK = parseOK && treatmentOK;
	errorMsg.append(treatmentErrorMsg);


	// Ensures that "oauth_callback_confirmed" is the last argument of the list.
	treatmentOK = resultMap.size() == 1 && resultMap.contains("oauth_callback_confirmed");
	parseOK = parseOK && treatmentOK;

	// Listing all the unexpected parameters
	if (!treatmentOK) {
		QList<QString> argNames = resultMap.keys();
		argNames.removeOne("oauth_callback_confirmed");
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
