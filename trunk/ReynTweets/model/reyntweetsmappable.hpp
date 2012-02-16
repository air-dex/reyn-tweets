/// @file reyntweetsmappable.hpp
/// @brief Header of ReynTweetsMappable
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
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

#ifndef REYNTWEETSMAPPABLE_HPP
#define REYNTWEETSMAPPABLE_HPP

#include <QObject>
#include <QStringList>
#include <QVariant>
#include "reyntweetsserializable.hpp"

/// @class ReynTweetsMappable
/// @brief Serializable objects that needed to be converted into a QVariantMap.
///
/// In practice, QJSON parses replies in QVariantMaps whose keys are the name
/// of the different fields of the replies. The values corresponding to
/// the fields are stocked in QVariant objects. Complex field values are stored
/// in QVariantLists or QVariantMaps.
///
/// But ReynTweets do not manipulate QVariantMaps with fields but complex model
/// objects with values which get a meaning, just like a tweet with a text
/// (string), an ID(number), a writer. Not a QVariantMap with fields named
/// "text", "id" or "user". Informations needed by these objects are stored
/// in the QVariantMaps made by QJSON. As a consequence, the QVariantMaps
/// replies have to be converted in these model objects.<br/>
/// Moreover, the model objects may be serialized and QJSON can only
/// manipulate simple types or QVariantMaps (or QVariantLists for lists with
/// things whose type can be manipulated by QJSON). That's why the complex
/// model objects needs to be converted into QVariantMaps.
///
/// In the complex objects, the fields of QVariantMaps are stocked in QObject
/// properties which are represented by class members. Types of the class
/// members are the type of the QVariant value of the field.
///
/// However, some properties gets a particular meaning and cannot be represented
/// with a simple type manipulable by QJSON. These fields get an equivalent
/// member (often a ReynTweetsSerializable - the class was made for them) that
/// corresponds to a QVariantList or a QVariantMap property.
class ReynTweetsMappable : public QObject, public ReynTweetsSerializable<QVariantMap>
{
	Q_OBJECT

	public:
		/// @fn explicit ReynTweetsMappable(bool blacklistObjectName = true);
		/// @brief Constructor
		/// @param blacklistObjectName Boolean indicating if the "objectName"
		/// property of QObject has to be included in transientProperties.
		explicit ReynTweetsMappable(bool blacklistObjectName = true);

		/// @fn virtual ~ReynTweetsMappable();
		/// @brief Destructor
		virtual ~ReynTweetsMappable();

		/// @fn ReynTweetsMappable(const ReynTweetsMappable & mappable);
		/// @brief Copy constructor
		/// @param mappable ReynTweetsMappable to copy
		ReynTweetsMappable(const ReynTweetsMappable & mappable);

		/// @fn const ReynTweetsMappable & operator=(const ReynTweetsMappable & mappable);
		/// @brief Affecting a ReynTweetsMappable
		/// @param mappable ReynTweetsMappable to copy
		const ReynTweetsMappable & operator=(const ReynTweetsMappable & mappable);

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
		/// @brief List of properties to ignore while converting the object into
		/// a QVariant.
		///
		/// These properties might be used by QML Views and be unserializable
		/// correctly by QJSON. They could cause problems just like what happened
		/// for the
		/// <a href="https://code.google.com/p/reyn-tweets/issues/detail?id=50#c8">
		/// reopening of issue 50</a>.
		QStringList transientProperties;

		/// @fn void recopie(const ReynTweetsMappable & mappable);
		/// @brief Core method for recopying a ReynTweetsMappable
		/// @param mappable ReynTweetsMappable to copy
		void recopie(const ReynTweetsMappable & mappable);

		/// @fn virtual void blacklistProperties(bool blacklistObjectName = true);
		/// @brief Building transientProperties
		/// @param blacklistObjectName Boolean indicating if the "objectName"
		/// property of QObject has to be included in transientProperties.
		virtual void blacklistProperties(bool blacklistObjectName);
};

#endif // REYNTWEETSMAPPABLE_HPP
