/// @file genericcoordinates.hpp
/// @brief Header of GenericCoordinates
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

#ifndef GENERICCOORDINATES_HPP
#define GENERICCOORDINATES_HPP

#include "gencoord.hpp"

/// @class GenericCoordinates
/// @brief Base class for coordinates handling.
///
/// It is the part with template and implementation handling.
///
/// A C++ template class cannot get Qt properties. The GenericCoordinates class
/// as conceived is in this case. So it was splat into two classes :<ul>
/// <li>The GenCoord class which is not a template and which contains
/// properties.</li>
/// <li>The GenericCoordinates class which is a template class and which
/// implements GenCoord.</li>
/// </ul>
/// @param C class representing coordinates
template <typename C>
class GenericCoordinates : public GenCoord
{
	public:
		/// @fn GenericCoordinates();
		/// @brief Default constructor
		GenericCoordinates();

		/// @fn virtual ~GenericCoordinates();
		/// @brief Destructor
		virtual ~GenericCoordinates();

		/// @fn GenericCoordinates(const GenericCoordinates & coord);
		/// @brief Copy constructor
		/// @param coord GenericCoordinates to copy
		GenericCoordinates(const GenericCoordinates &coord);

		/// @fn const GenericCoordinates & operator=(const GenericCoordinates & coord);
		/// @brief Affectation
		/// @param coord GenericCoordinates to copy
		/// @return Copy of the original coordinates
		const GenericCoordinates & operator=(const GenericCoordinates & coord);

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
		virtual QJsonObject toJSON() const;


	protected:
		/// @fn virtual void recopie(const GenericCoordinates & coord);
		/// @brief Copy of a GenericCoordinates
		/// @param coord GenericCoordinates to copy
		virtual void recopie(const GenericCoordinates & coord);


		///////////////////////////
		// Properties management //
		///////////////////////////

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
		C geoCoordinates;

		/// @brief String version of retweetID
		CoordinatesType coordType;

	public:
		// coordinates
		/// @fn C getCoordinates();
		/// @brief Reading coordinates
		/// @return this
		C getCoordinates();

		/// @fn void setCoordinates(C newValue);
		/// @brief Writing coordinates
		/// @param newValue New value for coordinate locations
		void setCoordinates(C newValue);

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

#endif // GENERICCOORDINATES_HPP
