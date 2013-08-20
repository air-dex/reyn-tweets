/// @file hashtaglist.hpp
/// @brief Header of HashtagList
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

#ifndef HASHTAGLIST2_HPP
#define HASHTAGLIST2_HPP

#include <QDataStream>
#include <QVariant>
#include "../json/jsonarray.tpp"
#include "hashtag.hpp"

/// @class HashtagList
/// @brief Lists of Hashtags
class HashtagList2 : public JsonArray<Hashtag2>
{
	public:
		/// @fn HashtagList();
		/// @brief Constructor
		HashtagList2();

		/// @fn virtual ~HashtagList();
		/// @brief Destructor
		virtual ~HashtagList2();

		/// @fn HashtagList(const HashtagList & list);
		/// @brief Copy constructor
		/// @param list HashtagList to copy
		HashtagList2(const HashtagList2 & list);

		/// @fn const HashtagList & operator=(const HashtagList & list);
		/// @brief Affrection operator
		/// @param list HashtagList to affect
		const HashtagList2 & operator=(const HashtagList2 & list);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	protected:
		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const HashtagList & list);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const HashtagList2 & list);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										HashtagList & list);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										HashtagList2 & list);
};

// Serialization of HashtagList
Q_DECLARE_METATYPE(HashtagList2)

/// @fn QDataStream & operator<<(QDataStream & out, const HashtagList & list);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const HashtagList2 & list);

/// @fn QDataStream & operator>>(QDataStream & in, HashtagList & list);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, HashtagList2 & list);

#endif // HASHTAGLIST_HPP
