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
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#include "accesstokenrequester.hpp"
#include "../../parsers/oauthparser.hpp"

AccessTokenRequester::AccessTokenRequester(OAuthManager & authManager,
											 QObject *requester) :
	OAuthRequester(authManager,
				   POST,
				   TwitterURL::ACCESS_TOKEN_URL,
				   requester)
{}

// Building POST Parameters
void AccessTokenRequester::buildPOSTParameters() {
	postParameters.insert("oauth_verifier", oauthManager->getVerifier());
}

// Parse the raw results of the request.
QVariant AccessTokenRequester::parseResult(bool & parseOK, QVariantMap & parsingErrors) {
	OAuthParser parser;
	QByteArray rawResponse = communicator->getResponseBuffer();
	QString parseErrorMsg = "";

	QVariantMap resultMap = parser.parse(rawResponse, parseOK, parseErrorMsg);

	QString errorMsg = "";
	bool expectedParameter;

	// Extracting the "oauth_token" prameter
	expectedParameter = resultMap.contains("oauth_token");
	parseOK = parseOK && expectedParameter;

	if (expectedParameter) {
		QVariant token = resultMap.value("oauth_token");
		oauthManager->setOAuthToken(token.toString());
		resultMap.remove("oauth_token");
	} else {
		errorMsg.append("Parameter 'oauth_token' expected.\n");
	}


	// Extracting the "oauth_token_secret" prameter
	if (resultMap.contains("oauth_token_secret")) {
		QVariant tokenSecret = resultMap.value("oauth_token_secret");
		oauthManager->setOAuthSecret(tokenSecret.toString());
		resultMap.remove("oauth_token_secret");
	} else {
		errorMsg.append("Parameter 'oauth_token_secret' expected.\n");
	}


	// Ensures that the two remaining arguments are "user_id" and "screen_name"
	// TODO

/*
	QVariantMap resultMap;	// Result of the request
	bool rightParameter;	// Boolean indicating if the parameter name is right

	// Parsing
	QList<QByteArray> results = rawResponse.split('&');

	QList<QByteArray> resultPair;
	QByteArray parameterName;
	QByteArray result;
//*/
/*
	// Getting the user ID
	resultPair = results.at(2).split('=');

	// Ensures that the parameter name is "user_id"
	parameterName = resultPair.at(0);
	rightParameter = "user_id" == parameterName;
	parseOK = parseOK && rightParameter;

	if (rightParameter) {
		result = resultPair.at(1);
		resultMap.insert("user_id", QVariant(result));
	} else {
		subErrorMsg = "parameter '";
		subErrorMsg.append(parameterName);
		subErrorMsg.append("' (supposed to be 'user_id')");
		errorMsg.append(subErrorMsg);
	}


	// Getting the screen name
	resultPair = results.at(3).split('=');

	// Ensures that the parameter name is "screen_name"
	parameterName = resultPair.at(0);
	rightParameter = "screen_name" == parameterName;
	parseOK = parseOK && rightParameter;

	if (rightParameter) {
		result = resultPair.at(1);
		resultMap.insert("screen_name", QVariant(result));
	} else {
		subErrorMsg = "parameter '";
		subErrorMsg.append(parameterName);
		subErrorMsg.append("' (supposed to be 'screen_name')");
		errorMsg.append(subErrorMsg);
	}
//*/

	// There was a problem while parsing -> fill the parsingErrors map !
	if (!parseOK) {
		errorMsg.append(parseErrorMsg);
		parsingErrors.insert("errorMsg", QVariant(errorMsg));
	}

	return QVariant(resultMap);
}

