/// @file mappable.hpp
/// @brief Header of Mappable
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

#ifndef MAPPABLE_HPP
#define MAPPABLE_HPP

#include <QObject>
#include <QStringList>
#include <QVariant>
#include "variantable.hpp"

/// @class Mappable
/// @brief Serializable objects that needed to be converted into a QVariantMap.
///
/// In practice, some network replies can be parsed in QVariantMaps whose keys
/// are the name of the different fields of the replies. The values corresponding
/// to the fields are stocked in QVariant objects. Complex field values are
/// stored in QVariantLists or QVariantMaps too.
///
/// But ReynTweets do not manipulate QVariantMaps with fields but complex model
/// objects with values which get a meaning, just like a tweet with a text
/// (string), an ID (number), an author. Not a QVariantMap with fields named
/// "text", "id" or "user". Informations needed by these objects are stored
/// in QVariantMaps. As a consequence, the QVariantMaps replies have to
/// be converted in these model objects.<br/>
/// Moreover, the complex model objects might need to be converted into
/// QVariant objects. It is the case when they are manipulated by QML. For this,
/// Mappables ar first converted into QVariantMaps which are then put in a
/// QVariant object.
///
/// In the complex objects, the fields of QVariantMaps are stocked in QObject
/// properties which are represented by class members. Types of the class
/// members are the type of the QVariant value of the field.
///
/// However, some properties are complex objects (ex. author of a tweet) too
/// and they are not easily handled by Qt. These fields get an equivalent
/// member (often a ReynTweetsSerializable - the class was made for them) that
/// corresponds to a QVariantList or a QVariantMap property.
class Mappable : public QObject, public Variantable<QVariantMap>
{
	Q_OBJECT

	public:
		/// @fn explicit Mappable(bool blacklistObjectName = true);
		/// @brief Constructor
		/// @param blacklistObjectName Boolean indicating if the "objectName"
		/// property of QObject has to be included in transientProperties.
		explicit Mappable(bool blacklistObjectName = true);

		/// @fn virtual ~Mappable();
		/// @brief Destructor
		virtual ~Mappable();

		/// @fn Mappable(const Mappable & mappable);
		/// @brief Copy constructor
		/// @param mappable Mappable to copy
		Mappable(const Mappable & mappable);

		/// @fn const Mappable & operator=(const Mappable & mappable);
		/// @brief Affecting a Mappable
		/// @param mappable Mappable to copy
		const Mappable & operator=(const Mappable & mappable);

		/// @fn virtual QVariantMap toVariant() const;
		/// @brief Converting the object into a QVariantMap
		/// @return A QVariantMap containing all the informations.
		virtual QVariantMap toVariant() const = 0;

		/// @fn virtual void fillWithVariant(QVariantMap map);
		/// @brief Filling a serializable object with the informations
		/// contained in a map.
		/// @param map The map
		virtual void fillWithVariant(QVariantMap map) = 0;

		/// @fn QStringList & getTransientProperties();
		/// @brief Getter on transientProperties.
		///
		/// Used by the specialization of writing in streams for Mappables.
		/// @return A reference on transientProperties
		QStringList & getTransientProperties();

		/// @fn virtual void reset() = 0;
		/// @brief Resets the mappable to a default value
		virtual void reset() = 0;

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

		/// @fn void recopie(const Mappable & mappable);
		/// @brief Core method for recopying a Mappable
		/// @param mappable Mappable to copy
		void recopie(const Mappable & mappable);

		/// @fn virtual void blacklistProperties(bool blacklistObjectName = true);
		/// @brief Building transientProperties
		/// @param blacklistObjectName Boolean indicating if the "objectName"
		/// property of QObject has to be included in transientProperties.
		virtual void blacklistProperties(bool blacklistObjectName);
};

#endif // MAPPABLE_HPP
