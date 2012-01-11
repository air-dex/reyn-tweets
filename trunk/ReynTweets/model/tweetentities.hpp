/// @file tweetentities.hpp
/// @brief Header of TweetEntities
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

#ifndef TWEETENTITIES_HPP
#define TWEETENTITIES_HPP

#include <QList>
#include "hashtag.hpp"
#include "media.hpp"
#include "reyntweetsserializable.hpp"
#include "urlentity.hpp"
#include "usermention.hpp"

/// @class TweetEntities
/// @brief Entities of a tweet, such as its hashtags, its mentions and its URLs.
class TweetEntities : public ReynTweetsSerializable
{
		Q_OBJECT
	public:
		explicit TweetEntities(QObject *parent = 0);

	protected:
		/// @brief Medias
		QList<Media> medias;

		/// @brief URLs
		QList<URLEntity> urls;

		/// @brief User mentions
		QList<UserMention> userMentions;

		/// @brief Hashtags
		QList<Hashtag> hashtags;
};

#endif // TWEETENTITIES_HPP
