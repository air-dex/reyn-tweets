/// @file coordinates.cpp
/// @brief Implementation of Coordinates
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

#include "coordinates.hpp"
#include <QJsonArray>

/////////////
// Coplien //
/////////////

// Default constructor
Coordinates::Coordinates() :
	GenericCoordinates<GeoCoord>(),
	coordType(CoordType::POINT)
{}

// Destructor
Coordinates::~Coordinates() {}

// Copy constructor
Coordinates::Coordinates(const Coordinates & coord) :
	GenericCoordinates<GeoCoord>(),
	coordType(CoordType::POINT)
{
	this->recopie(coord);
}

// Affectation
const Coordinates & Coordinates::operator=(const Coordinates & coord) {
	this->recopie(coord);
	return *this;
}

// Serialization declaration
void Coordinates::initSystem() {
	qRegisterMetaTypeStreamOperators<Coordinates>("Coordinates");
	qMetaTypeId<Coordinates>();
}

// Reset
void Coordinates::reset() {
	*this = Coordinates();
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
void Coordinates::setType(CoordinatesType) {}
