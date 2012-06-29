/// @file settingscontrol.hpp
/// @brief Header of SettingsControl
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

#ifndef SETTINGSCONTROL_HPP
#define SETTINGSCONTROL_HPP

#include "genericcontrol.hpp"
#include "../reyncore.hpp"
#include "../../model/configuration/reyntweetsuserconfiguration.hpp"

/// @class SettingsControl
/// @brief Control for managing the configuration
class SettingsControl : public GenericControl
{
	Q_OBJECT

	public:
		/// @fn SettingsControl();
		/// @brief Constructor
		SettingsControl();

		/// @fn static void declareQML();
		/// @brief Declaring SettingsControl to the QML system
		static void declareQML();

		/// @fn Q_INVOKABLE void saveChanges();
		/// @brief Saving changes in the configuration
		Q_INVOKABLE void saveChanges();

	signals:
		/// @fn void configurationChanged();
		/// @brief Emitted to notify changes about the configuration property
		void configurationChanged();

		/// @fn void currentAccountChanged();
		/// @brief Emitted to notify changes about the current_account property
		void currentAccountChanged();

	protected:
		/// @brief Reference on the configuration of Reyn Tweets
		ReynTweetsUserConfiguration & conf;

		/// @property configuration
		/// @brief Read only property to access to the configuration for QML.
		Q_PROPERTY(ReynTweetsUserConfiguration * configuration
				   READ getConfiguration
				   WRITE setConfiguration
				   NOTIFY configurationChanged)

		/// @fn ReynTweetsConfiguration * getConfiguration();
		/// @brief Reading the configuration property
		/// @return Pointer on conf.
		ReynTweetsUserConfiguration * getConfiguration();

		/// @fn void setConfiguration(ReynTweetsUserConfiguration * config);
		/// @brief Writing the configuration property
		/// @param config New value for the configuration
		void setConfiguration(ReynTweetsUserConfiguration * config);

		/// @property current_account
		/// @brief Shortcut for configuration.current_account
		Q_PROPERTY(UserAccount * current_account
				   READ getCurrentAccount
				   WRITE setCurrentAccount
				   NOTIFY currentAccountChanged)

		/// @fn UserAccount * getCurrentAccount();
		/// @brief Reading the current_account property
		/// @return Pointer on conf.current_account
		UserAccount * getCurrentAccount();

		/// @fn void setCurrentAccount(UserAccount * account);
		/// @brief Writing the current_account property
		/// @param account New value for the account
		void setCurrentAccount(UserAccount *account);
};

#endif // SETTINGSCONTROL_HPP
