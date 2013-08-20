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

#include "authorizerequester.hpp"

#include <QDomElement>
#include "../../../common/utils/parsers/xmlparser.hpp"
#include "../../../common/utils/connectionutils.hpp"

// Constructor
AuthorizeRequester::AuthorizeRequester(TwitterAuthenticator &authManager, bool forceLog, QString writeLogin) :
	OAuthRequester(LibRT::GET,
				   Twitter::AUTHORIZE_URL,
				   authManager,
				   LibRT::NO_PARSING),	// Change because of pbms ?
	forceLogin(forceLog),
	screenName(writeLogin)
{}

// Building GET Parameters
void AuthorizeRequester::buildGETParameters() {
	getParameters.insert("oauth_token",
						 QString::fromLatin1(oauthManager.getOAuthToken().data()));

	getParameters.insert("force_login", boolInString(forceLogin));

	if (!screenName.isEmpty()) {
		getParameters.insert("screen_name", screenName);
	}
}

// Parsing results
QVariant AuthorizeRequester::parseResult(NetworkResponse results,
										 bool &parseOK,
										 QVariantMap &parsingErrors)
{
	parsingErrors = QVariantMap();

	// Look at the return code
	if (results.getHttpResponse().code == 200) {
		// It's the HTML page. Send back its code
		QVariantMap resmap;
		resmap.insert("html", QVariant::fromValue(results.getResponseBody()));
		resmap.insert("reply_url", QVariant::fromValue(results.getReplyURL()));
		parseOK = true;
		return QVariant::fromValue(resmap);
	} else {
		// Send an XML error message. Let's get it !
		parsingErrorType = LibRT::XML_PARSING;

		XMLParser parser;
		QString parseErr;
		bool parseOK;
		int lineErr, colErr;

		QDomElement parsedError = parser.parse(results.getResponseBody(),
											   &parseOK,
											   &parseErr,
											   &lineErr,
											   &colErr);

		if (!parseOK) {
			parsingErrors.insert("errorMsg", parseErr);
			parsingErrors.insert("lineError", QVariant::fromValue(lineErr));
			parsingErrors.insert("columnError", QVariant::fromValue(colErr));
		}

		if (parsedError.tagName() != "hash") {
			return QVariant();
		}

		QVariantMap parsedResults;

		for (QDomElement elt = parsedError.firstChildElement();
			 !elt.isNull();
			 elt = elt.nextSiblingElement())
		{
			parsedResults.insert(elt.tagName(), elt.text());
		}

		return QVariant::fromValue(parsedResults);
	}
}

QList<ResponseInfos> AuthorizeRequester::treatServiceErrors(QVariant parsedResults,
															NetworkResponse netResponse)
{
	QList<ResponseInfos> serviceErrors;

	int httpCode = netResponse.getHttpResponse().code;

	// Is the return code expected ?
	switch (httpCode) {
		case 200:
			// If the response code is 200, it is not an error
			return QList<ResponseInfos>();

		// Expected return codes
		case 304:
		case 400:
		case 401:
		case 403:
		case 404:
		case 406:
		case 410:
		case 420:
		case 422:
		case 429:
		case 500:
		case 502:
		case 503:
		case 504:
			break;

		// Unexpected return code
		default: {
			ResponseInfos error;
			error.code = httpCode;
			error.message = TwitterRequester::trUtf8("Unexpected HTTP return code")
					.append(" '")
					.append(QString::number(httpCode))
					.append("'.");

			serviceErrors.append(error);
		} break;
	}

	// Error due to code

	// Does the parsed results contain Twitter errors ?
	bool areTwitterErrors = false;
	QVariantMap errmap;

	// Twitter error : 2 fields : "error" and "request" in a QVariantMap

	if (parsedResults.canConvert<QVariantMap>()) {
		errmap = parsedResults.toMap();

		areTwitterErrors = errmap.contains("error") && errmap.contains("request");
	}

	if (areTwitterErrors) {
		ResponseInfos error;
		error.code = httpCode;
		error.message = AuthorizeRequester::trUtf8("Error during the request ")
				.append("https://api.twitter.com")
				.append(errmap.value("request").toString())
				.append(" : ")
				.append(errmap.value("error").toString())
				.append('.');

		serviceErrors.append(error);
	}

	return serviceErrors;
}
