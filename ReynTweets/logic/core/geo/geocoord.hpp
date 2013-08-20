/// @file geocoord.hpp
/// @brief Header of GeoCoord
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

#ifndef GEOCOORD_HPP
#define GEOCOORD_HPP

#include <QPointF>
#include "../json/jsonarray.tpp"

/// @class GeoCoord
/// @brief Class representing a point somewhere on the Earth, with its longitude
/// and its latitude.
///
/// The JSON coordinates array is formatted as <a href="http://www.geojson.org/">
/// geoJSON</a> (longitude first, then latitude). As for the QPointF :<ul>
/// <li>x : the longitude</li>
/// <li>y : the latitude</li>
/// </ul>
class GeoCoord : public JsonArray<double>, public QPointF
{
	public:
		/// @fn GeoCoord();
		/// @brief Default constructor
		GeoCoord();

		/// @fn virtual ~GeoCoord();
		/// @brief Destructor
		virtual ~GeoCoord();

		/// @fn Coordinates(const GeoCoord & coord);
		/// @brief Copy constructor
		/// @param coord GeoCoord to copy
		GeoCoord(const GeoCoord & coord);

		/// @fn const Tweet & operator=(const GeoCoord & coord);
		/// @brief Affectation
		/// @param coord GeoCoord to copy
		/// @return Copy of the original coordinates
		const GeoCoord & operator=(const GeoCoord & coord);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn void reset();
		/// @brief Resets the mappable to a default value
		void reset();

		/// @fn bool operator==(const GeoCoord & coord) const;
		/// @brief Equality between GeoCoord
		///
		/// Two GeoCoords are considered equals if they have got both the same
		/// longitude and the same latitude.
		/// @param coord The GeoCoord to compare
		/// @return True if they are equals, false otherwise.
		bool operator==(const GeoCoord & coord) const;

		/////////////////////
		// JSON conversion //
		/////////////////////

		/// @fn virtual void fillWithVariant(QJsonArray json);
		/// @brief Filling the object with a QJsonArray.
		///
		/// The method is overriden because of JSON optimization
		/// @param json The QJsonArray used to fill the GeoCoord
		virtual void fillWithVariant(QJsonArray json);

		/// @fn virtual QJsonArray toVariant();
		/// @brief Getting a QJsonArray representation of the object
		///
		/// The method is overriden because of JSON optimization
		/// @return The QJsonArray representation
		virtual QJsonArray toVariant() const;


	protected:
		/// @brief Constant for fake coordinates
		static qreal FAKE_COORD;

		/// @fn void recopie(const GeoCoord & coord);
		/// @brief Copy of a Coordinates
		/// @param coord GeoCoord to copy
		void recopie(const GeoCoord & coord);

		/// @fn virtual void appendJsonValue(QJsonValue v);
		/// @brief Appending the content of a QJsonValue in the GeoCoord
		///
		/// Quite useless here since toVariant() is overriden.
		/// @param v the QJsonValue
		virtual void appendJsonValue(QJsonValue v);

		/// @fn virtual void appendJsonArrayElement(QJsonArray & array,
		///											double elt) const;
		/// @brief Appends an element of the list in a QJsonArray
		/// @param array The QJsonArray
		/// @param elt The list element
		virtual void appendJsonArrayElement(QJsonArray & array, double elt) const;

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const GeoCoord & coord);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param coord GeoCoord to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const GeoCoord & coord);

		/// @fn friend QDataStream & operator>>(QDataStream & in, GeoCoord & coord);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param coord GeoCoord to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, GeoCoord & coord);
};

// Serialization of GeoCoord
Q_DECLARE_METATYPE(GeoCoord)

/// @fn QDataStream & operator<<(QDataStream & out, const GeoCoord & infos);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param infos GeoCoord to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const GeoCoord & infos);

/// @fn QDataStream & operator>>(QDataStream & in, GeoCoord & infos);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param infos GeoCoord to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, GeoCoord & infos);

#endif // GEOCOORD_HPP
