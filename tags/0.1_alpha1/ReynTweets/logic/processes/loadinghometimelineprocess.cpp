/// @file loadinghometimelineprocess.cpp
/// @brief Implementation of LoadingHomeTimelineProcess
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

#include "loadinghometimelineprocess.hpp"

LoadingHomeTimelineProcess::LoadingHomeTimelineProcess(qlonglong oldestTweetID,
													   qlonglong youngestTweetID,
													   bool userIDonly,
													   bool withRetweets,
													   bool withEntities,
													   bool withoutReplies,
													   int nbPage,
													   int nbTweets,
													   bool withContributorsDetails) :
	SingleTwitterCallProcess(TIMELINE_RETRIEVED),
	count(nbTweets),
	sinceID(oldestTweetID),
	maxID(youngestTweetID),
	page(nbPage),
	trimUser(userIDonly),
	includeRetweets(withRetweets),
	includeEntities(withEntities),
	excludeReplies(withoutReplies),
	contributorsDetails(withContributorsDetails)
{}

// Asking something to Twitter
void LoadingHomeTimelineProcess::callTwitter() {
	twitter.retrieveHomeTimeline(sinceID,
								 maxID,
								 trimUser,
								 includeRetweets,
								 includeEntities,
								 excludeReplies,
								 page,
								 count,
								 contributorsDetails);
}
