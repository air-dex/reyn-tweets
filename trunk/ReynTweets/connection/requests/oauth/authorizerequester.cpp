/// @file authorizerequester.cpp
/// @brief Implementation of AuthorizeRequester
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

#include <QWebElement>
#include "authorizerequester.hpp"
#include "../../../tools/parsers/htmlparser.hpp"
#include "../../../tools/utils.hpp"

// Constructor
AuthorizeRequester::AuthorizeRequester(OAuthManager &authManager) :
	OAuthRequester(GET,
				   TwitterURL::AUTHORIZE_URL,
				   authManager,
				   HTML_PARSING)
{}

// Building GET Parameters
void AuthorizeRequester::buildGETParameters() {
	getParameters.insert("oauth_token",
						 QString::fromAscii(oauthManager.getOAuthToken().data()));
}

// Parsing results
QVariant AuthorizeRequester::parseResult(bool &parseOK, QVariantMap &parsingErrors) {
	// Flags for treatment
	bool treatmentOK;
	QString errTreatment = "";

	// Error message for the whole parsing process
	QString errorMsg = "";

	// Getting the HTML document
	HTMLParser parser;
	QWebElement htmlDocument = parser.parse(communicator->getResponseBuffer(),
											parseOK,
											errTreatment);
	errorMsg.append(errTreatment);

	treatmentOK = !htmlDocument.isNull();
	parseOK = parseOK && treatmentOK;

	if (treatmentOK) {
		// Getting the parameters (auth token, oauth_token and deny)

		// Boolean indicating if the parameters are found
		bool authenticityTokenFound = false;
		bool oauthTokenFound = false;
		bool denyFound = false;

		// treatmentOK : 3 parameters found
		// treatmentOK = authenticityTokenFound && oauthTokenFound && denyFound
		treatmentOK = false;

		QWebElementCollection inputs = htmlDocument.findAll("input");

		// It stops when the 3 parameters are found xor when all is seen in the collection
		for (QWebElementCollection::iterator it = inputs.begin();
			 it != inputs.end() && !treatmentOK;
			 ++it)
		{
			QWebElement input = *it;
			QString inputName = input.attribute("name");
			QString inputValue = input.attribute("value");

			// Is a parameter found ?
			if (!authenticityTokenFound && inputName == "authenticity_token") {
				// The authenticity token is found !
				oauthManager.setAuthenticityToken(inputValue.toAscii());
				authenticityTokenFound = true;
			} else if (!oauthTokenFound && inputName == "oauth_token") {
				// The oauth token is found. (WTF)
				oauthManager.setOAuthToken(inputValue.toAscii());
				oauthTokenFound = true;
			} else if (!denyFound && inputName == "deny") {
				// The deny value is found !
				oauthManager.setDeny(inputValue);
				denyFound = true;
			}

			treatmentOK = authenticityTokenFound && oauthTokenFound && denyFound;
		}

		parseOK = parseOK && treatmentOK;

		// Are all the parameters found ?
		if (!treatmentOK) {
			if (!authenticityTokenFound) {
				errorMsg.append(AuthorizeRequester::trUtf8("Authenticity token not found."))
						.append('\n');
			}

			if (!oauthTokenFound) {
				errorMsg.append(AuthorizeRequester::trUtf8("OAuth token not found."))
						.append('\n');
			}

			if (!denyFound) {
				errorMsg.append(AuthorizeRequester::trUtf8("Deny value not found."))
						.append('\n');
			}
		}
	} else {
		errorMsg.append(AuthorizeRequester::trUtf8("Empty HTML page.\n"))
				.append('\n');
	}


	// There was a problem while parsing -> fill the parsingErrors map !
	if (!parseOK) {
		parsingErrors.insert("errorMsg", QVariant(errorMsg));
	}

	return QVariant();
}
