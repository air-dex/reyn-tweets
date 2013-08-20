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

// Apparently, g++ needs to include QJsonArray.
#ifdef Q_OS_LINUX
	#include <QJsonArray>
#endif

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
void GenericCoordinates<C>::fillWithVariant(QJsonObject json) {
	this->geoCoordinates.fillWithVariant(json.value(COORDINATES_PN).toArray());
	this->coordType = CoordType::string2coord(json.value(TYPE_PN).toString(""));
}

// QJsonObject representation of the object
template <typename C>
QJsonObject GenericCoordinates<C>::toVariant() const {
	QJsonObject json;

	json.insert(COORDINATES_PN, QJsonValue(this->geoCoordinates.toVariant()));
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
	return this->geoCoordinates.toVariant().toVariantList();
}

template <typename C>
C GenericCoordinates<C>::getCoordinates() {
	return this->geoCoordinates;
}

template <typename C>
void GenericCoordinates<C>::setCoordinates(QVariantList newValue) {
	this->geoCoordinates.fillWithVariant(QJsonArray::fromVariantList(newValue));
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

