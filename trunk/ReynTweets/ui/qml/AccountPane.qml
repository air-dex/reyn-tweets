/// @file AccountPane.qml
/// @brief Pane dealing with accounts
/// @author Romain DUCHER
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

import QtQuick 1.1
import ReynTweetsControls 0.1
import ReynTweetsEntities 0.1

Item {
	id: account_pane
	width: profile_action.width
	height: profile_action.height

	// Access to the settings
	SettingsControl { id: settings_control }

	// User of the account
	property UserInfos twitto: settings_control.configuration.current_account.current_user

	ActionElement {
		id: profile_action
		//image_source: settings_control.configuration.current_account.current_user.profile_image_url
		legend: '<strong style="color: '.concat(settings_control.configuration.current_account.current_user.profile_link_color)
			.concat('">@')
			.concat(settings_control.configuration.current_account.current_user.screen_name)
			.concat("</strong>")
		onAct: {
			settings_control.dummyDebug();
			showProfile()
		}
	}

	signal showProfile
}
