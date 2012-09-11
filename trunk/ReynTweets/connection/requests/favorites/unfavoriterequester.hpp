/// @file unfavoriterequester.hpp
/// @brief Header of UnfavoriteRequester
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

#ifndef UNFAVORITEREQUESTER_HPP
#define UNFAVORITEREQUESTER_HPP

#include "../twitterrequester.hpp"

/// @class UnfavoriteRequester
/// @brief Requester to unfavorite a tweet.
///
/// No need to override GenericRequester::buildPOSTParameters since there is not
/// any POST arguments.
/// @see https://dev.twitter.com/docs/api/1.1/post/favorites/destroy
class UnfavoriteRequester : public TwitterRequester
{
	Q_OBJECT

	public:
		/// @fn UnfavoriteRequester(OAuthManager & authManager,
		///							qlonglong id,
		///							bool withEntities = true);
		/// @brief Constructor
		/// @param authManager Entity with authentication datas
		/// @param id ID of the tweet to favorite
		/// @param withEntities Value of includeEntities
		UnfavoriteRequester(OAuthManager & authManager,
							qlonglong id,
							bool withEntities = true);

	protected:
		/// @brief ID of the tweet to unfavorite
		qlonglong tweetID;

		/// @brief Include Tweet Entities of the tweet in the reply ?
		bool includeEntities;

		/// @fn void buildPOSTParameters();
		/// @brief Building postParameters
		void buildPOSTParameters();
};

#endif // UNFAVORITEREQUESTER_HPP
