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
		/// @fn FavoriteProcess(qlonglong id, bool fav);
		/// @brief Constructor
		/// @param id ID of the tweet
		/// @param fav Boolean indicating if the tweet hyas to be favorited
		/// (true) or unfavorited (false).
		FavoriteProcess(qlonglong id, bool fav);

	protected:
		/// @brief ID of the tweet to favorite
		qlonglong tweetID;

		/// @brief Boolean whose value is true if the process has to favorite
		/// the tweet or false if it has to unfavorite it.
		bool favorite;

		/// @fn void favoriteTweet();
		/// @brief Entry point of the process if un
		void callTwitter();
};

#endif // FAVORITEPROCESS_HPP
