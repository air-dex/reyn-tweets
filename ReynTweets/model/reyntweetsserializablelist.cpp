/// @file reyntweetsserializablelist.cpp
/// @brief Implementation of ReynTweetsSerializable
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

#include "reyntweetsserializablelist.hpp"

// Constructor
template <class S>
ReynTweetsSerializableList<S>::ReynTweetsSerializableList() :
	QList<S>()
{}

// Converting a QVariantList serialized by QJSON into a list of entities.
template <class S>
void ReynTweetsSerializableList<S>::fillWithVariant(QVariantList entities) {
	empty();

	for (QVariantList::Iterator it = entities.begin();
		 it != entities.end();
		 ++it)
	{
		QVariant v = *it;
		S entity = qVariantValue<S>(v);
		append(entity);
	}
}

// Converting a list of serializables into a QVariantList
template <class S>
QVariantList ReynTweetsSerializableList<S>::toVariant() const {
	QVariantList res;

	for (QList<S>::const_iterator it = this->begin();
		 it != end();
		 ++it)
	{
		S serializable = *it;
		res.append(qVariantFromValue(serializable));
	}

	return res;
}
