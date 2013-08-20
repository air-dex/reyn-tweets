/// @file urlentitylist.hpp
/// @brief Header of URLEntityList
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

#ifndef URLENTITYLIST2_HPP
#define URLENTITYLIST2_HPP

#include <QVariant>
#include "urlentity.hpp"
#include "../json/jsonarray.tpp"

/// @class URLEntityList
/// @brief List of URL Entities
class URLEntityList2 : public JsonArray<URLEntity2>
{
	public:
		/// @fn URLEntityList();
		/// @brief Constructor
		URLEntityList2();

		/// @fn virtual ~URLEntityList();
		/// @brief Destructor
		virtual ~URLEntityList2();

		/// @fn URLEntityList(const URLEntityList & list);
		/// @brief Copy constructor
		/// @param list URLEntityList to copy
		URLEntityList2(const URLEntityList2 & list);

		/// @fn const URLEntityList & operator=(const URLEntityList & list);
		/// @brief Affrection operator
		/// @param list URLEntityList to affect
		const URLEntityList2 & operator=(const URLEntityList2 & list);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	protected:
		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const URLEntityList & list);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const URLEntityList2 & list);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										URLEntityList & list);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										URLEntityList2 & list);
};

// Serialization of URLEntityList
Q_DECLARE_METATYPE(URLEntityList2)

/// @fn QDataStream & operator<<(QDataStream & out, const URLEntityList & list);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const URLEntityList2 & list);

/// @fn QDataStream & operator>>(QDataStream & in, URLEntityList & list);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, URLEntityList2 & list);

#endif // URLENTITYLIST_HPP
