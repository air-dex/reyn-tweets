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

// Default constructor
GeoCoord::GeoCoord() :
	JsonArray<qreal>(),
	QPointF()
{}

// Destructor
GeoCoord::~GeoCoord() {}

// Copy constructor
GeoCoord::GeoCoord(const GeoCoord & coord) :
	JsonArray<qreal>(),
	QPointF()
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


////////////////////////
// Variant conversion //
////////////////////////

// Converting the bounds into a QVariantList
QVariantList GeoCoord::toVariant() const {
	return this->toJSON().toVariantList();
}

// Filling the object with a QVariantList
void GeoCoord::fillWithVariant(QVariantList variantList) {
	this->fillWithJSON(QJsonArray::fromVariantList(variantList));
}

/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonArray.
void GeoCoord::fillWithJSON(QJsonArray json) {
	if (json.size() != 2) {
		return;
	}

	this->clear();

	// longitude
	QJsonValue coord = json.at(0);
	if (!coord.isUndefined() && coord.isDouble()) {
		qreal longi = coord.toDouble();
		if (qAbs(longi) <= 180) {
			this->setX(longi);
		}
	}

	// latitude
	coord = json.at(1);
	if (!coord.isUndefined() && coord.isDouble()) {
		qreal lati = coord.toDouble();
		if (qAbs(lati) <= 90) {
			this->setY(lati);
		}
	}
}

// QJsonArray representation of the object
QJsonArray GeoCoord::toJSON() const {
	QJsonArray coordz;

	coordz.append(QJsonValue(this->x()));
	coordz.append(QJsonValue(this->y()));

	return coordz;
}


/////////////////////////////////////
// Friends serialization operators //
/////////////////////////////////////

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const GeoCoord & coord) {
	return jsonStreamingOut<qreal>(out, coord);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, GeoCoord & coord) {
	return jsonStreamingIn<qreal>(in, coord);
}
