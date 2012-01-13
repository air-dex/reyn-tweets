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

#ifndef REYNTWEETSSERIALIZABLE_HPP
#define REYNTWEETSSERIALIZABLE_HPP

#include <QObject>
#include <QVariant>

/// @class ReynTweetsSerializable
/// @brief Abstract class to represent classes which are serializable. It
/// converts the object into a QVariantMap which are serializable by QJSON
/// (<code>toMap();</code>) and vice versa (<code>fillWithMap();</code>).
/// Here are two default methods using the QObjectHelper class of QJSON.
class ReynTweetsSerializable : public QObject
{
	Q_OBJECT

	public:
		/// @fn virtual QVariantMap toMap();
		/// @brief Converting the object into a QVariantMap
		/// @return A QVariantMap containing all the informations.
		virtual QVariantMap toMap();

		/// @fn virtual void fillWithMap(QVariantMap map);
		/// @brief Filling a ReynTweetsSerializable object with the informations
		/// contained in the map.
		/// @param map The map
		virtual void fillWithMap(QVariantMap map);
/*
		/// @fn static QVariantList toVariantList(QList<ReynTweetsSerializable> serializables);
		/// @brief Converting a list of serializables into a QVariantList
		/// serializable by QJSON.
		/// @param serializables List to convert
		/// @return The corresponding QVariantList
		static QVariantList toVariantList(QList<ReynTweetsSerializable> serializables);

		/// @fn static QList<ReynTweetsSerializable> fillWithList(QVariantList serializables);
		/// @brief Converting a QVariantList serialized by QJSON into a list of
		/// ReynTweetsSerializable.
		/// @param serializables List to convert
		/// @return The corresponding list of ReynTweetsSerializable
		static QList<ReynTweetsSerializable> fillWithList(QVariantList serializables);
//*/

};

//////////
// Util //
//////////
/// @fn template <class T> QList<T> fillWithList(QVariantList entities);
/// @brief Converting a QVariantList serialized by QJSON into a list of
/// entities whose class is represented by the template parameter T.
/// @param entities List to convert
/// @return The corresponding list of entities
template <class T>
QList<T> fillWithList(QVariantList entities);

/// @fn QVariantList toVariantList(QList<ReynTweetsSerializable> serializables);
/// @brief Converting a list of serializables into a QVariantList
/// serializable by QJSON.
/// @param serializables List to convert
/// @return The corresponding QVariantList
template <class T>
QVariantList toVariantList(QList<T> serializables);

#endif // REYNTWEETSSERIALIZABLE_HPP
