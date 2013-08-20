/// @file destroytweetrequester.hpp
/// @brief Header of DestroyTweetRequester
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

#ifndef DESTROYTWEETREQUESTER_HPP
#define DESTROYTWEETREQUESTER_HPP

#include "../twitterrequester.hpp"

/// @class DestroyTweetRequester
/// @brief Deleting tweets
/// @see https://dev.twitter.com/docs/api/1.1/post/statuses/destroy/%3Aid
class DestroyTweetRequester : public TwitterRequester
{
		Q_OBJECT
	public:
		/// @fn DestroyTweetRequester(OAuthManager & authManager,
		///							  qlonglong statusID,
		///							  bool userIDonly = false);
		/// @brief Constructor
		/// @param authManager Entities with OAuth values
		/// @param statusID ID of the tweet
		/// @param userIDonly Omit user details in the reply ?
		DestroyTweetRequester(TwitterManager & authManager,
							  qlonglong statusID,
							  bool userIDonly = false);

	protected:
		/// @brief ID of the tweet to favorite
		qlonglong tweetID;

		/// @brief Only include the userID in the "user" field of a tweet
		bool trimUser;

		/// @fn void buildPOSTParameters();
		/// @brief Building postParameters
		void buildPOSTParameters();
};

#endif // DESTROYTWEETREQUESTER_HPP
