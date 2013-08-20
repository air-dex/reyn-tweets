/// @file genericcoordinates.cpp
/// @brief Implementation of GenericCoordinates
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

#include "genericcoordinates.hpp"

/////////////
// Coplien //
/////////////

// Default constructor
template <typename C>
GenericCoordinates<C>::GenericCoordinates() :
	GenCoord(),
	geoCoordinates(),
	coordType(CoordType::FAKE_COORDINATES)
{}

// Destructor
template <typename C>
GenericCoordinates<C>::~GenericCoordinates() {}

// Copy constructor
template <typename C>
GenericCoordinates<C>::GenericCoordinates(const GenericCoordinates<C> & coord) :
	GenCoord(),
	geoCoordinates(),
	coordType(CoordType::FAKE_COORDINATES)
{
	this->recopie(coord);
}

// Affectation
template <typename C>
const GenericCoordinates<C> & GenericCoordinates<C>::operator=(const GenericCoordinates<C> & coord) {
	this->recopie(coord);
	return *this;
}

// Copy of a GenericCoordinates
template <typename C>
void GenericCoordinates<C>::recopie(const GenericCoordinates<C> & coord) {
	GenCoord::recopie(coord);
	this->geoCoordinates = coord.geoCoordinates;
	this->coordType = coord.coordType;
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
template <typename C>
void GenericCoordinates<C>::fillWithJSON(QJsonObject json) {
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
		this->coordType = CoordType::string2coord(kind);
	}
}

// QJsonObject representation of the object
template <typename C>
QJsonObject GenericCoordinates<C>::toJSON() const {
	QJsonObject json;

	json.insert(COORDINATES_PN, QJsonValue(this->geoCoordinates.toJSON()));
	json.insert(TYPE_PN, QJsonValue(CoordType::coord2string(this->coordType)));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// coordinates
template <typename C>
QString GenericCoordinates<C>::COORDINATES_PN = "coordinates";

template <typename C>
QVariantList GenericCoordinates<C>::getCoordinatesProperty() {
	return this->geoCoordinates.toVariant();
}

template <typename C>
C GenericCoordinates<C>::getCoordinates() {
	return this->geoCoordinates;
}

template <typename C>
void GenericCoordinates<C>::setCoordinates(QVariantList newValue) {
	this->geoCoordinates.fillWithVariant(newValue);
	changeCoord();
}

template <typename C>
void GenericCoordinates<C>::setCoordinates(C newValue) {
	this->geoCoordinates = newValue;
	changeCoord();
}

// type
template <typename C>
QString GenericCoordinates<C>::TYPE_PN = "type";

template <typename C>
QString GenericCoordinates<C>::getTypeProperty() {
	return coord2string(this->coordType);
}

template <typename C>
CoordinatesType GenericCoordinates<C>::getType() {
	return this->coordType;
}

template <typename C>
void GenericCoordinates<C>::setType(CoordinatesType newValue) {
	this->coordType = newValue;
	changeType();
}

template <typename C>
void GenericCoordinates<C>::setType(QString newValue) {
	this->coordType = CoordType::string2coord(newValue);
	changeType();
}

