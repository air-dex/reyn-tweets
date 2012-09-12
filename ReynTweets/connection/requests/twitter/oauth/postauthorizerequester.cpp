/// @file postauthorizerequester.cpp
/// @brief Implementation of PostAuthorizeRequester
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

#include "postauthorizerequester.hpp"
#include "../../../../tools/parsers/htmlparser.hpp"
#include "../../../../tools/parsers/oauthparser.hpp"

// Constructor
PostAuthorizeRequester::PostAuthorizeRequester(OAuthManager &authManager,
											   QString pseudo,
											   QString pwd,
											   bool deny) :
	OAuthRequester(POST,
				   TwitterURL::AUTHORIZE_URL,
				   authManager,
				   HTML_PARSING),
	login(pseudo),
	password(pwd),
	denyReynTweets(deny)
{}

// Building postParameters
void PostAuthorizeRequester::buildPOSTParameters() {
	postParameters.insert("authenticity_token",
						  QString::fromAscii(oauthManager.getAuthenticityToken().data()));
	getParameters.insert("oauth_token",
						 QString::fromAscii(oauthManager.getOAuthToken().data()));

	postParameters.insert("session[username_or_email]", login);
	postParameters.insert("session[password]", password);

	if (denyReynTweets) {
		postParameters.insert("deny", oauthManager.getDeny());
	}
}

// Parsing the raw results of the request.
QVariant PostAuthorizeRequester::parseResult(bool & parseOK,
											 QVariantMap & parsingErrors)
{
	QVariantMap parsedResults;		// Map for results
	QString errorMsg = "";			// Error message written while parsing

	// Looking at the URL. Is it the right one ?
	QString replyURL = weblink.getReplyURL();
	bool urlOK = replyURL.startsWith(TwitterURL::AUTHORIZE_URL);
	parsedResults.insert("urlOK", QVariant(urlOK));
	parseOK = urlOK;

	if (urlOK) {
		// For treatments
		bool treatmentOK;
		QString errTreatment = "";

		// Getting the HTML document
		HTMLParser parser;
		QWebElement htmlDocument = parser.parse(weblink.getResponseBuffer(),
												treatmentOK,
												errTreatment);
		parseOK = parseOK && treatmentOK;
		errorMsg.append(errTreatment);

		if (treatmentOK) {
			treatmentOK = !htmlDocument.isNull();
			parseOK = parseOK && treatmentOK;

			// Page for what ?
			if (treatmentOK) {
				// Get the body class
				QWebElement body = htmlDocument.findFirst("body");
				QString bodyClass = body.attribute("class");


				if (bodyClass.startsWith("oauth denied")) {
					// Reyn Tweets was denied. :(
					treatmentOK = true;
					parseOK = parseOK && treatmentOK;
					parsedResults.insert("denied", QVariant(true));
					parsedResults.insert("rightCredentials", QVariant(true));
				} else if(bodyClass.startsWith("oauth write")) {
					/*
					 * Two cases :
					 * - oauth_callback="oob" and a <div id="oauth_pin"> tag exists :
					 *   Reyn Tweets is authorized and the verifier is a PIN code.
					 * - Otherwise, credentials were wrong.
					 */
					if (oauthManager.getCallbackUrl() == "oob") {
						// Looking for the <div id="oauth_pin"> HTML tag
						QWebElementCollection divs = body.findAll("div");
						QWebElement oauthPinDiv;

						for (QWebElementCollection::iterator it = divs.begin();
							 it != divs.end() && oauthPinDiv.isNull();
							 ++it)
						{
							QWebElement div = *it;

							if (div.attribute("id") == "oauth_pin") {
								oauthPinDiv = div;
							}
						}

						if (oauthPinDiv.isNull()) {
							// Credentials were bad.
							treatmentOK = true;
							parseOK = parseOK && treatmentOK;
							parsedResults.insert("rightCredentials", QVariant(false));
						} else {
							// Reyn Tweets is authorized ! :D Let's get the PIN code !
							QWebElement codeTag = oauthPinDiv.findFirst("code");
							treatmentOK = !codeTag.isNull();
							parseOK = parseOK && treatmentOK;

							// Writing the verifier
							if (treatmentOK) {
								oauthManager.setVerifier(codeTag.toPlainText().toAscii());
								parsedResults.insert("denied", QVariant(false));
								parsedResults.insert("rightCredentials", QVariant(true));
							} else {
								errorMsg.append(PostAuthorizeRequester::trUtf8("PIN code (oauth verifier) not found.")).append('\n');
							}
						}
					} else {
						// Credentials were bad.
						treatmentOK = true;
						parsedResults.insert("rightCredentials", QVariant(false));
					}
				} else {
					// Reyn Tweets is authorized if a <div class="happy notice callback"> exists
					QWebElementCollection divs = body.findAll("div");
					QWebElement happyDiv;

					// Looking for the <div class="happy notice callback"> HTML tag
					for (QWebElementCollection::iterator it = divs.begin();
						 it != divs.end() && happyDiv.isNull();
						 ++it)
					{
						QWebElement div = *it;

						if (div.attribute("class") == "happy notice callback") {
							happyDiv = div;
						}
					}

					treatmentOK = !happyDiv.isNull();
					parseOK = parseOK && treatmentOK;

					if (treatmentOK) {
						// Reyn Tweets is authorized ! :D
						parsedResults.insert("denied", QVariant(false));
						parsedResults.insert("rightCredentials", QVariant(true));

						// Retrieving the oauth_token and the oauth_verifier in the URL (GET parameters)
						QString redirectURL = happyDiv.findFirst("a").attribute("href");
						QByteArray oauthParameters = redirectURL.toUtf8().split('?').at(1);

						// Parsing oauthParameters to get oauth_token and the oauth_verifier
						setParsingErrorType(OAUTH_PARSING);
						OAuthParser parser;
						QVariantMap resultMap = parser.parse(oauthParameters, parseOK, errTreatment);
						errorMsg.append(errTreatment);

						QVariant extractedCredential;

						// Extracting the "oauth_token" parameter
						extractedCredential = parser.extractParameter(resultMap,
																	  "oauth_token",
																	  treatmentOK,
																	  errTreatment);
						parseOK = parseOK && treatmentOK;
						errorMsg.append(errTreatment);
						oauthManager.setOAuthToken(extractedCredential.toByteArray());

						// Extracting the "oauth_verifier" parameter
						extractedCredential = parser.extractParameter(resultMap,
																	  "oauth_verifier",
																	  treatmentOK,
																	  errTreatment);
						parseOK = parseOK && treatmentOK;
						errorMsg.append(errTreatment);
						oauthManager.setVerifier(extractedCredential.toByteArray());
					} else {
						// Error according to the observations done for the process
						errorMsg.append(PostAuthorizeRequester::trUtf8("&lt;div class=\"happy notice callback\"&gt; HTML tag expected."))
								.append('\n');
					}
				}
			} else {
				errorMsg.append(PostAuthorizeRequester::trUtf8("Empty HTML page."))
						.append('\n');
			}
		} else {
			errorMsg.append(PostAuthorizeRequester::trUtf8("HTML parsing failed."))
					.append('\n');
		}
	} else {
		errorMsg.append(PostAuthorizeRequester::trUtf8("Wrong URL."))
				.append('\n');
	}


	// There was a problem while parsing -> fill the parsingErrors map !
	if (!parseOK) {
		parsingErrors.insert("errorMsg", QVariant(errorMsg));
	}

	return QVariant(parsedResults);
}
