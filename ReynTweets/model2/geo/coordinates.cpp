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

// Default constructor
Coordinates::Coordinates() :
	JsonObject(),
	coordType("")
{}

// Destructor
Coordinates::~Coordinates() {}

// Copy constructor
Coordinates::Coordinates(const Coordinates & coord) :
	JsonObject(),
	coordType("")
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
	this->setX(coord.x());
	this->setY(coord.y());
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

		this->setCoordinatesArray(coordz);
	}

	// "type" property
	propval = json.value(TYPE_PN);

	if (!propval.isUndefined() && propval.isString()) {
		QString kind = propval.toString();
		this->coordType = kind;
	}
}

// QJsonObject representation of the object
QJsonObject Coordinates::toJSON() {
	QJsonObject json;

	json.insert(COORDINATES_PN, QJsonValue(this->getCoordinatesArray()));
	json.insert(TYPE_PN, QJsonValue(this->coordType));

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
	return this->getCoordinatesArray().toVariantList();
}

QPointF Coordinates::getCoordinates() {
	return this;
}

QJsonArray Coordinates::getCoordinatesArray() {
	QJsonArray coordz;

	coordz.append(QJsonValue(this->x()));
	coordz.append(QJsonValue(this->y()));

	return coordz;
}

void Coordinates::setCoordinates(QVariantList newValue) {
	setCoordinatesArray(QJsonArray::fromVariantList(newValue));
	emit coordinatesChanged();
}

void Coordinates::setCoordinates(QPointF newValue) {
	this->setX(newValue.x());
	this->setY(newValue.y());

	emit coordinatesChanged();
}

void Coordinates::setCoordinatesArray(QJsonArray coordz) {
	if (coordz.size() != 2) {
		return;
	}

	// longitude
	QJsonValue coord = coordz.at(0);
	if (!coord.isUndefined() && coord.isDouble()) {
		qreal longi = coord.toDouble();
		if (qAbs(longi) <= 180) {
			this->setX(longi);
		}
	}

	// latitude
	coord = coordz.at(1);
	if (!coord.isUndefined() && coord.isDouble()) {
		qreal lati = coord.toDouble();
		if (qAbs(lati) <= 180) {
			this->setX(lati);
		}
	}
}

// type
QString Coordinates::TYPE_PN = "type";

QString Coordinates::getType() {
	return this->coordType;
}

void Coordinates::setType(QString newValue) {
	this->coordType = newValue;
	emit typeChanged();
}
