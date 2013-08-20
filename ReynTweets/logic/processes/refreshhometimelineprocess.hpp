/// @file refreshhometimelineprocess.hpp
/// @brief Header of RefreshHomeTimelineProcess
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2013 Romain Ducher
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

#ifndef REFRESHHOMETIMELINEPROCESS_HPP
#define REFRESHHOMETIMELINEPROCESS_HPP

#include "refreshtimelineprocess.hpp"

/// @class RefreshHomeTimelineProcess
/// @brief Process for refreshing a home timeline.
class RefreshHomeTimelineProcess : public RefreshTimelineProcess
{
	Q_OBJECT

	public:
		/// @fn RefreshHomeTimelineProcess(Tweet oldestTweet,
		///								   bool userIDonly = false,
		///								   bool withEntities = false,
		///								   bool withoutReplies = false,
		///								   bool withContributorsDetails = false);
		/// @brief Constructor
		/// @param oldestTweet Value of latestTweet
		/// @param userIDonly Value of trimUser
		/// @param withEntities Value of includeEntities
		/// @param withoutReplies Value of excludeReplies
		/// @param withContributorsDetails Value of contributorsDetails
		RefreshHomeTimelineProcess(Tweet oldestTweet,
								   bool userIDonly = false,
								   bool withEntities = false,
								   bool withoutReplies = false,
								   bool withContributorsDetails = false);


	protected:
		////////////////
		// Parameters //
		////////////////

		/// @brief Only include the userID in the "user" field of a tweet
		bool trimUser;

		/// @brief Including Tweet Entities in tweets
		bool includeEntities;

		/// @brief Prevent the return timeline from replies
		bool excludeReplies;

		/// @brief Including details about contributors
		bool contributorsDetails;


		/////////////////
		// The process //
		/////////////////

		/// @fn virtual void retrievingFirstTweets();
		/// @brief Calling Twitter to load the most recent tweets.
		virtual void retrievingFirstTweets();

		/// @fn virtual void retrievingIntermediateTweets();
		/// @brief Calling Twitter to load intermediate tweets.
		virtual void retrievingIntermediateTweets();
};

#endif // REFRESHHOMETIMELINEPROCESS_HPP
