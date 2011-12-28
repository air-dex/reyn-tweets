/// @file requestresult.hpp
/// @brief Header of RequestResult
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
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#include "requestresult.hpp"

// Default constructor
RequestResult::RequestResult() :
	resultType(INVALID_RESULT),
	parsedResult(),
	httpInfos(),
	parsingErrors()
{}

// Constructor
RequestResult::RequestResult(ErrorType errorType,
							 QVariant parsedResults,
							 int httpCode,
							 QString httpReason,
							 QVariantMap parsingErrorInfos,
							 QString errorMsg) :
	resultType(errorType),
	parsedResult(parsedResults),
	httpInfos(),
	parsingErrors(parsingErrorInfos),
	errorMessage(errorMsg)
{
	// Filling httpInfos
	httpInfos.insert("httpCode", QVariant(httpCode));
	httpInfos.insert("httpReason", QVariant(httpReason));
}

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

// Getter on httpInfos
QVariantMap RequestResult::getHttpInfos() {
	return httpInfos;
}

// Getter on parsingErrors
QVariantMap RequestResult::getParsingErrors() {
	return parsingErrors;
}

// Getter on the error massage
QString RequestResult::getErrorMessage() {
	return errorMessage;
}
