/// @file RTButton.qml
/// @brief Custom button
///
/// The file was known as "Button.qml" until r203.
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

/// @class RTButton
/// @brief Custom button
Rectangle {
	/// @brief Distance between the text and the border
	property int margin_value: constant.margin

	/// @brief Default text for the button
	property alias button_text: action_text.text

	/// @brief ID of the button
	id: button

	// Dimnsions
	width: action_text.width + 2*margin_value
	height: action_text.height + 2*margin_value

	/// @brief Reyn Tweets constants
	Constants {	id:constant	}

	/// @brief Signal sent while clicking on the button
	signal click

	// Button design
	// Border colors and interior
	radius: constant.margin

	/// @brief Proportion for the gradient
	property real bordeur: 0.25

	/// @brief Proportion for the gradient
	property string border_color: constant.grey

	gradient: Gradient {
		GradientStop {
			position: 0
			color: border_color
		}

		GradientStop {
			position: bordeur
			color: constant.orange
		}

		GradientStop {
			position: 1-bordeur
			color: constant.orange
		}

		GradientStop {
			position: 1
			color: border_color
		}
	}
	//border.color: "#000000"

	// Anchors
	anchors.right: parent.right
	anchors.rightMargin: margin_value
	anchors.bottom: parent.bottom
	anchors.bottomMargin: margin_value

	// Text written in the button
	Text {
		id: action_text
		text: "OK"
		horizontalAlignment: Text.AlignHCenter
		verticalAlignment: Text.AlignVCenter
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		font.family: constant.font
		font.pixelSize: constant.font_size
	}

	// Clickable area of the component
	MouseArea {
		id: click_area
		x: 0
		y: 0
		width: parent.width
		height: parent.height
		anchors.fill: parent
		onClicked: button.click()
	}
}
