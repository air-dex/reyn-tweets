/// @file user.hpp
/// @brief Header of User
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

#ifndef USER2_HPP
#define USER2_HPP

#include "../json/jsonarray.hpp"
#include "../tweets/tweet.hpp"

/// @class User
/// @brief Person who uses Twitter
class User2 : public UserInfos2
{
	Q_OBJECT


	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn User();
		/// @brief Default constructor
		User2();

		/// @fn virtual ~User();
		/// @brief Destructor
		virtual ~User2();

		/// @fn User(const User & user);
		/// @brief Copy constructor
		/// @param user User to copy
		User2(const User2 & user);

		/// @fn const User & operator=(const User & user);
		/// @brief Affectation
		/// @param user User to copy
		/// @return Copy of the original user
		const User2 & operator=(const User2 & user);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

		/// @fn void reset();
		/// @brief Resets the mappable to a default value
		void reset();

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

	private:
		/// @fn void recopie(const User & user);
		/// @brief Copy of a User
		/// @param user User to copy
		void recopie(const User2 & user);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const User & user);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param user Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const User2 & user);

		/// @fn friend QDataStream & operator>>(QDataStream & in, User & user);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param user Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, User2 & user);


	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		// status
		/// @property status
		/// @brief Serializable form of lastTweet
		///
		/// lastTweet is the attribute beneath this property.
		Q_PROPERTY(QVariantMap status
				   READ getStatusProperty
				   WRITE setStatus
				   NOTIFY statusChanged)

		/// @brief Name of the property status
		static QString STATUS_PN;

		/// @fn QVariantMap getStatusProperty();
		/// @brief Reading the "status" property
		/// @return lastTweetMap
		QVariantMap getStatusProperty();

		/// @fn void setStatus(QVariantMap statusMap);
		/// @brief Writing the status property
		/// @param statusMap The new value of the property
		void setStatus(QVariantMap statusMap);

		/// @property last_status
		/// @brief Serializable form of lastTweet
		///
		/// lastTweet is the attribute beneath this property.
		Q_PROPERTY(Tweet2 * last_status
				   READ getStatusPtr
				   WRITE setStatus
				   NOTIFY statusChanged)

		/// @brief Name of the property last_status
		static QString LAST_STATUS_PN;

		/// @fn Tweet2 * getStatusProperty();
		/// @brief Reading the "status" property
		/// @return lastTweetMap
		Tweet2 * getStatusPtr();

		/// @fn void setStatus(Tweet2 * statusMap);
		/// @brief Writing the status property
		/// @param statusMap The new value of the property
		void setStatus(Tweet2 * statusMap);

	signals:
		/// @fn void statusChanged();
		/// @brief Signal emitted when the property status changes.
		void statusChanged();


	/////////////////////
	// User management //
	/////////////////////

	protected:
		/// @brief Last tweet posted by the user
		Tweet2 lastTweet;


	////////////////////////
	// Getter and setters //
	////////////////////////

	public:
		// status
		/// @fn Tweet getStatus();
		/// @brief Getter on the last tweet written by the user
		/// @return The value of the last tweet written by the user
		Tweet2 getStatus();

		/// @fn void setStatus(Tweet newLastTweet);
		/// @brief Setter on the last tweet written by the user
		/// @param newLastTweet The new value of the last tweet written by the user
		void setStatus(Tweet2 newLastTweet);
};

// Serialization of User
Q_DECLARE_METATYPE(User2)

/// @fn QDataStream & operator<<(QDataStream & out, const User & user);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param user Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const User2 & user);

/// @fn QDataStream & operator>>(QDataStream & in, User & user);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param user Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, User2 & user);


/// @typedef JsonArray<User> UserList;
/// @brief Shortcut for lists of users
typedef JsonArray<User2> UserList;

#endif // USER_HPP