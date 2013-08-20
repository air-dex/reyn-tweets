/// @file jsonobject.hpp
/// @brief Header of JsonObject
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

#ifndef JSONOBJECT_HPP
#define JSONOBJECT_HPP

#include <QJsonObject>
#include "../mappable.hpp"
#include "jsonable.hpp"

/// @class JsonObject
/// @brief Base class for all objects which can be represented by a JSON object.
class JsonObject : public Mappable, public Jsonable<QJsonObject>
{
	Q_OBJECT

	public:
		// Coplien

		/// @fn JsonObject();
		/// @brief Constructor
		/// @param blacklistObjectName Boolean indicating if the "objectName"
		/// property of QObject has to be included in transientProperties.
		JsonObject(bool blacklistObjectName = true);

		/// @fn virtual ~JsonObject();
		/// @brief Destructor
		virtual ~JsonObject();

		/// @fn JsonObject(const JsonObject & jsonobj);
		/// @brief Copy constructor
		/// @param jsonobj The JsonObject to copy
		JsonObject(const JsonObject & jsonobj);

		/// @fn const JsonObject & operator=(const JsonObject & jsonobj);
		/// @brief Affectation of a JsonObject
		/// @param jsonobj The JsonObject to copy
		const JsonObject & operator=(const JsonObject & jsonobj);

		// Implementation of abstract methods

		/// @fn virtual void fillWithVariant(QVariantMap map);
		/// @brief Filling the object with a QVariantMap.
		/// @param map The QVariantMap used to fill the JsonObject
		virtual void fillWithVariant(QVariantMap map);

		/// @fn virtual QVariantMap toVariant();
		/// @brief Getting a QVariantMap representation of the JsonObject
		/// @return QVariantMap representation
		virtual QVariantMap toVariant() const;

		/// @fn virtual void fillWithJSON(QJsonObject json);
		/// @brief Filling the object with a QJsonObject.
		///
		/// The method is virtual because its implementation depends on the
		/// object type.
		/// @param json The QJsonObject used to fill the JsonObject
		virtual void fillWithJSON(QJsonObject json) = 0;

		/// @fn virtual QJsonObject toJSON();
		/// @brief Getting a QJsonObject representation of the JsonObject
		/// @return QJsonObject representation, i.e. <code>this</code>
		virtual QJsonObject toJSON() const = 0;

	protected:
		/// @fn void recopie(const JsonObject & jsonobj);
		/// @brief Core method to copy a JsonObject
		/// @param jsonobj The JsonObject to copy
		virtual void recopie(const JsonObject & jsonobj);
};


/////////////////////
// Stream handling //
/////////////////////

/// @fn QDataStream & jsonObjectStreamingOut(QDataStream & out,
///											 const JsonObject & jsonobj);
/// @brief Output stream operator for serialization.
///
/// This method is a specialization for JsonObjects because they have
/// got properties to ignore. These properties are blacklisted in
/// the Mappable::transientProperties attribute.
/// @param out The output stream
/// @param jsonobj JsonObject to put in the stream
/// @return The stream with the object
QDataStream & jsonObjectStreamingOut(QDataStream & out,
									 const JsonObject & jsonobj);

/// @fn QDataStream & jsonObjectStreamingIn(QDataStream & in,
///											JsonObject & jsonobj);
/// @brief Input stream operator for serialization.
///
/// This method is a specialization for JsonObjects because they have
/// got properties to ignore. These properties are blacklisted in
/// the Mappable::transientProperties attribute.
/// @param in The input stream
/// @param jsonobj JsonObject to put in the stream
/// @return The stream with the object
QDataStream & jsonObjectStreamingIn(QDataStream & in,
									JsonObject &jsonobj);

#endif // JSONOBJECT_HPP
