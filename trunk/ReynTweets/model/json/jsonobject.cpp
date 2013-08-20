/// @file jsonobject.cpp
/// @brief Implementation of JsonObject
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

#include "jsonobject.hpp"
#include <QJsonDocument>
#include "../../tools/parsers/jsonparser.hpp"
#include "../../tools/utils.hpp"

/////////////
// Coplien //
/////////////

// Default constructor
JsonObject::JsonObject() :
	QObject(),
	Variantable<QJsonObject>()
{}

// Destructor
JsonObject::~JsonObject() {}

// Copy constructor
JsonObject::JsonObject(const JsonObject & jsonobj) :
	QObject(),
	Variantable<QJsonObject>()
{
	this->recopie(jsonobj);
}

// Affectation of a JsonObject
const JsonObject & JsonObject::operator=(const JsonObject & jsonobj) {
	this->recopie(jsonobj);
	return *this;
}

// Core method to copy a JsonObject
void JsonObject::recopie(const JsonObject & ) {}

/////////////////////
// Stream handling //
/////////////////////

// Filling the JsonObject with the content of a QDataStream
QDataStream & JsonObject::fillWithStream(QDataStream & in) {
	QByteArray json = "";
	in >> json;

	JSONParser parser;
	bool parseOK;
	QJsonValue parsedJson = parser.parse(json, &parseOK);

	if (parseOK && parsedJson.isObject()) {
		this->fillWithVariant(parsedJson.toObject());
	}

	return in;
}

// Writing a QDataStream with the content of the JsonObject
QDataStream & JsonObject::writeInStream(QDataStream & out) const {
	QJsonObject obj = this->toVariant();
	QJsonDocument doc(obj);
	QByteArray json = doc.toJson();
	out << json;
	return out;
}
