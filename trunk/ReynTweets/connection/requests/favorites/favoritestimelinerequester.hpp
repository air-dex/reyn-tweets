/// @file favoritestimelinerequester.hpp
/// @brief Header of FavoritesTimelineRequester
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

#ifndef FAVORITESTIMELINEREQUESTER_HPP
#define FAVORITESTIMELINEREQUESTER_HPP

#include "../authenticationrequester.hpp"
#include "../identificationway.hpp"

class FavoritesTimelineRequester : public AuthenticationRequester
{
	Q_OBJECT

	public:
		/// @fn FavoritesTimelineRequester(OAuthManager & authManager,
		///								   qlonglong uid = -1,
		///								   int nbTweets = 1-,
		///								   qlonglong oldestTweetID = -1,
		///								   int nbPages = 0,
		///								   bool withEntities = false);
		/// @brief Constructor with an ID.
		/// @param authManager Entity with authentication datas
		/// @param uid ID of the user whose favorites timeline will be
		/// retrieved by the request.
		/// @param nbTweets Value of count
		/// @param oldestTweetID Value of sinceID
		/// @param nbPages Value of page
		/// @param withEntities Value of includeEntities
		FavoritesTimelineRequester(OAuthManager & authManager,
								   qlonglong uid = -1,
								   int nbTweets = -1,
								   qlonglong oldestTweetID = -1,
								   int nbPages = 0,
								   bool withEntities = false);

		/// @fn FavoritesTimelineRequester(OAuthManager & authManager,
		///								   QString userName = "",
		///								   int nbTweets = 20,
		///								   qlonglong oldestTweetID = -1,
		///								   int nbPages = 0,
		///								   bool withEntities = false);
		/// @brief Constructor with a screen name.
		/// @param authManager Entity with authentication datas
		/// @param userName Screen name of the user whose favorites timeline
		/// will be retrieved by the request.
		/// @param nbTweets Value of count
		/// @param oldestTweetID Value of sinceID
		/// @param nbPages Value of page
		/// @param withEntities Value of includeEntities
		FavoritesTimelineRequester(OAuthManager & authManager,
								   QString userName = "",
								   int nbTweets = 20,
								   qlonglong oldestTweetID = -1,
								   int nbPages = 0,
								   bool withEntities = false);

	protected:
		/// @brief How the user is identified
		IdentificationWay idWay;

		/// @brief ID of the user
		qlonglong userID;

		/// @brief Screen name of the user
		QString screenName;

		/// @brief Number of tweets
		int count;

		/// @brief Minimum ID possible in the timeline
		qlonglong sinceID;

		/// @brief Number of pages
		int page;

		/// @brief Boolean whose value is true if tweet entities have to be
		/// included in the tweets
		bool includeEntities;

		/// @fn void buildGETParameters();
		/// @brief Building getParameters
		void buildGETParameters();
};

#endif // FAVORITESTIMELINEREQUESTER_HPP
