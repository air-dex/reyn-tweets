/// @file urlentitylist.hpp
/// @brief Header of URLEntityList
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012, 2013 Romain Ducher
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

#ifndef URLENTITYLIST_HPP
#define URLENTITYLIST_HPP

#include <QVariant>
#include "urlentity.hpp"
#include "../json/jsonobjectarray.tpp"

/// @class URLEntityList
/// @brief List of URL Entities
class URLEntityList : public JsonObjectArray<URLEntity>
{
	public:
		/// @fn URLEntityList();
		/// @brief Constructor
		URLEntityList();

		/// @fn virtual ~URLEntityList();
		/// @brief Destructor
		virtual ~URLEntityList();

		/// @fn URLEntityList(const URLEntityList & list);
		/// @brief Copy constructor
		/// @param list URLEntityList to copy
		URLEntityList(const URLEntityList & list);

		/// @fn const URLEntityList & operator=(const URLEntityList & list);
		/// @brief Affrection operator
		/// @param list URLEntityList to affect
		const URLEntityList & operator=(const URLEntityList & list);

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
										const URLEntityList & list);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										URLEntityList & list);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param list Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										URLEntityList & list);
};

// Serialization of URLEntityList
Q_DECLARE_METATYPE(URLEntityList)

/// @fn QDataStream & operator<<(QDataStream & out, const URLEntityList & list);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const URLEntityList & list);

/// @fn QDataStream & operator>>(QDataStream & in, URLEntityList & list);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, URLEntityList & list);

#endif // URLENTITYLIST_HPP
