/// @file gencoord.hpp
/// @brief Header of GenCoord
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

#ifndef GENCOORD_HPP
#define GENCOORD_HPP

#include "../json/jsonobject.hpp"
#include "coordinatestype.hpp"

/// @class GenCoord
/// @brief Part of the base class for coordinates handling.
///
/// It is the part with properties handling and virtual classes depending
/// to properties.
///
/// A C++ template class cannot get Qt properties. The GenericCoordinates class
/// as conceived is in this case. So it was splat into two classes :<ul>
/// <li>The GenCoord class which is not a template and which contains
/// properties.</li>
/// <li>The GenericCoordinates class which is a template class and which
/// implements GenCoord.</li>
/// </ul>
class GenCoord : public JsonObject
{
	Q_OBJECT

	public:
		/// @fn GenCoord();
		/// @brief Default constructor
		GenCoord();

		/// @fn virtual ~GenCoord();
		/// @brief Destructor
		virtual ~GenCoord();

		/// @fn GenericCoordinates(const GenCoord & coord);
		/// @brief Copy constructor
		/// @param coord GenCoord to copy
		GenCoord(const GenCoord &coord);

		/// @fn const GenericCoordinates & operator=(const GenCoord & coord);
		/// @brief Affectation
		/// @param coord GenCoord to copy
		/// @return Copy of the original coordinates
		const GenCoord & operator=(const GenCoord & coord);


	protected:
		/// @fn virtual void recopie(const GenCoord & coord);
		/// @brief Copy of a GenCoord
		/// @param coord GenCoord to copy
		virtual void recopie(const GenCoord & coord);

		/////////////////////
		// JSON conversion //
		/////////////////////

		/// @fn virtual void fillWithVariant(QJsonObject json);
		/// @brief Filling the object with a QJsonObject.
		///
		/// The method is virtual because its implementation depends on the
		/// object type.
		/// @param json The QJsonObject used to fill the JsonObject
		virtual void fillWithVariant(QJsonObject json);

		/// @fn virtual QJsonObject toVariant();
		/// @brief Getting a QJsonObject representation of the object
		/// @return The QJsonObject representation
		virtual QJsonObject toVariant() const;

		///////////////////////////
		// Properties management //
		///////////////////////////

		// coordinates
		// Only common Q_OBJECT related parts are defined here (NOTIFY signal).

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

		/// @brief Type of coordinates.
		CoordType::CoordinatesType coordType;

		/// @fn virtual QString getType();
		/// @brief Reading type
		/// @return coordType
		virtual QString getTypeProperty();

		/// @fn virtual void setType(QString newValue);
		/// @brief Writing type
		/// @param newValue New value for coordType
		virtual void setType(QString newValue);


	signals:
		/// @fn void coordinatesChanged();
		/// @brief Emitted when the coordinates property changes its value.
		void coordinatesChanged();

		/// @fn void typeChanged();
		/// @brief Emitted when the type property changes its value.
		void typeChanged();

	public:
		// type
		/// @fn CoordType::CoordinatesType getType();
		/// @brief Reading type
		/// @return coordType
		CoordType::CoordinatesType getType();

		/// @fn void setType(CoordType::CoordinatesType newValue);
		/// @brief Writing type
		/// @param newValue New value for coordType
		void setType(CoordType::CoordinatesType newValue);


	/////////////////////////
	// Q_OBJECT workaround //
	/////////////////////////

	protected:
		/// @fn void changeCoord();
		/// @brief Emitting the coordinatesChanged signal.
		///
		/// It is a workaround to avoid using Q_OBJECT-related things just like
		/// signals in GenericCoordinates (template class).
		void changeCoord();
};

#endif // GENCOORD_HPP
