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
#include "../../../tools/utils.hpp"

// Constructor with ID
FavoritesTimelineRequester::FavoritesTimelineRequester(OAuthManager & authManager,
													   qlonglong uid,
													   qlonglong oldestTweetID,
													   bool withEntities,
													   int nbPages,
													   int nbTweets) :
	TwitterRequester(GET, TwitterURL::FAVORITE_TIMELINE_URL, authManager),
	idWay(ID),
	userID(uid),
	screenName(""),
	count(nbTweets),
	sinceID(oldestTweetID),
	page(nbPages),
	includeEntities(withEntities)
{}

// Constructor with screen name
FavoritesTimelineRequester::FavoritesTimelineRequester(OAuthManager & authManager,
													   QString userName,
													   qlonglong oldestTweetID,
													   bool withEntities,
													   int nbPages,
													   int nbTweets) :
	TwitterRequester(GET, TwitterURL::FAVORITE_TIMELINE_URL, authManager),
	idWay(SCREEN_NAME),
	userID(-1),
	screenName(userName),
	count(nbTweets),
	sinceID(oldestTweetID),
	page(nbPages),
	includeEntities(withEntities)
{}


// Building getParameters
void FavoritesTimelineRequester::buildGETParameters() {
	QString idString = "";

	// Value for "id"
	switch (idWay) {
		case ID:
			idString = QString::number(userID);
			break;
		case SCREEN_NAME:
			idString = screenName;
			break;
	}

	getParameters.insert("id", idString);

	if (count != -1) {
		getParameters.insert("count", QString::number(count));
	}


	if (sinceID != -1) {
		getParameters.insert("since_id", QString::number(sinceID));
	}

	if (page > 0) {
		getParameters.insert("page", QString::number(page));
	}

	getParameters.insert("include_entities", boolInString(includeEntities));
}
