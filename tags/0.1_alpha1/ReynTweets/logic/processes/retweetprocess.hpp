/// @file retweetprocess.hpp
/// @brief Header of RetweetProcess
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

#ifndef RETWEETPROCESS_HPP
#define RETWEETPROCESS_HPP

#include "singletwittercallprocess.hpp"

/// @class RetweetProcess
/// @brief Process consisting in retweeting a tweet
class RetweetProcess : public SingleTwitterCallProcess
{
	Q_OBJECT

	public:
		/// @fn RetweetProcess(qlonglong statusID,
		///					   bool withEntities = true,
		///					   bool userIDonly = false);
		/// @brief Constructor
		/// @param statusID ID of the tweet
		/// @param withEntities Including Tweet Entities ?
		/// @param userIDonly Omit user details in the reply ?
		RetweetProcess(qlonglong statusID,
					   bool withEntities = true,
					   bool userIDonly = false);

	protected:
		/// @brief ID of the tweet to favorite
		qlonglong tweetID;

		/// @brief Include Tweet Entities of the tweet in the reply ?
		bool includeEntities;

		/// @brief Only include the userID in the "user" field of a tweet
		bool trimUser;

		/// @fn void callTwitter();
		/// @brief Calling the Twitter API to retweet the tweet.
		void callTwitter();
};

#endif // RETWEETPROCESS_HPP
