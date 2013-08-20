/// @file singletwittercallprocess.cpp
/// @brief Implementation of SingleTwitterCallProcess
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

#include "singletwittercallprocess.hpp"
#include "processutils.hpp"

SingleTwitterCallProcess::SingleTwitterCallProcess(ReynTweets::CoreResult rightEnd) :
	GenericProcess(),
	twitter(this),
	successfullEnd(rightEnd)
{}

// Starting the process by calling Twitter
void SingleTwitterCallProcess::startProcess() {
	connect(&twitter, &ReynTwitterCalls::sendResult,
			this, &SingleTwitterCallProcess::callEnded);
	callTwitter();
}

// After calling Twitter
void SingleTwitterCallProcess::callEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);

	if (result.resultType == LibRT::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, &ReynTwitterCalls::sendResult,
			   this, &SingleTwitterCallProcess::callEnded);

	// For a potenitial anticipated end
	QString errorMsg = "";
	ReynTweets::CoreResult procEnd;
	//QVariant res;

	// Analysing the Twitter response
	switch (result.resultType) {
		case LibRT::NO_REQUEST_ERROR:
			/*
			res = result.parsedResult;
			procEnd = successfullEnd;
			break;
			//*/
			return treatSuccessfulResult(result.parsedResult);

		case LibRT::SERVICE_ERRORS:
			treatTwitterErrorResult(result, errorMsg, procEnd);
			break;

		case LibRT::API_CALL:
			treatApiCallResult(result, errorMsg, procEnd);
			break;

		case LibRT::JSON_PARSING:
			treatQjsonParsingResult(result.parsingErrors, errorMsg, procEnd);
			break;

		default:
			treatUnknownResult(result.errorMessage, errorMsg, procEnd);
			break;
	}

	// End of the process
	endProcess(procEnd, /*res,*/ errorMsg);
}

void SingleTwitterCallProcess::treatSuccessfulResult(QVariant result) {
	endProcess(successfullEnd, result);
}

void SingleTwitterCallProcess::treatTwitterErrorResult(RequestResult result,
													   QString & errorMsg,
													   ReynTweets::CoreResult & procEnd)
{
	ProcessUtils::treatTwitterErrorResult(result, errorMsg, procEnd);
}

void SingleTwitterCallProcess::treatApiCallResult(RequestResult result,
												  QString & errorMsg,
												  ReynTweets::CoreResult & procEnd)
{
	ProcessUtils::treatApiCallResult(result, errorMsg, procEnd);
}

void SingleTwitterCallProcess::treatQjsonParsingResult(ResponseInfos parsingErrors,
													   QString & errorMsg,
													   ReynTweets::CoreResult & procEnd)
{
	ProcessUtils::treatQjsonParsingResult(parsingErrors, errorMsg, procEnd);
}

void SingleTwitterCallProcess::treatUnknownResult(QString resultErrorMessage,
												  QString &errorMsg,
												  ReynTweets::CoreResult &procEnd)
{
	ProcessUtils::treatUnknownResult(resultErrorMessage, errorMsg, procEnd);
}
