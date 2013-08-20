/// @file userentities.hpp
/// @brief Header of UserEntities
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

#ifndef USERENTITIES_HPP
#define USERENTITIES_HPP

#include "../json/jsonobject.hpp"
#include "../tweets/tweetentities.hpp"

/// @class UserEntities
/// @brief User Entities
/// @see https://dev.twitter.com/docs/platform-objects/entities#user_entities
class UserEntities : public JsonObject
{
		Q_OBJECT
	public:
		/// @fn UserEntities();
		/// @brief Default constructor
		UserEntities();

		/// @fn virtual ~UserEntities();
		/// @brief Destructor
		virtual ~UserEntities();

		/// @fn UserEntities(const UserEntities & entities);
		/// @brief Copy constructor
		/// @param entities UserEntities to copy
		UserEntities(const UserEntities & entities);

		/// @fn const UserEntities & operator=(const UserEntities & entities);
		/// @brief Affectation
		/// @param entities UserEntities to copy
		/// @return Copy of the original UserEntities
		const UserEntities & operator=(const UserEntities & entities);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

		/// @fn virtual void reset();
		/// @brief Resets the mappable to a default value
		virtual void reset();

		/////////////////////
		// JSON conversion //
		/////////////////////

		/// @fn virtual void fillWithJSON(QJsonObject json);
		/// @brief Filling the object with a QJsonObject.
		///
		/// The method is virtual because its implementation depends on the
		/// object type.
		/// @param json The QJsonObject used to fill the JsonObject
		virtual void fillWithJSON(QJsonObject json);

		/// @fn virtual QJsonObject toJSON() const;
		/// @brief Getting a QJsonObject representation of the object
		/// @return The QJsonObject representation
		virtual QJsonObject toJSON() const;

	protected:
		/// @fn void recopie(const UserEntities & entities);
		/// @brief Copy of a UserEntities
		/// @param entities UserEntities to copy
		void recopie(const UserEntities & entities);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const UserEntities & entities);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param entities Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const UserEntities & entities);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										UserEntities & entities);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param entities Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										UserEntities & entities);


	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		// url
		/// @property url
		/// @brief URL entities (QVariant form)
		///
		/// userURL is the attribute beneath the property.
		Q_PROPERTY(QVariantMap url
				   READ getURLProperty
				   WRITE setURL
				   NOTIFY urlChanged)

		/// @brief Name of the property url.
		static QString URL_PN;

		/// @fn QVariantMap getURLProperty();
		/// @brief Reading url.
		/// @return userURL.toVariant();
		QVariantMap getURLProperty();

		/// @fn void setURL(QVariantMap newValue);
		/// @brief Writing url.
		/// @param newValue Variant list containing new values for userURL
		void setURL(QVariantMap newValue);

		/// @property url_ent
		/// @brief URL entities
		///
		/// userURL is the attribute beneath the property.
		Q_PROPERTY(TweetEntities * url_ent
				   READ getURLptr
				   WRITE setURL
				   NOTIFY urlChanged)

		/// @brief Name of the property url_ent.
		static QString URL_ENT_PN;

		/// @fn TweetEntities * getURLptr();
		/// @brief Reading url.
		/// @return &userURL
		TweetEntities * getURLptr();

		/// @fn void setURL(TweetEntities * newValue);
		/// @brief Writing url.
		/// @param newValue New value for userURL
		void setURL(TweetEntities * newValue);

		/// @brief URL entities
		TweetEntities userURL;

		// description
		/// @property description
		/// @brief URL entities in the description (QVariant form)
		///
		/// userDescription is the attribute beneath the property.
		Q_PROPERTY(QVariantMap description
				   READ getDescriptionProperty
				   WRITE setDescription
				   NOTIFY descriptionChanged)

		/// @brief Name of the property description.
		static QString DESCRIPTION_PN;

		/// @fn QVariantMap getDescriptionProperty();
		/// @brief Reading description.
		/// @return userDescription.toVariant();
		QVariantMap getDescriptionProperty();

		/// @fn void setDescription(QVariantMap newValue);
		/// @brief Writing description.
		/// @param newValue Variant list containing new values for userDescription.
		void setDescription(QVariantMap newValue);

		/// @property description_ent
		/// @brief URL entities in the description.
		///
		/// userDescription is the attribute beneath the property.
		Q_PROPERTY(TweetEntities * description_ent
				   READ getDescriptionptr
				   WRITE setDescription
				   NOTIFY descriptionChanged)

		/// @brief Name of the property description_ent.
		static QString DESCRIPTION_ENT_PN;

		/// @fn TweetEntities * getDescriptionptr();
		/// @brief Reading description.
		/// @return &userDescription
		TweetEntities * getDescriptionptr();

		/// @fn void setDescription(TweetEntities * newValue);
		/// @brief Writing description.
		/// @param newValue New value for userDescription
		void setDescription(TweetEntities * newValue);

		/// @brief URL entities in description
		TweetEntities userDescription;

	signals:
		/// @fn void urlChanged();
		/// @brief Signal emitted when the property "url" gets a new value.
		void urlChanged();

		/// @fn void descriptionChanged();
		/// @brief Signal emitted when the property "description"
		/// gets a new value.
		void descriptionChanged();

	public:
		// url
		/// @fn TweetEntities getURL();
		/// @brief Reading url.
		/// @return userURL
		TweetEntities getURL();

		/// @fn void setURL(TweetEntities newValue);
		/// @brief Writing url.
		/// @param newValue New value for
		void setURL(TweetEntities newValue);

		// description
		/// @fn TweetEntities getDescription();
		/// @brief Reading description.
		/// @return userDescription
		TweetEntities getDescription();

		/// @fn void setDescription(TweetEntities newValue);
		/// @brief Writing description.
		/// @param newValue New value for userDescription
		void setDescription(TweetEntities newValue);

};

// Serialization of UserEntities
Q_DECLARE_METATYPE(UserEntities)

/// @fn QDataStream & operator<<(QDataStream & out, const UserEntities & entities);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param entities Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const UserEntities & entities);

/// @fn QDataStream & operator>>(QDataStream & in, UserEntities & entities);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param entities Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, UserEntities & entities);

#endif // USERENTITIES_HPP
