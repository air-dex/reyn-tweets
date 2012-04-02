/// @file TwoButtonsActionPane.qml
/// @brief Popup with 2 buttons for 2 different actions.
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

/// @class TwoButtonsActionPane
/// @brief Widget displayed to quit Reyn Tweets, after fatal issues for example.
Rectangle {
	/// @brief Text of the pane
	property string pane_text: "Yeah ! It's Reyn time !"

	/// @brief Text of the left button
	property string left_button_text: "Leave it to Reyn !"

	/// @brief Text of the right button
	property string right_button_text: "Here we go... LARIAT !"

	/// @brief Value for marges
	property int margin_value: 5

	/// @brief Space between the text and the button
	property int spacing: 6*margin_value

	/// @brief Radius of the corners of the component
	property int pane_radius: 10

	/// @brief Signal sent when the user click on the left button
	signal actLeft

	/// @brief Signal sent when the user click on the right button
	signal actRight

	Constants {	id:constant	}

	id: two_buttons_pane
	width: 360
	height: description_action.height + spacing + left_button.height
	color: "#a4a4a4"
	radius: pane_radius
	opacity: 0.800

	// Description
	Text {
		id: description_action
		text: two_buttons_pane.pane_text
		anchors.right: parent.right
		anchors.rightMargin: margin_value
		anchors.left: parent.left
		anchors.leftMargin: margin_value
		wrapMode: Text.WordWrap
		font.family: constant.font
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignLeft
		anchors.top: parent.top
		anchors.topMargin: margin_value
		font.pixelSize: constant.font_size
		elide: Text.ElideRight
	}

	// Left button
	RTButton {
		id: left_button
		button_text: two_buttons_pane.left_button_text
		anchors.right: right_button.left
		anchors.rightMargin: two_buttons_pane.margin_value
		anchors.bottom: two_buttons_pane.bottom
		anchors.bottomMargin: two_buttons_pane.margin_value
		onClick: actLeft();
	}

	// Right button
	RTButton {
		id: right_button
		button_text: two_buttons_pane.right_button_text
		anchors.right: two_buttons_pane.right
		anchors.rightMargin: two_buttons_pane.margin_value
		anchors.bottom: two_buttons_pane.bottom
		anchors.bottomMargin: two_buttons_pane.margin_value
		onClick: actRight();
	}
}
