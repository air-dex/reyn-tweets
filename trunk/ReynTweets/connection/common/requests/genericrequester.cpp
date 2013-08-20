/// @file genericrequester.cpp
/// @brief Implementation of GenericRequester
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

#include "genericrequester.hpp"
#include "../utils/parsers/jsonparser.hpp"
#include "../utils/librtconstants.hpp"

// Constructor. It just calls the parent constructor.
GenericRequester::GenericRequester(LibRT::HTTPRequestType type,
								   QString url,
								   LibRT::NetworkResultType parseError) :
	QObject(),
	uuid(QUuid::createUuid()),
	requestURL(url),
	requestType(type),
	getParameters(),
	postParameters(),
	headers(),
	weblink(requestURL, requestType, getParameters, postParameters, headers),
	parsingErrorType(parseError)
{}


// Destructor
GenericRequester::~GenericRequester() {}


/////////////
// Getters //
/////////////

// Getter on the requester's UUID
QUuid GenericRequester::getUuid() {
	return uuid;
}

// Setting parsingErrorType
void GenericRequester::setParsingErrorType(LibRT::NetworkResultType parseErrorType) {
	parsingErrorType = parseErrorType;
}


///////////////////////////
// Executing the request //
///////////////////////////

// Building GET Parameters
void GenericRequester::buildGETParameters() {}

// Building POST Parameters
void GenericRequester::buildPOSTParameters() {}

// Building HTTP Headers
void GenericRequester::buildHTTPHeaders() {}

// Executing the request
void GenericRequester::executeRequest() {
	buildGETParameters();
	buildPOSTParameters();
	buildHTTPHeaders();

	// Request time !
	connect(&weblink, &TwitterCommunicator::requestDone,
			this, &GenericRequester::treatResults);

	weblink.executeRequest();
}


//////////////////////////
// Treatment of results //
//////////////////////////

// Slot executed when the Twitter Communicator has just finished its work.
void GenericRequester::treatResults(NetworkResponse netResponse) {
	disconnect(&weblink, &TwitterCommunicator::requestDone,
			   this, &GenericRequester::treatResults);

	RequestResult requestResult;

	// Looking the HTTP request
	ResponseInfos netHTTPRep = netResponse.getHttpResponse();
	requestResult.httpResponse = netHTTPRep;
	requestResult.errorMessage = netResponse.getRequestError();

	switch (netHTTPRep.code) {
		case LibRT::INVALID_HTTP_CODE:
			// Invalid response => INVALID_RESULT
			requestResult.resultType = LibRT::INVALID_RESULT;
			break;

		case LibRT::TIMEOUT_HTTP_CODE:
			// No response (because of timeout) => API_CALL
			requestResult.resultType = LibRT::API_CALL;
			break;

		default: {
			// Parsing the response and filling requestResult
			bool parseOK;
			QVariantMap parseErrorMap;
			requestResult.parsedResult = this->parseResult(netResponse,
														   parseOK,
														   parseErrorMap);
			requestResult.parsingErrors.code = parseErrorMap.value("lineError").toInt();
			requestResult.parsingErrors.message = parseErrorMap.value("errorMsg").toString();

			if (parseOK) {
				// Other treatments related to the service
				requestResult.serviceErrors = this->treatServiceErrors(requestResult.parsedResult,
																	   netResponse);
				// Updating the NetworkResultType with service errors
				requestResult.resultType = requestResult.serviceErrors.isEmpty() ?
							LibRT::NO_REQUEST_ERROR
						  : LibRT::SERVICE_ERRORS;
			} else {
				requestResult.resultType = parsingErrorType;

				// Giving the response just in case the user would like to do sthg with it.
				requestResult.parsedResult = QVariant::fromValue(netResponse.getResponseBody());
			}
		} break;
	}

	// Telling the Calls that the request is finished
	emit requestDone(requestResult);
}
