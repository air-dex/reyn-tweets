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
#include "../../tools/parsers/jsonparser.hpp"

// Constructor
TwitterRequester::TwitterRequester(RequestType type,
								   QString url,
								   OAuthManager &authManager,
								   ErrorType parseError,
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
QVariant TwitterRequester::parseResult(bool & parseOK, QVariantMap & parsingErrors) {
	JSONParser parser;
	QByteArray rawResponse = weblink.getResponseBuffer();
	QString errorMsg;
	int lineMsg;

	// Special treatment for lists because of a QJSON bug while parsing lists
	bool isList = rawResponse.startsWith('[');

	// Bugfixer : the list to parse is the "reslist" value of a JSON object.
	if (isList) {
		rawResponse.prepend("{\"reslist\":");
		rawResponse.append('}');
	}

	QVariant result = parser.parse(rawResponse, parseOK, errorMsg, &lineMsg);

	if (!parseOK) {
		// There was a problem while parsing -> fill the parsingErrors map !
		parsingErrors.insert("errorMsg", QVariant(errorMsg));
		parsingErrors.insert("lineError", QVariant(lineMsg));
	}

	// Retrieveing the list to parse
	if (isList) {
		result = QVariant(result.toMap().value("reslist"));
	}

	return result;
}

// Treating parsed results
void TwitterRequester::treatParsedResult() {
	int httpReturnCode = weblink.getHttpResponse().code;

	// Is it a map with error messages
	switch (httpReturnCode) {
		case 200:
			break;

		// Uncomment when the following feature is deployed :
		// https://dev.twitter.com/blog/making-api-responses-match-request-content-type
		case 404:
		case 500:
		case 503:
			if (parsingErrorType == QJSON_PARSING
					&& requestResult.parsedResult.type() == QVariant::Map
				)
			{
				// Table error : one row ("errors"; QVariantList)
				QVariantMap resultMap = requestResult.parsedResult.toMap();

				if (resultMap.size() == 1
						&& resultMap.contains("errors")
						&& resultMap.value("errors").type() == QVariant::List
					)
				{
					QVariantList errorList = resultMap.value("errors").toList();

					// Building the list of errors
					for (QVariantList::Iterator it = errorList.begin();
						 it != errorList.end();
						 ++it)
					{
						QVariantMap error = it->toMap();
						ResponseInfos twitterError;
						twitterError.code = error.value("code").toInt();
						twitterError.message = error.value("message").toString();
						requestResult.serviceErrors.append(twitterError);
					}

					requestResult.resultType = SERVICE_ERRORS;
				}
			}
			break;

		case 304:
		case 400:
		case 401:
		case 403:
		case 406:
		case 420:
		case 502:
			if (parsingErrorType == QJSON_PARSING
					&& requestResult.parsedResult.type() == QVariant::Map
				)
			{
				// Table error : two rows called "error" and "request"
				QVariantMap resultMap = requestResult.parsedResult.toMap();

				if (resultMap.size() == 2
						&& resultMap.contains("error")
						&& resultMap.contains("request")
					)
				{
					ResponseInfos twitterError;
					twitterError.code = httpReturnCode;

					twitterError.message = TwitterRequester::trUtf8("Error in request ");
					twitterError.message.append(resultMap.value("request").toString());
					twitterError.message.append(" : ");
					twitterError.message.append(resultMap.value("error").toString());
					twitterError.message.append('.');

					requestResult.serviceErrors.append(twitterError);

					requestResult.resultType = SERVICE_ERRORS;
				}
			}
			break;

		default:
			requestResult.resultType = API_CALL;
			break;
	}
}
