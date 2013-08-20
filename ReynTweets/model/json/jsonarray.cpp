/// @file jsonarray.cpp
/// @brief Implementation of JsonArray
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

#include "jsonarray.hpp"
#include <QJsonDocument>
#include "../../tools/parsers/jsonparser.hpp"
#include "../../tools/utils.hpp"

/////////////
// Coplien //
/////////////

// Constructor
template <typename V>
JsonArray<V>::JsonArray() :
	Listable<V>(),
	Jsonable<QJsonArray>()
{}

// Destructor
template <typename V>
JsonArray<V>::~JsonArray() {}

// Copy constructor
template <typename V>
JsonArray<V>::JsonArray(const JsonArray<V> & list) :
	Listable<V>(),
	Jsonable<QJsonArray>()
{
	this->recopie(list);
}

// Affrection operator
template <typename V>
const JsonArray<V> & JsonArray<V>::operator=(const JsonArray<V> & list) {
	this->recopie(list);
	return *this;
}

// Copy of a Listable
template <typename V>
void JsonArray<V>::recopie(const JsonArray<V> & list) {
	this->Listable<V>::recopie(list);
}


//////////////////////////////
// Jsonable virtual methods //
//////////////////////////////

// Filling a JsonArray with a QJsonArray.
template <typename V>
void JsonArray<V>::fillWithJSON(QJsonArray json) {
	QVariantList entities = json.toVariantList();
	this->fillWithVariant(entities);
}

// Converting the JsonArray into a QJsonArray
template <typename V>
QJsonArray JsonArray<V>::toJSON() const {
	return QJsonArray::fromVariantList(this->toVariant());
}


/////////////////////
// Stream handling //
/////////////////////

// Filling the Jsonable with the content of a QDataStream
template <typename V>
QDataStream & JsonArray<V>::fillWithStream(QDataStream & in) {
	QByteArray json = "";
	in >> json;

	JSONParser parser;
	bool parseOK;
	QJsonValue parsedJson = parser.parse(json, &parseOK);

	if (parseOK && parsedJson.isArray()) {
		this->fillWithJSON(parsedJson.toArray());
	}

	return in;
}

// Writing a QDataStream with the content of the Jsonable
template <typename V>
QDataStream & JsonArray<V>::writeInStream(QDataStream & out) const {
	QJsonArray array = this->toJSON();
	QJsonDocument doc(array);
	QByteArray json = doc.toJson();
	out << json;
	return out;
}
