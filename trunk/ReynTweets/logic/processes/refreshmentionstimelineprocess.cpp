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
#include "../reyntweetsutils.hpp"

// Constructor
RefreshMentionsTimelineProcess::RefreshMentionsTimelineProcess(Tweet oldestTweet,
															   bool userIDonly,
															   bool withEntities,
															   bool withContributorsDetails) :
	RefreshTimelineProcess(oldestTweet),
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

	twitter.retrieveMentionsTimeline(latestTweet.getIDstr().toLongLong() -1,
									 ReynTweets::FAKE_TWEET_ID,
									 trimUser,
									 includeEntities,
									 Twitter::MAX_TWEETS_COUNT,
									 contributorsDetails);
}

// Step 2
void RefreshMentionsTimelineProcess::retrievingIntermediateTweets() {
	connect(&twitter, &ReynTwitterCalls::sendResult,
			this, &RefreshMentionsTimelineProcess::loadIntermediateTweetsEnded);

	twitter.retrieveMentionsTimeline(latestTweet.getIDstr().toLongLong() -1,
									 oldestNewTweet.getIDstr().toLongLong(),
									 trimUser,
									 includeEntities,
									 Twitter::MAX_TWEETS_COUNT,
									 contributorsDetails);
}
