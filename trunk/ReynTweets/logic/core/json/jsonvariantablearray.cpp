/// @file jsonvariantablearray.cpp
/// @brief Implementation of JsonVariantableArray
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

#include "jsonvariantablearray.hpp"

// Constructor
template <typename V>
JsonVariantableArray<V>::JsonVariantableArray() :
	JsonArray<V>()
{}

// Destructor
template <typename V>
JsonVariantableArray<V>::~JsonVariantableArray() {}

// Copy constructor
template <typename V>
JsonVariantableArray<V>::JsonVariantableArray(const JsonVariantableArray<V> & list) :
	JsonArray<V>()
{
	recopie(list);
}

//Affection operator
template <typename V>
const JsonVariantableArray<V> & JsonVariantableArray<V>::operator=(const JsonVariantableArray<V> & list) {
	this->recopie(list);
	return *this;
}

// Appends an element of the list in a QJsonArray
template <typename V>
void JsonVariantableArray<V>::appendJsonArrayElement(QJsonArray & array, V elt) const {
	array.append(elt.toVariant());
}
