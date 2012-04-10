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

#include <QObject>
#include "../reyncore.hpp"
#include "../../model/configuration/reyntweetsconfiguration.hpp"

/// @class SettingsControl
/// @brief Control for managing the configuration
class SettingsControl : public QObject
{
	Q_OBJECT

	public:
		/// @fn SettingsControl();
		/// @brief Constructor
		SettingsControl();

		/// @fn static void declareQML();
		/// @brief Declaring SettingsControl to the QML system
		static void declareQML();

	signals:
		/// @fn void configurationChanged();
		/// @brief Emitted to notify changes about the configuration property
		void configurationChanged();

	protected:
		/// @brief Heart of Reyn Tweets. Unused for the moment
		ReynCore reyn;

		/// @brief Reference on the configuration of Reyn Tweets
		ReynTweetsConfiguration & conf;

		/// @property configuration
		/// @brief Read only property to access to the configuration for QML.
		Q_PROPERTY(ReynTweetsConfiguration * configuration
				   READ getConfiguration
				   NOTIFY configurationChanged)

		/// @fn ReynTweetsConfiguration * getConfiguration();
		/// @brief Reading the configuration property
		ReynTweetsConfiguration * getConfiguration();
};

#endif // SETTINGSCONTROL_HPP
