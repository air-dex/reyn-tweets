/// @file requestresult.cpp
/// @brief Implementation of RequestResult
///
/// Revisions older than r242 were in /trunk/ReynTweets/connection
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
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#include "requestresult.hpp"

// Default constructor
RequestResult::RequestResult() :
	resultType(INVALID_RESULT),
	parsedResult(),
	httpCode(),
	httpReason(),
	parsingErrors(),
	errorMessage("Invalid result")
{}

// Constructor
RequestResult::RequestResult(ErrorType errorType,
							 QVariant parsedResults,
							 int httpReturnCode,
							 QString httpReturnReason,
							 QVariantMap parsingErrorInfos,
							 QString errorMsg) :
	resultType(errorType),
	parsedResult(parsedResults),
	httpCode(httpReturnCode),
	httpReason(httpReturnReason),
	parsingErrors(parsingErrorInfos),
	errorMessage(errorMsg)
{}

// Method indicating if the request was successful
bool RequestResult::isRequestSuccessful() {
	return resultType == NO_ERROR;
}

// Method indicating if the request result is fake
bool RequestResult::isFakeResult() {
	return resultType == INVALID_RESULT;
}

// Getter of requestSuccessful
ErrorType RequestResult::getErrorType() {
	return resultType;
}

// Getter on real results
QVariant RequestResult::getParsedResult() {
	return parsedResult;
}

// Getter on httpCode
int RequestResult::getHttpCode() {
	return httpCode;
}

// Getter on httpReason
QString RequestResult::getHttpReason() {
	return httpReason;
}

// Getter on the parsing error message
QString RequestResult::getParsingErrorMessage() {
	return parsingErrors.value("errorMsg").toString();
}

// Getter on parsingErrors
QVariantMap RequestResult::getParsingErrors() {
	return parsingErrors;
}

// Getter on the error massage
QString RequestResult::getErrorMessage() {
	return errorMessage;
}
