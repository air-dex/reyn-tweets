/// @file favoriteprocess.cpp
/// @brief Implementation of FavoriteProcess
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

#include "favoriteprocess.hpp"

// Constructor
FavoriteProcess::FavoriteProcess(qlonglong id, bool fav, bool entities) :
	SingleTwitterCallProcess(ReynTweets::FAVORITE_SUCCESSFUL),
	tweetID(id),
	favorite(fav),
	includeEntities(entities)
{}

// Start the process calling twitter to favorite the tweet
void FavoriteProcess::callTwitter() {
	if (favorite) {
		twitter.favoriteTweet(tweetID, includeEntities);
	} else {
		twitter.unfavoriteTweet(tweetID, includeEntities);
	}
}
