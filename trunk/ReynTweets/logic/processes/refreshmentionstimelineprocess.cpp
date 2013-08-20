/// @file refreshmentionstimelineprocess.cpp
/// @brief Implementation of RefreshMentionsTimelineProcess
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2013 Romain Ducher
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

#include "refreshmentionstimelineprocess.hpp"

// Constructor
RefreshMentionsTimelineProcess::RefreshMentionsTimelineProcess(qlonglong oldestTweetID,
															   bool userIDonly,
															   bool withEntities,
															   bool withContributorsDetails) :
	RefreshTimelineProcess(oldestTweetID),
	trimUser(userIDonly),
	includeEntities(withEntities),
	contributorsDetails(withContributorsDetails)
{}


/////////////////////
// Calling Twitter //
/////////////////////

// Step 1
void RefreshMentionsTimelineProcess::retrievingFirstTweets() {
	connect(&twitter, &ReynTwitterCalls::sendResult,
			this, &RefreshMentionsTimelineProcess::loadFirstTweetsEnded);

	twitter.retrieveMentionsTimeline(sinceID -1,
									 -1,
									 trimUser,
									 includeEntities,
									 ReynTwitterCalls::MAX_TWEETS_COUNT,
									 contributorsDetails);
}

// Step 2
void RefreshMentionsTimelineProcess::retrievingIntermediateTweets() {
	connect(&twitter, &ReynTwitterCalls::sendResult,
			this, &RefreshMentionsTimelineProcess::loadIntermediateTweetsEnded);

	twitter.retrieveMentionsTimeline(sinceID -1,
									 oldestNewTweetID,
									 trimUser,
									 includeEntities,
									 ReynTwitterCalls::MAX_TWEETS_COUNT,
									 contributorsDetails);
}
