/// @file Constants.qml
/// @brief QML constants of Reyn Tweets.
///
/// It were in the /trunk/ReynTweets/ui/qml folder until r491.
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
	/////////////
	// Version //
	/////////////

	// Major version
	property int major_version: 0

	// Minor version
	property int minor_version: 2

	// Number of bugfixes
	property int bugfix_version: 1

	function getVersion() {
		var versionString = "".concat(major_version).concat('.').concat(minor_version)

		if (bugfix_version > 0) {
			versionString = versionString.concat('.').concat(bugfix_version)
		}

		return versionString
	}


	//////////////////////
	// Application size //
	//////////////////////

	// Width
	property int reyn_tweets_width: 360

	// Height
	property int reyn_tweets_height: 640

	// Margin
	property int margin: 5


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

	// Orange for own tweets (separator_color)
	property string orange_author: "#ffd35e"

	// Orange for own tweets (middle_color)
	property string light_orange_author: "#ffe08d"


	//////////
	// Font //
	//////////

	// Font used for Reyn Tweets
	property string font: "Ubuntu"

	// Font size for big titles
	property int font_size_title: 36

	// Font size
	property int font_size: 14

	// Font size (small - S)
	property int font_size_s: 12

	// Font size (very small - XS)
	property int font_size_xs: 11


	//////////////////
	// Miscanellous //
	//////////////////

	// Folder storing the icons
	property string icon_folder: "/resources/icons"
}
