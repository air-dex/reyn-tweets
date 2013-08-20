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

TimelineControl::TimelineControl() :
	GenericControl(),
	tlhandler(),
	timeline(tlhandler.getHandledListRef()),
	backupedNewTweet()
{}

// Declaring TweetControl to the QML system
void TimelineControl::declareQML() {
	qmlRegisterType<TimelineControl>("ReynTweetsControls",
									 0, 2,
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

	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(loadTimelineEnded(ProcessWrapper)));

	processing = true;

	switch (tlhandler.getType()) {
		case TimelineHandler::HOME:
			emit showInfoMessage(TimelineControl::trUtf8("Loading timeline..."));
			reyn.loadHomeTimeline(-1, -1, 50);
			break;

		case TimelineHandler::MENTIONS:
			emit showInfoMessage(TimelineControl::trUtf8("Loading mentions..."));
			reyn.loadMentionsTimeline(-1, -1, 50);
			break;

		default:
			processing = false;
			disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
					   this, SLOT(loadTimelineEnded(ProcessWrapper)));
			emit actionEnded(false,
							 TimelineControl::trUtf8("Invalid type of timeline"),
							 false);
			break;
	}
}

// After loading a timeline
void TimelineControl::loadTimelineEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(loadTimelineEnded(ProcessWrapper)));

	CoreResult issue = result.processIssue;

	switch (issue) {
		case TIMELINE_RETRIEVED: {
			QVariantList resList = result.results.toList();
			Timeline tl;
			tl.fillWithVariant(QJsonArray::fromVariantList(resList));
			tlhandler.appendTimeline(tl);
			emit tlhandler.handledListChanged();
			// Process successful
			emit actionEnded(true,
							 TimelineControl::trUtf8("Timeline loaded"),
							 false);

		}break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			return;

		// Problems that can be solved trying later
		case NO_MORE_DATA:
		case BAD_REQUEST:
		case REFUSED_REQUEST:
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
		case NETWORK_CALL:
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case UNKNOWN_PROBLEM:

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

	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(refreshTimelineEnded(ProcessWrapper)));

	processing = true;

	switch (tlhandler.getType()) {
		case TimelineHandler::HOME:
			emit showInfoMessage(TimelineControl::trUtf8("Refreshing timeline..."));
			reyn.loadHomeTimeline(timeline.getFirstID());
			break;

		case TimelineHandler::MENTIONS:
			emit showInfoMessage(TimelineControl::trUtf8("Refreshing mentions..."));
			reyn.loadMentionsTimeline(timeline.getFirstID());
			break;

		default:
			processing = false;
			disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
					   this, SLOT(refreshTimelineEnded(ProcessWrapper)));
			emit actionEnded(false,
							 TimelineControl::trUtf8("Invalid type of timeline"),
							 false);
			break;
	}
}


// After loading a timeline
void TimelineControl::refreshTimelineEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(refreshTimelineEnded(ProcessWrapper)));

	CoreResult issue = result.processIssue;
	Timeline newTweets;

	// newerTweets is static because it contains all the new tweets of the TL.
	static Timeline newerTweets;

	switch (issue) {
		case TIMELINE_RETRIEVED:
			// Retrieving the new tweets
			newTweets.fillWithVariant(QJsonArray::fromVariantList(result.results.toList()));

			if (!newTweets.isEmpty()) {
				qlonglong newMinID = newTweets.getLastID();
				static qlonglong maxID = timeline.getFirstID();

				// Is there missing tweets in the timeline ?
				if (newMinID == maxID) {
					newTweets.removeLast();
				} else {
					// There's a gap to fill

					// Save the the retrieved tweets before
					newerTweets.append(newTweets);

					// Fill the gap
					switch (tlhandler.getType()) {
						case TimelineHandler::HOME:
							connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
									this, SLOT(refreshTimelineEnded(ProcessWrapper)));
							return reyn.loadHomeTimeline(maxID -1, newMinID -1);

						case TimelineHandler::MENTIONS:
							connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
									this, SLOT(refreshTimelineEnded(ProcessWrapper)));
							return reyn.loadMentionsTimeline(maxID -1, newMinID -1);

						default:
							newerTweets.clear();
							emit actionEnded(false,
											 TimelineControl::trUtf8("Invalid type of timeline"),
											 false);
							return;
					}
				}
			}

			newerTweets.append(newTweets);
			emit loadedMoreTweets(newerTweets.size());
			tlhandler.prependTimeline(newerTweets);

			// Process successful
			emit tlhandler.handledListChanged();
			emit actionEnded(true, TimelineControl::trUtf8("Timeline refreshed"), false);
			break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			return;

		// Problems that can be solved trying later
		case NO_MORE_DATA:
		case BAD_REQUEST:
		case REFUSED_REQUEST:
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
		case NETWORK_CALL:
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case UNKNOWN_PROBLEM:

		default:
			emit actionEnded(false, result.errorMsg, true);
			break;
	}

	// Resetting this static variable (no former "new tweets" for the next refresh)
	newerTweets.clear();
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

	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(refreshTimelineAfterWriteEnded(ProcessWrapper)));
	processing = true;

	switch (tlhandler.getType()) {
		case TimelineHandler::HOME:
			emit showInfoMessage(TimelineControl::trUtf8("Refreshing timeline..."));
			reyn.loadHomeTimeline(timeline.getFirstID());
			break;

		case TimelineHandler::MENTIONS: {
			// "Refresh after write" only if the user mentions himself. "Refrsh" otherwise.
			Tweet backupedTweet;
			backupedTweet.fillWithVariant(QJsonObject::fromVariantMap(backupedNewTweet.toMap()));

			UserConfiguration & conf = reyn.getUserConfiguration();
			QString authorID = conf.getUserAccount().getUser().getIDstr();
			UserMentionList tweetMentions = backupedTweet.getEntities().getUserMentions();

			for (UserMentionList::Iterator it = tweetMentions.begin();
				 it != tweetMentions.end();
				 ++it)
			{
				QString userID = it->getIDstr();

				if (userID == authorID) {
					// The user mentions itself
					emit showInfoMessage(TimelineControl::trUtf8("Refreshing mentions..."));
					return reyn.loadMentionsTimeline(timeline.getFirstID());
				}
			}

			// The user desn't mention itself. Just do a simple refresh.
			processing = false;
			disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
					   this, SLOT(refreshTimelineAfterWriteEnded(ProcessWrapper)));

			return refreshTimeline();
		}break;

		default:
			processing = false;
			disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
					   this, SLOT(refreshTimelineAfterWriteEnded(ProcessWrapper)));
			emit actionEnded(false,
							 TimelineControl::trUtf8("Invalid type of timeline"),
							 false);
			break;
	}
}


// After refreshHomeTimelineAfterWrite
void TimelineControl::refreshTimelineAfterWriteEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(refreshTimelineAfterWriteEnded(ProcessWrapper)));

	CoreResult issue = result.processIssue;
	Timeline newTweets;
	Tweet lastTweet;

	// newerTweets is static because it contains all the new tweets of the TL.
	static Timeline newerTweets;

	switch (issue) {
		case TIMELINE_RETRIEVED:
			newTweets.fillWithVariant(QJsonArray::fromVariantList(result.results.toList()));

			if (!newTweets.isEmpty()) {
				qlonglong newMinID = newTweets.getLastID();
				qlonglong maxID = timeline.getFirstID();

				// Is there missing tweets in the timeline ?
				if (newMinID == maxID) {
					newTweets.removeLast();
				} else {
					// There's a gap to fill

					// Save the the retrieved tweets before
					newerTweets.append(newTweets);

					// Fill the gap
					switch (tlhandler.getType()) {
						case TimelineHandler::HOME:
							connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
									this, SLOT(refreshTimelineAfterWriteEnded(ProcessWrapper)));
							return reyn.loadHomeTimeline(maxID -1, newMinID -1);

						case TimelineHandler::MENTIONS:
							connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
									this, SLOT(refreshTimelineAfterWriteEnded(ProcessWrapper)));
							return reyn.loadMentionsTimeline(maxID -1, newMinID -1);

						default:
							newerTweets.clear();
							emit actionEnded(false,
											 TimelineControl::trUtf8("Invalid type of timeline"),
											 false);
							return;
					}
				}
			}

			// Inserting the new Tweet in the timeline of new tweets
			lastTweet.fillWithVariant(QJsonObject::fromVariantMap(backupedNewTweet.toMap()));
			newerTweets.insertElement(lastTweet);

			emit loadedMoreTweets(newerTweets.size());

			tlhandler.prependTimeline(newerTweets);

			// Process successful
			emit tlhandler.handledListChanged();
			emit actionEnded(true, TimelineControl::trUtf8("Timeline refreshed"), false);
			break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			return;

		// Problems that can be solved trying later
		case NO_MORE_DATA:
		case BAD_REQUEST:
		case REFUSED_REQUEST:
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
		case NETWORK_CALL:
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case UNKNOWN_PROBLEM:

		default:
			emit actionEnded(false, result.errorMsg, true);
			break;
	}

	// Resetting this static variable
	newerTweets.clear();
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

	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(moreOldTimelineEnded(ProcessWrapper)));

	processing = true;

	switch (tlhandler.getType()) {
		case TimelineHandler::HOME:
			emit showInfoMessage(TimelineControl::trUtf8("Loading more tweets..."));
			reyn.loadHomeTimeline(-1, maxTweetID, 50);
			break;

		case TimelineHandler::MENTIONS:
			emit showInfoMessage(TimelineControl::trUtf8("Loading more mentions..."));
			reyn.loadMentionsTimeline(-1, maxTweetID, 50);
			break;

		default:
			processing = false;
			disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
					   this, SLOT(moreOldTimelineEnded(ProcessWrapper)));
			emit actionEnded(false,
							 TimelineControl::trUtf8("Invalid type of timeline"),
							 false);
			break;
	}
}


// After loading a timeline
void TimelineControl::moreOldTimelineEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(moreOldTimelineEnded(ProcessWrapper)));

	CoreResult issue = result.processIssue;

	switch (issue) {
		case TIMELINE_RETRIEVED:{
			QVariantList resList = result.results.toList();
			Timeline newTweets;
			newTweets.fillWithVariant(QJsonArray::fromVariantList(resList));
			tlhandler.appendTimeline(newTweets);
			emit tlhandler.handledListChanged();
			// Process successful
			emit actionEnded(true, TimelineControl::trUtf8("Tweets loaded"), false);

		} break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			return;

		// Problems that can be solved trying later
		case NO_MORE_DATA:
		case BAD_REQUEST:
		case REFUSED_REQUEST:
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
		case NETWORK_CALL:
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case UNKNOWN_PROBLEM:

		default:
			emit actionEnded(false, result.errorMsg, true);
			break;
	}
}
