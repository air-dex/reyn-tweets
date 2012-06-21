/// @file processutils.cpp
/// @brief Useful methods for processes (implementation).
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

#include "processutils.hpp"

/////////////////////////////
// Building ProcessResults //
/////////////////////////////

ProcessResult ProcessUtils::buildProcessResult(bool processOK,
											   CoreResult issue,
											   QString errMsg,
											   bool isFatal)
{
	ProcessResult processResult;

	processResult.processOK = processOK;
	processResult.processIssue = issue;
	processResult.errorMsg = errMsg;
	processResult.fatalError = isFatal;
	processResult.results = QVariant();

	return processResult;
}

ProcessResult ProcessUtils::buildProcessResult(CoreResult issue, QVariant result) {
	ProcessResult processResult;

	processResult.processOK = true;
	processResult.processIssue = issue;
	processResult.errorMsg = "";
	processResult.fatalError = false;
	processResult.results = result;

	return processResult;
}


//////////////////////////////////////
// Treating Twitter request results //
//////////////////////////////////////

// For Twitter errors
void ProcessUtils::treatTwitterErrorResult(RequestResult result,
										   QString & errorMsg,
										   CoreResult & issue)
{
	int httpCode = result.httpResponse.code;

	// Looking for specific value of the return code
	if (httpCode / 100 == 5) {
		issue = TWITTER_DOWN;
		errorMsg = QObject::trUtf8("Twitter seems down:");
	} else switch(httpCode) {
		case 304:
			issue = NO_MORE_DATA;
			errorMsg = QObject::trUtf8("Twitter do not return new datas:");
			break;

		case 400:
			issue = BAD_REQUEST;
			errorMsg = QObject::trUtf8("Your request was invalid:");
			break;

		case 401:
			issue = TOKENS_NOT_AUTHORIZED;
			errorMsg = QObject::trUtf8("Tokens were not authorized:");
			break;

		case 403:
			issue = REFUSED_REQUEST;
			errorMsg = QObject::trUtf8("Twitter refuses to treat your request:");
			break;

		case 404:
			issue = RESOURCE_NOT_FOUND;
			errorMsg = QObject::trUtf8("There is something invalid in your request:");
			break;

		case 406:
			issue = INVALID_SEARCH;
			errorMsg = QObject::trUtf8("Your research was invalid:");
			break;

		case 420:
			issue = RATE_LIMITED;
			errorMsg = QObject::trUtf8("You reach the authentication rate:");
			break;

		default:
			issue = UNKNOWN_PROBLEM;
			errorMsg = QObject::trUtf8("Unexpected result:");
			break;
	}

	// Building error message
	errorMsg.append('\n')
			.append(writeTwitterErrors(result.serviceErrors));
}

QString ProcessUtils::writeTwitterErrors(QList<ResponseInfos> twitterErrors) {
	// Uncomment when the following feature is deployed :
	// https://dev.twitter.com/blog/making-api-responses-match-request-content-type

		/*
	// Building error message
	QString errorMsg = QObject::trUtf8("Twitter errors:");
	errorMsg.append('\n');

	for (QList<ResponseInfos>::Iterator it = twitterErrors.begin();
		 it < twitterErrors.end();
		 ++it)
	{
		errorMsg.append(QObject::trUtf8("Error "))
				.append(QString::number(it->code))
				.append(" : ")
				.append(it->message)
				.append(".\n");
	}

	// Erasing the last '\n'
	errorMsg.chop(1);
	//*/

	QString errorMsg = QObject::trUtf8("Error ");
	errorMsg.append(QString::number(twitterErrors.at(0).code))
			.append(" : ")
			.append(twitterErrors.at(0).message)
			.append(".\n")
			.append(QObject::trUtf8("Request : "))
			.append(twitterErrors.at(1).message)
			.append('.');

	return errorMsg;
}

// For Twitter API callings
void ProcessUtils::treatApiCallResult(RequestResult result,
									  QString & errorMsg,
									  CoreResult & issue)
{
	// Building error message
	errorMsg = QObject::trUtf8("Network error ");
	errorMsg.append(QString::number(result.httpResponse.code));

	if (!result.httpResponse.message.isEmpty()) {
		errorMsg.append(" (")
				.append(result.httpResponse.message)
				.append(")");
	}

	errorMsg.append(result.httpResponse.message)
			.append(" : ")
			.append(result.errorMessage)
			.append('.');

	issue = NETWORK_CALL;
}

// For unparsable JSON results
void ProcessUtils::treatQjsonParsingResult(ResponseInfos parsingErrors,
										   QString & errorMsg,
										   CoreResult & issue)
{
	// Building error message
	errorMsg = QObject::trUtf8("Parsing error:");
	errorMsg.append('\n')
			.append(QObject::trUtf8("Line "))
			.append(QString::number(parsingErrors.code))
			.append(" : ")
			.append(parsingErrors.message);

	issue = PARSE_ERROR;
}

// For unparsable XML results
void ProcessUtils::treatXMLParsingResult(ResponseInfos parsingErrors,
										 QString & errorMsg,
										 CoreResult & issue)
{
	// Building error message
	errorMsg = QObject::trUtf8("Parsing error:");
	errorMsg.append('\n')
			.append(QObject::trUtf8("Line "))
			.append(QString::number(parsingErrors.code))
			.append(" , ")
			.append(QObject::trUtf8("Column "))
			.append(QString::number(parsingErrors.code))
			.append(" : ")
			.append(parsingErrors.message);

	issue = PARSE_ERROR;
}

// For unparsable OAuth results
void ProcessUtils::treatOAuthParsingResult(QString parsingErrorsMsg,
										   QString & errorMsg,
										   CoreResult & issue)
{
	// Building error message
	errorMsg = QObject::trUtf8("Parsing error:");
	errorMsg.append('\n')
			.append(parsingErrorsMsg);
	issue = PARSE_ERROR;
}

// For unknown treatments
void ProcessUtils::treatUnknownResult(QString resultErrorMessage,
									  QString &errorMsg,
									  CoreResult &issue,
									  bool &fatal)
{
	// Unexpected problem. Abort.
	errorMsg = QObject::trUtf8("Unexpected problem:");
	errorMsg.append('\n').append(resultErrorMessage).append('.');
	fatal = true;
	issue = UNKNOWN_PROBLEM;
}
