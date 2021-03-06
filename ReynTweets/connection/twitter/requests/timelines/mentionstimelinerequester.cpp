/// @file mentionstimelinerequester.cpp
/// @brief Implementation of MentionsTimelineRequester
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

#include "mentionstimelinerequester.hpp"
#include "../../../common/utils/connectionutils.hpp"

MentionsTimelineRequester::MentionsTimelineRequester(TwitterAuthenticator &authManager,
													 qlonglong oldestTweetID,
													 qlonglong youngestTweetID,
													 bool userIDonly,
													 bool withEntities,
													 int nbTweets,
													 bool withContributorsDetails) :
	TwitterRequester(LibRT::GET, Twitter::MENTIONS_TIMELINE_URL, authManager),
	count(nbTweets),
	sinceID(oldestTweetID),
	maxID(youngestTweetID),
	trimUser(userIDonly),
	includeEntities(withEntities),
	contributorsDetails(withContributorsDetails)
{}

// Building getParameters
void MentionsTimelineRequester::buildGETParameters() {
	if (count != Twitter::DEFAULT_TWEETS_COUNT) {
		getParameters.insert("count", QString::number(count));
	}

	if (sinceID > Twitter::FAKE_TWEET_ID) {
		getParameters.insert("since_id", QString::number(sinceID));
	}


	if (maxID > Twitter::FAKE_TWEET_ID) {
		getParameters.insert("max_id", QString::number(maxID));
	}

	getParameters.insert("trim_user", boolInString(trimUser));
	getParameters.insert("include_entities", boolInString(includeEntities));
	getParameters.insert("contributors_details", boolInString(contributorsDetails));
}
