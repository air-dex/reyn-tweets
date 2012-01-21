/// @file showtweetrequester.hpp
/// @brief Header of ShowTweetRequester
/// @author Romain Ducher

/*
Copyright 2012 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SHOWTWEETREQUESTER_HPP
#define SHOWTWEETREQUESTER_HPP

#include "../genericrequester.hpp"

/// @class ShowTweetRequester
/// @brief Requester for getting details about a tweet identified by its ID.
class ShowTweetRequester : public GenericRequester
{
	Q_OBJECT

	public:
		/// @fn ShowTweetRequester(qlonglong id,
		///						   bool entities = true,
		///						   bool userIdsOnly = false);
		/// @brief Constructor
		/// @param id ID of the tweet
		/// @param entities Include Tweet Entities in th reply ?
		/// @param userIdsOnly Return only user IDs instead of all the values ?
		ShowTweetRequester(qlonglong iD,
						   bool entities = true,
						   bool userIdsOnly = false);

	protected:
		/// @brief ID of the tweet
		qlonglong tweetID;

		/// @brief Boolean indicating if entities of a tweet have to be included
		/// in the reply
		bool includeEntities;

		/// @brief When this value is set to true, only the id and id_str values
		/// of the user are returned.
		bool trimUser;

		/// @fn void buildGETParameters();
		/// @brief Building getParameters
		void buildGETParameters();

};

#endif // SHOWTWEETREQUESTER_HPP
