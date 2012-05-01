/// @file deletetweetprocess.cpp
/// @brief Implementation of DeleteTweetProcess
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

#include "deletetweetprocess.hpp"
#include "../../tools/processutils.hpp"
#include "../../model/timelines/timeline.hpp"

// Constructor
DeleteTweetProcess::DeleteTweetProcess(UserInfos & u,
									   Tweet statusToDelete,
									   bool withEntities,
									   bool userIDonly) :
	GenericProcess(),
	twitter(this),
	user(u),
	tweetToDelete(statusToDelete),
	includeEntities(withEntities),
	trimUser(userIDonly),
	keepInTimeline(tweetToDelete.getAuthor()->isFollowedByMe())
{
	connect(this, SIGNAL(allowDelete(bool,DeleteComplement)),
			this, SLOT(deleteTweet(bool,DeleteComplement)));
}

// Destructor
DeleteTweetProcess::~DeleteTweetProcess() {
	disconnect(this, SIGNAL(allowDelete(bool,DeleteComplement)),
			   this, SLOT(deleteTweet(bool,DeleteComplement)));
}

// Starting the process by determining if the tweet can be deleted.
void DeleteTweetProcess::startProcess() {
	canDeleteTweet();
}

// Determining if the tweet can be deleted
void DeleteTweetProcess::canDeleteTweet() {
	DeleteComplement addInfos;

	// Is the user the author ?
	if (user.getID() == tweetToDelete.getAuthor()->getID()) {
		// Yes ! The tweet can be deleted and the ID is already known :) !
		addInfos.tweetID = tweetToDelete.getID();

		emit allowDelete(true, addInfos);
	} else {
		// No. The tweet can be deleted only if the user retweeted it.
		if (tweetToDelete.isRetweetedByMe()) {
			// Tweet can be deleted but the retweet ID is unknown. Search it.

			// The ID is in the timeline of the user's retweets.
			connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
					this, SLOT(searchRetweetIDEnded(ResultWrapper)));

			// Moreover, the user's retweet is more recent than the original
			// tweet. So retweet ID > tweet ID
			twitter.userRetweetsTimeline(tweetToDelete.getID(),
										 -1, 20, true, false);
		} else {
			// Tweet cannot be deleted
			strcpy(addInfos.errMsg,
				   DeleteTweetProcess::trUtf8("The user is not the author of the tweet").toUtf8().data());
			emit allowDelete(false, addInfos);
		}
	}
}

// After searching the ID of the retweet
void DeleteTweetProcess::searchRetweetIDEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == INVALID_RESULT) {
		processResult = ProcessUtils::buildProcessResult(false,
														 INVALID_ISSUE,
														 DeleteTweetProcess::trUtf8("Dead end"),
														 false);
		endProcess();
		return;
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(searchRetweetIDEnded(ResultWrapper)));

	ErrorType errorType = result.resultType;

	// For a potenitial anticipated end
	QString beginErrMsg = DeleteTweetProcess::trUtf8("Retrieving retweet ID:") + '\n';
	QString errorMsg = "";
	bool isFatal = false;
	CoreResult issue;	// Filled in ProcessUtils methods

	// For NO_ERROR requests
	Timeline retweets;
	qlonglong tweetToDeleteID = -1;
	bool idFound = false;
	DeleteComplement addInfos;

	// Analysing the Twitter response
	switch (errorType) {
		case NO_ERROR:
			// Let's analyse the timeline to retrieve that fucking ID
			retweets.fillWithVariant(result.parsedResult.toList());

			for (Timeline::Iterator it = retweets.begin();
				 it != retweets.end() && !idFound;
				 ++it)
			{
				Tweet & retweet = *it;

				if (!retweet.isRetweet()) {
					continue;
				}

				// Is it the good ID ?
				qlonglong originalTweetID = retweet.getRetweetedStatus()->getID();

				if (originalTweetID == tweetToDelete.getID()) {
					tweetToDeleteID = retweet.getID();
					idFound = true;
				}
			}

			if (idFound) {
				// We got the ID. Let's delete
				addInfos.tweetID = tweetToDeleteID;
			} else {
				// Tweet cannot be deleted because the ID is still unknown
				errorMsg = beginErrMsg
						+ DeleteTweetProcess::trUtf8("Reweet ID unreachable");

				strcpy(addInfos.errMsg, errorMsg.toUtf8().data());
			}

			emit allowDelete(idFound, addInfos);
			return;

		case TWITTER_ERRORS:
			ProcessUtils::treatTwitterErrorResult(result, errorMsg, issue);
			break;

		case API_CALL:
			ProcessUtils::treatApiCallResult(result, errorMsg, issue);
			break;

		case QJSON_PARSING:
			ProcessUtils::treatQjsonParsingResult(result.parsingErrors, errorMsg, issue);
			break;

		default:
			ProcessUtils::treatUnknownResult(result.errorMessage, errorMsg, issue, isFatal);
			break;
	}

	// Failed end
	errorMsg.prepend(beginErrMsg);
	processResult = ProcessUtils::buildProcessResult(false, issue, errorMsg, isFatal);
	endProcess();
}

// Deleting the tweet
void DeleteTweetProcess::deleteTweet(bool allowToDelete,
									 DeleteComplement addInfos)
{
	if (allowToDelete) {
		// Let's destroy the tweet
		connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
				this, SLOT(deleteEnded(ResultWrapper)));

		twitter.destroyTweet(addInfos.tweetID, includeEntities, trimUser);
	} else {
		processResult = ProcessUtils::buildProcessResult(false,
														 TWEET_UNDESTROYABLE,
														 QString(addInfos.errMsg),
														 false);
		endProcess();
	}
}

// After deleting the tweet
void DeleteTweetProcess::deleteEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == INVALID_RESULT) {
		processResult = ProcessUtils::buildProcessResult(false,
														 INVALID_ISSUE,
														 DeleteTweetProcess::trUtf8("Dead end"),
														 false);
		return endProcess();
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(deleteEnded(ResultWrapper)));

	ErrorType errorType = result.resultType;

	// For a potenitial anticipated end
	QString errorMsg = "";
	bool isFatal = false;
	CoreResult issue;	// Filled in ProcessUtils methods

	// For NO_ERROR requests
	QVariantMap deletionResult;

	// Analysing the Twitter response
	switch (errorType) {
		case NO_ERROR:
			deletionResult.insert("twitter_result", result.parsedResult);
			deletionResult.insert("keep_in_timeline", QVariant(keepInTimeline));
			processResult = ProcessUtils::buildProcessResult(TWEET_DELETED,
															 QVariant(deletionResult));
			return endProcess();

		case TWITTER_ERRORS:
			ProcessUtils::treatTwitterErrorResult(result, errorMsg, issue);
			break;

		case API_CALL:
			ProcessUtils::treatApiCallResult(result, errorMsg, issue);
			break;

		case QJSON_PARSING:
			ProcessUtils::treatQjsonParsingResult(result.parsingErrors, errorMsg, issue);
			break;

		default:
			ProcessUtils::treatUnknownResult(result.errorMessage, errorMsg, issue, isFatal);
			break;
	}

	// Failed end
	processResult = ProcessUtils::buildProcessResult(false, issue, errorMsg, isFatal);
	endProcess();
}
