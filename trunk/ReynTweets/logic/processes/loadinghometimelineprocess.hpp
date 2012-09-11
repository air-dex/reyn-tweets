/// @file loadinghometimelineprocess.hpp
/// @brief Header of LoadingHomeTimelineProcess
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

#ifndef LOADINGHOMETIMELINEPROCESS_HPP
#define LOADINGHOMETIMELINEPROCESS_HPP

#include "singletwittercallprocess.hpp"

/// @class LoadingHomeTimelineProcess
/// @brief Process to load the Home timeline
class LoadingHomeTimelineProcess : public SingleTwitterCallProcess
{
	Q_OBJECT

	public:
		/// @fn LoadingHomeTimelineProcess(qlonglong oldestTweetID = -1,
		///								   qlonglong youngestTweetID = -1,
		///								   bool userIDonly = false,
		///								   bool withEntities = false,
		///								   bool withoutReplies = false,
		///								   int nbTweets = 20,
		///								   bool withContributorsDetails = false);
		/// @brief Constructor
		/// @param oldestTweetID Value of sinceID
		/// @param youngestTweetID Value of maxID
		/// @param userIDonly Value of trimUser
		/// @param withEntities Value of includeEntities
		/// @param withoutReplies Value of excludeReplies
		/// @param nbTweets Value of count
		/// @param withContributorsDetails Value of contributorsDetails
		LoadingHomeTimelineProcess(qlonglong oldestTweetID = -1,
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

		/// @fn void callTwitter();
		/// @brief Loading the Home Timeline
		void callTwitter();
};

#endif // LOADINGHOMETIMELINEPROCESS_HPP
