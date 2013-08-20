/// @file jsonobjectarray.hpp
/// @brief Header of JsonObjectArray
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

#ifndef JSONOBJECTARRAY_HPP
#define JSONOBJECTARRAY_HPP

#include "jsonvariantablearray.tpp"

/// @class JsonObjectArray
/// @brief Base class for JsonArray containing JsonObject.
/// @param V Type of element in the array. <strong>V has to extend
/// JsonObject.</strong>
template <class V>
class JsonObjectArray : public JsonVariantableArray<V>
{
	public:
		/// @fn JsonObjectArray();
		/// @brief Constructor
		JsonObjectArray();

		/// @fn virtual ~JsonObjectArray();
		/// @brief Destructor
		virtual ~JsonObjectArray();

		/// @fn JsonObjectArray(const JsonObjectArray<V> & list);
		/// @brief Copy constructor
		/// @param list JsonObjectArray to copy
		JsonObjectArray(const JsonObjectArray<V> & list);

		/// @fn const JsonObjectArray<V> & operator=(const JsonObjectArray<V> & list);
		/// @brief Affection operator
		/// @param list JsonObjectArray to affect
		const JsonObjectArray<V> & operator=(const JsonObjectArray<V> & list);

	protected:
		/// @fn virtual void appendJsonValue(QJsonValue v);
		/// @brief Appending the content of a QJsonValue in the JsonArray
		/// @param v the QJsonValue
		virtual void appendJsonValue(QJsonValue v);
};

#endif // JSONOBJECTARRAY_HPP
