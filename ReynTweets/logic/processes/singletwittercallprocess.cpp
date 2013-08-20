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

SingleTwitterCallProcess::SingleTwitterCallProcess(CoreResult rightIssue) :
	GenericProcess(),
	twitter(this),
	successfullIssue(rightIssue)
{}

// Starting the process by calling Twitter
void SingleTwitterCallProcess::startProcess() {
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(callEnded(ResultWrapper)));
	callTwitter();
}

// After calling Twitter
void SingleTwitterCallProcess::callEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);

	if (result.resultType == Network::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(callEnded(ResultWrapper)));

	NetworkResultType errorType = result.resultType;

	// For a potenitial anticipated end
	QString errorMsg = "";
	CoreResult issue;

	// Analysing the Twitter response
	switch (errorType) {
		case Network::NO_REQUEST_ERROR:
			return treatSuccessfulResult(result.parsedResult);

		case Network::SERVICE_ERRORS:
			treatTwitterErrorResult(result, errorMsg, issue);
			break;

		case Network::API_CALL:
			treatApiCallResult(result, errorMsg, issue);
			break;

		case Network::JSON_PARSING:
			treatQjsonParsingResult(result.parsingErrors, errorMsg, issue);
			break;

		default:
			treatUnknownResult(result.errorMessage, errorMsg, issue);
			break;
	}

	// Failed end
	endProcess(issue, errorMsg);
}

void SingleTwitterCallProcess::treatSuccessfulResult(QVariant result) {
	endProcess(successfullIssue, result);
}

void SingleTwitterCallProcess::treatTwitterErrorResult(RequestResult result,
													   QString & errorMsg,
													   CoreResult & issue)
{
	ProcessUtils::treatTwitterErrorResult(result, errorMsg, issue);
}

void SingleTwitterCallProcess::treatApiCallResult(RequestResult result,
												  QString & errorMsg,
												  CoreResult & issue)
{
	ProcessUtils::treatApiCallResult(result, errorMsg, issue);
}

void SingleTwitterCallProcess::treatQjsonParsingResult(ResponseInfos parsingErrors,
													   QString & errorMsg,
													   CoreResult & issue)
{
	ProcessUtils::treatQjsonParsingResult(parsingErrors, errorMsg, issue);
}

void SingleTwitterCallProcess::treatUnknownResult(QString resultErrorMessage,
												  QString &errorMsg,
												  CoreResult &issue)
{
	ProcessUtils::treatUnknownResult(resultErrorMessage, errorMsg, issue);
}
