/// @file jsonarrayarray.hpp
/// @brief Header of JsonArrayArray
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

#ifndef JSONARRAYARRAY_HPP
#define JSONARRAYARRAY_HPP

#include "jsonvariantablearray.tpp"

/// @class JsonArrayArray
/// @brief Base class for JsonArrays containing JsonArrays.
/// @param V Type of element in the array. <strong>V has to extend
/// JsonArray.</strong>
template <class V>
class JsonArrayArray : public JsonVariantableArray<V>
{
	public:
		/// @fn JsonArrayArray();
		/// @brief Constructor
		JsonArrayArray();

		/// @fn virtual ~JsonArrayArray();
		/// @brief Destructor
		virtual ~JsonArrayArray();

		/// @fn JsonArrayArray(const JsonArrayArray<V> & list);
		/// @brief Copy constructor
		/// @param list JsonArrayArray to copy
		JsonArrayArray(const JsonArrayArray<V> & list);

		/// @fn const JsonArrayArray<V> & operator=(const JsonArrayArray<V> & list);
		/// @brief Affection operator
		/// @param list JsonArrayArray to affect
		const JsonArrayArray<V> & operator=(const JsonArrayArray<V> & list);

	protected:
		/// @fn virtual void appendJsonValue(QJsonValue v);
		/// @brief Appending the content of a QJsonValue in the JsonArray
		/// @param v the QJsonValue
		virtual void appendJsonValue(QJsonValue v);
};

#endif // JSONARRAYARRAY_HPP
