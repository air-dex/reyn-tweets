/// @file medialist.hpp
/// @brief Header of Medialist
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

#ifndef MEDIALIST2_HPP
#define MEDIALIST2_HPP

#include <QVariant>
#include "media.hpp"
#include "../json/jsonarray.tpp"

/// @class MediaList
/// @brief List of Medias
class MediaList2 : public JsonArray<Media2>
{
	public:
		/// @fn MediaList();
		/// @brief Constructor
		MediaList2();

		/// @fn virtual ~MediaList();
		/// @brief Destructor
		virtual ~MediaList2();

		/// @fn MediaList(const MediaList & list);
		/// @brief Copy constructor
		/// @param list MediaList to copy
		MediaList2(const MediaList2 & list);

		/// @fn const MediaList & operator=(const MediaList & list);
		/// @brief Affrection operator
		/// @param list MediaList to affect
		const MediaList2 & operator=(const MediaList2 & list);

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
										const MediaList2 & list);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										MediaList & list);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										MediaList2 & list);
};

// Serialization of MediaList
Q_DECLARE_METATYPE(MediaList2)

/// @fn QDataStream & operator<<(QDataStream & out, const MediaList & list);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const MediaList2 & list);

/// @fn QDataStream & operator>>(QDataStream & in, MediaList & list);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, MediaList2 & list);

#endif // MEDIALIST_HPP
