/// @file genericrequester.cpp
/// @brief Code of the GenericRequest class
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
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "genericrequester.hpp"
#include "../parsers/jsonparser.hpp"

// Constructor. It just calls the parent constructor.
GenericRequester::GenericRequester(QObject * requester,
								   RequestType type,
								   QString url,
								   ErrorType parseError) :
	QObject(requester),
	uuid(QUuid::createUuid()),
	requestURL(url),
	requestType(type),
	getParameters(),
	postParameters(),
	communicator(0),
	parsingErrorType(parseError),
	requestResult()
{}


// Destructor
GenericRequester::~GenericRequester() {
	// Deleting the communicator
	if (communicator != 0) {
		delete communicator;
		communicator = 0;
	}
}


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


///////////////////////////
// Executing the request //
///////////////////////////

// Building GET Parameters
void GenericRequester::buildGETParameters() {}

// Bbuilding POST Parameters
void GenericRequester::buildPOSTParameters() {}

// Initialize the communicator.
void GenericRequester::initCommunicator() {
	communicator = new TwitterCommunicator(this,
										   requestURL,
										   requestType,
										   getParameters,
										   postParameters,
										   false);
	connect(communicator, SIGNAL(requestDone(bool)),
			this, SLOT(treatResults(bool)));
}

// Executing the request
void GenericRequester::executeRequest() {
	buildGETParameters();
	buildPOSTParameters();
	initCommunicator();
	communicator->executeRequest();
}


//////////////////////////
// Treatment of results //
//////////////////////////

// Slot executed when the Twitter Communicator has just finished its work.
void GenericRequester::treatResults(bool requestOK) {
	ErrorType errorType;
	QVariant parsedResults;
	QVariantMap parsingErrorInfos;

	if (requestOK) {
		bool parseOK;
		parsedResults = this->parseResult(parseOK, parsingErrorInfos);
		errorType = parseOK ? NO_ERROR : parsingErrorType;
	} else {
		errorType = API_CALL;
	}

	fillParsedResult(errorType, parsedResults, parsingErrorInfos);

	// Telling the ReynTwitterAPI that the request is finished
	emit requestDone();
}

// Method that will parse the raw results of the request.
QVariant GenericRequester::parseResult(bool & parseOK, QVariantMap & parsingErrors) {
	JSONParser parser;
	QByteArray rawResponse = communicator->getResponseBuffer();
	QString errorMsg;
	int lineMsg;
	QVariantMap result = parser.parse(rawResponse, parseOK, errorMsg, &lineMsg);

	if (!parseOK) {
		// There was a problem while parsing -> fill the parsingErrors map !
		parsingErrors.insert("errorMsg", QVariant(errorMsg));
		parsingErrors.insert("lineError", QVariant(lineMsg));
	}

	return QVariant(result);
}

// Filling parsedResult
void GenericRequester::fillParsedResult(ErrorType errorType,
										QVariant parsedResults,
										QVariantMap parsingErrors) {
	requestResult = RequestResult(errorType,
								  parsedResults,
								  communicator->getHttpCode(),
								  communicator->getHttpReason(),
								  communicator->getNetworkError(),
								  parsingErrors,
								  communicator->getErrorMessage());
}
