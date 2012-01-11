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

#ifndef URLENTITY_HPP
#define URLENTITY_HPP

#include <QString>
#include "indexbounds.hpp"
#include "reyntweetsserializable.hpp"

class URLEntity : public ReynTweetsSerializable
{
		Q_OBJECT
	public:
		explicit URLEntity(QObject *parent = 0);

	protected:
		/// @brief Extracted URL
		QString url;

		/// @brief URL displayed on the tweet
		QString displayedURL;

		/// @brief Full URL (only for t.co URLs)
		QString expandedURL;

		/// @brief Indexes in the tweet
		IndexBounds indexes;
};

#endif // URLENTITY_HPP
