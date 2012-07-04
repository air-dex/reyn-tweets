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
#include "../../../tools/utils.hpp"

MentionsTimelineRequester::MentionsTimelineRequester(OAuthManager &authManager,
													 qlonglong oldestTweetID,
													 qlonglong youngestTweetID,
													 bool userIDonly,
													 bool withRetweets,
													 bool withEntities,
													 int nbTweets,
													 bool withContributorsDetails) :
	AuthenticationRequester(GET, TwitterURL::MENTIONS_TIMELINE_URL, authManager),
	count(nbTweets),
	sinceID(oldestTweetID),
	maxID(youngestTweetID),
	trimUser(userIDonly),
	includeRetweets(withRetweets),
	includeEntities(withEntities),
	contributorsDetails(withContributorsDetails)
{}

// Building getParameters
void MentionsTimelineRequester::buildGETParameters() {
	if (count != 20) {
		getParameters.insert("count", QString::number(count));
	}

	if (sinceID > -1) {
		getParameters.insert("since_id", QString::number(sinceID));
	}


	if (maxID > -1) {
		getParameters.insert("max_id", QString::number(maxID));
	}

	getParameters.insert("trim_user", boolInString(trimUser));
	getParameters.insert("include_rts", boolInString(includeRetweets));
	getParameters.insert("include_entities", boolInString(includeEntities));
	getParameters.insert("contributors_details", boolInString(contributorsDetails));
}
