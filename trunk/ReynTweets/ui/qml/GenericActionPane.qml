/// @file GenericActionPane.qml
/// @brief Pane with one button
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

/// @class GenericActionPane
/// @brief Pane with one button
Rectangle {
	/// @brief Text of the pane
	property string pane_text: "Yeah ! It's Reyn time !"

	/// @brief Text in the button
	property string button_text: "Leave it to Reyn !"

	/// @brief Value for marges
	property int margin_value: 5

	/// @brief Space between the text and the button
	property int spacing: 6*margin_value

	/// @brief Radius of the corners of the component
	property int pane_radius: 10

	/// @brief Signal sent whene th user click on the button
	signal act

	id: generic_action_pane
	width: 360
	height: description_action.height + spacing + action_button.height
	color: "#a4a4a4"
	radius: pane_radius

	// Text to display.
	Text {
		id: description_action
		width: generic_action_pane.width - 2* generic_action_pane.margin_value
		text: generic_action_pane.pane_text
		font.family: "Ubuntu"
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignLeft
		anchors.right: parent.right
		anchors.rightMargin: margin_value
		anchors.left: parent.left
		anchors.leftMargin: margin_value
		anchors.top: parent.top
		anchors.topMargin: margin_value
		font.pixelSize: 14
		elide: Text.ElideRight
	}

	// Button to act
	RTButton {
		id: action_button
		button_text: generic_action_pane.button_text
		anchors.right: parent.right
		anchors.rightMargin: margin_value
		anchors.bottom: parent.bottom
		anchors.bottomMargin: margin_value
		onClick: act();
	}
}