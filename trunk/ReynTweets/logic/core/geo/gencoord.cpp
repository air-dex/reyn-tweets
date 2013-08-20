/// @file gencoord.cpp
/// @brief Implementation of GenCoord
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

#include "gencoord.hpp"

/////////////
// Coplien //
/////////////

// Default constructor
GenCoord::GenCoord() :
	JsonObject(),
	coordType(CoordType::FAKE_COORDINATES)
{}

// Destructor
GenCoord::~GenCoord() {}

// Copy constructor
GenCoord::GenCoord(const GenCoord & coord) :
	JsonObject(),
	coordType(CoordType::FAKE_COORDINATES)
{
	recopie(coord);
}

// Affectation
const GenCoord & GenCoord::operator=(const GenCoord & coord) {
	recopie(coord);
	return *this;
}

// Copy of a GenCoord
void GenCoord::recopie(const GenCoord & coord) {
	JsonObject::recopie(coord);
	this->coordType = coord.coordType;
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void GenCoord::fillWithVariant(QJsonObject json) {
	this->coordType = CoordType::string2coord(json.value(TYPE_PN).toString(""));
}

// QJsonObject representation of the object
QJsonObject GenCoord::toVariant() const {
	QJsonObject json;

	json.insert(TYPE_PN, QJsonValue(CoordType::coord2string(this->coordType)));

	return json;
}


////////////////
// Properties //
////////////////

// type
QString GenCoord::TYPE_PN = "type";

QString GenCoord::getTypeProperty() {
	return CoordType::coord2string(this->coordType);
}

CoordType::CoordinatesType GenCoord::getType() {
	return this->coordType;
}

void GenCoord::setType(CoordType::CoordinatesType newValue) {
	this->coordType = newValue;
	emit typeChanged();
}


/////////////////////////
// Q_OBJECT workaround //
/////////////////////////

// coordinatesChanged signal.
void GenCoord::changeCoord() {
	emit coordinatesChanged();
}
