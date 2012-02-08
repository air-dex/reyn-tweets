/// @file medialist.hpp
/// @brief Header of Medialist
///
/// Revisions older than r243 was in /trunk/ReynTwets/model
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

#ifndef MEDIALIST_HPP
#define MEDIALIST_HPP

#include <QVariant>
#include "media.hpp"
#include "../reyntweetslistable.tpp"

/// @class MediaList
/// @brief List of Medias
class MediaList : public ReynTweetsListable<Media>
{
	public:
		/// @fn MediaList();
		/// @brief Constructor
		MediaList();

		/// @fn virtual ~MediaList();
		/// @brief Destructor
		virtual ~MediaList();

		/// @fn MediaList(const MediaList & list);
		/// @brief Copy constructor
		/// @param list MediaList to copy
		MediaList(const MediaList & list);

		/// @fn const MediaList & operator=(const MediaList & list);
		/// @brief Affrection operator
		/// @param list MediaList to affect
		const MediaList & operator=(const MediaList & list);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	protected:
		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const MediaList & list);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const MediaList & list);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										MediaList & list);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										MediaList & list);
};

// Serialization of MediaList
Q_DECLARE_METATYPE(MediaList)

/// @fn QDataStream & operator<<(QDataStream & out, const MediaList & list);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const MediaList & list);

/// @fn QDataStream & operator>>(QDataStream & in, MediaList & list);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, MediaList & list);

#endif // MEDIALIST_HPP
