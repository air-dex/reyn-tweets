/// @file geocoordpolygonhandler.cpp
/// @brief Implementation of GeoCoordPolygonHandler
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

#include "geocoordpolygonhandler.hpp"
#include <QtQml>

// Constructor
GeoCoordPolygonHandler::GeoCoordPolygonHandler() :
	ListHandler<GeoCoordPolygon, GeoCoordList>()
{}

// Destructor
GeoCoordPolygonHandler::~GeoCoordPolygonHandler() {}

// Copy constructor
GeoCoordPolygonHandler::GeoCoordPolygonHandler(const GeoCoordPolygonHandler & handler) :
	ListHandler<GeoCoordPolygon, GeoCoordList>()
{
	recopie(handler);
}

// Affrection operator
const GeoCoordPolygonHandler & GeoCoordPolygonHandler::operator=(const GeoCoordPolygonHandler & handler) {
	recopie(handler);
	return *this;
}

// Copy of a HashtagsHandler
void GeoCoordPolygonHandler::recopie(const GeoCoordPolygonHandler &handler) {
	ListHandler<GeoCoordPolygon, GeoCoordList>::recopie(handler);
}

// Serialization initialization
void GeoCoordPolygonHandler::initSystem() {
	qRegisterMetaTypeStreamOperators<GeoCoordPolygonHandler>("GeoCoordPolygonHandler");
	qMetaTypeId<GeoCoordPolygonHandler>();
}

// Declaring to the QML components
void GeoCoordPolygonHandler::declareQML() {
	qmlRegisterType<GeoCoordPolygonHandler>("ReynTweetsEntities",
											0, 2,
											"GeoCoordPolygonHandler");
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out,
						 const GeoCoordPolygonHandler & handler)
{
	return handler.handledList.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, GeoCoordPolygonHandler & handler) {
	return handler.handledList.fillWithStream(in);
}


///////////////////
// List Handling //
///////////////////

GeoCoordList * GeoCoordPolygonHandler::get(int index) {
	return ListHandler<GeoCoordPolygon, GeoCoordList>::get(index);
}

// Filling an element with a QVariant
void GeoCoordPolygonHandler::fillElement(GeoCoordList &realElt,
										 QVariant varelt,
										 bool resetValue)
{
	if (resetValue) {
		realElt.clear();
	}

	realElt.fillWithVariant(QJsonArray::fromVariantList(varelt.toList()));
}
