/// @file postauthorizerequester.cpp
/// @brief Implementation of PostAuthorizeRequester
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

#include "postauthorizerequester.hpp"
#include "../../parsers/htmlparser.hpp"
#include "../../parsers/oauthparser.hpp"

// Constructor
PostAuthorizeRequester::PostAuthorizeRequester(QObject * requester,
											   OAuthManager & authManager,
											   QString pseudo,
											   QString pwd,
											   bool deny) :
	OAuthRequester(requester,
				   POST,
				   TwitterURL::AUTHORIZE_URL,
				   authManager,
				   HTML_PARSING),
	login(pseudo),
	password(pwd),
	denyReynTweets(deny)
{}

// Building postParameters
void PostAuthorizeRequester::buildPOSTParameters() {
	postParameters.insert("authenticity_token", oauthManager.getAuthenticityToken());
	postParameters.insert("oauth_token", oauthManager.getOAuthToken());

	postParameters.insert("session[username_or_email]", login);
	postParameters.insert("session[password]", password);

	if (denyReynTweets) {
		postParameters.insert("deny", oauthManager.getDeny());
	}
}

// Parsing the raw results of the request.
QVariant PostAuthorizeRequester::parseResult(bool & parseOK, QVariantMap & parsingErrors) {
	// Map for results
	QVariantMap parsedResults;

	// For treatments
	QString errorMsg = "";
	bool treatmentOK;
	QString errTreatment = "";

	// Looking at the URL
	QString replyURL = communicator->getReplyURL();


	// If it is URL callback, OK ! denied=false then retrieve oauth_token and oauth_verfier
	if (replyURL.startsWith(oauthManager.getCallbackUrl())) {
		// Reyn Tweets is accepted ! :D
		parsedResults.insert("urlOK", QVariant(true));
		parsedResults.insert("denied", QVariant(false));
		parsedResults.insert("rightCredentials", QVariant(true));

		// Retrieving the oauth_token and the oauth_verifier in the URL (GET parameters)
		setParsingErrorType(OAUTH_PARSING);
		OAuthParser parser;
		QByteArray rawResponse = replyURL.toUtf8().split('?').at(1);

		// Parsing
		QVariantMap resultMap = parser.parse(rawResponse, parseOK, errorMsg);
		errorMsg.append(errTreatment);

		QVariant extractedCredential;

		// Extracting the "oauth_token" parameter
		extractedCredential = parser.extractParameter(resultMap,
													  "oauth_token",
													  treatmentOK,
													  errTreatment);
		parseOK = parseOK && treatmentOK;
		errorMsg.append(errTreatment);
		oauthManager.setOAuthToken(extractedCredential.toString());


		// Extracting the "oauth_verifier" parameter
		extractedCredential = parser.extractParameter(resultMap,
													  "oauth_verifier",
													  treatmentOK,
													  errTreatment);
		parseOK = parseOK && treatmentOK;
		errorMsg.append(errTreatment);
		oauthManager.setVerifier(extractedCredential.toString());
	} else if (replyURL.startsWith(TwitterURL::AUTHORIZE_URL)) {
		/*
		 * Parsing the HTML page to know if Reyn Tweets was denied or
		 * if the credentials were bad.
		 */
		parsedResults.insert("urlOK", QVariant(true));

		// Getting the HTML document
		HTMLParser parser;
		QWebElement htmlDocument = parser.parse(communicator->getResponseBuffer(),
												parseOK,
												errTreatment);
		errorMsg.append(errTreatment);

		treatmentOK = !htmlDocument.isNull();
		parseOK = parseOK && treatmentOK;

		if (treatmentOK) {
			// Get the body class
			QWebElement body = htmlDocument.findFirst("body");
			QString bodyClass = body.attribute("class");

			if(bodyClass.startsWith("oauth write")) {
				// Credentials were bad.
				treatmentOK = true;
				parsedResults.insert("rightCredentials", QVariant(false));
			} else if (bodyClass.startsWith("oauth denied")) {
				// Reyn Tweets was denied. :(
				treatmentOK = true;
				parsedResults.insert("denied", QVariant(true));
				parsedResults.insert("rightCredentials", QVariant(true));
			} else {
				// Error according to the observations done for the process
				treatmentOK = false;
				errorMsg.append("Unexpected <body> class.\n");
			}

			parseOK = parseOK && treatmentOK;
		} else {
			errorMsg.append("Empty HTML page.\n");
		}
	} else {
		parsedResults.insert("urlOK", QVariant(false));
		errorMsg.append("Wrong URL.\n");
	}


	// There was a problem while parsing -> fill the parsingErrors map !
	if (!parseOK) {
		parsingErrors.insert("errorMsg", QVariant(errorMsg));
	}

	return QVariant(parsedResults);
}
