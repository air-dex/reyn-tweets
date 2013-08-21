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

import QtQuick 2.0

/// @class Constants
/// @brief QML constants of Reyn Tweets.
QtObject {
	/////////////
	// Version //
	/////////////

	// Major version
	property int major_version: 0

	// Minor version
	property int minor_version: 3

	// Number of bugfixes
	property int bugfix_version: 0

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
	readonly property int reyn_tweets_width: 360

	// Height
	readonly property int reyn_tweets_height: 640

	// Margin
	readonly property int margin: 5


	////////////
	// Colors //
	////////////

	// Orange Reyn Tweets
	readonly property string orange: "#eb8801"

	// Grey
	readonly property string grey: "#c4c4c4"

	// Light grey
	readonly property string very_light_grey: "#fafafa"

	// White
	readonly property string white: "#ffffff"

	// Black
	readonly property string black: "#000000"

	// Red
	readonly property string red: "#ff0000"

	// Green for mentions (separator_color)
	readonly property string green_mention: "#b8fe86"

	// Green for mentions (middle_color)
	readonly property string light_green_mention: "#d3ffb4"

	// Blue for Direct messages (separator_color)
	readonly property string blue_dm: "#90c0fd"

	// Blue for Direct messages (middle_color)
	readonly property string light_blue_dm: "#b3d3fd"

	// Orange for own tweets (separator_color)
	readonly property string orange_author: "#ffd35e"

	// Orange for own tweets (middle_color)
	readonly property string light_orange_author: "#ffe08d"


	//////////
	// Font //
	//////////

	// Font used for Reyn Tweets
	readonly property string font: {
		switch (Qt.platform.os) {
			case "windows":
				return "Calibri"

			case "linux":
				return "Ubuntu"

			case "osx":
			case "ios":
				return "Comic Sans MS"

			default:
				return "Arial"
		}
	}

	// Font size XXL for big titles
	readonly property real font_size_xxl: {
		switch (Qt.platform.os) {
			case "windows":
				return 37.0

			case "linux":
				return 36.0

			default:
				return 36.0
		}
	}

	// Font size XL
	readonly property real font_size_xl: {
		switch (Qt.platform.os) {
			case "windows":
				return 26.0

			case "linux":
				return 24.75

			default:
				return 24.75
		}
	}

	// Font size Large
	readonly property real font_size_l: {
		switch (Qt.platform.os) {
			case "windows":
				return 15.0

			case "linux":
				return 15.0

			default:
				return 15.0
		}
	}

	// Font size Medium
	readonly property real font_size: {
		switch (Qt.platform.os) {
			case "windows":
				return 12.0

			case "linux":
				return 11.0

			case "ubuntu":
				return 10.5

			default:
				return 11.0
		}
	}

	// Font size (small - S)
	readonly property real font_size_s: {
		switch (Qt.platform.os) {
			case "windows":
				return 10.0

			case "linux":
				return 9.0

			default:
				return 9.0
		}
	}

	// Font size (very small - XS)
	readonly property real font_size_xs: {
		switch (Qt.platform.os) {
			case "windows":
				return 8.5

			case "linux":
				return 7.5

			default:
				return 7.5
		}
	}

	// Font size (very small - XXS)
	readonly property real font_size_xxs: {
		switch (Qt.platform.os) {
			case "windows":
				return 7.0

			case "linux":
				return 6.0

			default:
				return 6.0
		}
	}


	//////////////////
	// Miscanellous //
	//////////////////

	// Folder storing the icons
	readonly property string icon_folder: "/resources/icons"
}
