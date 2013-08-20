/// @file geocoordpolygon.cpp
/// @brief Implementation of GeoCoordPolygon
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

#include "geocoordpolygon.hpp"

// Constructor
GeoCoordPolygon::GeoCoordPolygon() :
	JsonArray<GeoCoordList>()
{}

// Destructor
GeoCoordPolygon::~GeoCoordPolygon() {}

// Copy constructor
GeoCoordPolygon::GeoCoordPolygon(const GeoCoordPolygon & polygon) :
	JsonArray<GeoCoordList>()
{
	recopie(polygon);
}

// Affrection operator
const GeoCoordPolygon & GeoCoordPolygon::operator=(const GeoCoordPolygon & polygon) {
	recopie(polygon);
	return *this;
}

// Serialization initialization
void GeoCoordPolygon::initSystem() {
	qRegisterMetaTypeStreamOperators<GeoCoordPolygon>("GeoCoordPolygon");
	qMetaTypeId<GeoCoordPolygon>();
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const GeoCoordPolygon & polygon) {
	return polygon.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, GeoCoordPolygon & polygon) {
	return polygon.fillWithStream(in);
}
