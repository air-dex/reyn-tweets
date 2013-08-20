/// @file jsonarrayarray.cpp
/// @brief Implementation of JsonArrayArray
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

#include "jsonarrayarray.hpp"

// Constructor
template <typename V>
JsonArrayArray<V>::JsonArrayArray() :
	JsonVariantableArray<V>()
{}

// Destructor
template <typename V>
JsonArrayArray<V>::~JsonArrayArray() {}

// Copy constructor
template <typename V>
JsonArrayArray<V>::JsonArrayArray(const JsonArrayArray<V> & list) :
	JsonVariantableArray<V>()
{
	recopie(list);
}

// Affection operator
template <typename V>
const JsonArrayArray<V> & JsonArrayArray<V>::operator=(const JsonArrayArray<V> & list) {
	recopie(list);
	return *this;
}

// Appending the content of a QJsonValue in the JsonArray
template <typename V>
void JsonArrayArray<V>::appendJsonValue(QJsonValue v) {
	if (v.isArray()) {
		V elt;
		elt.fillWithVariant(v.toArray());
		this->append(elt);
	}
}
