/// @file unfavoriteprocess.cpp
/// @brief Implementation of UnfavoriteProcess
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

#include "unfavoriteprocess.hpp"

UnfavoriteProcess::UnfavoriteProcess(qlonglong id) :
	GenericProcess(),
	twitter(this),
	tweetID(id)
{
}

// Start the process calling twitter to favorite the tweet
void UnfavoriteProcess::startProcess() {
	unfavoriteTweet();
}

// Entry point of the process
void UnfavoriteProcess::unfavoriteTweet() {
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(unfavoriteEnded(ResultWrapper)));

	twitter.unfavoriteTweet(tweetID);
}

// Slot executing after favoriting the tweet
void UnfavoriteProcess::unfavoriteEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == INVALID_RESULT) {
		return;
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(favoriteEnded(ResultWrapper)));

	ErrorType errorType = result.resultType;

	// For a potenitial anticipated end
	int httpCode = result.httpResponse.code;
	QString errorMsg = "";
	bool isFatal = false;
	CoreResult issue;

	// Analysing the Twitter response
	switch (errorType) {
		case NO_ERROR: {
			// The tweet was favorited
			QVariantMap resultMap = result.parsedResult.toMap();

			// No need to convert resultMap into a Tweet to convert it back just after.
			buildResult(true, FAVORITE_SUCCESSFUL, "", false, resultMap);
			emit processEnded();
		} return;

		case TWITTER_ERRORS:
			// Looking for specific value of the return code
			if (httpCode / 100 == 5) {
				issue = TWITTER_DOWN;
				errorMsg = UnfavoriteProcess::trUtf8("Twitter seems down:");
			} else if (httpCode == 401) {
				issue = TOKENS_NOT_AUTHORIZED;
				errorMsg = UnfavoriteProcess::trUtf8("Tokens were not authorized:");
			} else if (httpCode == 420) {
				issue = RATE_LIMITED;
				errorMsg = UnfavoriteProcess::trUtf8("You reach the authentication rate:");
			} else {
				issue = UNKNOWN_PROBLEM;
				errorMsg = UnfavoriteProcess::trUtf8("Unexpected result:");
			}

			// Building error message
			errorMsg.append('\n')
					.append(UnfavoriteProcess::trUtf8("Twitter errors:"));

			for (QList<ResponseInfos>::Iterator it = result.twitterErrors.begin();
				 it < result.twitterErrors.end();
				 ++it)
			{
				errorMsg.append(UnfavoriteProcess::trUtf8("Error "))
						.append(QString::number(it->code))
						.append(" : ")
						.append(it->message)
						.append(".\n");
			}

			// Erasing the last '\n'
			errorMsg.chop(1);
			break;

		case API_CALL:
			// Building error message
			errorMsg = UnfavoriteProcess::trUtf8("Network error ");
			errorMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(result.httpResponse.message)
					.append(" :\n")
					.append(result.errorMessage)
					.append('.');

			// Looking for specific value of the return code
			issue = NETWORK_CALL;
			break;

		case QJSON_PARSING:
			// Building error message
			errorMsg = UnfavoriteProcess::trUtf8("Parsing error:");
			errorMsg.append('\n')
					.append(UnfavoriteProcess::trUtf8("Line "))
					.append(QString::number(result.parsingErrors.code))
					.append(" : ")
					.append(result.parsingErrors.message);
			issue = PARSE_ERROR;
			break;

		default:
			// Unexpected problem. Abort.
			errorMsg = UnfavoriteProcess::trUtf8("Unexpected problem:");
			errorMsg.append('\n').append(result.errorMessage).append('.');
			isFatal = true;
			issue = UNKNOWN_PROBLEM;
			break;
	}

	// Failed end
	buildResult(false, issue, errorMsg, isFatal);
	emit processEnded();
}

// Building the process results
void UnfavoriteProcess::buildResult(bool processOK,
									CoreResult issue,
									QString errMsg,
									bool isFatal,
									QVariantMap tweetMap)
{
	processResult.processOK = processOK;
	processResult.processIssue = issue;
	processResult.errorMsg = errMsg;
	processResult.fatalError = isFatal;
	processResult.results = tweetMap;
}

