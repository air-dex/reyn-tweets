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
#include "../../../tools/parsers/jsonparser.hpp"

// Constructor. It just calls the parent constructor.
GenericRequester::GenericRequester(HTTPRequestType type,
								   QString url,
								   NetworkResultType parseError) :
	QObject(),
	uuid(QUuid::createUuid()),
	requestURL(url),
	requestType(type),
	getParameters(),
	postParameters(),
	headers(),
	weblink(requestURL, requestType, getParameters, postParameters, headers),
	parsingErrorType(parseError),
	requestResult()
{}


// Destructor
GenericRequester::~GenericRequester() {}


/////////////
// Getters //
/////////////

// Getting parsed results
RequestResult GenericRequester::getRequestResult() {
	return requestResult;
}

// Getter on the requester's UUID
QUuid GenericRequester::getUuid() {
	return uuid;
}

// Setting parsingErrorType
void GenericRequester::setParsingErrorType(NetworkResultType parseErrorType) {
	parsingErrorType = parseErrorType;
}


///////////////////////////
// Executing the request //
///////////////////////////

// Building GET Parameters
void GenericRequester::buildGETParameters() {}

// Bbuilding POST Parameters
void GenericRequester::buildPOSTParameters() {}

// Bbuilding HTTP Headers
void GenericRequester::buildHTTPHeaders() {
	// Be careful for update with medias
	//headers.insert("Content-Type", "application/x-www-form-urlencoded");
}

// Executing the request
void GenericRequester::executeRequest() {
	buildGETParameters();
	buildPOSTParameters();
	buildHTTPHeaders();

	// Request time !
	connect(&weblink, SIGNAL(requestDone(NetworkResponse)),
			this, SLOT(treatResults(NetworkResponse)));

	weblink.executeRequest();
}


//////////////////////////
// Treatment of results //
//////////////////////////

// Slot executed when the Twitter Communicator has just finished its work.
void GenericRequester::treatResults(NetworkResponse netResponse) {
	disconnect(&weblink, SIGNAL(requestDone(NetworkResponse)),
			   this, SLOT(treatResults(NetworkResponse)));

	// Looking the HTTP request
	ResponseInfos netHTTPRep = netResponse.getHttpResponse();
	requestResult.httpResponse = netHTTPRep;
	requestResult.errorMessage = netResponse.getRequestError();

	int httpReturnCode = netHTTPRep.code;

	if (httpReturnCode == 0) {
		// No response => API_CALL
		requestResult.resultType = Network::API_CALL;
	} else {
		// A response to parse
		bool parseOK;
		QVariantMap parseErrorMap;
		requestResult.parsedResult = this->parseResult(netResponse,
													   parseOK,
													   parseErrorMap);
		requestResult.resultType = parseOK ? Network::NO_REQUEST_ERROR : parsingErrorType;
		requestResult.parsingErrors.code = parseErrorMap.value("lineError").toInt();
		requestResult.parsingErrors.message = parseErrorMap.value("errorMsg").toString();

		if (!parseOK) {
			// Giving the response just in case the user would like to do sthg with it.
			requestResult.parsedResult = QVariant::fromValue(netResponse.getResponseBody());
		} else {
			this->treatParsedResult();
		}
	}

	// Telling the ReynTwitterCalls that the request is finished
	emit requestDone();
}
