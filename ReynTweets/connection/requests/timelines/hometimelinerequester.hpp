/// @file hometimelinerequester.hpp
/// @brief Header of HomeTimelineRequester
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

#ifndef HOMETIMELINEREQUESTER_HPP
#define HOMETIMELINEREQUESTER_HPP

#include "../authenticationrequester.hpp"

/// @class HomeTimelineRequester
/// @brief Request to retrieve the timeline withh all the users' friends ' tweets.
/// @see https://dev.twitter.com/docs/api/1/get/statuses/home_timeline
class HomeTimelineRequester : public AuthenticationRequester
{
	Q_OBJECT

	public:
		/// @fn HomeTimelineRequester(OAuthManager & authManager,
		///							  int nbTweets = 20,
		///							  qlonglong oldestTweetID = -1,
		///							  qlonglong youngestTweetID = -1,
		///							  int nbPage = 0,
		///							  bool userIDonly = false,
		///							  bool withRetweets = false,
		///							  bool withEntities = false,
		///							  bool withoutReplies = false,
		///							  bool withContributorsDetails = false);
		/// @brief Constructor
		/// @param authManager Entity with authentication datas
		/// @param nbTweets Value of count
		/// @param oldestTweetID Value of sinceID
		/// @param youngestTweetID Value of maxID
		/// @param nbPage Value of page
		/// @param userIDonly Value of trimUser
		/// @param withRetweets Value of includeRetweets
		/// @param withEntities Value of includeEntities
		/// @param withoutReplies Value of excludeReplies
		/// @param withContributorsDetails Value of contributorsDetails
		HomeTimelineRequester(OAuthManager & authManager,
							  int nbTweets = 20,
							  qlonglong oldestTweetID = -1,
							  qlonglong youngestTweetID = -1,
							  int nbPage = 0,
							  bool userIDonly = false,
							  bool withRetweets = false,
							  bool withEntities = false,
							  bool withoutReplies = false,
							  bool withContributorsDetails = false);

	protected:
		/// @brief Number of tweets in the timeline.
		/// <strong>count &lt; 200</strong>
		int count;

		/// @brief Minimum tweet ID allowed in the timeline
		qlonglong sinceID;

		/// @brief Maximum tweet ID allowed in the timeline
		qlonglong maxID;

		/// @brief Number of pages to retrieve. Start at 1, not 0.
		int page;

		/// @brief Only include the userID in the "user" field of a tweet
		bool trimUser;

		/// @brief Includng retweets
		bool includeRetweets;

		/// @brief Including Tweet Entities in tweets
		bool includeEntities;

		/// @brief Prevent the return timeline from replies
		bool excludeReplies;

		/// @brief Including details about contributors
		bool contributorsDetails;

		/// @fn void buildGETParameters();
		/// @brief Building getParameters
		void buildGETParameters();
};

#endif // HOMETIMELINEREQUESTER_HPP
