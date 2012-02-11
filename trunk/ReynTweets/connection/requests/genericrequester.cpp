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
#include "../../tools/parsers/jsonparser.hpp"

// Constructor. It just calls the parent constructor.
GenericRequester::GenericRequester(RequestType type,
								   QString url,
								   ErrorType parseError) :
	QObject(),
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

// Setting parsingErrorType
void GenericRequester::setParsingErrorType(ErrorType parseErrorType) {
	parsingErrorType = parseErrorType;
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
	communicator = new TwitterCommunicator(requestURL,
										   requestType,
										   getParameters,
										   postParameters,
										   false);
	connect(communicator, SIGNAL(requestDone()),
			this, SLOT(treatResults()));
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
void GenericRequester::treatResults() {
	// On regarde la réponse HTTP. Si défaut => API_CALL
	requestResult.httpResponse = communicator->getHttpResponse();
	requestResult.errorMessage = communicator->getErrorMessage();

	int httpReturnCode = communicator->getHttpResponse().code;

	if (httpReturnCode == 0) {
		requestResult.resultType = API_CALL;
	} else {
		// Sinon on parse
		bool parseOK;
		QVariantMap parseErrorMap;
		requestResult.parsedResult = this->parseResult(parseOK, parseErrorMap);
		requestResult.resultType = parseOK ? NO_ERROR : parsingErrorType;
		requestResult.parsingErrors.code = parseErrorMap.value("lineError").toInt();
		requestResult.parsingErrors.message = parseErrorMap.value("errorMsg").toString();

		// Analyse the response (if it is a table from JSON with errors => FAIL)
		if (parseOK
				&& parsingErrorType == QJSON_PARSING
				&& requestResult.parsedResult.type() == QVariant::Map
			)
		{
			// Table error : one row ("errors"; QVariantList)
			QVariantMap resultMap = requestResult.parsedResult.toMap();

			if (resultMap.size() == 1
					&& resultMap.contains(("errors"))
					&& resultMap.value("errors").type() == QVariant::List
				)
			{
				QVariantList errorList = resultMap.value("errors");

				// Building the list of errors
				for (QVariantList::Iterator it = errorList.begin();
					 it != errorList.end();
					 ++it)
				{
					QVariantMap error = it->toMap();
					ResponseInfos twitterError;
					twitterError.code = error.value("code").toInt();
					twitterError.message = error.value("message").toString();
					requestResult.twitterErrors.append(twitterError);
				}

				requestResult.resultType = TWITTER_ERRORS;
			}
		} else {
			requestResult.parsedResult = QVariant::fromValue(communicator->getResponseBuffer());
		}
	}

	// Telling the ReynTwitterCalls that the request is finished
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
