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
#include "../../parsers/oauthparser.hpp"

AuthorizeRequester::AuthorizeRequester(QWebView & twitterBrowser,
									   OAuthManager &authManager,
									   QObject *requester) :
	OAuthRequester(requester,
				   GET,
				   TwitterURL::AUTHORIZE_URL,
				   authManager),
	browser(twitterBrowser)
{}

// Building GET Parameters
void AuthorizeRequester::buildGETParameters() {
	getParameters.insert("oauth_token", oauthManager.getOAuthToken());
}

// Initialize the communicator.
void AuthorizeRequester::initCommunicator() {
	communicator = new AuthorizeTwitterCommunicator(browser,
													oauthManager,
													getParameters,
													this);
	connect(communicator, SIGNAL(requestDone(bool)),
			this, SLOT(treatResults(bool)));
}

// Parse the raw results of the request.
QVariant AuthorizeRequester::parseResult(bool & parseOK, QVariantMap & parsingErrors) {
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


	// Rewriting the "denied" parameter as a boolean
	parser.rewriteAsBool(resultMap,
						 "denied",
						 treatmentOK,
						 treatmentErrorMsg);
	parseOK = parseOK && treatmentOK;
	errorMsg.append(treatmentErrorMsg);

	if (treatmentOK) {
		bool reynTweetsDenied = resultMap.value("denied").toBool();

		if (reynTweetsDenied) {
			// Extracting the "oauth_token" parameter
			extractedCredential = parser.extractParameter(resultMap,
														  "oauth_token",
														  treatmentOK,
														  treatmentErrorMsg);
			parseOK = parseOK && treatmentOK;
			errorMsg.append(treatmentErrorMsg);
			if (treatmentOK) {
				oauthManager.setOAuthToken(extractedCredential.toString());
			}

			// Extracting the "oauth_verifier" parameter
			extractedCredential = parser.extractParameter(resultMap,
														  "oauth_verifier",
														  treatmentOK,
														  treatmentErrorMsg);
			parseOK = parseOK && treatmentOK;
			errorMsg.append(treatmentErrorMsg);
			if (treatmentOK) {
				oauthManager.setVerifier(extractedCredential.toString());
			}
		}
	}

	// Ensures that there was not any parameters excepting "denied"
	treatmentOK = resultMap.size() == 1 && resultMap.contains("denied");
	parseOK = parseOK && treatmentOK;

	// Listing all the unexpected parameters
	if (!treatmentOK) {
		QList<QString> argNames = resultMap.keys();
		argNames.removeOne("denied");
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
