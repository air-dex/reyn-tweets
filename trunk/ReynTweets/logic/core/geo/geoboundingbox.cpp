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
#include <QtQml>
#include <QJsonArray>
#include "../../reyntweetsutils.hpp"

/////////////
// Coplien //
/////////////

// Default constructor
GeoBoundingBox::GeoBoundingBox() :
	GenericCoordinates<GeoCoordPolygon, GeoCoordPolygonHandler>()
{
	this->coordType = ReynTweets::POLYGON;
}

// Destructor
GeoBoundingBox::~GeoBoundingBox() {}

// Copy constructor
GeoBoundingBox::GeoBoundingBox(const GeoBoundingBox & coord) :
	GenericCoordinates<GeoCoordPolygon, GeoCoordPolygonHandler>()
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

// Declaring to the QML components
void GeoBoundingBox::declareQML() {
	// @uri ReynTweetsComponents
	qmlRegisterType<GeoBoundingBox>(ReynTweets::QML_LIBRARY_NAME.toLatin1().constData(),
									ReynTweets::MAJOR_VERSION, ReynTweets::MINOR_VERSION,
									"GeoBoundingBox");
}

// Reset
void GeoBoundingBox::reset() {
	*this = GeoBoundingBox();
}


/////////////////////////////////////
// Friends serialization operators //
/////////////////////////////////////

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const GeoBoundingBox & coord) {
	return coord.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, GeoBoundingBox & coord) {
	return coord.fillWithStream(in);
}


// Getting all the coordinates bounds.
GeoCoordList GeoBoundingBox::getBoundsList() const {
	return geoCoordinates.at(0);
}
