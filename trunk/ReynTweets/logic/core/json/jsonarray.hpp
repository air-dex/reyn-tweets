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
#include <QDataStream>
#include "../variantable.hpp"

/// @class JsonArray
/// @brief Base class for all objects which can be represented by a JSON array.
/// @param V Type of the objects which composed the list.
template <typename V>
class JsonArray : public Variantable<QJsonArray>, public QList<V>
{
	public:
		/// @fn JsonArray();
		/// @brief Constructor
		JsonArray();

		/// @fn virtual ~JsonArray();
		/// @brief Destructor
		virtual ~JsonArray();

		/// @fn JsonArray(const JsonArray<V> & list);
		/// @brief Copy constructor
		/// @param list JsonArray to copy
		JsonArray(const JsonArray<V> & list);

		/// @fn const JsonArray<V> & operator=(const JsonArray<V> & list);
		/// @brief Affection operator
		/// @param list JsonArray to affect
		const JsonArray<V> & operator=(const JsonArray<V> & list);


		////////////
		// Search //
		////////////

		/// @fn virtual int elementIndex(V element);
		/// @brief Custom method for getting the element of an index.
		///
		/// This method uses QList::indexOf(); but it could be overriden for
		/// better performances (dichotomy in sorted JsonArrays like Timelines).
		/// @param element The element
		/// @return The index
		virtual int elementIndex(V element);

		/// @fn virtual void insertElement(V element);
		/// @brief Custom method for inserting an element.
		/// @param element The element to insert
		virtual void insertElement(V element);

		/////////////////////////////////
		// Variantable virtual methods //
		/////////////////////////////////

		/// @fn virtual void fillWithVariant(QJsonArray json);
		/// @brief Filling a JsonArray with a QJsonArray.
		/// contained in the map.
		/// @param json The QJsonArray
		virtual void fillWithVariant(QJsonArray json);

		/// @fn virtual QJsonArray toVariant() const;
		/// @brief Converting the JsonArray into a QJsonArray.
		/// @return The corresponding QJsonArray.
		virtual QJsonArray toVariant() const;

		/////////////////////
		// Stream handling //
		/////////////////////

		/// @fn virtual QDataStream & fillWithStream(QDataStream & in);
		/// @brief Filling the JsonArray with the content of a QDataStream
		/// @param in The stream
		/// @return The stream after being read.
		virtual QDataStream & fillWithStream(QDataStream & in);

		/// @fn virtual QDataStream & writeInStream(QDataStream & out) const;
		/// @brief Writing a QDataStream with the content of the JsonArray
		/// @param out The stream
		/// @return The stream after being written.
		virtual QDataStream & writeInStream(QDataStream & out) const;

	protected:
		/// @fn virtual void recopie(const JsonArray<V> & list);
		/// @brief Copy of a JsonArray
		/// @param list JsonArray to copy
		virtual void recopie(const JsonArray<V> &list);

		/// @fn virtual void appendJsonValue(QJsonValue v) = 0;
		/// @brief Appending the content of a QJsonValue in the JsonArray
		/// @param v the QJsonValue
		virtual void appendJsonValue(QJsonValue v) = 0;

		/// @fn virtual void appendJsonArrayElement(QJsonArray & array,
		///											V elt) const = 0;
		/// @brief Appends an element of the list in a QJsonArray
		/// @param array The QJsonArray
		/// @param elt The list element
		virtual void appendJsonArrayElement(QJsonArray & array, V elt) const = 0;
};

#endif // JSONARRAY_HPP
