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
	TwitterRequester(Network::GET, TwitterURL::FAVORITE_TIMELINE_URL, authManager),
	idWay(IdWay::ID),
	userID(uid),
	screenName(""),
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
	TwitterRequester(Network::GET, TwitterURL::FAVORITE_TIMELINE_URL, authManager),
	idWay(IdWay::SCREEN_NAME),
	userID(-1),
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
		case IdWay::ID:
			getParameters.insert("user_id", QString::number(userID));
			break;
		case IdWay::SCREEN_NAME:
			getParameters.insert("screen_name", screenName);
			break;
	}

	if (count != 20) {
		getParameters.insert("count", QString::number(count));
	}


	if (sinceID != -1) {
		getParameters.insert("since_id", QString::number(sinceID));
	}


	if (maxID != -1) {
		getParameters.insert("max_id", QString::number(maxID));
	}

	getParameters.insert("include_entities", boolInString(includeEntities));
}
