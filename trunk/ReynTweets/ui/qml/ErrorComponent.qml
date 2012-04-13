/// @file ErrorComponent.qml
/// @brief Component with items for displaying errors
///
/// @author Romain Ducher
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

Rectangle {
	id: error_component

	// Margin
	property int margin: 5

	// Sent when the user allows the component which made the error to try again
	signal tryAgain

	//property Rectangle sender

	Constants { id: constant }

	// Popup to make the user quit the application
	QuitPane {
		id: abort_pane
		z: 3
		width: error_component.width - 2* error_component.margin
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: false
	}

	// Popup to try again
	TwoButtonsActionPane {
		id: try_again_pane
		z: 3
		width: error_component.width - 2* error_component.margin
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: false

		// Left button
		left_button_text: qsTr("Try again")
		onActLeft: {
			try_again_pane.visible = false;
			tryAgain();
		}

		// Right button
		right_button_text: qsTr("Quit")
		onActRight: Qt.quit();
	}

	// TODO : Popup to show a simple message

	function displayMessage(action, message) {
		var pane;

		switch (action) {
			case constant.quit_action:
				pane = abort_pane
				break;

			case constant.try_again_action:
				pane = try_again_pane
				break;

			case constant.info_msg_action:
				// TODO
				break;

			default:
				break;
		}

		if (pane == undefined) {
			return;
		}

		pane.pane_text = message
		pane.visible = true;
	}
}
