/// @file userconfiguration.hpp
/// @brief Header of UserConfiguration
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012, 2013 Romain Ducher
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

#ifndef USERCONFIGURATION_HPP
#define USERCONFIGURATION_HPP

#include <QByteArray>
#include <QDataStream>
#include <QFile>
#include <QList>
#include <QObject>
#include <QVariant>
#include "../coreresult.hpp"
#include "../json/jsonobject.hpp"
#include "useraccount.hpp"

/// @class ReynTweetsUserConfiguration
/// @brief User configuration of Reyn Tweets
class UserConfiguration : public JsonObject
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn UserConfiguration();
		/// @brief Default constructor
		UserConfiguration();

		/// @fn virtual ~UserConfiguration();
		/// @brief Destructor
		virtual ~UserConfiguration();

		/// @fn UserConfiguration(const UserConfiguration & configuration);
		/// @brief Copy constructor
		/// @param configuration Configuration to copy
		UserConfiguration(const UserConfiguration & configuration);

		/// @fn const UserConfiguration & operator=(const UserConfiguration & configuration);
		/// @brief Affectation
		/// @param configuration Configuration to copy
		/// @return Copy of the original configuration
		const UserConfiguration & operator=(const UserConfiguration & configuration);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring ReynTweetsConfiguration to the QML system
		static void declareQML();

		/// @fn void reset();
		/// @brief Resets the mappable to a default value
		void reset();

		/////////////////////
		// JSON conversion //
		/////////////////////

		/// @fn virtual void fillWithVariant(QJsonObject json);
		/// @brief Filling the object with a QJsonObject.
		///
		/// The method is virtual because its implementation depends on the
		/// object type.
		/// @param json The QJsonObject used to fill the JsonObject
		virtual void fillWithVariant(QJsonObject json);

		/// @fn virtual QJsonObject toVariant() const;
		/// @brief Getting a QJsonObject representation of the object
		/// @return The QJsonObject representation
		virtual QJsonObject toVariant() const;

		//////////////////////////////
		// Configuration management //
		//////////////////////////////

		/// @fn ReynTweets::CoreResult load(QString &errorMsg);
		/// @brief Loading the configuration from its file
		/// @param errorMsg Error message
		/// @return A value depending on what happened
		ReynTweets::CoreResult load(QString &errorMsg);

		/// @fn ReynTweets::CoreResult save(QString &errorMsg);
		/// @brief Writing the configuration in its file
		/// @param errorMsg Error message
		/// @return A value depending on what happened
		ReynTweets::CoreResult save(QString &errorMsg);

		/// @fn ReynTweets::CoreResult reinit(QString &errorMsg);
		/// @brief Reinits the configuration file
		/// @param errorMsg Error message
		/// @return true
		ReynTweets::CoreResult reinit(QString &errorMsg);

	protected:
		/// @fn void recopie(const UserConfiguration & configuration);
		/// @brief Copy of a ReynTweetsConfiguration
		/// @param configuration Configuration to copy
		void recopie(const UserConfiguration & configuration);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const UserConfiguration & configuration);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param configuration Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const UserConfiguration & configuration);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										UserConfiguration & configuration);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param configuration Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										UserConfiguration & configuration);

		////////////////
		// Properties //
		////////////////

		// user_account
		/// @property user_account
		/// @brief QML property to access to the user account.
		///
		/// userAccount is the property beneath this property.
		Q_PROPERTY(UserAccount * user_account
				   READ getUserAccountPtr
				   WRITE setUserAccount
				   NOTIFY currentAccountChanged)

		/// @brief Name of the property user_account.
		static QString USER_ACCOUNT_PN;

		/// @brief Twitter Account
		UserAccount userAccount;

		/// @fn UserAccount * getUserAccountPtr();
		/// @brief Reading the property user_account
		/// @return The user account
		UserAccount * getUserAccountPtr();

		/// @fn void setUserAccount(UserAccount * account);
		/// @brief Writing the property user_account
		/// @param account New value for the account
		void setUserAccount(UserAccount * account);


	signals:
		/// @fn void currentAccountChanged();
		/// @brief Signal notifying about changes dealing with user_account
		void currentAccountChanged();


	protected:
		////////////////////////////////////////
		// User configuration file management //
		////////////////////////////////////////

		/// @fn bool checkConfigurationFile();
		/// @brief Checks if the user configuration file exists and is writable.
		/// @return true if the user configuration file is OK, false otherwise.
		bool checkConfigurationFile();

		/// @fn QString getConfigurationFilePath();
		/// @brief Getting the name of the user configuration file with
		/// its absolute path.
		/// @return The name of the user configuration file with
		/// its absolute path.
		QString getConfigurationFilePath();

		/// @fn ReynTweets::CoreResult writeConfigurationInFile(QString &errorMsg,
		///														QIODevice::OpenMode openMode = QIODevice::WriteOnly);
		/// @brief Writing the configuration.
		/// @param errorMsg Error message
		/// @param openMode How to open the file to write it.
		/// @return ReynTweets::CONFIGURATION_FILE_UNKNOWN if the configuration
		/// file do not exist, ReynTweets::CONFIGURATION_FILE_NOT_OPEN if it
		/// cannot be opened and ReynTweets::WRITE_SUCCESSFUL if the
		/// configuration was written successfully.
		ReynTweets::CoreResult writeConfigurationInFile(QString &errorMsg,
														QIODevice::OpenMode openMode = QIODevice::WriteOnly);

		/// @brief Configuration file name
		static QString CONFIGURATION_NAMEFILE;

	public:
		/////////////////////////
		// Getters and setters //
		/////////////////////////

		// user_account
		/// @fn UserAccount getUserAccount();
		/// @brief Getter on the user account
		/// @return The user account
		UserAccount getUserAccount();

		/// @fn UserAccount & getUserAccountRef();
		/// @brief Getting a reference on the user account
		/// @return The user account
		UserAccount & getUserAccountRef();

		/// @fn void setUserAccount(UserAccount account);
		/// @brief Setter on the user account
		/// @param account New value for the account
		void setUserAccount(UserAccount account);
};

// Serialization of ReynTweetsUserConfiguration
Q_DECLARE_METATYPE(UserConfiguration)

/// @fn friend QDataStream & operator<<(QDataStream & out,
///										const UserConfiguration & configuration);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param configuration Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out,
						 const UserConfiguration & configuration);

/// @fn friend QDataStream & operator>>(QDataStream & in,
///										UserConfiguration & configuration);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param configuration Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in,
						 UserConfiguration & configuration);

#endif // USERCONFIGURATION_HPP
