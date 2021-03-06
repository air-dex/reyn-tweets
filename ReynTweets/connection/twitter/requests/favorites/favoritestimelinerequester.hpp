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

#include "../twitterrequester.hpp"
#include "../../../common/requests/identificationway.hpp"

/// @class FavoritesTimelineRequester
/// @brief Requester to retrieve the timeline with the favorite tweets of a user
/// @see https://dev.twitter.com/docs/api/1.1/get/favorites
class FavoritesTimelineRequester : public TwitterRequester
{
	Q_OBJECT

	public:
		/// @fn FavoritesTimelineRequester(TwitterAuthenticator & authManager,
		///								   qlonglong uid = Twitter::FAKE_USER_ID,
		///								   qlonglong oldestTweetID = Twitter::FAKE_TWEET_ID,
		///								   qlonglong earliestTweetID = Twitter::FAKE_TWEET_ID,
		///								   bool withEntities = false,
		///								   int nbTweets = Twitter::DEFAULT_TWEETS_COUNT);
		/// @brief Constructor with an ID.
		/// @param authManager Entity with authentication datas
		/// @param uid ID of the user whose favorites timeline will be
		/// retrieved by the request.
		/// @param oldestTweetID Value of sinceID
		/// @param earliestTweetID Value of maxID
		/// @param withEntities Value of includeEntities
		/// @param nbTweets Value of count
		FavoritesTimelineRequester(TwitterAuthenticator & authManager,
								   qlonglong uid = Twitter::FAKE_USER_ID,
								   qlonglong oldestTweetID = Twitter::FAKE_TWEET_ID,
								   qlonglong earliestTweetID = Twitter::FAKE_TWEET_ID,
								   bool withEntities = false,
								   int nbTweets = Twitter::DEFAULT_TWEETS_COUNT);

		/// @fn FavoritesTimelineRequester(TwitterAuthenticator & authManager,
		///								   QString userName = Twitter::FAKE_SCREEN_NAME,
		///								   qlonglong oldestTweetID = Twitter::FAKE_TWEET_ID,
		///								   qlonglong earliestTweetID = Twitter::FAKE_TWEET_ID,
		///								   bool withEntities = false,
		///								   int nbTweets = Twitter::DEFAULT_TWEETS_COUNT);
		/// @brief Constructor with a screen name.
		/// @param authManager Entity with authentication datas
		/// @param userName Screen name of the user whose favorites timeline
		/// will be retrieved by the request.
		/// @param oldestTweetID Value of sinceID
		/// @param earliestTweetID Value of maxID
		/// @param withEntities Value of includeEntities
		/// @param nbTweets Value of count
		FavoritesTimelineRequester(TwitterAuthenticator & authManager,
								   QString userName = Twitter::FAKE_SCREEN_NAME,
								   qlonglong oldestTweetID = Twitter::FAKE_TWEET_ID,
								   qlonglong earliestTweetID = Twitter::FAKE_TWEET_ID,
								   bool withEntities = false,
								   int nbTweets = Twitter::DEFAULT_TWEETS_COUNT);

	protected:
		/// @brief How the user is identified
		LibRT::IdentificationWay idWay;

		/// @brief ID of the user
		qlonglong userID;

		/// @brief Screen name of the user
		QString screenName;

		/// @brief Number of tweets
		int count;

		/// @brief Minimum ID possible in the timeline
		qlonglong sinceID;

		/// @brief Minimum ID possible in the timeline
		qlonglong maxID;

		/// @brief Boolean whose value is true if tweet entities have to be
		/// included in the tweets
		bool includeEntities;

		/// @fn void buildGETParameters();
		/// @brief Building getParameters
		void buildGETParameters();
};

#endif // FAVORITESTIMELINEREQUESTER_HPP
