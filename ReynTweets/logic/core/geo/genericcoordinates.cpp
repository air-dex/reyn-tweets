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
template <typename C, typename LH>
GenericCoordinates<C,LH>::GenericCoordinates() :
	GenCoord(),
	coordinatesHandler(),
	geoCoordinates(coordinatesHandler.getHandledListRef())
{}

// Destructor
template <typename C, typename LH>
GenericCoordinates<C,LH>::~GenericCoordinates() {}

// Copy constructor
template <typename C, typename LH>
GenericCoordinates<C,LH>::GenericCoordinates(const GenericCoordinates<C,LH> & coord) :
	GenCoord(),
	coordinatesHandler(),
	geoCoordinates(coordinatesHandler.getHandledListRef())
{
	this->recopie(coord);
}

// Affectation
template <typename C, typename LH>
const GenericCoordinates<C,LH> & GenericCoordinates<C,LH>::operator=(const GenericCoordinates<C,LH> & coord) {
	this->recopie(coord);
	return *this;
}

// Copy of a GenericCoordinates
template <typename C, typename LH>
void GenericCoordinates<C,LH>::recopie(const GenericCoordinates<C,LH> & coord) {
	GenCoord::recopie(coord);
	this->geoCoordinates = coord.geoCoordinates;
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
template <typename C, typename LH>
void GenericCoordinates<C,LH>::fillWithVariant(QJsonObject json) {
	GenCoord::fillWithVariant(json);	// Base class

	this->geoCoordinates.fillWithVariant(json.value(COORDINATES_PN).toArray());
}

// QJsonObject representation of the object
template <typename C, typename LH>
QJsonObject GenericCoordinates<C,LH>::toVariant() const {
	QJsonObject json = GenCoord::toVariant();	// Base class

	json.insert(COORDINATES_PN, QJsonValue(this->geoCoordinates.toVariant()));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// coordinates
template <typename C, typename LH>
QString GenericCoordinates<C,LH>::COORDINATES_PN = "coordinates";

template <typename C, typename LH>
LH * GenericCoordinates<C,LH>::getCoordinatesProperty() {
	return &coordinatesHandler;
}

template <typename C, typename LH>
C GenericCoordinates<C,LH>::getCoordinates() {
	return this->geoCoordinates;
}

template <typename C, typename LH>
void GenericCoordinates<C, LH>::setCoordinates(C newValue) {
	this->geoCoordinates = newValue;
	changeCoord();
}

