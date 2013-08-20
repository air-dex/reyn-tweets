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

#include "genericcoordinates.tpp"
#include "geocoordlist.hpp"

using CoordType::CoordinatesType;

/// @class GeoBoundingBox
/// @brief Bounding box used for places
class GeoBoundingBox : public GenericCoordinates<GeoCoordList>
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


	private:
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

		// Don't change the CoordinatesType

		/// @fn void setType(CoordinatesType newValue);
		/// @brief Overriden to set the CoordinatesType readonly.
		void setType(CoordinatesType);
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
