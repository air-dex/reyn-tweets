/// @file reyntweetsserializable.hpp
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

#include "reyntweetsserializable.hpp"

// Syncing members with properties to serialize.
template <class V>
void ReynTweetsSerializable<V>::syncMembers() {}

// Syncing properties to serialize with the corresponding members.
template <class V>
void ReynTweetsSerializable<V>::syncProperties() {}

/*
// Converting the object into a QVariantMap
V ReynTweetsSerializable::toVariant() {
	return QJson::QObjectHelper::qobject2qvariant(this);
}

// Filling a ReynTweetsSerializable object with the informations
void ReynTweetsSerializable::fillWithMap(V map) {
	QJson::QObjectHelper::qvariant2qobject(map, this);
}


//////////
// Util //
//////////
// Converting a QVariantList serialized by QJSON into a list of entities.
template <class T>
QList<T> fillWithList(QVariantList entities) {
	QList<T> res;

	for (QVariantList::Iterator it = entities.begin();
		 it != entities.end();
		 ++it) {
		QVariant v = *it;
		T entity = qVariantValue(v);
		res.append(entity);
	}

	return res;
}

// Converting a list of serializables into a QVariantList
template <class T>
QVariantList toVariantList(QList<T> serializables) {
	QVariantList res;

	for (QList<T>::iterator it = serializables.begin();
		 it != serializables.end();
		 ++it)
	{
		T serializable = *it;
		res.append(qVariantFromValue(serializable));
	}

	return res;
}

/*
// Converting a list of serializables into a QVariantList
QVariantList ReynTweetsSerializable::toVariantList(QList<ReynTweetsSerializable> serializables) {
	QVariantList res;

	for (QList<ReynTweetsSerializable>::iterator it = serializables.begin();
		 it != serializables.end();
		 ++it)
	{
		ReynTweetsSerializable serializable = *it;
		res.append(qVariantFromValue(serializable));
	}

	return res;
}

// Converting a QVariantList into a list of ReynTweetsSerializable
QList<ReynTweetsSerializable> ReynTweetsSerializable::fillWithList(QVariantList serializables) {

}
//*/
