/// @file twitterrequester.cpp
/// @brief Implementation of TwitterRequester
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
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

#include "twitterrequester.hpp"
#include "../../../tools/parsers/jsonparser.hpp"
#include <QJsonObject>
#include <QJsonArray>

// Constructor
TwitterRequester::TwitterRequester(HTTPRequestType type,
								   QString url,
								   OAuthManager &authManager,
								   NetworkResultType parseError,
								   bool tokenNeeded,
								   bool callbackURLNeeded,
								   bool verifierNeeded) :
	GenericRequester(type, url, parseError),
	oauthManager(authManager),
	oauthTokenNeeded(tokenNeeded),
	oauthCallbackUrlNeeded(callbackURLNeeded),
	oauthVerifierNeeded(verifierNeeded)
{}

// Building HTTP Headers
void TwitterRequester::buildHTTPHeaders() {
	// For the Content-Type
	GenericRequester::buildHTTPHeaders();

	// Building the OAuth header
	QByteArray authHeader = oauthManager.getAuthorizationHeader(requestType,
																requestURL,
																getParameters,
																postParameters,
																oauthTokenNeeded,
																oauthCallbackUrlNeeded,
																oauthVerifierNeeded);

	headers.insert("Authorization", authHeader);
}

// Method that will parse the raw results of the request.
QVariant TwitterRequester::parseResult(NetworkResponse results,
									   bool & parseOK,
									   QVariantMap & parsingErrors)
{
	JSONParser parser;
	QByteArray rawResponse = results.getResponseBody();
	QString errorMsg;
	int lineMsg;

	// TODO : improve it because of improved JSONParser
	QVariant result = parser.parse(rawResponse, parseOK, errorMsg, &lineMsg).toVariant();

	if (!parseOK) {
		// There was a problem while parsing -> fill the parsingErrors map !
		parsingErrors.insert("errorMsg", QVariant(errorMsg));
		parsingErrors.insert("lineError", QVariant(lineMsg));
	}

	return result;
}

// Treating parsed results
void TwitterRequester::treatParsedResult(RequestResult & requestResult,
										 NetworkResponse netResponse)
{
	int httpCode = netResponse.getHttpResponse().code;

	// Is the return code expected ?
	switch (httpCode) {
		case 200:
			// If the response code is 200, it is not an error
			return;

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

		default:
			requestResult.resultType = Network::API_CALL;
			break;
	}


	// Does the parsed results contain Twitter errors ?
	bool areTwitterErrors = false;

	// If there were twitter errors, parsed results are aa QJsonObject
	QJsonValue resval = QJsonValue::fromVariant(requestResult.parsedResult);

	if (resval.isObject()) {
		// It is a QJsonObject. Does it contain the "errors" JSON Array ?
		QJsonObject resobj = resval.toObject();
		areTwitterErrors = resobj.value("errors").isArray();
	}

	// Treat if bad

	if (!areTwitterErrors) {
		return;
	}

	requestResult.resultType = Network::SERVICE_ERRORS;

	// Filling the service errors
	QJsonArray twitterErrors = resval.toObject().value("errors").toArray();

	for (QJsonArray::Iterator it = twitterErrors.begin();
		 it != twitterErrors.end();
		 ++it)
	{
		QJsonValue twitterError = *it;

		if (twitterError.isObject()) {
			QJsonObject twError = twitterError.toObject();
			ResponseInfos resError;
			resError.code = int(twError.value("code").toDouble());
			resError.message = twError.value("message").toString();

			requestResult.serviceErrors.append(resError);
		}
	}
}
