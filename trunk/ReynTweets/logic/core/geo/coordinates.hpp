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

#include "genericcoordinates.tpp"
#include "../../controls/listhandlers/geocoordhandler.hpp"

/// @class Coordinates
/// @brief Class representing coordinates
class Coordinates : public GenericCoordinates<GeoCoord, GeoCoordHandler>
{
	Q_OBJECT

	public:
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

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

		/// @fn void reset();
		/// @brief Resets the mappable to a default value
		void reset();

	protected:
		//////////////////////////
		// coordinates property //
		//////////////////////////

		/// @property coordinates
		/// @brief Geographic coordinates of the point
		Q_PROPERTY(GeoCoordHandler * coordinates
				   READ getCoordinatesProperty
				   NOTIFY coordinatesChanged)

	signals:
		/// @fn void coordinatesChanged();
		/// @brief Emitted when the coordinates property changes its value.
		void coordinatesChanged();

	private:
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
