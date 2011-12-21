/// @file authenticaterequester.cpp
/// @brief Implementation of AuthenticateRequester
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

#include "authenticaterequester.hpp"

AuthenticateRequester::AuthenticateRequester(OAuthManager & authManager,
											 QObject *requester) :
	OAuthRequester(authManager,
				   GET,
				   RequestUrl::AUTHENTICATE_URL,
				   requester)
{}

// Building GET Parameters
void AuthenticateRequester::buildGETParameters() {
	getParameters.insert("oauth_token", oauthManager->getOAuthToken());
}

// Building POST Parameters
void AuthenticateRequester::buildPOSTParameters() {}

// Parse the raw results of the request.
QVariant AuthenticateRequester::parseResult(bool & parseOK, QVariantMap & parsingErrors) {
	/*
	QVariantMap resultMap;	// Result of the request
	bool rightParameter;	// Boolean indicating if the parameter name is right
	QString errorMsg = "Error for parameter ";
	QString subErrorMsg;

	// Parsing
	QByteArray rawResponse = communicator->getResponseBuffer();
	QList<QByteArray> results = rawResponse.split('&');

	QList<QByteArray> resultPair;
	QByteArray parameterName;
	QByteArray result;

	// Getting the request token
	resultPair = results.at(0).split('=');

	// Ensures that the parameter name is "oauth_token"
	parameterName = resultPair.at(0);
	rightParameter = "oauth_token" == parameterName;
	parseOK = rightParameter;

	if (rightParameter) {
		result = resultPair.at(1);
		oauthManager->setOAuthToken(QString(result));
	} else {
		subErrorMsg = "'";
		subErrorMsg.append(parameterName);
		subErrorMsg.append("' (supposed to be 'oauth_token'), ");
		errorMsg.append(subErrorMsg);
	}

	// Getting the request secret
	resultPair = results.at(1).split('=');

	// Ensures that the parameter name is "oauth_token_secret"
	parameterName = resultPair.at(0);
	rightParameter = "oauth_token_secret" == parameterName;
	parseOK = parseOK && rightParameter;

	if (rightParameter) {
		result = resultPair.at(1);
		oauthManager->setOAuthSecret(QString(result));
	} else {
		subErrorMsg = "parameter '";
		subErrorMsg.append(parameterName);
		subErrorMsg.append("' (supposed to be 'oauth_token_secret'), ");
		errorMsg.append(subErrorMsg);
	}


	// Was the callback URL confirmed ?
	resultPair = results.at(2).split('=');

	// Ensures that the parameter name is "oauth_callback_confirmed"
	parameterName = resultPair.at(0);
	rightParameter = "oauth_callback_confirmed" == parameterName;
	parseOK = parseOK && rightParameter;

	if (rightParameter) {
		result = resultPair.at(1);
		bool callbackUrlConfirmed = ("true" == result) || !("false" == result);
		resultMap.insert("oauth_callback_confirmed", QVariant(callbackUrlConfirmed));
	} else {
		subErrorMsg = "parameter '";
		subErrorMsg.append(parameterName);
		subErrorMsg.append("' (supposed to be 'oauth_callback_confirmed')");
		errorMsg.append(subErrorMsg);
	}


	// There was a problem while parsing -> fill the parsingErrors map !
	if (!parseOK) {
		if (errorMsg.endsWith(", ")) {
			errorMsg.chop(2);
			errorMsg.append('.');
		}

		parsingErrors.insert("errorMsg", QVariant(errorMsg));
	}

	return QVariant(resultMap);
	//*/

	return QVariant();
}

