/// @file Constants.qml
/// @brief QML constants of Reyn Tweets.
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

/// @class Constants
/// @brief QML constants of Reyn Tweets.
QtObject {
	////////////
	// Colors //
	////////////

	// Orange Reyn Tweets
	property string orange: "#eb8801"

	// Grey
	property string grey: "#c4c4c4"

	// Light grey
	property string very_light_grey: "#fafafa"

	// White
	property string white: "#ffffff"

	// Black
	property string black: "#000000"

	// Red
	property string red: "#ff0000"

	// Green for mentions (separator_color)
	property string green_mention: "#b8fe86"

	// Green for mentions (middle_color)
	property string light_green_mention: "#d3ffb4"

	// Blue for Direct messages (separator_color)
	property string blue_dm: "#90c0fd"

	// Blue for Direct messages (middle_color)
	property string light_blue_dm: "#b3d3fd"


	//////////
	// Font //
	//////////

	// Font used for Reyn Tweets
	property string font: "Ubuntu"

	// Font size
	property int font_size: 14

	// Font size
	property int font_small_size: 12


	//////////////////////////
	// Actions after errors //
	//////////////////////////

	// Showing temporary message
	property string info_msg_action: "Info message"

	// Font size
	property string try_again_action: "Try again"

	// Font size
	property string quit_action: "Quit"
}
