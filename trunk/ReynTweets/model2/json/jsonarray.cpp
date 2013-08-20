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

/////////////
// Coplien //
/////////////

// Constructor
template <class V>
JsonArray<V>::JsonArray() :
	Listable<V>(),
	Jsonable<QJsonArray>(),
	QJsonArray()
{}

// Destructor
template <class V>
JsonArray<V>::~JsonArray() {}

// Copy constructor
template <class V>
JsonArray<V>::JsonArray(const JsonArray<V> & list) :
	Listable<V>(),
	Jsonable<QJsonArray>(),
	QJsonArray()
{
	this->recopie(list);
}

// Affrection operator
template <class V>
const JsonArray<V> & JsonArray<V>::operator=(const JsonArray<V> & list) {
	this->recopie(list);
	return *this;
}

// Copy of a Listable
template <class V>
void JsonArray<V>::recopie(const JsonArray<V> & list) {
	this->Listable<V>::recopie(list);
}

/////////////////
// Conversions //
/////////////////

// Special optimisations due to JSON

/*
// Filling the MappableList with a QVariantList.
template <class V>
void JsonArray<V>::fillWithVariant(QVariantList entities) {
	QJsonArray array = QJsonArray::fromVariantList(entities);
	this->fillWithJSON(array);
}
//*/

// Converting a MappableList into a QVariantList
template <class V>
QVariantList JsonArray<V>::toVariant() const {
	return this->toVariantList();
}

// Filling the MappableList with a QVariantList.
template <class V>
void JsonArray<V>::fillWithJSON(QJsonArray json) {
	QVariantList entities = json.toVariantList();
	this->fillWithVariant(entities);
}

// Converting a MappableList into a QVariantList
template <class V>
QJsonArray JsonArray<V>::toJSON() const {
	return this;
}


///////////////////////////
// Serialization streams //
///////////////////////////

template <class V>
QDataStream & jsonStreamingOut(QDataStream & out, const JsonArray<M> & list) {
	// Serialize the QVariantList form of the listable and putting it in the stream.
	return streamVariantOut(out, list.toVariant());
}

// Input stream operator for serialization
template <class V>
QDataStream & jsonStreamingIn(QDataStream & in, JsonArray<V> & list) {
	// TODO : use an improved JSONParser
	// TODO : handling parse errors

	QByteArray json = "";
	in >> json;

	QJsonDocument doc = QJsonDocument::fromJson(json, &parseErr);

	if (doc.isArray()) {
		QJsonArray array = doc.array();
		list.fillWithJSON(array);
	}

	return in;
}
