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
	JsonObject(),
	geoCoordinates(),
	coordType(Coordinates::FAKE_COORDINATES)
{}

// Destructor
GeoBoundingBox::~GeoBoundingBox() {}

// Copy constructor
GeoBoundingBox::GeoBoundingBox(const GeoBoundingBox & coord) :
	JsonObject(),
	geoCoordinates(),
	coordType(Coordinates::FAKE_COORDINATES)
{
	this->recopie(coord);
}

// Affectation
const GeoBoundingBox & GeoBoundingBox::operator=(const GeoBoundingBox & coord) {
	this->recopie(coord);
	return *this;
}

// Copy of a Coordinates
void GeoBoundingBox::recopie(const GeoBoundingBox & coord) {
	this->geoCoordinates = coord.geoCoordinates;
	this->coordType = coord.coordType;
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


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void GeoBoundingBox::fillWithJSON(QJsonObject json) {
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
		this->coordType = Coordinates::string2coord(kind);
	}
}

// QJsonObject representation of the object
QJsonObject GeoBoundingBox::toJSON() {
	QJsonObject json;

	json.insert(COORDINATES_PN, QJsonValue(this->geoCoordinates.toJSON()));
	json.insert(TYPE_PN, QJsonValue(Coordinates::coord2string(this->coordType)));

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
QString GeoBoundingBox::COORDINATES_PN = "coordinates";

QVariantList GeoBoundingBox::getCoordinatesProperty() {
	return this->geoCoordinates.toVariant();
}

GeoCoordList GeoBoundingBox::getCoordinates() {
	return this->geoCoordinates;
}

void GeoBoundingBox::setCoordinates(QVariantList newValue) {
	this->geoCoordinates.reset();
	this->geoCoordinates.fillWithVariant(newValue);
	emit coordinatesChanged();
}

void GeoBoundingBox::setCoordinates(GeoCoordList newValue) {
	this->geoCoordinates = newValue;
	emit coordinatesChanged();
}

// type
QString GeoBoundingBox::TYPE_PN = "type";

QString GeoBoundingBox::getTypeProperty() {
	return Coordinates::coord2string(this->coordType);
}

Coordinates::CoordinatesType GeoBoundingBox::getType() {
	return this->coordType;
}

void GeoBoundingBox::setType(Coordinates::CoordinatesType newValue) {
	this->coordType = newValue;
	emit typeChanged();
}

void GeoBoundingBox::setType(QString newValue) {
	this->coordType = Coordinates::string2coord(newValue);
	emit typeChanged();
}
