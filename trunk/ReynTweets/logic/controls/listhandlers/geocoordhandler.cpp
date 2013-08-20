/// @file geocoordhandler.cpp
/// @brief Implementation of CoordinatesListHandler
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

#include "geocoordhandler.hpp"
#include <QtQml>
#include "../../reyntweetsutils.hpp"

// Constructor
GeoCoordHandler::GeoCoordHandler() :
	ListHandler<GeoCoord, double>()
{}

// Destructor
GeoCoordHandler::~GeoCoordHandler() {}

// Copy constructor
GeoCoordHandler::GeoCoordHandler(const GeoCoordHandler & handler) :
	ListHandler<GeoCoord, double>()
{
	recopie(handler);
}

// Affection operator
const GeoCoordHandler & GeoCoordHandler::operator=(const GeoCoordHandler & handler) {
	recopie(handler);
	return *this;
}

// Copy of a IndexBoundsHandler
void GeoCoordHandler::recopie(const GeoCoordHandler &handler) {
	ListHandler<GeoCoord, double>::recopie(handler);
}

// Serialization initialization
void GeoCoordHandler::initSystem() {
	qRegisterMetaTypeStreamOperators<GeoCoordHandler>("GeoCoordHandler");
	qMetaTypeId<GeoCoordHandler>();
}

// Declaring to the QML components
void GeoCoordHandler::declareQML() {
	// @uri ReynTweetsComponents
	qmlRegisterType<GeoCoordHandler>(ReynTweets::QML_LIBRARY_NAME.toLatin1().constData(),
									 ReynTweets::MAJOR_VERSION, ReynTweets::MINOR_VERSION,
									 "GeoCoordHandler");
}


/////////////////////////////////////
// Friends serialization operators //
/////////////////////////////////////

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const GeoCoordHandler & handler) {
	return handler.handledList.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, GeoCoordHandler & handler) {
	return handler.handledList.fillWithStream(in);
}


////////////////////////////
// Rewriting some methods //
////////////////////////////

// Filling an element with a QVariant
void GeoCoordHandler::fillElement(double &realElt,
								  QVariant varelt,
								  bool resetValue)
{
	Q_UNUSED(resetValue)
	realElt = varelt.toDouble();
}


///////////////////
// List Handling //
///////////////////

double * GeoCoordHandler::get(int index) {
	return ListHandler<GeoCoord, double>::get(index);
}


//////////////////////////////////////////
// Properties on longitude and latitude //
//////////////////////////////////////////

// longitude
double GeoCoordHandler::getLongitude() {
	return handledList.x();
}

void GeoCoordHandler::setLongitude(double newLong) {
	handledList.setX(newLong);
	emit longitudeChanged();
}

// latitude
double GeoCoordHandler::getLatitude() {
	return handledList.y();
}

void GeoCoordHandler::setLatitude(double newLat) {
	handledList.setY(newLat);
	emit latitudeChanged();
}
