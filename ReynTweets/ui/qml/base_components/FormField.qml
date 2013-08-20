/// @file FormField.qml
/// @brief Text Input with a description.
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

/// @class FormField
/// @brief Text Input with a description.
Rectangle {
	/// @brief Property to determine the width of the input
	property int field_left_margin: text.width

	/// @brief Boolean indicating if the input text has to be hidden
	property bool clear_field: true

	/// @brief Boolean indicating if the cursor of the input text has to be hidden
	property bool cursor_visible: false

	/// @brief Legend of the field
	property string legend: "Description:"

	/// @brief Default text in the input
	property alias field_text: field.text

	id: form_field
	property int spacing: 10
	width: 360
	height: field_background.height + 2*radius
	radius: 5

	Constants { id:constant }

	// Legend
	Text {
		id: text
		text: legend
		anchors.left: parent.left
		anchors.leftMargin: radius
		anchors.verticalCenter: parent.verticalCenter
		verticalAlignment: Text.AlignVCenter
		font.family: constant.font
		font.pointSize: constant.font_size
	}

	// Rectangle behind field for design concerns.
	Rectangle {
		id: field_background
		height: text.height + 2*radius
		radius: 4
		anchors.verticalCenter: parent.verticalCenter
		anchors.leftMargin: field_left_margin + spacing + radius
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.rightMargin: radius
		border.color: "#000000"
		color: "#ffffff"

		// Input
		TextInput {
			id: field
			text: ""
			anchors.leftMargin: parent.radius
			anchors.rightMargin: parent.radius
			anchors.bottomMargin: parent.radius
			anchors.topMargin: parent.radius
			anchors.fill: parent
			echoMode: clear_field ? TextInput.Normal : TextInput.Password
			font.family: constant.font
			horizontalAlignment: TextEdit.AlignLeft
			font.pointSize: constant.font_size
		}
	}

	/// @fn function getLegendWidth();
	/// @brief Getting the width of the text
	///
	/// It is used to align field_background borders
	/// @return text.width
	function getLegendWidth() { return text.width;}
}
