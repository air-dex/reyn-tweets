/// @file geoboundingbox.cpp
/// @brief Implementation of GeoBoundingBox
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

#include "geoboundingbox.hpp"
#include <QJsonArray>

/////////////
// Coplien //
/////////////

// Default constructor
GeoBoundingBox::GeoBoundingBox() :
	GenericCoordinates<GeoCoordList>(),
	coordType(CoordType::POLYGON)
{}

// Destructor
GeoBoundingBox::~GeoBoundingBox() {}

// Copy constructor
GeoBoundingBox::GeoBoundingBox(const GeoBoundingBox & coord) :
	GenericCoordinates<GeoCoordList>(),
	geoCoordinates(),
	coordType(CoordType::POLYGON)
{
	this->recopie(coord);
}

// Affectation
const GeoBoundingBox & GeoBoundingBox::operator=(const GeoBoundingBox & coord) {
	this->recopie(coord);
	return *this;
}

// Serialization declaration
void GeoBoundingBox::initSystem() {
	qRegisterMetaTypeStreamOperators<GeoBoundingBox>("GeoBoundingBox");
	qMetaTypeId<GeoBoundingBox>();
}

// Reset
void GeoBoundingBox::reset() {
	*this = GeoBoundingBox();
}


/////////////////////////////////////
// Friends serialization operators //
/////////////////////////////////////

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const Coordinates & coord) {
	return jsonStreamingOut(out, coord);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, Coordinates & coord) {
	return jsonStreamingIn(in, coord);
}


// Do not change CoordinatesType
void GeoBoundingBox::setType(CoordinatesType) {}
