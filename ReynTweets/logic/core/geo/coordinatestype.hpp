/// @file coordinatestype.hpp
/// @brief Header of CoordinatesType
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

#ifndef COORDINATESTYPE_HPP
#define COORDINATESTYPE_HPP

#include <QString>

namespace ReynTweets {
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

	/// @fn static QString coord2string(CoordinatesType coord);
	/// @brief Converting a CoordinatesType into a QString.
	/// @param coord The CoordinatesType
	/// @return The corresponding QString
	QString coord2string(CoordinatesType coord);

	/// @fn static CoordinatesType string2coord(QString coordStr);
	/// @brief Converting a QString into a CoordinatesType.
	/// @param coordStr The QString to convert
	/// @return The corresponding CoordinatesType
	CoordinatesType string2coord(QString coordStr);
}

#endif // COORDINATESTYPE_HPP
