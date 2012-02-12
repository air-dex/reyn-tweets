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
#include "../../tools/processutils.hpp"

SingleTwitterCallProcess::SingleTwitterCallProcess(CoreResult rightIssue) :
	GenericProcess(),
	twitter(this),
	successfullIssue(rightIssue)
{}

void SingleTwitterCallProcess::startProcess() {
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(callEnded(ResultWrapper)));
	callTwitter();
}

void SingleTwitterCallProcess::callEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == INVALID_RESULT) {
		return;
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(callEnded(ResultWrapper)));

	ErrorType errorType = result.resultType;

	// For a potenitial anticipated end
	QString errorMsg = "";
	bool isFatal = false;
	CoreResult issue;

	// Analysing the Twitter response
	switch (errorType) {
		case NO_ERROR:
			return treatSuccessfulResult(result.parsedResult);

		case TWITTER_ERRORS:
			treatTwitterErrorResult(result, errorMsg, issue);
			break;

		case API_CALL:
			treatApiCallResult(result, errorMsg, issue);
			break;

		case QJSON_PARSING:
			treatQjsonParsingResult(result.parsingErrors, errorMsg, issue);
			break;

		default:
			treatUnknownResult(result.errorMessage, errorMsg, issue, isFatal);
			break;
	}

	// Failed end
	buildResult(false, issue, errorMsg, isFatal);
	emit processEnded();
}

// Building the process results
void SingleTwitterCallProcess::buildResult(bool processOK,
										   CoreResult issue,
										   QString errMsg,
										   bool isFatal)
{
	processResult = ProcessUtils::buildProcessResult(processOK,
													 issue,
													 errMsg,
													 isFatal);
}

// Building the process results
void SingleTwitterCallProcess::buildResult(QVariant result) {
	processResult = ProcessUtils::buildProcessResult(successfullIssue, result);
}

void SingleTwitterCallProcess::treatSuccessfulResult(QVariant result) {
	buildResult(result);
	emit processEnded();
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
												  CoreResult &issue,
												  bool &fatal)
{
	ProcessUtils::treatUnknownResult(resultErrorMessage, errorMsg, issue, fatal);
}
