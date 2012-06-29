/// @file gettweetprocess.hpp
/// @brief Header of GetTweetProcess
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

#ifndef GETTWEETPROCESS_HPP
#define GETTWEETPROCESS_HPP

#include "singletwittercallprocess.hpp"

/// @class GetTweetProcess
/// @brief Retrieving a tweet
class GetTweetProcess : public SingleTwitterCallProcess
{
	Q_OBJECT

	public:
		/// @fn GetTweetProcess(qlonglong id,
		///						bool userIDonly,
		///						bool withEntities,
		///						bool withRTid);
		/// @brief Constructor
		/// @param id ID of the tweet to retrieve
		/// @param userIDonly Only include the userID in the "user" field of a tweet
		/// @param withEntities Including Tweet Entities in tweets
		/// @param withRTid If set to true and if the user retweeted the tweet,
		/// including the user's retweet ID.
		GetTweetProcess(qlonglong id,
						bool userIDonly,
						bool withEntities,
						bool withRTid);

	protected:
		/// @brief ID of the tweet to retrieve
		qlonglong tweetID;

		/// @brief Only include the userID in the "user" field of a tweet
		bool trimUser;

		/// @brief Including Tweet Entities in tweets
		bool includeEntities;

		/// @brief If set to true and if the user retweeted the tweet,
		/// including the user's retweet ID.
		bool includeMyRetweet;

		/// @fn void callTwitter();
		/// @brief Retrieving the tweet
		void callTwitter();
};

#endif // GETTWEETPROCESS_HPP
