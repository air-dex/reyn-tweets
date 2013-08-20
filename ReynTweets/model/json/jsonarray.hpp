/// @file jsonarray.hpp
/// @brief Header of JsonArray
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

#ifndef JSONARRAY_HPP
#define JSONARRAY_HPP

#include <QJsonArray>
#include "../listable.tpp"
#include "jsonable.hpp"

/// @class JsonArray
/// @brief Base class for all objects which can be represented by a JSON array.
/// @param V Type of the objects which composed the list.
template <typename V>
class JsonArray : public Listable<V>, public Jsonable<QJsonArray>
{
	public:
		/// @fn JsonArray();
		/// @brief Constructor
		JsonArray();

		/// @fn virtual ~JsonArray();
		/// @brief Destructor
		virtual ~JsonArray();

		/// @fn Listable(const JsonArray<V> & list);
		/// @brief Copy constructor
		/// @param list JsonArray to copy
		JsonArray(const JsonArray<V> & list);

		/// @fn const JsonArray<V> & operator=(const JsonArray<V> & list);
		/// @brief Affrection operator
		/// @param list Listable to affect
		const JsonArray<V> & operator=(const JsonArray<V> & list);

		//////////////////////////////
		// Jsonable virtual methods //
		//////////////////////////////

		/// @fn virtual void fillWithJSON(QJsonArray json);
		/// @brief Filling a JsonArray with a QJsonArray.
		/// contained in the map.
		/// @param json The QJsonArray
		virtual void fillWithJSON(QJsonArray json);

		/// @fn virtual QJsonArray toJSON() const;
		/// @brief Converting the JsonArray into a QJsonArray.
		/// @return The corresponding QJsonArray.
		virtual QJsonArray toJSON() const;

		/////////////////////
		// Stream handling //
		/////////////////////

		/// @fn virtual QDataStream & fillWithStream(QDataStream & in);
		/// @brief Filling the Jsonable with the content of a QDataStream
		/// @param in The stream
		/// @return The stream after being read.
		virtual QDataStream & fillWithStream(QDataStream & in);

		/// @fn virtual QDataStream & writeInStream(QDataStream & out) const;
		/// @brief Writing a QDataStream with the content of the Jsonable
		/// @param out The stream
		/// @return The stream after being written.
		virtual QDataStream & writeInStream(QDataStream & out) const;

	protected:
		/// @fn virtual void recopie(const JsonArray<V> & list);
		/// @brief Copy of a Listable
		/// @param list JsonArray to copy
		virtual void recopie(const JsonArray<V> &list);
};

#endif // JSONARRAY_HPP