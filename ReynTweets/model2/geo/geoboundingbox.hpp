/// @file geoboundingbox.hpp
/// @brief Header of GeoBoundingBox
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

#ifndef GEOBOUNDINGBOX_HPP
#define GEOBOUNDINGBOX_HPP

#include "../json/jsonobject.hpp"
#include "geocoordlist.hpp"
#include "coordinates.hpp"

/// @class GeoBoundingBox
/// @brief Bounding box used for places
class GeoBoundingBox : public JsonObject
{
	Q_OBJECT

	public:
		/// @fn GeoBoundingBox();
		/// @brief Default constructor
		GeoBoundingBox();

		/// @fn virtual ~GeoBoundingBox();
		/// @brief Destructor
		virtual ~GeoBoundingBox();

		/// @fn GeoBoundingBox(const GeoBoundingBox & coord);
		/// @brief Copy constructor
		/// @param coord GeoBoundingBox to copy
		GeoBoundingBox(const GeoBoundingBox & coord);

		/// @fn const GeoBoundingBox & operator=(const GeoBoundingBox & coord);
		/// @brief Affectation
		/// @param coord GeoBoundingBox to copy
		/// @return Copy of the original coordinates
		const GeoBoundingBox & operator=(const GeoBoundingBox & coord);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn void reset();
		/// @brief Resets the mappable to a default value
		void reset();

		/////////////////////
		// JSON conversion //
		/////////////////////

		/// @fn virtual void fillWithJSON(QJsonObject json);
		/// @brief Filling the object with a QJsonObject.
		///
		/// The method is virtual because its implementation depends on the
		/// object type.
		/// @param json The QJsonObject used to fill the JsonObject
		virtual void fillWithJSON(QJsonObject json);

		/// @fn virtual QJsonObject toJSON();
		/// @brief Getting a QJsonObject representation of the object
		/// @return The QJsonObject representation
		virtual QJsonObject toJSON();


	private:
		/// @fn void recopie(const GeoBoundingBox & coord);
		/// @brief Copy of a GeoBoundingBox
		/// @param coord GeoBoundingBox to copy
		void recopie(const GeoBoundingBox & coord);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const GeoBoundingBox & coord);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param coord GeoBoundingBox to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const GeoBoundingBox & coord);

		/// @fn friend QDataStream & operator>>(QDataStream & in, GeoBoundingBox & coord);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param coord GeoBoundingBox to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, GeoBoundingBox & coord);


	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		// coordinates
		/// @property id
		/// @brief Series of longitude and latitude points.
		///
		/// geoCoordinates is the attribute beneath this property.
		Q_PROPERTY(QVariantList coordinates
				   READ getCoordinatesProperty
				   WRITE setCoordinates
				   NOTIFY coordinatesChanged)

		/// @brief Name of the property id.
		static QString COORDINATES_PN;

		/// @fn QVariantList getCoordinatesProperty();
		/// @brief Reading coordinates
		/// @return retweetID
		QVariantList getCoordinatesProperty();

		/// @fn void setCoordinates(QVariantList newValue);
		/// @brief Writing coordinates
		/// @param newValue New value for id
		void setCoordinates(QVariantList newValue);

		// type
		/// @property type
		/// @brief Type of coordinates.
		///
		/// coordType is the attribute beneath this property.
		Q_PROPERTY(QString type
				   READ getTypeProperty
				   WRITE setType
				   NOTIFY typeChanged)

		/// @brief Name of the property type.
		static QString TYPE_PN;

		/// @fn QString getType();
		/// @brief Reading type
		/// @return coordType
		QString getTypeProperty();

		/// @fn void setType(QString newValue);
		/// @brief Writing type
		/// @param newValue New value for coordType
		void setType(QString newValue);


	signals:
		/// @fn void coordinatesChanged();
		/// @brief Emitted when the id and id_str properties change
		void coordinatesChanged();

		/// @fn void typeChanged();
		/// @brief Emitted when the id and id_str properties change
		void typeChanged();

	protected:
		/// @brief Coordinates of the point
		GeoCoordList geoCoordinates;

		/// @brief String version of retweetID
		Coordinates::CoordinatesType coordType;

	public:
		// coordinates
		/// @fn GeoCoord getCoordinates();
		/// @brief Reading coordinates
		/// @return this
		GeoCoordList getCoordinates();

		/// @fn void setCoordinates(GeoCoord newValue);
		/// @brief Writing coordinates
		/// @param newValue New value for coordinate locations
		void setCoordinates(GeoCoordList newValue);

		// type
		/// @fn Coordinates::CoordinatesType getType();
		/// @brief Reading type
		/// @return coordType
		Coordinates::CoordinatesType getType();

		/// @fn void setType(Coordinates::CoordinatesType newValue);
		/// @brief Writing type
		/// @param newValue New value for coordType
		void setType(Coordinates::CoordinatesType newValue);

};

// Serialization of GeoBoundingBox
Q_DECLARE_METATYPE(GeoBoundingBox)

/// @fn QDataStream & operator<<(QDataStream & out, const GeoBoundingBox & infos);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param infos GeoBoundingBox to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const GeoBoundingBox & infos);

/// @fn QDataStream & operator>>(QDataStream & in, GeoBoundingBox & infos);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param infos GeoBoundingBox to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, GeoBoundingBox & infos);

#endif // GEOBOUNDINGBOX_HPP
