/// @file geocoordlist.hpp
/// @brief Header of GeoCoordList
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

#ifndef GEOCOORDLIST_HPP
#define GEOCOORDLIST_HPP

#include <QDataStream>
#include <QVariant>
#include "../json/jsonarrayarray.tpp"
#include "geocoord.hpp"

/// @class GeoCoordList
/// @brief Lists of GeoCoord
class GeoCoordList : public JsonArrayArray<GeoCoord>
{
	public:
		/// @fn GeoCoordList();
		/// @brief Constructor
		GeoCoordList();

		/// @fn virtual ~GeoCoordList();
		/// @brief Destructor
		virtual ~GeoCoordList();

		/// @fn GeoCoordList(const GeoCoordList & list);
		/// @brief Copy constructor
		/// @param list GeoCoordList to copy
		GeoCoordList(const GeoCoordList & list);

		/// @fn const GeoCoordList & operator=(const GeoCoordList & list);
		/// @brief Affrection operator
		/// @param list GeoCoordList to affect
		const GeoCoordList & operator=(const GeoCoordList & list);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	protected:
		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const GeoCoordList & list);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param list GeoCoordList to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const GeoCoordList & list);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										GeoCoordList & list);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param list GeoCoordList to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										GeoCoordList & list);
};

// Serialization of GeoCoordList
Q_DECLARE_METATYPE(GeoCoordList)

/// @fn QDataStream & operator<<(QDataStream & out, const GeoCoordList & list);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param list GeoCoordList to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const GeoCoordList & list);

/// @fn QDataStream & operator>>(QDataStream & in, GeoCoordList & list);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param list GeoCoordList to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, GeoCoordList & list);

#endif // GEOCOORDLIST_HPP
