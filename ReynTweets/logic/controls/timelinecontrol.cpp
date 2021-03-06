/// @file timelinecontrol.cpp
/// @brief Implementation of TimelineControl
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

#include <QtQml>
#include "timelinecontrol.hpp"

// Constructor
TimelineControl::TimelineControl() :
	GenericControl(),
	tlhandler(),
	timeline(tlhandler.getHandledListRef()),
	backupedNewTweet()
{}

// Declaring TweetControl to the QML system
void TimelineControl::declareQML() {
	// @uri ReynTweetsComponents
	qmlRegisterType<TimelineControl>(ReynTweets::QML_LIBRARY_NAME.toLatin1().constData(),
									 ReynTweets::MAJOR_VERSION, ReynTweets::MINOR_VERSION,
									 "TimelineControl");
}


/////////////////////////
// Property management //
/////////////////////////

// timeline_handler
TimelineHandler * TimelineControl::getTimelineHandler() {
	return &tlhandler;
}


///////////////////////
// Loading timelines //
///////////////////////

// Loading the home timeline
void TimelineControl::loadTimeline() {
	if (processing) {
		return;
	}

	connect(&reyn, &ReynCore::sendResult,
			this, &TimelineControl::loadTimelineEnded);

	processing = true;

	switch (tlhandler.getType()) {
		case TimelineHandler::HOME:
			emit showInfoMessage(TimelineControl::trUtf8("Loading timeline..."));
			reyn.loadHomeTimeline(ReynTweets::FAKE_TWEET_ID,
								  ReynTweets::FAKE_TWEET_ID,
								  50);
			break;

		case TimelineHandler::MENTIONS:
			emit showInfoMessage(TimelineControl::trUtf8("Loading mentions..."));
			reyn.loadMentionsTimeline(ReynTweets::FAKE_TWEET_ID,
									  ReynTweets::FAKE_TWEET_ID,
									  50);
			break;

		default:
			processing = false;
			disconnect(&reyn, &ReynCore::sendResult,
					   this, &TimelineControl::loadTimelineEnded);
			emit actionEnded(false,
							 TimelineControl::trUtf8("Invalid type of timeline."),
							 false);
			break;
	}
}

// After loading a timeline
void TimelineControl::loadTimelineEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (ReynTweets::INVALID_END == result.processEnd) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, &ReynCore::sendResult,
			   this, &TimelineControl::loadTimelineEnded);

	switch (result.processEnd) {
		case ReynTweets::TIMELINE_RETRIEVED: {
			QVariantList resList = result.results.toList();
			Timeline tl;
			tl.fillWithVariant(QJsonArray::fromVariantList(resList));
			tlhandler.appendTimeline(tl);
			emit tlhandler.handledListChanged();
			// Process successful
			emit actionEnded(true,
							 TimelineControl::trUtf8("Timeline loaded."),
							 false);

		}break;

		case ReynTweets::TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			return;

		// Problems that can be solved trying later
		case ReynTweets::NO_MORE_DATA:
		case ReynTweets::BAD_REQUEST:
		case ReynTweets::REFUSED_REQUEST:
		case ReynTweets::RATE_LIMITED:	// The user reached rates.
		case ReynTweets::TWITTER_DOWN:	// Twitter does not respond.
		case ReynTweets::NETWORK_CALL:
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case ReynTweets::UNKNOWN_PROBLEM:

		default:
			emit actionEnded(false, result.errorMsg, true);
			break;
	}
}


//////////////////////////
// Refreshing timelines //
//////////////////////////

// Loading the home timeline
void TimelineControl::refreshTimeline() {
	if (processing) {
		return;
	}

	// Refreshing an empty timeline == loading the timeline
	if (timeline.isEmpty()) {
		return loadTimeline();
	}

	connect(&reyn, &ReynCore::sendResult,
			this, &TimelineControl::refreshTimelineEnded);

	processing = true;

	switch (tlhandler.getType()) {
		case TimelineHandler::HOME:
			emit showInfoMessage(TimelineControl::trUtf8("Refreshing timeline..."));
			reyn.refreshHomeTimeline(timeline.first());
			break;

		case TimelineHandler::MENTIONS:
			emit showInfoMessage(TimelineControl::trUtf8("Refreshing mentions..."));
			reyn.refreshMentionsTimeline(timeline.first());
			break;

		default:
			processing = false;
			disconnect(&reyn, &ReynCore::sendResult,
					   this, &TimelineControl::refreshTimelineEnded);
			emit actionEnded(false,
							 TimelineControl::trUtf8("Invalid type of timeline."),
							 false);
			break;
	}
}


// After loading a timeline
void TimelineControl::refreshTimelineEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (ReynTweets::INVALID_END == result.processEnd) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, &ReynCore::sendResult,
			   this, &TimelineControl::refreshTimelineEnded);

	switch (result.processEnd) {
		case ReynTweets::TIMELINE_RETRIEVED: {
			QVariantMap procRes = result.results.toMap();

			// If something bad happened while loading missing tweets, say it
			ReynTweets::CoreResult intermediateEnd = ReynTweets::CoreResult(procRes.value("intermediate_end").toInt());

			if (intermediateEnd != ReynTweets::INVALID_END) {
				emit showInfoMessage(result.errorMsg);
			}

			// Do the timeline modifications and end the action
			Timeline newerTweets = procRes.value("newer_tweets").value<Timeline>();

			tlhandler.prependTimeline(newerTweets);
			emit loadedMoreTweets(newerTweets.size());
			emit actionEnded(true,
							 TimelineControl::trUtf8("Timeline refreshed."),
							 false);
		} break;


		case ReynTweets::TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			return;

		// Problems that can be solved trying later
		case ReynTweets::NO_MORE_TWEETS:
		case ReynTweets::NO_MORE_DATA:
		case ReynTweets::BAD_REQUEST:
		case ReynTweets::REFUSED_REQUEST:
		case ReynTweets::RATE_LIMITED:	// The user reached rates.
		case ReynTweets::TWITTER_DOWN:	// Twitter does not respond.
		case ReynTweets::NETWORK_CALL:
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case ReynTweets::UNKNOWN_PROBLEM:

		default:
			emit actionEnded(false, result.errorMsg, true);
			break;
	}
}

// Refreshing after writing a tweet
void TimelineControl::refreshTimelineAfterWrite(QVariant newTweetVariant) {
	if (processing) {
		return;
	}

	// Refreshing an empty timeline == loading the timeline
	if (timeline.isEmpty()) {
		return loadTimeline();
	}

	backupedNewTweet = newTweetVariant;

	connect(&reyn, &ReynCore::sendResult,
			this, &TimelineControl::refreshTimelineAfterWriteEnded);
	processing = true;

	switch (tlhandler.getType()) {
		case TimelineHandler::HOME:
			emit showInfoMessage(TimelineControl::trUtf8("Refreshing timeline..."));
			reyn.refreshHomeTimeline(timeline.first());
			break;

		case TimelineHandler::MENTIONS: {
			// TODO : simplify

			// "Refresh after write" only if the user mentions himself. "Refresh" otherwise.
			Tweet backupedTweet;
			backupedTweet.fillWithVariant(QJsonObject::fromVariantMap(backupedNewTweet.toMap()));

			UserConfiguration & conf = reyn.getUserConfiguration();
			QString authorID = conf.getUserAccount().getUser().getIDstr();
			UserMentionList tweetMentions = backupedTweet.getEntities().getUserMentions();

			// Searching the auto mention
			for (UserMentionList::Iterator it = tweetMentions.begin();
				 it != tweetMentions.end();
				 ++it)
			{
				QString userID = it->getIDstr();

				if (userID == authorID) {
					// The user mentions itself : let's refresh !
					emit showInfoMessage(TimelineControl::trUtf8("Refreshing mentions..."));
					return reyn.refreshMentionsTimeline(timeline.first());
				}
			}

			// The user desn't mention itself. Just do a simple refresh.
			processing = false;
			disconnect(&reyn, &ReynCore::sendResult,
					   this, &TimelineControl::refreshTimelineAfterWriteEnded);

			return refreshTimeline();
		}break;

		default:
			processing = false;
			disconnect(&reyn, &ReynCore::sendResult,
					   this, &TimelineControl::refreshTimelineAfterWriteEnded);
			emit actionEnded(false,
							 TimelineControl::trUtf8("Invalid type of timeline."),
							 false);
			break;
	}
}


// After refreshHomeTimelineAfterWrite
void TimelineControl::refreshTimelineAfterWriteEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (ReynTweets::INVALID_END == result.processEnd) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, &ReynCore::sendResult,
			   this, &TimelineControl::refreshTimelineAfterWriteEnded);

	switch (result.processEnd) {
		case ReynTweets::TIMELINE_RETRIEVED: {
			QVariantMap procRes = result.results.toMap();

			// If something bad happened while loading missing tweets, say it
			ReynTweets::CoreResult intermediateEnd = ReynTweets::CoreResult(procRes.value("intermediate_end").toInt());

			if (intermediateEnd != ReynTweets::INVALID_END) {
				emit showInfoMessage(result.errorMsg);
			}

			// Do the timeline modifications and end the action
			Timeline newerTweets = procRes.value("newer_tweets").value<Timeline>();

			// Inserting the new Tweet in the timeline of new tweets
			Tweet lastTweet;
			lastTweet.fillWithVariant(QJsonObject::fromVariantMap(backupedNewTweet.toMap()));
			newerTweets.insertElement(lastTweet);

			tlhandler.prependTimeline(newerTweets);
			emit loadedMoreTweets(newerTweets.size());
			emit actionEnded(true,
							 TimelineControl::trUtf8("Timeline refreshed."),
							 false);
		} break;

		case ReynTweets::TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			return;

		// Problems that can be solved trying later
		case ReynTweets::NO_MORE_DATA:
		case ReynTweets::BAD_REQUEST:
		case ReynTweets::REFUSED_REQUEST:
		case ReynTweets::RATE_LIMITED:	// The user reached rates.
		case ReynTweets::TWITTER_DOWN:	// Twitter does not respond.
		case ReynTweets::NETWORK_CALL:
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case ReynTweets::UNKNOWN_PROBLEM:

		default:
			emit actionEnded(false, result.errorMsg, true);
			break;
	}

}


///////////////////////
// Loading timelines //
///////////////////////

// Loading the home timeline
void TimelineControl::moreOldTimeline() {
	if (processing) {
		return;
	}

	// Getting older tweets in an empty timeline == loading the timeline
	if (timeline.isEmpty()) {
		return loadTimeline();
	}

	qlonglong maxTweetID = timeline.getLastID() - 1;

	connect(&reyn, &ReynCore::sendResult,
			this, &TimelineControl::moreOldTimelineEnded);

	processing = true;

	switch (tlhandler.getType()) {
		case TimelineHandler::HOME:
			emit showInfoMessage(TimelineControl::trUtf8("Loading more tweets..."));
			reyn.loadHomeTimeline(ReynTweets::FAKE_TWEET_ID, maxTweetID, 50);
			break;

		case TimelineHandler::MENTIONS:
			emit showInfoMessage(TimelineControl::trUtf8("Loading more mentions..."));
			reyn.loadMentionsTimeline(ReynTweets::FAKE_TWEET_ID, maxTweetID, 50);
			break;

		default:
			processing = false;
			disconnect(&reyn, &ReynCore::sendResult,
					   this, &TimelineControl::moreOldTimelineEnded);
			emit actionEnded(false,
							 TimelineControl::trUtf8("Invalid type of timeline."),
							 false);
			break;
	}
}


// After loading a timeline
void TimelineControl::moreOldTimelineEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (ReynTweets::INVALID_END == result.processEnd) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, &ReynCore::sendResult,
			   this, &TimelineControl::moreOldTimelineEnded);

	switch (result.processEnd) {
		case ReynTweets::TIMELINE_RETRIEVED:{
			QVariantList resList = result.results.toList();
			Timeline newTweets;
			newTweets.fillWithVariant(QJsonArray::fromVariantList(resList));
			tlhandler.appendTimeline(newTweets);
			emit tlhandler.handledListChanged();
			// Process successful
			emit actionEnded(true,
							 TimelineControl::trUtf8("Tweets loaded."),
							 false);

		} break;

		case ReynTweets::TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			return;

		// Problems that can be solved trying later
		case ReynTweets::NO_MORE_DATA:
		case ReynTweets::BAD_REQUEST:
		case ReynTweets::REFUSED_REQUEST:
		case ReynTweets::RATE_LIMITED:	// The user reached rates.
		case ReynTweets::TWITTER_DOWN:	// Twitter does not respond.
		case ReynTweets::NETWORK_CALL:
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case ReynTweets::UNKNOWN_PROBLEM:

		default:
			emit actionEnded(false, result.errorMsg, true);
			break;
	}
}
