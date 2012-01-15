/// @file reyntweetsmappable.hpp
/// @brief Header of ReynTweetsMappable
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

#ifndef REYNTWEETSMAPPABLE_HPP
#define REYNTWEETSMAPPABLE_HPP

#include <QObject>
#include <QVariant>
#include "reyntweetsserializable.hpp"

/// @class ReynTweetsMappable
/// @brief Serializable objects that needed to be converted into a QVariantMap.
///
/// In practice, QJSON often parses replies in QVariantMaps whose keys are
/// the name of the different fields of the replies. The values corresponding to
/// the fields are stocked in QVariant objects. Complex field values are stored
/// in QVariantLists or QVariantMaps.
///
/// But ReynTweets do not manipulate QVariantMaps with fields but complex objects
/// with values which gets a meaning (ex. : a tweet with a text (string), an ID
/// (number), a writer. Not a QVariantMap with fields named "text", "id" or
/// "user"). Informations needed by these objects are stored in the QVariantMaps
/// made by QJSON so the QVariantMaps have to be converted in these complex
/// objects. Moreover, the objects may be serialized and QJSON can only
/// manipulate simple types or QVariantMaps (or QVariantLists for lists with
/// things whose type can be manipulated by QJSON). That's why the complex
/// objects needs to be converted into QVariantMaps.
///
/// In the complex objects, the fields of QVariantMaps are stocked in QObject
/// properties which are represented by class members. Types of the class
/// members are the type of the QVariant value of the field.
///
/// However, some properties gets a particular meaning and cannot be represented
/// with a simple type manipulable by QJSON. These fields get an equivalent member
/// (often a ReynTweetsSerializable - the class was made for them) that are
/// synced with their corresponding properties via two methods called <code>
/// syncMembers()</code> and <code>syncProperties()</code>.
class ReynTweetsMappable : public QObject, public ReynTweetsSerializable<QVariantMap>
{
	Q_OBJECT

	public:
		/// @fn virtual QVariantMap toVariant() const;
		/// @brief Converting the object into a QVariantMap
		/// @return A QVariantMap containing all the informations.
		virtual QVariantMap toVariant() const;

		/// @fn virtual void fillWithVariant(QVariantMap map);
		/// @brief Filling a serializable object with the informations
		/// contained in a map.
		/// @param map The map
		virtual void fillWithVariant(QVariantMap map);

	protected:
		/// @fn virtual void syncMembers() = 0;
		/// @brief Syncing members with properties to serialize.
		virtual void syncMembers() = 0;

		/// @fn virtual void syncProperties() = 0;
		/// @brief Syncing properties to serialize with the corresponding members.
		virtual void syncProperties() = 0;
};

#endif // REYNTWEETSMAPPABLE_HPP
