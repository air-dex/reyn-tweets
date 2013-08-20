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

#include "../twitterrequester.hpp"

/// @class HomeTimelineRequester
/// @brief Request to retrieve the timeline withh all the users' friends' tweets
/// @see https://dev.twitter.com/docs/api/1.1/get/statuses/home_timeline
class HomeTimelineRequester : public TwitterRequester
{
	Q_OBJECT

	public:
		/// @fn HomeTimelineRequester(TwitterAuthenticator & authManager,
		///							  qlonglong oldestTweetID = -1,
		///							  qlonglong youngestTweetID = -1,
		///							  bool userIDonly = false,
		///							  bool withEntities = false,
		///							  bool withoutReplies = false,
		///							  int nbTweets = 20,
		///							  bool withContributorsDetails = false);
		/// @brief Constructor
		/// @param authManager Entity with authentication datas
		/// @param oldestTweetID Value of sinceID
		/// @param youngestTweetID Value of maxID
		/// @param userIDonly Value of trimUser
		/// @param withEntities Value of includeEntities
		/// @param withoutReplies Value of excludeReplies
		/// @param nbTweets Value of count
		/// @param withContributorsDetails Value of contributorsDetails
		HomeTimelineRequester(TwitterAuthenticator & authManager,
							  qlonglong oldestTweetID = -1,
							  qlonglong youngestTweetID = -1,
							  bool userIDonly = false,
							  bool withEntities = false,
							  bool withoutReplies = false,
							  int nbTweets = 20,
							  bool withContributorsDetails = false);

	protected:
		/// @brief Number of tweets in the timeline.
		/// <strong>count &lt; 200</strong>
		int count;

		/// @brief Minimum tweet ID allowed in the timeline
		qlonglong sinceID;

		/// @brief Maximum tweet ID allowed in the timeline
		qlonglong maxID;

		/// @brief Only include the userID in the "user" field of a tweet
		bool trimUser;

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
