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
									   bool userIDonly) :
	GenericProcess(),
	twitter(this),
	user(u),
	tweetToDelete(statusToDelete),
	trimUser(userIDonly),
	keepInTimeline(true)
{}

// Destructor
DeleteTweetProcess::~DeleteTweetProcess() {}

// Starting the process by determining if the tweet can be deleted.
void DeleteTweetProcess::startProcess() {
	canDeleteTweet();
}

// Determining if the tweet can be deleted
void DeleteTweetProcess::canDeleteTweet() {
	if (user == *(tweetToDelete.getAuthor())) {
		// The user is the author of the tweet
		// The tweet can be deleted and the ID is already known :) !

		keepInTimeline = tweetToDelete.isRetweet() ?
					tweetToDelete.getRetweetedStatus()->getAuthor()->isFollowedByMe()
				  : false;

		deleteTweet(true, tweetToDelete.getIDstr());
	}
	else if (user == *(tweetToDelete.getRetweetedStatus()->getAuthor())
			 && tweetToDelete.isRetweet())
	{
		// The user is the author of the retweet. Delete the retweet

		keepInTimeline = false;
		deleteTweet(true, tweetToDelete.getRetweetedStatus()->getIDstr());
	}
	else if (tweetToDelete.isRetweetedByMe()) {
		// Tweet can be deleted only if the user retweeted it.
		// But the retweet ID is unknown. So let's search it !

		keepInTimeline = tweetToDelete.isRetweet() ?
					tweetToDelete.getRetweetedStatus()->getAuthor()->isFollowedByMe()
				  : tweetToDelete.getAuthor()->isFollowedByMe();

		// Looking at the "current_retweet_infos" property
		RetweetInfos * rtInfos = tweetToDelete.getRetweetInfos();

		if (rtInfos->getIDstr() == "-1") {
			// The retweet ID is not in the tweet. Ask it to Twitter !

			// The ID is in the details of tweetToDelete.
			connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
					this, SLOT(searchRetweetIDEnded(ResultWrapper)));

			twitter.showTweet(tweetToDelete.getIDstr().toLongLong());
		} else {
			// The retweet ID is in the tweet. Time for deletion.
			deleteTweet(true, rtInfos->getIDstr());
		}

	}
	else {
		// Tweet cannot be deleted
		deleteTweet(false,
					DeleteTweetProcess::trUtf8("The user is not the author of the tweet"));
	}
}

// After searching the ID of the retweet
void DeleteTweetProcess::searchRetweetIDEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == Network::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(searchRetweetIDEnded(ResultWrapper)));

	NetworkResultType errorType = result.resultType;

	// For a potenitial anticipated end
	QString beginErrMsg = DeleteTweetProcess::trUtf8("Retrieving retweet ID:") + '\n';
	QString errorMsg = "";
	bool isFatal = false;
	CoreResult issue;	// Filled in ProcessUtils methods

	// Analysing the Twitter response
	switch (errorType) {
		case Network::NO_REQUEST_ERROR:{
			// Updating tweetToDelete
			tweetToDelete.reset();
			tweetToDelete.fillWithVariant(QJsonObject::fromVariantMap(result.parsedResult.toMap()));

			// Looking at the "current_retweet_infos" property
			RetweetInfos * rtInfos = tweetToDelete.getRetweetInfos();
			bool idFound = rtInfos->getIDstr() != "-1";

			QString addInfos = "";
			if (idFound) {
				// The retweet ID is retrieved. Time for deletion.
				addInfos = rtInfos->getIDstr();
			} else {
				// It is definitely not a retweet. Abort.
				addInfos = beginErrMsg.append(DeleteTweetProcess::trUtf8("Reweet ID unreachable"));
			}

			return deleteTweet(idFound, addInfos);
		}break;

		case Network::SERVICE_ERRORS:
			ProcessUtils::treatTwitterErrorResult(result, errorMsg, issue);
			break;

		case Network::API_CALL:
			ProcessUtils::treatApiCallResult(result, errorMsg, issue);
			break;

		case Network::JSON_PARSING:
			ProcessUtils::treatQjsonParsingResult(result.parsingErrors, errorMsg, issue);
			break;

		default:
			ProcessUtils::treatUnknownResult(result.errorMessage, errorMsg, issue, isFatal);
			break;
	}

	// Failed end
	errorMsg.prepend(beginErrMsg);
	buildResult(false, issue, errorMsg, isFatal);
	endProcess();
}

// Deleting the tweet
void DeleteTweetProcess::deleteTweet(bool allowToDelete,
									 QString addInfos)
{
	CoreResult issue = TWEET_UNDESTROYABLE;
	QString errMsg = "";
	bool isFatal = false;

	if (allowToDelete) {
		// Let's destroy the tweet
		connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
				this, SLOT(deleteEnded(ResultWrapper)));

		bool toLongLongOK = false;

		qlonglong tweetID = addInfos.toLongLong(&toLongLongOK);

		if (toLongLongOK) {
			return twitter.destroyTweet(tweetID, trimUser);
		} else {
			errMsg.append(DeleteTweetProcess::trUtf8("Unknown tweet ID '"));
			errMsg.append(addInfos);
			errMsg.append("'.");
		}
	} else {
		errMsg = addInfos;
	}

	// Failed ends
	GenericProcess::buildResult(false, issue, errMsg, isFatal);
	endProcess();
}

// After deleting the tweet
void DeleteTweetProcess::deleteEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == Network::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(deleteEnded(ResultWrapper)));

	NetworkResultType errorType = result.resultType;

	// For a potenitial anticipated end
	QString errorMsg = "";
	bool isFatal = false;
	CoreResult issue;	// Filled in ProcessUtils methods

	// For NO_REQUEST_ERROR requests
	QVariantMap deletionResult;

	// Analysing the Twitter response
	switch (errorType) {
		case Network::NO_REQUEST_ERROR:
			deletionResult.insert("twitter_result", result.parsedResult);
			deletionResult.insert("keep_in_timeline", QVariant(keepInTimeline));
			processResult = ProcessUtils::buildProcessResult(TWEET_DELETED,
															 QVariant(deletionResult));
			return endProcess();

		case Network::SERVICE_ERRORS:
			ProcessUtils::treatTwitterErrorResult(result, errorMsg, issue);
			break;

		case Network::API_CALL:
			ProcessUtils::treatApiCallResult(result, errorMsg, issue);
			break;

		case Network::JSON_PARSING:
			ProcessUtils::treatQjsonParsingResult(result.parsingErrors, errorMsg, issue);
			break;

		default:
			ProcessUtils::treatUnknownResult(result.errorMessage, errorMsg, issue, isFatal);
			break;
	}

	// Failed end
	buildResult(false, issue, errorMsg, isFatal);
	endProcess();
}
