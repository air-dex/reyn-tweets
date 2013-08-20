/// @file coordinatestype.cpp
/// @brief Implementation of functions for converting CoordinatesType into
/// QString and vice versa.
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

#include "coordinatestype.hpp"

//////////////////////
// Coordinates type //
//////////////////////

// Converting a CoordinatesType into a QString
QString ReynTweets::coord2string(ReynTweets::CoordinatesType coord) {
	switch (coord) {
		case POINT:
			return "Point";

		case POLYGON:
			return "Polygon";

		default:
			return "";
	}
}

// Converting a QString into a CoordinatesType
ReynTweets::CoordinatesType ReynTweets::string2coord(QString coordStr) {
	QString coord = coordStr.toLower();

	if ("point" == coord) {
		return POINT;
	} else if ("polygon" == coord) {
		return POLYGON;
	} else {
		return FAKE_COORDINATES;
	}
}
