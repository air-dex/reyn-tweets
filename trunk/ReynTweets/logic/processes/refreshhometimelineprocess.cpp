/// @file refreshhometimelineprocess.cpp
/// @brief Implementation of RefreshHomeTimelineProcess
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

#include "refreshhometimelineprocess.hpp"
#include "../reyntweetsutils.hpp"

// Constructor
RefreshHomeTimelineProcess::RefreshHomeTimelineProcess(Tweet oldestTweet,
													   bool userIDonly,
													   bool withEntities,
													   bool withoutReplies,
													   bool withContributorsDetails) :
	RefreshTimelineProcess(oldestTweet),
	trimUser(userIDonly),
	includeEntities(withEntities),
	excludeReplies(withoutReplies),
	contributorsDetails(withContributorsDetails)
{}


/////////////////////
// Calling Twitter //
/////////////////////

// Step 1
void RefreshHomeTimelineProcess::retrievingFirstTweets() {
	twitter.retrieveHomeTimeline(latestTweet.getIDstr().toLongLong() -1,
								 ReynTweets::FAKE_TWEET_ID,
								 trimUser,
								 includeEntities,
								 excludeReplies,
								 Twitter::MAX_TWEETS_COUNT,
								 contributorsDetails);
}

// Step 2
void RefreshHomeTimelineProcess::retrievingIntermediateTweets() {
	twitter.retrieveHomeTimeline(latestTweet.getIDstr().toLongLong() -1,
								 oldestNewTweet.getIDstr().toLongLong(),
								 trimUser,
								 includeEntities,
								 excludeReplies,
								 Twitter::MAX_TWEETS_COUNT,
								 contributorsDetails);
}
