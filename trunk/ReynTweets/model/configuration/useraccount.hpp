/// @file useraccount.hpp
/// @brief Header of UserAccount
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

#ifndef USERACCOUNT_HPP
#define USERACCOUNT_HPP

#include <QByteArray>
#include <QDataStream>
#include <QObject>
#include <QVariant>
#include "../reyntweetsmappable.hpp"
#include "../users/user.hpp"

/// @class UserAccount
/// @brief User account.
class UserAccount : public ReynTweetsMappable
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

		/// @fn static void declareQML();
		/// @brief Declaring ReynTweetsConfiguration to the QML system
		static void declareQML();

		/// @fn void reset();
		/// @brief Resets the mappable to a default value
		void reset();


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
		/// @fn void blacklistProperties();
		/// @brief Blacklisting properties used only for and by QML views.
		///
		/// The following properties are blacklisted in this class : <ul>
		/// <li>current_user</li>
		/// </ul>
		void blacklistProperties();

		//////////////
		// Settings //
		//////////////

		// Access Token
		/// @property access_token
		/// @brief Access token
		Q_PROPERTY(QByteArray access_token
				   READ getAccessToken
				   WRITE setAccessToken)

		// Token Secret
		/// @property token_secret
		/// @brief Token secret
		Q_PROPERTY(QByteArray token_secret
				   READ getTokenSecret
				   WRITE setTokenSecret)

		// User
		/// @property twitter_user
		/// @brief Twitter user
		Q_PROPERTY(QVariantMap twitter_user
				   READ getUserProperty
				   WRITE setUser
				   NOTIFY currentUserChanged)

		/// @fn QVariantMap getUserProperty();
		/// @brief Reading the property twitter_user
		/// @return userMap
		QVariantMap getUserProperty();

		/// @fn void setUser(QVariantMap newUserMap);
		/// @brief Writing the property twitter_user
		/// @param newUserMap New value for twitter_user
		void setUser(QVariantMap newUserMap);

		/// @property current_user
		/// @brief Twitter user
		Q_PROPERTY(UserInfos * current_user
				   READ getCurrentUser
				   NOTIFY currentUserChanged)

		/// @fn User * getCurrentUser();
		/// @brief Reading the property current_user
		/// @return A pointer on user
		UserInfos * getCurrentUser();


		// Hello message
		/// @property hello_message
		/// @brief Message to say hello.
		///
		/// The helloMessage attribute is behind this property.
		Q_PROPERTY(QString hello_message
				   READ getHelloMessage
				   WRITE setHelloMessage
				   NOTIFY helloMessageChanged)


	signals:
		/// @fn void currentUserChanged();
		/// @brief Notifying changes about current_user
		void currentUserChanged();

		/// @fn void helloMessageChanged();
		/// @brief Notifying changes about hello_message
		void helloMessageChanged();


	//////////////////////////////
	// Configuration management //
	//////////////////////////////

	protected:
		/// @brief Access token
		QByteArray accessToken;

		/// @brief Token Secret
		QByteArray tokenSecret;

		/// @brief User of the account
		UserInfos user;

		/// @brief Message to say hello
		QString helloMessage;

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

		/// @fn UserInfos getUser();
		/// @brief Getter on the user
		/// @return The user
		UserInfos getUser();

		/// @fn UserInfos & getUserRef();
		/// @brief Getting a reference on the user
		/// @return The user
		UserInfos & getUserRef();

		/// @fn void setUser(UserInfos u);
		/// @brief Setter on the user
		/// @param u The new user
		void setUser(UserInfos u);

		/// @fn QString getHelloMessage();
		/// @brief Reading the property hello_message
		/// @return helloMessage
		QString getHelloMessage();

		/// @fn void setHelloMessage(QString newMsg);
		/// @brief Writing the property hello_message
		/// @param newMsg New value for helloMessage
		void setHelloMessage(QString newMsg);
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
