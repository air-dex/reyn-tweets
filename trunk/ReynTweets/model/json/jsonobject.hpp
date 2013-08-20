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
#include <QDataStream>
#include "../variantable.hpp"

/// @class JsonObject
/// @brief Base class for all objects which can be represented by a JSON object.
class JsonObject : public QObject, public Variantable<QJsonObject>
{
	Q_OBJECT

	public:
		// Coplien

		/// @fn JsonObject();
		/// @brief Constructor
		JsonObject();

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

		/// @fn virtual void reset() = 0;
		/// @brief Resets the object to a default value
		virtual void reset() = 0;

		// Implementation of abstract methods

		/// @fn virtual void fillWithVariant(QJsonObject json) = 0;
		/// @brief Filling the object with a QJsonObject.
		///
		/// The method is virtual because its implementation depends on the
		/// object type.
		/// @param json The QJsonObject used to fill the JsonObject
		virtual void fillWithVariant(QJsonObject json) = 0;

		/// @fn virtual QJsonObject toVariant() = 0;
		/// @brief Getting a QJsonObject representation of the JsonObject
		/// @return QJsonObject representation, i.e. <code>this</code>
		virtual QJsonObject toVariant() const = 0;

		/////////////////////
		// Stream handling //
		/////////////////////

		/// @fn virtual QDataStream & fillWithStream(QDataStream & in);
		/// @brief Filling the JsonObject with the content of a QDataStream
		/// @param in The stream
		/// @return The stream after being read.
		virtual QDataStream & fillWithStream(QDataStream & in);

		/// @fn virtual QDataStream & writeInStream(QDataStream & out) const;
		/// @brief Writing a QDataStream with the content of the JsonObject
		/// @param out The stream
		/// @return The stream after being written.
		virtual QDataStream & writeInStream(QDataStream & out) const;

	protected:
		/// @fn void recopie(const JsonObject & );
		/// @brief Core method to copy a JsonObject
		/// @param jsonobj The JsonObject to copy
		virtual void recopie(const JsonObject &);
};

#endif // JSONOBJECT_HPP
