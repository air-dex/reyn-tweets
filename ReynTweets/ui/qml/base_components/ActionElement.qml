/// @file ActionElement.qml
/// @brief QML Component with an icon and a description that can be clicked
/// to do something
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
import "../js/jstools.js" as Tools

// QML Component with an icon and a description that can be clicked to do sthg
Item {
	id: action_element
	width: act_icon.width + action_row.spacing + act_legend.width
	height: Tools.max(freeSizeMode ? act_icon.height : givenSize,
					  act_legend.height)

	// Source of the image in the icon
	property string image_source

	// Description of the action to realize
	property string legend

	// Source of the image in the icon
	property bool freeSizeMode: true

	// Source of the image in the icon
	property int givenSize: act_legend.height

	// That will be done while clicking
	signal act

	Constants { id: constants }

	Row {
		id: action_row
		anchors.fill: parent
		spacing: 5

		Image {
			id: act_icon
			anchors.verticalCenter: action_row.verticalCenter
			source: action_element.image_source
		}

		Text {
			id: act_legend
			text: action_element.legend
			verticalAlignment: Text.AlignVCenter
			anchors.verticalCenter: action_row.verticalCenter
			font.family: constants.font
			font.pointSize: constants.font_size
		}
	}

	MouseArea {
		id: act_zone
		anchors.fill: parent
		onClicked: action_element.act();
	}

	states: [
		State {
			name: "free_size"
			when: freeSizeMode
			PropertyChanges {
				target: action_element
				height: Tools.max(act_icon.height, act_legend.height)
			}
		},
		State {
			name: "limit_size"
			when: !freeSizeMode
			PropertyChanges {
				target: action_element
				height: Tools.max(givenSize, act_legend.height)
			}

			PropertyChanges {
				target: act_icon
				height: givenSize
				sourceSize.height: givenSize
				fillMode: Image.PreserveAspectFit
			}
		}
	]
}
