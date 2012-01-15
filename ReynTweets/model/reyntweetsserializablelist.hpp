/// @file reyntweetsserializablelist.hpp
/// @brief Header of ReynTweetsSerializable
/// @author Romain Ducher

/*
Copyright 2012 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef REYNTWEETSSERIALIZABLELIST_HPP
#define REYNTWEETSSERIALIZABLELIST_HPP

#include <QList>
#include <QVariant>
#include "reyntweetsserializable.hpp"

/// @class ReynTweetsSerializableList
/// @brief Class for object that needs to be converted into a QVariantList.
///
/// In practice, these objects will be lists of ReynTweetsSerializable objects
/// whose type is represented by the template type S.
/// @param S Type of a ReynTweetsSerializable object.
template <class S>
class ReynTweetsSerializableList : public ReynTweetsSerializable<QVariantList>, public QList<S>
{
	public:
		/// @fn ReynTweetsSerializableList();
		/// @brief Constructor
		ReynTweetsSerializableList();

		/// @fn virtual void fillWithVariant(QVariantList entities);
		/// @brief Filling the list with the contentnt of a QVariantList
		/// @param entities The QVariantList
		virtual void fillWithVariant(QVariantList entities);

		/// @fn virtual QVariantList toVariant() const;
		/// @brief Converting the list of serializables into a QVariantList.
		/// @return The corresponding QVariantList.
		virtual QVariantList toVariant() const;
};

#endif // REYNTWEETSSERIALIZABLELIST_HPP
