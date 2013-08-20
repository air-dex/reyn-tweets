/// @file coordinates.hpp
/// @brief Header of Coordinates
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

#ifndef COORDINATES_HPP
#define COORDINATES_HPP

#include "../json/jsonobject.hpp"
#include "geocoord.hpp"

/// @class Coordinates
/// @brief Class representing coordinates
class Coordinates : public JsonObject
{
	Q_OBJECT

	//////////////////////
	// Coordinates type //
	//////////////////////

	public:
		/// @enum CoordinatesType
		/// @brief Type of coordiante.
		enum CoordinatesType {
			/// @brief Fake type
			FAKE_COORDINATES,

			/// @brief Coordinates are a point
			POINT,

			/// @brief Coordinates are a polygon (Place)
			POLYGON
		};

		Q_ENUMS(CoordinatesType)

		/// @fn static QString coord2string(CoordinatesType coord);
		/// @brief Converting a CoordinatesType into a QString.
		/// @param coord The CoordinatesType
		/// @return The corresponding QString
		static QString coord2string(CoordinatesType coord);

		/// @fn static CoordinatesType string2coord(QString coordStr);
		/// @brief Converting a QString into a CoordinatesType.
		/// @param coord The QString
		/// @return The corresponding CoordinatesType
		static CoordinatesType string2coord(QString coordStr);


		/// @fn Coordinates();
		/// @brief Default constructor
		Coordinates();

		/// @fn virtual ~Coordinates();
		/// @brief Destructor
		virtual ~Coordinates();

		/// @fn Coordinates(const Coordinates & coord);
		/// @brief Copy constructor
		/// @param coord Coordinates to copy
		Coordinates(const Coordinates & coord);

		/// @fn const Coordinates & operator=(const Coordinates & coord);
		/// @brief Affectation
		/// @param coord Coordinates to copy
		/// @return Copy of the original coordinates
		const Coordinates & operator=(const Coordinates & coord);

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
		/// @fn void recopie(const Coordinates & coord);
		/// @brief Copy of a Coordinates
		/// @param coord Coordinates to copy
		void recopie(const Coordinates & coord);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const Coordinates & coord);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param coord Coordinates to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const Coordinates & coord);

		/// @fn friend QDataStream & operator>>(QDataStream & in, Coordinates & coord);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param coord Coordinates to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, Coordinates & coord);


	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		// coordinates
		/// @property id
		/// @brief Longitude and latitude.
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
		GeoCoord geoCoordinates;

		/// @brief String version of retweetID
		CoordinatesType coordType;

	public:
		// coordinates
		/// @fn GeoCoord getCoordinates();
		/// @brief Reading coordinates
		/// @return this
		GeoCoord getCoordinates();

		/// @fn void setCoordinates(GeoCoord newValue);
		/// @brief Writing coordinates
		/// @param newValue New value for coordinate locations
		void setCoordinates(GeoCoord newValue);

		// type
		/// @fn CoordinatesType getType();
		/// @brief Reading type
		/// @return coordType
		CoordinatesType getType();

		/// @fn void setType(CoordinatesType newValue);
		/// @brief Writing type
		/// @param newValue New value for coordType
		void setType(CoordinatesType newValue);
};

// Serialization of Coordinates
Q_DECLARE_METATYPE(Coordinates)

/// @fn QDataStream & operator<<(QDataStream & out, const Coordinates & infos);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param infos Coordinates to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const Coordinates & infos);

/// @fn QDataStream & operator>>(QDataStream & in, Coordinates & infos);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param infos Coordinates to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, Coordinates & infos);

#endif // COORDINATES_HPP
