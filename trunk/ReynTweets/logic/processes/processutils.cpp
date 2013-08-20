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

#include <QStringList>

//////////////////////////////////////
// Treating Twitter request results //
//////////////////////////////////////

// For Twitter errors
void ProcessUtils::treatTwitterErrorResult(RequestResult result,
										   QString & errorMsg,
										   ReynTweets::CoreResult & procEnd)
{
	// Looking for specific value of the return code
	procEnd = ReynTweets::getCoreResultFromCode(result.getHTTPCode());
	switch (procEnd) {
		case ReynTweets::NO_MORE_DATA:
			errorMsg = QObject::trUtf8("Twitter do not return new datas:");
			break;

		case ReynTweets::BAD_REQUEST:
			errorMsg = QObject::trUtf8("Your request was invalid:");
			break;

		case ReynTweets::AUTHENTICATION_REQUIRED:
			procEnd = ReynTweets::TOKENS_NOT_AUTHORIZED;
			errorMsg = QObject::trUtf8("Tokens were not authorized:");
			break;

		case ReynTweets::REFUSED_REQUEST:
			errorMsg = QObject::trUtf8("Twitter refuses to treat your request:");
			break;

		case ReynTweets::RESOURCE_NOT_FOUND:
			errorMsg = QObject::trUtf8("There is something invalid in your request:");
			break;

		case ReynTweets::INVALID_SEARCH:
			errorMsg = QObject::trUtf8("Your research was invalid:");
			break;

		case ReynTweets::GONE:
			errorMsg = QObject::trUtf8("This resource is gone:");
			break;

		case ReynTweets::RATE_LIMITED:
			errorMsg = QObject::trUtf8("You reach the authentication rate:");
			break;

		case ReynTweets::UNPROCESSABLE:
			errorMsg = QObject::trUtf8("Your profile banner cannot be processed:");
			break;

		case ReynTweets::TWITTER_DOWN:
			errorMsg = QObject::trUtf8("Twitter seems down:");
			break;

		default:
			// This is an error so a 200 return code is not expected at all.
			procEnd = ReynTweets::UNKNOWN_PROBLEM;
			errorMsg = QObject::trUtf8("Unexpected result:");
			break;
	}

	// Building error message
	errorMsg.append(' ').append(writeTwitterErrors(result));
}

QString ProcessUtils::writeTwitterErrors(RequestResult result) {
	// Building the list of error messages
	QList<ResponseInfos> twitterErrors = result.serviceErrors;
	QStringList errorMsgs;

	if (!result.errorMessage.isEmpty()) {
		errorMsgs.append(result.errorMessage);
	}

	for (QList<ResponseInfos>::Iterator it = twitterErrors.begin();
		 it < twitterErrors.end();
		 ++it)
	{
		QString errorMsg = "";

		errorMsg.append(QObject::trUtf8("Error"))
				.append(' ')
				.append(QString::number(it->code))
				.append(" : ")
				.append(it->message)
				.append(".");

		errorMsgs.append(errorMsg);
	}

	// Build the final message
	QString twitterErrorsMsg = "";

	if (!errorMsgs.isEmpty()) {
		errorMsgs.prepend(QObject::trUtf8("Twitter errors:"));
		twitterErrorsMsg = errorMsgs.join("\n\t - ");
	}

	return twitterErrorsMsg;
}

// For Twitter API callings
void ProcessUtils::treatApiCallResult(RequestResult result,
									  QString & errorMsg,
									  ReynTweets::CoreResult & procEnd)
{
	// Building error message
	errorMsg = "";
	errorMsg.append(QObject::trUtf8("Network error"))
			.append(' ')
			.append(QString::number(result.httpResponse.code));

	if (!result.httpResponse.message.isEmpty()) {
		errorMsg.append(" (")
				.append(result.httpResponse.message)
				.append(")");
	}

	errorMsg.append(" : ")
			.append(result.errorMessage);

	procEnd = ReynTweets::NETWORK_CALL;
}

// For unparsable JSON results
void ProcessUtils::treatQjsonParsingResult(ResponseInfos parsingErrors,
										   QString & errorMsg,
										   ReynTweets::CoreResult & procEnd)
{
	// Building error message
	errorMsg = "";
	errorMsg.append(QObject::trUtf8("Parsing error:"))
			.append(' ')
			.append(QObject::trUtf8("Line"))
			.append(' ')
			.append(QString::number(parsingErrors.code))
			.append(" : ")
			.append(parsingErrors.message);

	procEnd = ReynTweets::PARSE_ERROR;
}

// For unparsable XML results
void ProcessUtils::treatXMLParsingResult(ResponseInfos parsingErrors,
										 QString & errorMsg,
										 ReynTweets::CoreResult & procEnd)
{
	// Building error message
	errorMsg = "";
	errorMsg.append(QObject::trUtf8("Parsing error:"))
			.append('\n')
			.append(QObject::trUtf8("Line"))
			.append(' ')
			.append(QString::number(parsingErrors.code))
			.append(" , ")
			.append(QObject::trUtf8("Column"))
			.append(' ')
			.append(QString::number(parsingErrors.code))
			.append(" : ")
			.append(parsingErrors.message);

	procEnd = ReynTweets::PARSE_ERROR;
}

// For unparsable OAuth results
void ProcessUtils::treatOAuthParsingResult(QString parsingErrorsMsg,
										   QString & errorMsg,
										   ReynTweets::CoreResult & procEnd)
{
	// Building error message
	errorMsg = "";
	errorMsg.append(QObject::trUtf8("Parsing error:"))
			.append(' ')
			.append(parsingErrorsMsg);
	procEnd = ReynTweets::PARSE_ERROR;
}

// For unknown treatments
void ProcessUtils::treatUnknownResult(QString resultErrorMessage,
									  QString &errorMsg,
									  ReynTweets::CoreResult &procEnd)
{
	// Unexpected problem. Abort.
	errorMsg = "";
	errorMsg.append(QObject::trUtf8("Unexpected problem:"))
			.append(' ')
			.append(resultErrorMessage);
	procEnd = ReynTweets::UNKNOWN_PROBLEM;
}
