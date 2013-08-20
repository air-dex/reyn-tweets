/// @file jsonvariantablearray.cpp
/// @brief Header of JsonVariantableArray
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

#ifndef JSONVARIANTABLEARRAY_HPP
#define JSONVARIANTABLEARRAY_HPP

#include "jsonarray.tpp"

/// @class JsonVariantableArray
/// @brief Base class for JsonArrays containing JsonObjects.
/// @param V Type of element in the array. <strong>V has to extend
/// Variantable.</strong>
template <class V>
class JsonVariantableArray : public JsonArray<V>
{
	public:
		/// @fn JsonVariantableArray();
		/// @brief Constructor
		JsonVariantableArray();

		/// @fn virtual ~JsonVariantableArray();
		/// @brief Destructor
		virtual ~JsonVariantableArray();

		/// @fn JsonVariantableArray(const JsonVariantableArray<V> & list);
		/// @brief Copy constructor
		/// @param list JsonVariantableArray to copy
		JsonVariantableArray(const JsonVariantableArray<V> & list);

		/// @fn const JsonVariantableArray<V> & operator=(const JsonVariantableArray<V> & list);
		/// @brief Affection operator
		/// @param list JsonVariantableArray to affect
		const JsonVariantableArray<V> & operator=(const JsonVariantableArray<V> & list);

	protected:
		/// @fn virtual void appendJsonArrayElement(QJsonArray & array,
		///											V elt) const;
		/// @brief Appends an element of the list in a QJsonArray
		/// @param array The QJsonArray
		/// @param elt The list element
		virtual void appendJsonArrayElement(QJsonArray & array, V elt) const;
};

#endif // JSONVARIANTABLEARRAY_HPP
