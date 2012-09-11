/// @file mentionstimelinerequester.hpp
/// @brief Header of MentionsTimelineRequester
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

#ifndef MENTIONSTIMELINEREQUESTER_HPP
#define MENTIONSTIMELINEREQUESTER_HPP

#include "../twitterrequester.hpp"

/// @class MentionsTimelineRequester
/// @brief Timeline containing the mentions of the user
/// @see https://dev.twitter.com/docs/api/1/get/statuses/mentions
class MentionsTimelineRequester : public TwitterRequester
{
		Q_OBJECT
	public:
		/// @fn MentionsTimelineRequester(OAuthManager & authManager,
		///								  qlonglong oldestTweetID = -1,
		///								  qlonglong youngestTweetID = -1,
		///								  bool userIDonly = false,
		///								  bool withRetweets = false,
		///								  bool withEntities = false,
		///								  int nbTweets = 20,
		///								  bool withContributorsDetails = false);
		/// @brief Constructor
		/// @param authManager Entity with authentication datas
		/// @param oldestTweetID Value of sinceID
		/// @param youngestTweetID Value of maxID
		/// @param userIDonly Value of trimUser
		/// @param withRetweets Value of includeRetweets
		/// @param withEntities Value of includeEntities
		/// @param nbTweets Value of count
		/// @param withContributorsDetails Value of contributorsDetails
		MentionsTimelineRequester(OAuthManager & authManager,
								  qlonglong oldestTweetID = -1,
								  qlonglong youngestTweetID = -1,
								  bool userIDonly = false,
								  bool withRetweets = false,
								  bool withEntities = false,
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

		/// @brief Includng retweets
		bool includeRetweets;

		/// @brief Including Tweet Entities in tweets
		bool includeEntities;

		/// @brief Including details about contributors
		bool contributorsDetails;

		/// @fn void buildGETParameters();
		/// @brief Building getParameters
		void buildGETParameters();
};

#endif // MENTIONSTIMELINEREQUESTER_HPP
