/// @file favoritestimelinerequester.cpp
/// @brief Implementation of FavoritesTimelineRequester
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

#include "favoritestimelinerequester.hpp"
#include "../../../common/utils/connectionutils.hpp"

// Constructor with ID
FavoritesTimelineRequester::FavoritesTimelineRequester(TwitterAuthenticator & authManager,
													   qlonglong uid,
													   qlonglong oldestTweetID,
													   qlonglong earliestTweetID,
													   bool withEntities,
													   int nbTweets) :
	TwitterRequester(LibRT::GET, Twitter::FAVORITE_TIMELINE_URL, authManager),
	idWay(LibRT::ID),
	userID(uid),
	screenName(Twitter::FAKE_SCREEN_NAME),
	count(nbTweets),
	sinceID(oldestTweetID),
	maxID(earliestTweetID),
	includeEntities(withEntities)
{}

// Constructor with screen name
FavoritesTimelineRequester::FavoritesTimelineRequester(TwitterAuthenticator & authManager,
													   QString userName,
													   qlonglong oldestTweetID,
													   qlonglong earliestTweetID,
													   bool withEntities,
													   int nbTweets) :
	TwitterRequester(LibRT::GET, Twitter::FAVORITE_TIMELINE_URL, authManager),
	idWay(LibRT::SCREEN_NAME),
	userID(Twitter::FAKE_USER_ID),
	screenName(userName),
	count(nbTweets),
	sinceID(oldestTweetID),
	maxID(earliestTweetID),
	includeEntities(withEntities)
{}


// Building getParameters
void FavoritesTimelineRequester::buildGETParameters() {
	// Value for the user identifier
	switch (idWay) {
		case LibRT::ID:
			getParameters.insert("user_id", QString::number(userID));
			break;
		case LibRT::SCREEN_NAME:
			getParameters.insert("screen_name", screenName);
			break;
	}

	if (count != Twitter::DEFAULT_TWEETS_COUNT) {
		getParameters.insert("count", QString::number(count));
	}


	if (sinceID != Twitter::FAKE_TWEET_ID) {
		getParameters.insert("since_id", QString::number(sinceID));
	}


	if (maxID != Twitter::FAKE_TWEET_ID) {
		getParameters.insert("max_id", QString::number(maxID));
	}

	getParameters.insert("include_entities", boolInString(includeEntities));
}
