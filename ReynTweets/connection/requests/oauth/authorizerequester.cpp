/// @file authorizerequester.cpp
/// @brief Implementation of AuthorizeRequester
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

#include "authorizerequester.hpp"
#include "../../twittercommunicators/authorizetwittercommunicator.hpp"

AuthorizeRequester::AuthorizeRequester(QWebView & twitterBrowser,
									   OAuthManager &authManager,
									   QObject *requester) :
	OAuthRequester(authManager,
				   GET,
				   TwitterURL::AUTHORIZE_URL,
				   requester),
	browser(twitterBrowser)
{}

// Building GET Parameters
void AuthorizeRequester::buildGETParameters() {
	getParameters.insert("oauth_token", oauthManager->getOAuthToken());
}

// Initialize the communicator.
void AuthorizeRequester::initCommunicator() {
	communicator = new AuthorizeTwitterCommunicator(browser,
													*oauthManager,
													getParameters,
													this);
	connect(communicator, SIGNAL(requestDone(bool)),
			this, SLOT(treatResults(bool)));
}

// Parse the raw results of the request.
QVariant AuthorizeRequester::parseResult(bool & parseOK, QVariantMap & parsingErrors) {
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

	// Getting the request token or the "denied"
	resultPair = results.at(0).split('=');
	parameterName = resultPair.at(0);

	if ("denied" == parameterName) {
		resultMap.insert("denied", result);
		parseOK = true;
		return QVariant(resultMap);
	} else if ("oauth_token" == parameterName) {
		result = resultPair.at(1);
		parseOK = true;
		oauthManager->setOAuthToken(QString(result));
	} else {
		parseOK = false;
		subErrorMsg = "'";
		subErrorMsg.append(parameterName);
		subErrorMsg.append("' (supposed to be 'oauth_token' or 'denied'), ");
		errorMsg.append(subErrorMsg);
	}

	// Getting the verifier
	resultPair = results.at(1).split('=');

	// Ensures that the parameter name is "oauth_verifier"
	parameterName = resultPair.at(0);
	rightParameter = "oauth_verifier" == parameterName;
	parseOK = parseOK && rightParameter;

	if (rightParameter) {
		result = resultPair.at(1);
		oauthManager->setVerifier(QString(result));
	} else {
		subErrorMsg = "parameter '";
		subErrorMsg.append(parameterName);
		subErrorMsg.append("' (supposed to be 'oauth_verifier'), ");
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
}
