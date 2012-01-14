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
template <class V>
class ReynTweetsSerializable
{
	public:
		/// @fn virtual V toVariant() const = 0;
		/// @brief Converting the object into a QVariantMap
		/// @return A QVariantMap containing all the informations.
		virtual V toVariant() const = 0;

		/// @fn virtual void fillWithVariant(V map) = 0;
		/// @brief Filling a ReynTweetsSerializable object with the informations
		/// contained in the map.
		/// @param map The map
		virtual void fillWithVariant(V map) = 0;

	protected:
		/// @fn virtual void syncMembers() = 0;
		/// @brief Syncing members with properties to serialize.
		virtual void syncMembers() = 0;

		/// @fn virtual void syncProperties();
		/// @brief Syncing properties to serialize with the corresponding members.
		virtual void syncProperties() = 0;
};

#endif // REYNTWEETSSERIALIZABLE_HPP
