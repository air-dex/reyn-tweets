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

#include <QJson/Parser>
#include "genericrequester.hpp"

// Constructor. It just calls the parent constructor.
GenericRequester::GenericRequester(QObject * requester, QString url) :
	QObject(requester),
	uuid(QUuid::createUuid()),
	requestURL(url),
	getParameters(),
	postParameters(),
	communicator(0),
	requestResult(RequestResult::FAKE_REQUEST_RESULT)
{}


// Destructor
GenericRequester::~GenericRequester() {
	// Deleting the communicator
	if (communicator != 0) {
		delete communicator;
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

void GenericRequester::executeRequest() {
	// Building the ArgsMap
	buildGETParameters();
	buildPOSTParameters();

	// Executing the request
	communicator = new TwitterCommunicator(requestURL,
										   getParameters,
										   postParameters);
	connect(communicator, SIGNAL(requestDone(bool)),
			this, SLOT(treatResults(bool)));
	communicator->executeRequest();
}


//////////////////////////
// Treatment of results //
//////////////////////////

// Slot executed when the Twitter Communicator has just finished its work.
void GenericRequester::treatResults(bool ok) {
	ErrorType errorType;
	QVariant parsedResults;
	QVariantMap parsingErrorInfos;

	if (ok) {
		bool parseOK;
		parsedResults = parseResult(parseOK, parsingErrorInfos);
		errorType = parseOK ? NO_ERROR : QJSON_PARSING;
	} else {
		errorType = API_CALL;
		//treatError();
	}

	fillParsedResult(errorType, parsedResults, parsingErrorInfos);

	// Telling the ReynTwitterAPI that the request is finished
	emit requestDone();
}

// Method that will parse the raw results of the request.
QVariant GenericRequester::parseResult(bool & parseOK, QVariantMap & parsingErrors) {
	QByteArray rawResponse = communicator->getResponseBuffer();

	// Parsing with QJson
	QJson::Parser parser;
	QVariant result = parser.parse(rawResponse, &parseOK);

	if (!parseOK) {
		// There was a problem while parsing -> fill the parsingErrors map !
		QString errorMsg = parser.errorString();
		parsingErrors.insert("errorMsg", QVariant(errorMsg));

		int lineMsg = parser.errorLine();
		parsingErrors.insert("lineError", QVariant(lineMsg));
	}

	return result;
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
								  parsingErrors);
}
