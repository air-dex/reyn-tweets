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
/// @see https://dev.twitter.com/docs/api/1.1/get/statuses/mentions_timeline
class MentionsTimelineRequester : public TwitterRequester
{
		Q_OBJECT
	public:
		/// @fn MentionsTimelineRequester(TwitterAuthenticator & authManager,
		///								  qlonglong oldestTweetID = Twitter::FAKE_TWEET_ID,
		///								  qlonglong youngestTweetID = Twitter::FAKE_TWEET_ID,
		///								  bool userIDonly = false,
		///								  bool withEntities = false,
		///								  int nbTweets = Twitter::DEFAULT_TWEETS_COUNT,
		///								  bool withContributorsDetails = false);
		/// @brief Constructor
		/// @param authManager Entity with authentication datas
		/// @param oldestTweetID Value of sinceID
		/// @param youngestTweetID Value of maxID
		/// @param userIDonly Value of trimUser
		/// @param withEntities Value of includeEntities
		/// @param nbTweets Value of count
		/// @param withContributorsDetails Value of contributorsDetails
		MentionsTimelineRequester(TwitterAuthenticator & authManager,
								  qlonglong oldestTweetID = Twitter::FAKE_TWEET_ID,
								  qlonglong youngestTweetID = Twitter::FAKE_TWEET_ID,
								  bool userIDonly = false,
								  bool withEntities = false,
								  int nbTweets = Twitter::DEFAULT_TWEETS_COUNT,
								  bool withContributorsDetails = false);

	protected:
		/// @brief Number of tweets in the timeline. <strong>0 &lt; count &lt;
		/// Twitter::MAX_TWEETS_COUNT</strong>
		int count;

		/// @brief Minimum tweet ID allowed in the timeline
		qlonglong sinceID;

		/// @brief Maximum tweet ID allowed in the timeline
		qlonglong maxID;

		/// @brief Only include the userID in the "user" field of a tweet
		bool trimUser;

		/// @brief Including Tweet Entities in tweets
		bool includeEntities;

		/// @brief Including details about contributors
		bool contributorsDetails;

		/// @fn void buildGETParameters();
		/// @brief Building getParameters
		void buildGETParameters();
};

#endif // MENTIONSTIMELINEREQUESTER_HPP
