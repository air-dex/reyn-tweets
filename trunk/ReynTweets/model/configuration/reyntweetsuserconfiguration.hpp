/// @file reyntweetsuserconfiguration.hpp
/// @brief Header of ReynTweetsUserConfiguration
///
/// Revisions older than r242 were in /trunk/ReynTweets/connection
/// Revisions until r431 were known as ReynTweetsConfiguration
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

#ifndef REYNTWEETSUSERCONFIGURATION_HPP
#define REYNTWEETSUSERCONFIGURATION_HPP

#include <QByteArray>
#include <QDataStream>
#include <QList>
#include <QObject>
#include <QVariant>
#include "../../logic/coreresult.hpp"
#include "../reyntweetsmappable.hpp"
#include "useraccount.hpp"

/// @class ReynTweetsUserConfiguration
/// @brief User configuration of Reyn Tweets
class ReynTweetsUserConfiguration : public ReynTweetsMappable
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn ReynTweetsUserConfiguration();
		/// @brief Default constructor
		ReynTweetsUserConfiguration();

		/// @fn virtual ~ReynTweetsUserConfiguration();
		/// @brief Destructor
		virtual ~ReynTweetsUserConfiguration();

		/// @fn ReynTweetsUserConfiguration(const ReynTweetsUserConfiguration & configuration);
		/// @brief Copy constructor
		/// @param configuration Configuration to copy
		ReynTweetsUserConfiguration(const ReynTweetsUserConfiguration & configuration);

		/// @fn const ReynTweetsUserConfiguration & operator=(const ReynTweetsUserConfiguration & configuration);
		/// @brief Affectation
		/// @param configuration Configuration to copy
		/// @return Copy of the original configuration
		const ReynTweetsUserConfiguration & operator=(const ReynTweetsUserConfiguration & configuration);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring ReynTweetsConfiguration to the QML system
		static void declareQML();

	private:
		/// @fn void recopie(const ReynTweetsUserConfiguration & configuration);
		/// @brief Copy of a ReynTweetsConfiguration
		/// @param configuration Configuration to copy
		void recopie(const ReynTweetsUserConfiguration & configuration);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const ReynTweetsUserConfiguration & configuration);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param configuration Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const ReynTweetsUserConfiguration & configuration);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										ReynTweetsUserConfiguration & configuration);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param configuration Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										ReynTweetsUserConfiguration & configuration);

	////////////////
	// Properties //
	////////////////

	protected:
		/// @fn void blacklistProperties();
		/// @brief Blacklisting properties used only for and by QML views.
		///
		/// The following properties are blacklisted in this class : <ul>
		/// <li>current_account</li>
		/// </ul>
		void blacklistProperties();

		// User account
		/// @property user_account
		/// @brief Serializable form of the account
		Q_PROPERTY(QVariantMap user_account
				   READ getUserAccountProperty
				   WRITE setUserAccount)

		/// @fn QVariantMap getUserAccountProperty();
		/// @brief Reading the property user_account
		/// @return The user account
		QVariantMap getUserAccountProperty();

		/// @fn void setUserAccount(QVariantMap account);
		/// @brief Writing the property user_account
		/// @param account New value for the account
		void setUserAccount(QVariantMap accountMap);

		/// @property user_account
		/// @brief QML read only property to access to the user account.
		Q_PROPERTY(UserAccount * current_account
				   READ getCurrentAccount
				   NOTIFY currentAccountChanged)

		/// @fn UserAccount * getCurrentAccount();
		/// @brief Reading the property current_account
		/// @return The user account
		UserAccount * getCurrentAccount();


	signals:
		/// @fn void currentAccountChanged();
		/// @brief Signal notifying about changes dealing with current_account
		void currentAccountChanged();


	//////////////////////////////
	// Configuration management //
	//////////////////////////////

	public:
		/// @fn CoreResult load();
		/// @brief Loading the configuration from its file
		/// @return A value depending on what happened
		CoreResult load();

		/// @fn CoreResult save();
		/// @brief Writing the configuration in its file
		/// @return A value depending on what happened
		CoreResult save();

	protected:
		/// @brief Twitter Account
		UserAccount userAccount;

		/// @brief Configuration file name
		static QString CONFIGURATION_NAMEFILE;


	/////////////////////////
	// Getters and setters //
	/////////////////////////

	public:
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

		/// @fn void reset();
		/// @brief Resets the mappable to a default value
		void reset();
};

// Serialization of ReynTweetsUserConfiguration
Q_DECLARE_METATYPE(ReynTweetsUserConfiguration)

/// @fn friend QDataStream & operator<<(QDataStream & out,
///										const ReynTweetsUserConfiguration & configuration);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param configuration Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out,
						 const ReynTweetsUserConfiguration & configuration);

/// @fn friend QDataStream & operator>>(QDataStream & in,
///										ReynTweetsUserConfiguration & configuration);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param configuration Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in,
						 ReynTweetsUserConfiguration & configuration);

#endif // REYNTWEETSCONFIGURATION_HPP