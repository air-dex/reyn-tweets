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
#include "../core/reyncore.hpp"
#include "../core/configuration/userconfiguration.hpp"
#include "../core/configuration/appconfiguration.hpp"

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

		/// @fn Q_INVOKABLE QString getCallbackURL();
		/// @brief Gets the callback URL.
		///
		/// Needed for Twitter OAuth authentication.
		/// @return The Twitter callback URL.
		Q_INVOKABLE QString getCallbackURL();

	signals:
		/// @fn void configurationChanged();
		/// @brief Emitted to notify changes about the configuration property
		void configurationChanged();

	protected:
		/// @brief Reyn Tweets' general settings
		AppConfiguration & reynTweetsConf;

		/// @brief Reference on the configuration of Reyn Tweets
		UserConfiguration & conf;

		// configuration
		/// @property configuration
		/// @brief Read only property to access to the configuration for QML.
		///
		/// conf is the attribute beneath this property.
		Q_PROPERTY(UserConfiguration * configuration
				   READ getConfiguration
				   WRITE setConfiguration
				   NOTIFY configurationChanged)

		/// @fn ReynTweetsConfiguration * getConfiguration();
		/// @brief Reading the configuration property
		/// @return Pointer on conf.
		UserConfiguration * getConfiguration();

		/// @fn void setConfiguration(ReynTweetsUserConfiguration * config);
		/// @brief Writing the configuration property
		/// @param config New value for the configuration
		void setConfiguration(UserConfiguration * config);
};

#endif // SETTINGSCONTROL_HPP
