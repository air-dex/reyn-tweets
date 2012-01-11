/// @file tweet.hpp
/// @brief Header of Tweet
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

#ifndef USERMENTION_HPP
#define USERMENTION_HPP

#include "indexbounds.hpp"
#include "reyntweetsserializable.hpp"

class UserMention : public ReynTweetsSerializable
{
		Q_OBJECT
	public:
		explicit UserMention(QObject *parent = 0);

	protected:
		/// @brief UserID
		long userID;

		/// @brief String version of userID
		QString IDstr;

		/// @brief Screen name of the user
		QString screenName;

		/// @brief User's name
		QString userName;

		/// @brief Indexes of the mention in the tweet
		IndexBounds indices;

};

#endif // USERMENTION_HPP
