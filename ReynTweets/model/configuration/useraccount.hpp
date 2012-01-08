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

/// @class UserAccount
/// @brief User account.
class UserAccount : public QObject
{
	Q_OBJECT

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

	protected:
		/// @brief Access token
		QByteArray accessToken;

		/// @brief Token Secret
		QByteArray tokenSecret;

		/// @brief Twitter User
		QString user;

	private:
		/// @fn void recopie(const UserAccount & account);
		/// @brief Copy of a UserAccount
		/// @param account Account to copy
		void recopie(const UserAccount & account);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		// Friends function
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
