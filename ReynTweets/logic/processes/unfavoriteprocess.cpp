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
	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(unfavoriteEnded(ResultWrapper)));

	RequestResult result = res.accessResult(this);

	int httpCode = result.getHttpCode();

	CoreResult issue;
	QString errMsg = "";
	bool isFatal = false;

	switch (httpCode) {
		case 200:
			// No problem during the request
			switch (result.getErrorMessage()) {
				case NO_ERROR: {
					// The tweet was favorited
					QVariantMap resultMap = result.getParsedResult().toMap();

					// No need to convert resultMap into a Tweet to convert it back just after.
					buildResult(true, FAVORITE_SUCCESSFUL, "", false, resultMap);
					emit processEnded();
				} return;

				case QJSON_PARSING:
					// Parsing error
					issue = PARSE_ERROR;
					errMsg = FavoriteProcess::trUtf8("Error while parsing request results.");
					break;

				default:
					issue = UNKNOWN_PROBLEM;
					errMsg = FavoriteProcess::trUtf8("Unexpected result.");
					isFatal = true;
					break;
			}
			break;

		case 401:
			// Credentials were wrong
			issue = TOKENS_NOT_AUTHORIZED;
			errMsg = FavoriteProcess::trUtf8("Tokens were not authorized.");
			break;

		case 420:
			// Rate limited
			issue = RATE_LIMITED;
			errMsg = FavoriteProcess::trUtf8("You reach the authentication rate.");
			break;

		default:
			// Return == 5xx -> Twitter problem. Unknown problem otherwise.
			if (httpCode / 100 == 5) {
				issue = TWITTER_DOWN;
				errMsg = FavoriteProcess::trUtf8("Twitter seems down.");
			} else {
				issue = UNKNOWN_PROBLEM;
				errMsg = FavoriteProcess::trUtf8("Unknown problem.");
				isFatal = true;
			}
			break;
	}

	// Failed end
	buildResult(false, issue, "", isFatal, resultMap);
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

