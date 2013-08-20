/// @file geocoordlist.cpp
/// @brief Implementation of GeoCoordList
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

#include "geocoordlist.hpp"

// Constructor
GeoCoordList::GeoCoordList() :
	JsonArray<GeoCoord>()
{}

// Destructor
GeoCoordList::~GeoCoordList() {}

// Copy constructor
GeoCoordList::GeoCoordList(const GeoCoordList & list) :
	JsonArray<GeoCoord>()
{
	recopie(list);
}

// Affrection operator
const GeoCoordList & GeoCoordList::operator=(const GeoCoordList & list) {
	recopie(list);
	return *this;
}

// Serialization initialization
void GeoCoordList::initSystem() {
	qRegisterMetaTypeStreamOperators<GeoCoordList>("GeoCoordList");
	qMetaTypeId<GeoCoordList>();
}

// Appending the content of a QJsonValue
void GeoCoordList::appendJsonValue(QJsonValue v) {
	if (v.isArray()) {
		GeoCoord gc;
		gc.fillWithVariant(v.toArray());
		this->append(gc);
	}
}

// Appends an element of the list in a QJsonArray
void GeoCoordList::appendJsonArrayElement(QJsonArray & array, GeoCoord elt) const {
	array.append(elt.toVariant());
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const GeoCoordList & list) {
	return list.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, GeoCoordList & list) {
	return list.fillWithStream(in);
}