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

#include <QtDeclarative>
#include "timelinecontrol.hpp"

TimelineControl::TimelineControl() :
	GenericControl(),
	backupedNewTweet()
{}

// Declaring TweetControl to the QML system
void TimelineControl::declareQML() {
	qmlRegisterType<TimelineControl>("ReynTweetsControls",
									 0, 1,
									 "TimelineControl");
}


/////////////////////////
// Property management //
/////////////////////////

// Read
QVariantList TimelineControl::getVariantTimeline() {
	return timeline.toVariant();
}

// Write
void TimelineControl::setVariantTimeline(QVariantList variantTimeline) {
	timeline.fillWithVariant(variantTimeline);
}


///////////////////////////////////
// Accessing tweets in QML views //
///////////////////////////////////

// Getting a pointer on a tweet in the timeline.
Tweet * TimelineControl::getTweet(int tweetIndex) {
	if (tweetIndex >= 0 && tweetIndex < timeline.size()) {
		return &(timeline[tweetIndex]);
	} else {
		return new Tweet;
	}
}

// Replacing a tweet
void TimelineControl::replaceTweet(QVariant updatedTweet, int tweetIndex) {
	if (tweetIndex < 0 || tweetIndex >= timeline.count()) {
		return;
	}

	Tweet & tweet = timeline[tweetIndex];
	tweet.reset();
	tweet.fillWithVariant(updatedTweet.toMap());

	emit tweetUpdated(tweetIndex);
}

// Replacing a tweet
void TimelineControl::deleteTweet(int tweetIndex) {
	if (tweetIndex < 0 || tweetIndex >= timeline.count()) {
		return;
	}

	timeline.removeAt(tweetIndex);
	emit timelineChanged();
}

// Inserting a tweet in a timeline
void TimelineControl::insertInTimeline(Timeline & tl, Tweet newTweet) {
	if (tl.isEmpty()) {
		// Just add the tweet.
		return tl.append(newTweet);
	}

	int newTweetIndex;
	qlonglong newTweetID = newTweet.getID();
	qlonglong tlMaxID = tl.last().getID();

	if (newTweetID < tlMaxID) {
		newTweetIndex = tl.size();
	} else {
		int a = 0;
		int b = tl.size();

		while (a != b) {
			int m = (a + b) /2;
			qlonglong midTweetID = tl[m].getID();

			if (newTweetID >= midTweetID) {
				b = m;
			} else {
				a = m + 1;
			}
		}

		newTweetIndex = a;
	}

	if (newTweetIndex >= tl.size()
			|| newTweet.getID() != tl[newTweetIndex].getID())
	{
		tl.insert(newTweetIndex, newTweet);
	}
}


///////////////////////
// Loading timelines //
///////////////////////

// Loading the home timeline
void TimelineControl::loadHomeTimeline() {
	if (processing) {
		return;
	}

	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(loadTimelineEnded(ProcessWrapper)));

	processing = true;
	emit showInfoMessage(TimelineControl::trUtf8("Loading timeline..."));
	reyn.loadHomeTimeline(-1, -1, 50);
}


// After loading a timeline
void TimelineControl::loadTimelineEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		processing = true;
		return;
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(loadTimelineEnded(ProcessWrapper)));

	CoreResult issue = result.processIssue;
	QVariantList resList = result.results.toList();

	switch (issue) {
		case TIMELINE_RETRIEVED:
			timeline.fillWithVariant(resList);
			emit timelineChanged();
			// Process successful
			emit actionEnded(true, TimelineControl::trUtf8("Timeline loaded"), false);
			break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			return;

		// Problems that can be solved trying later
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
void TimelineControl::refreshHomeTimeline() {
	if (processing) {
		return;
	}

	// Refreshing an empty timeline == loading the timeline
	if (timeline.isEmpty()) {
		return loadHomeTimeline();
	}

	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(refreshTimelineEnded(ProcessWrapper)));

	processing = true;
	emit showInfoMessage(TimelineControl::trUtf8("Refreshing timeline..."));
	reyn.loadHomeTimeline(timeline[0].getID());
}


// After loading a timeline
void TimelineControl::refreshTimelineEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		processing = true;
		return;
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
			newTweets.fillWithVariant(result.results.toList());

			if (!newTweets.isEmpty()) {
				qlonglong newMinID = newTweets.last().getID();
				qlonglong maxID = timeline.first().getID();

				// Is there missing tweets in the timeline ?
				if (newMinID == maxID) {
					newTweets.removeLast();
				} else {
					// There's a gap to fill

					// Save the the retrieved tweets before
					newerTweets.append(newTweets);

					// Fill the gap
					connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
							this, SLOT(refreshTimelineEnded(ProcessWrapper)));
					return reyn.loadHomeTimeline(maxID -1, newMinID -1);
				}
			}

			newerTweets.append(newTweets);
			emit loadedMoreTweets(newerTweets.size());

			// Equivalent to timeline.prepend(newerTweets);
			newerTweets.append(timeline);
			timeline.clear();
			timeline.append(newerTweets);

			// Process successful
			emit timelineChanged();
			emit actionEnded(true, TimelineControl::trUtf8("Timeline refreshed"), false);
			break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			return;

		// Problems that can be solved trying later
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
void TimelineControl::refreshHomeTimelineAfterWrite(QVariant newTweetVariant) {
	if (processing) {
		return;
	}

	// Refreshing an empty timeline == loading the timeline
	if (timeline.isEmpty()) {
		return loadHomeTimeline();
	}

	backupedNewTweet = newTweetVariant;

	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(refreshTimelineAfterWriteEnded(ProcessWrapper)));

	processing = true;
	emit showInfoMessage(TimelineControl::trUtf8("Refreshing timeline..."));
	reyn.loadHomeTimeline(timeline[0].getID());
}


// After refreshHomeTimelineAfterWrite
void TimelineControl::refreshTimelineAfterWriteEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		processing = true;
		return;
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
			newTweets.fillWithVariant(result.results.toList());

			if (!newTweets.isEmpty()) {
				qlonglong newMinID = newTweets.last().getID();
				qlonglong maxID = timeline.first().getID();

				// Is there missing tweets in the timeline ?
				if (newMinID == maxID) {
					newTweets.removeLast();
				} else {
					// There's a gap to fill

					// Save the the retrieved tweets before
					newerTweets.append(newTweets);

					// Fill the gap
					connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
							this, SLOT(refreshTimelineEnded(ProcessWrapper)));
					return reyn.loadHomeTimeline(maxID -1, newMinID -1);
				}
			}

			// Inserting the new Tweet in the timeline of new tweets
			lastTweet.fillWithVariant(backupedNewTweet.toMap());
			insertInTimeline(newerTweets, lastTweet);

			emit loadedMoreTweets(newerTweets.size());

			// Equivalent to timeline.prepend(newerTweets);
			newerTweets.append(timeline);
			timeline.clear();
			timeline.append(newerTweets);

			// Process successful
			emit timelineChanged();
			emit actionEnded(true, TimelineControl::trUtf8("Timeline refreshed"), false);
			break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			return;

		// Problems that can be solved trying later
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
void TimelineControl::moreOldHomeTimeline() {
	if (processing) {
		return;
	}

	// Getting older tweets in an empty timeline == loading the timeline
	if (timeline.isEmpty()) {
		return loadHomeTimeline();
	}

	qlonglong maxTweetID = timeline[timeline.size() -1].getID() - 1;

	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(moreOldTimelineEnded(ProcessWrapper)));

	processing = true;
	emit showInfoMessage(TimelineControl::trUtf8("Loading more tweets..."));
	reyn.loadHomeTimeline(-1, maxTweetID, 50);
}


// After loading a timeline
void TimelineControl::moreOldTimelineEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		processing = true;
		return;
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(moreOldTimelineEnded(ProcessWrapper)));

	CoreResult issue = result.processIssue;
	QVariantList resList = result.results.toList();
	Timeline newTweets;

	switch (issue) {
		case TIMELINE_RETRIEVED:
			newTweets.fillWithVariant(resList);
			timeline.append(newTweets);
			emit timelineChanged();
			// Process successful
			emit actionEnded(true, TimelineControl::trUtf8("Tweets loaded"), false);
			break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			return;

		// Problems that can be solved trying later
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
