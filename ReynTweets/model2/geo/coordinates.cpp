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

//////////////////////
// Coordinates type //
//////////////////////

// Converting a CoordinatesType into a QString
QString Coordinates::coord2string(Coordinates::CoordinatesType coord) {
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
Coordinates::CoordinatesType Coordinates::string2coord(QString coordStr) {
	QString coord = coordStr.toLower();

	if ("point" == coord) {
		return POINT;
	} else if ("polygon" == coord) {
		return POLYGON;
	} else {
		return FAKE_COORDINATES;
	}
}


/////////////
// Coplien //
/////////////

// Default constructor
Coordinates::Coordinates() :
	JsonObject(),
	geoCoordinates(),
	coordType(FAKE_COORDINATES)
{}

// Destructor
Coordinates::~Coordinates() {}

// Copy constructor
Coordinates::Coordinates(const Coordinates & coord) :
	JsonObject(),
	geoCoordinates(),
	coordType(FAKE_COORDINATES)
{
	this->recopie(coord);
}

// Affectation
const Coordinates & Coordinates::operator=(const Coordinates & coord) {
	this->recopie(coord);
	return *this;
}

// Copy of a Coordinates
void Coordinates::recopie(const Coordinates & coord) {
	this->geoCoordinates = coord.geoCoordinates;
	this->coordType = coord.coordType;
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


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void Coordinates::fillWithJSON(QJsonObject json) {
	// "coordinates" property
	QJsonValue propval = json.value(COORDINATES_PN);

	if (!propval.isUndefined() && propval.isArray()) {
		QJsonArray coordz = propval.toArray();

		this->geoCoordinates.fillWithJSON(coordz);
	}

	// "type" property
	propval = json.value(TYPE_PN);

	if (!propval.isUndefined() && propval.isString()) {
		QString kind = propval.toString();
		this->coordType = string2coord(kind);
	}
}

// QJsonObject representation of the object
QJsonObject Coordinates::toJSON() {
	QJsonObject json;

	json.insert(COORDINATES_PN, QJsonValue(this->geoCoordinates.toJSON()));
	json.insert(TYPE_PN, QJsonValue(coord2string(this->coordType)));

	return json;
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


///////////////////////////
// Properties management //
///////////////////////////

// coordinates
QString Coordinates::COORDINATES_PN = "coordinates";

QVariantList Coordinates::getCoordinatesProperty() {
	return this->geoCoordinates.toVariant();
}

GeoCoord Coordinates::getCoordinates() {
	return this->geoCoordinates;
}

void Coordinates::setCoordinates(QVariantList newValue) {
	this->geoCoordinates.reset();
	this->geoCoordinates.fillWithVariant(newValue);
	emit coordinatesChanged();
}

void Coordinates::setCoordinates(GeoCoord newValue) {
	this->geoCoordinates = newValue;
	emit coordinatesChanged();
}

// type
QString Coordinates::TYPE_PN = "type";

QString Coordinates::getTypeProperty() {
	return coord2string(this->coordType);
}

Coordinates::CoordinatesType Coordinates::getType() {
	return this->coordType;
}

void Coordinates::setType(Coordinates::CoordinatesType newValue) {
	this->coordType = newValue;
	emit typeChanged();
}

void Coordinates::setType(QString newValue) {
	this->coordType = string2coord(newValue);
	emit typeChanged();
}
