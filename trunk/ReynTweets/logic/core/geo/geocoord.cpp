/// @file geocoord.cpp
/// @brief Implementation of GeoCoord
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

#include "geocoord.hpp"

// Constant for fake coordinates
qreal GeoCoord::FAKE_COORD = 361;

// Default constructor
GeoCoord::GeoCoord() :
	JsonArray<double>(),
	QPointF(FAKE_COORD, FAKE_COORD)
{}

// Destructor
GeoCoord::~GeoCoord() {}

// Copy constructor
GeoCoord::GeoCoord(const GeoCoord & coord) :
	JsonArray<double>(),
	QPointF(FAKE_COORD, FAKE_COORD)
{
	recopie(coord);
}

// Affectation
const GeoCoord & GeoCoord::operator=(const GeoCoord & coord) {
	recopie(coord);
	return *this;
}

// Copy of a Coordinates
void GeoCoord::recopie(const GeoCoord & coord) {
	JsonArray<double>::recopie(coord);
	this->setX(coord.x());
	this->setY(coord.y());
}

// Serialization declaration
void GeoCoord::initSystem() {
	qRegisterMetaTypeStreamOperators<GeoCoord>("GeoCoord");
	qMetaTypeId<GeoCoord>();
}

// Resets the mappable to a default value
void GeoCoord::reset() {
	*this = GeoCoord();
}

// Equality
bool GeoCoord::operator==(const GeoCoord & coord) const {
	return this->x() == coord.x() && this->y() == coord.y();
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonArray.
void GeoCoord::fillWithVariant(QJsonArray json) {
	if (json.size() != 2) {
		return;
	}

	this->clear();

	// longitude
	double longi = json.at(0).toDouble(181);	// Fake longitude by default
	if (qAbs(longi) <= 180) {
		this->setX(longi);
	}

	// latitude
	double lati = json.at(1).toDouble(91);		// Fake latitude by default
	if (qAbs(lati) <= 90) {
		this->setY(lati);
	}
}

// QJsonArray representation of the object
QJsonArray GeoCoord::toVariant() const {
	QJsonArray coordz;

	coordz.append(QJsonValue(this->x()));
	coordz.append(QJsonValue(this->y()));

	return coordz;
}

// Appending the content of a QJsonValue
void GeoCoord::appendJsonValue(QJsonValue v) {
	if (v.isDouble()) {
		double dvalue = v.toDouble();
		this->append(dvalue);
	}
}

// Appends an element of the list in a QJsonArray
void GeoCoord::appendJsonArrayElement(QJsonArray & array, double elt) const {
	array.append(elt);
}


/////////////////////////////////////
// Friends serialization operators //
/////////////////////////////////////

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const GeoCoord & coord) {
	return coord.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, GeoCoord & coord) {
	return coord.fillWithStream(in);
}
