/// @file useraccount.hpp
/// @brief Header of UserAccount
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

#ifndef USERACCOUNT_HPP
#define USERACCOUNT_HPP

#include <QByteArray>
#include <QDataStream>
#include <QObject>
#include <QVariant>
#include "../reyntweetsserializable.hpp"

/// @class UserAccount
/// @brief User account.
class UserAccount : public ReynTweetsSerializable
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////


	public:
		/// @fn UserAccount();
		/// @brief Default constructor
		UserAccount();

		/// @fn virtual ~UserAccount();
		/// @brief Destructor
		virtual ~UserAccount();

		/// @fn UserAccount(const UserAccount & account);
		/// @brief Copy constructor
		/// @param account Account to copy
		UserAccount(const UserAccount & account);

		/// @fn const UserAccount & operator=(const UserAccount & account);
		/// @brief Affectation
		/// @param account Account to copy
		/// @return Copy of the original account
		const UserAccount & operator=(const UserAccount & account);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	private:
		/// @fn void recopie(const UserAccount & account);
		/// @brief Copy of a UserAccount
		/// @param account Account to copy
		void recopie(const UserAccount & account);

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const UserAccount & account);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param account Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const UserAccount & account);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										UserAccount & account);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param account Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										UserAccount & account);

	private:
		// Properties

		// Access Token
		Q_PROPERTY(QByteArray p_accessToken
				   READ getAccessToken
				   WRITE setAccessToken)

		/// @fn void updateAccessTokenProperty();
		/// @brief Updates the property p_accessToken
		void updateAccessTokenProperty();

		// Token Secret
		Q_PROPERTY(QByteArray p_tokenSecret
				   READ getTokenSecret
				   WRITE setTokenSecret)

		/// @fn void updateTokenSecretProperty();
		/// @brief Updates the property p_tokenScret
		void updateTokenSecretProperty();

		//User
		Q_PROPERTY(QString p_user
				   READ getUser
				   WRITE setUser)

		/// @fn void updateUserProperty();
		/// @brief Updates the property p_user
		void updateUserProperty();


	//////////////////////////////
	// Configuration management //
	//////////////////////////////

	public:
		/// @fn QByteArray getAccessToken();
		/// @brief Getter on the access token
		/// @return The access token
		QByteArray getAccessToken();

		/// @fn void setAccessToken(QByteArray token);
		/// @brief Setter on the Access Token
		/// @param token The new Access Token
		void setAccessToken(QByteArray token);

		/// @fn QByteArray getTokenSecret();
		/// @brief Getter on the secret token
		/// @return The secret token
		QByteArray getTokenSecret();

		/// @fn void setTokenSecret(QByteArray secret);
		/// @brief Setter on the secret token
		/// @param secret The new token secret
		void setTokenSecret(QByteArray secret);

		/// @fn QString getUser();
		/// @brief Getter on the user
		/// @return The user
		QString getUser();

		/// @fn void setUser(QString u);
		/// @brief Setter on the user
		/// @param u The new user
		void setUser(QString u);

	protected:
		/// @brief Access token
		QByteArray accessToken;

		/// @brief Token Secret
		QByteArray tokenSecret;

		/// @brief Twitter User
		QString user;
};

// Serialization of UserAccount
Q_DECLARE_METATYPE(UserAccount)

/// @fn QDataStream & operator<<(QDataStream & out,
///								 const UserAccount & account);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param account Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out,
						 const UserAccount & account);

/// @fn QDataStream & operator>>(QDataStream & in,
///								 UserAccount & account);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param account Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in,
						 UserAccount & account);


#endif // USERACCOUNT_HPP
