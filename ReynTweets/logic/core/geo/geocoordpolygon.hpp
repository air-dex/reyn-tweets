/// @file geocoordpolygon.hpp
/// @brief Header of GeoCoordPolygon
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

#ifndef GEOCOORDPOLYGON_HPP
#define GEOCOORDPOLYGON_HPP

#include "../json/jsonarray.hpp"
#include "geocoordlist.hpp"

/// @class GeoCoordPolygon
/// @brief List of GeoCoordList.
///
/// It is used by the Twitter API for compatibility between bounding boxes for
/// Places (GeoBoundingBox class) and polygon representations.
class GeoCoordPolygon : public JsonArray<GeoCoordList>
{
	public:
		/// @fn GeoCoordPolygon();
		/// @brief Constructor
		GeoCoordPolygon();

		/// @fn virtual ~GeoCoordPolygon();
		/// @brief Destructor
		virtual ~GeoCoordPolygon();

		/// @fn GeoCoordPolygon(const GeoCoordPolygon & polygon);
		/// @brief Copy constructor
		/// @param polygon GeoCoordPolygon to copy
		GeoCoordPolygon(const GeoCoordPolygon & polygon);

		/// @fn const GeoCoordPolygon & operator=(const GeoCoordPolygon & polygon);
		/// @brief Affrection operator
		/// @param polygon GeoCoordPolygon to affect
		const GeoCoordPolygon & operator=(const GeoCoordPolygon & polygon);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	protected:
		/// @fn virtual void appendJsonValue(QJsonValue v);
		/// @brief Appending the content of a QJsonValue in the GeoCoordPolygon
		/// @param v the QJsonValue
		virtual void appendJsonValue(QJsonValue v);

		/// @fn virtual void appendJsonArrayElement(QJsonArray & array,
		///											GeoCoordList elt) const;
		/// @brief Appends an element of the list in a QJsonArray
		/// @param array The QJsonArray
		/// @param elt The list element
		virtual void appendJsonArrayElement(QJsonArray & array,
											GeoCoordList elt) const;

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const GeoCoordPolygon & polygon);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param polygon GeoCoordPolygon to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const GeoCoordPolygon & polygon);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										GeoCoordPolygon & polygon);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param polygon GeoCoordPolygon to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										GeoCoordPolygon & polygon);
};

// Serialization of GeoCoordPolygon
Q_DECLARE_METATYPE(GeoCoordPolygon)

/// @fn QDataStream & operator<<(QDataStream & out, const GeoCoordPolygon & polygon);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param polygon GeoCoordPolygon to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const GeoCoordPolygon & polygon);

/// @fn QDataStream & operator>>(QDataStream & in, GeoCoordPolygon & polygon);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param polygon GeoCoordPolygon to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, GeoCoordPolygon & polygon);

#endif // GEOCOORDPOLYGON_HPP
