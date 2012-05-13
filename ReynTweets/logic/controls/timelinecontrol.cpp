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
    GenericControl()
{}

// Declaring TweetControl to the QML system
void TimelineControl::declareQML() {
    qmlRegisterType<TimelineControl>("ReynTweetsControls",
                                     0, 1,
                                     "TimelineControl");
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

// Reading the property tl_length
int TimelineControl::getTimelineLength() {
    return timeline.size();
}

// Replacing a tweet
void TimelineControl::replaceTweet(QVariant updatedTweet, int tweetIndex) {
    if (tweetIndex < 0 || tweetIndex >= timeline.count()) {
        return;
    }

    Tweet & tweet = timeline[tweetIndex];
    tweet.reset();
    tweet.fillWithVariant(updatedTweet.toMap());
}

// Replacing a tweet
void TimelineControl::deleteTweet(int tweetIndex) {
    if (tweetIndex < 0 || tweetIndex >= timeline.count()) {
        return;
    }

    timeline.removeAt(tweetIndex);
    emit timelineChanged();
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
    reyn.loadHomeTimeline(-1, -1, 50, false, true, true, false, 0);
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
