/// @file hometimelinerequester.cpp
/// @brief Implementation of HomeTimelineRequester
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

#include "hometimelinerequester.hpp"
#include "../../../common/utils/connectionutils.hpp"

// Constructor
HomeTimelineRequester::HomeTimelineRequester(TwitterAuthenticator & authManager,
											 qlonglong oldestTweetID,
											 qlonglong youngestTweetID,
											 bool userIDonly,
											 bool withEntities,
											 bool withoutReplies,
											 int nbTweets,
											 bool withContributorsDetails) :
	TwitterRequester(LibRT::GET, TwitterURL::HOME_TIMELINE_URL, authManager),
	count(nbTweets),
	sinceID(oldestTweetID),
	maxID(youngestTweetID),
	trimUser(userIDonly),
	includeEntities(withEntities),
	excludeReplies(withoutReplies),
	contributorsDetails(withContributorsDetails)
{}

// Building getParameters
void HomeTimelineRequester::buildGETParameters() {
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
	getParameters.insert("include_entities", boolInString(includeEntities));
	getParameters.insert("exclude_replies", boolInString(excludeReplies));
	getParameters.insert("contributors_details", boolInString(contributorsDetails));
}
