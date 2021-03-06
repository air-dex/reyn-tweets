/// @file favoriteprocess.hpp
/// @brief Header of FavoriteProcess
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

#ifndef FAVORITEPROCESS_HPP
#define FAVORITEPROCESS_HPP

#include "singletwittercallprocess.hpp"

/// @class FavoriteProcess
/// @brief Process to favorite or to unfavorite a tweet.
class FavoriteProcess : public SingleTwitterCallProcess
{
	Q_OBJECT

	public:
		/// @fn FavoriteProcess(qlonglong id, bool fav, bool entities = true);
		/// @brief Constructor
		/// @param id ID of the tweet
		/// @param fav Boolean indicating if the tweet hyas to be favorited
		/// (true) or unfavorited (false).
		/// @param entities Including Tweet Entities in the favorited (true).
		FavoriteProcess(qlonglong id, bool fav, bool entities = true);

	protected:
		/// @brief ID of the tweet to favorite
		qlonglong tweetID;

		/// @brief Boolean whose value is true if the process has to favorite
		/// the tweet or false if it has to unfavorite it.
		bool favorite;

		/// @brief Boolean telling whether Tweet Entities have to be included in
		/// the response (when set to true).
		bool includeEntities;

		/// @fn void callTwitter();
		/// @brief Calling the Twitter API to favorite or to unfavorite the tweet.
		void callTwitter();
};

#endif // FAVORITEPROCESS_HPP
