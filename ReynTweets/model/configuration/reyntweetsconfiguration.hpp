/// @file reyntweetsconfiguration.hpp
/// @brief Header of ReynTweetsConfiguration
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

#ifndef REYNTWEETSCONFIGURATION_HPP
#define REYNTWEETSCONFIGURATION_HPP

#include <QByteArray>
#include <QDataStream>
#include <QList>
#include <QObject>
#include <QVariant>
#include "../reyntweetsserializable.hpp"
#include "useraccount.hpp"

/// @class ReynTweetsConfiguration
/// @brief Configuration of Reyn Tweets
class ReynTweetsConfiguration : public QObject, virtual public ReynTweetsSerializable
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn ReynTweetsConfiguration();
		/// @brief Default constructor
		ReynTweetsConfiguration();

		/// @fn virtual ~ReynTweetsConfiguration();
		/// @brief Destructor
		virtual ~ReynTweetsConfiguration();

		/// @fn ReynTweetsConfiguration(const ReynTweetsConfiguration & configuration);
		/// @brief Copy constructor
		/// @param configuration Configuration to copy
		ReynTweetsConfiguration(const ReynTweetsConfiguration & configuration);

		/// @fn const ReynTweetsConfiguration & operator=(const ReynTweetsConfiguration & configuration);
		/// @brief Affectation
		/// @param configuration Configuration to copy
		/// @return Copy of the original configuration
		const ReynTweetsConfiguration & operator=(const ReynTweetsConfiguration & configuration);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	private:
		/// @fn void recopie(const ReynTweetsConfiguration & configuration);
		/// @brief Copy of a ReynTweetsConfiguration
		/// @param configuration Configuration to copy
		void recopie(const ReynTweetsConfiguration & configuration);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const ReynTweetsConfiguration & configuration);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param configuration Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const ReynTweetsConfiguration & configuration);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										ReynTweetsConfiguration & configuration);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param configuration Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										ReynTweetsConfiguration & configuration);

	private:
		// Properties
		/// @fn void fillWithPropertiesMaps();
		/// @brief Filling serializable fields with thecorresponding  property maps
		void fillWithPropertiesMaps();

		// User account
		Q_PROPERTY(QVariantMap p_userAccount
				   READ getUserAccountProperty
				   WRITE setUserAccountProperty)

		/// @brief Representation of the property p_userAccount
		QVariantMap userAccountProperty;

		/// @fn QVariantMap getUserAccountProperty();
		/// @brief Reading the property p_userAccount
		/// @return The user account
		QVariantMap getUserAccountProperty();

		/// @fn void setUserAccountProperty(QVariantMap account);
		/// @brief Writing the property p_userAccount
		/// @param account New value for the account
		void setUserAccountProperty(QVariantMap accountMap);

		/// @fn void updateUserAccountProperty();
		/// @brief Updating the property p_userAccount
		void updateUserAccountProperty();


	//////////////////////////////
	// Configuration management //
	//////////////////////////////

	public:
		/// @fn UserAccount getUserAccount();
		/// @brief Getter on the user account
		/// @return The user account
		UserAccount getUserAccount();

		/// @fn void setUserAccount(UserAccount account);
		/// @brief Setter on the user account
		/// @param account New value for the account
		void setUserAccount(UserAccount account);

	protected:
		/// @brief Consumer Key
		static QByteArray REYN_TWEETS_CONSUMER_KEY;

		/// @brief Consumer Secret
		static QByteArray REYN_TWEETS_CONSUMER_SECRET;

		/// @brief Twitter Account
		UserAccount userAccount;
};

// Serialization of ReynTweetsConfiguration
Q_DECLARE_METATYPE(ReynTweetsConfiguration)

/// @fn friend QDataStream & operator<<(QDataStream & out,
///										const ReynTweetsConfiguration & configuration);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param configuration Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out,
						 const ReynTweetsConfiguration & configuration);

/// @fn friend QDataStream & operator>>(QDataStream & in,
///										ReynTweetsConfiguration & configuration);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param configuration Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in,
						 ReynTweetsConfiguration & configuration);

#endif // REYNTWEETSCONFIGURATION_HPP
