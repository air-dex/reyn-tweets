/// @file retweetsbymerequester.hpp
/// @brief Header of RetweetsByMeRequester
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

#ifndef RETWEETSBYMEREQUESTER_HPP
#define RETWEETSBYMEREQUESTER_HPP

#include "../twitterrequester.hpp"

/// @class RetweetsByMeRequester
/// @brief Retrieving the timeline with the tweets retweeted by the user.
/// @see https://dev.twitter.com/docs/api/1/get/statuses/retweeted_by_me
class RetweetsByMeRequester : public TwitterRequester
{
	Q_OBJECT

	public:
		/// @fn RetweetsByMeRequester(OAuthManager & authManager,
		///							  qlonglong oldestID = -1,
		///							  qlonglong youngestID = -1,
		///							  int nbRetweets = 20,
		///							  bool userIDonly = false,
		///							  bool withEntities = false);
		/// @brief Constructor
		/// @param authManager Entity with authentication datas
		/// @param oldestID Minimum tweet ID possible in the timeline
		/// @param youngestID Maximum tweet ID possible in the timeline
		/// @param nbRetweets Number of tweets
		/// @param userIDonly In tweets, giving only the ID of the author (true).
		/// @param withEntities Including Tweet Entities in the tweets (true).
		RetweetsByMeRequester(OAuthManager & authManager,
							  qlonglong oldestID = -1,
							  qlonglong youngestID = -1,
							  int nbRetweets = 20,
							  bool userIDonly = false,
							  bool withEntities = false);

	protected:
		/// @brief Minimum tweet ID allowed in the timeline
		qlonglong sinceID;

		/// @brief Maximum tweet ID allowed in the timeline
		qlonglong maxID;

		/// @brief Number of tweets in the timeline.
		/// <strong>count &lt; 100</strong>
		int count;

		/// @brief Only include the userID in the "user" field of a tweet
		bool trimUser;

		/// @brief Including Tweet Entities in tweets
		bool includeEntities;

		/// @fn void buildGETParameters();
		/// @brief Building getParameters
		void buildGETParameters();
};

#endif // RETWEETSBYMEREQUESTER_HPP
