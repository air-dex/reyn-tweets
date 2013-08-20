/// @file AccountPane.qml
/// @brief Pane dealing with accounts
///
/// It were in the /trunk/ReynTweets/ui/qml folder until r491
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

import QtQuick 2.0
import ReynTweetsComponents 0.2
import "../base_components"

ActionElement {
	id: account_pane

	// Access to the settings
	SettingsControl { id: settings }

	// Sent to show a profile
	signal showProfile

	image_source: settings.configuration.user_account.current_user.profile_image_url
	legend: '<strong style="color: '
		.concat(settings.configuration.user_account.current_user.profile_link_color)
		.concat('">@')
		.concat(settings.configuration.user_account.current_user.screen_name)
		.concat("</strong>")
	onAct: showProfile()
}
