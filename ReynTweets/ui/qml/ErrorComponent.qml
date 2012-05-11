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

	property alias info_pane: error_component.warning_pane

	//property Rectangle sender

	Constants { id: constant }

	// Popup to make the user quit the application
	QuitPane {
		id: abort_pane
		z: error_component.z + 1
		width: error_component.width - 2* error_component.margin
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: false
	}

	// Popup to try again
	TwoButtonsActionPane {
		id: try_again_pane
		z: error_component.z + 1
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

	// Popup to show a simple problem message. This is not fatal.
	Rectangle {
		id: warning_pane
		z: error_component.z + 1
		width: error_component.width - 2* error_component.margin
		color: constant.grey
		anchors.top: parent.top
		anchors.verticalCenter: parent.verticalCenter
		visible: false

		Text {
			id: warning_message
			text: "<strong>" + qsTr("A problem occured :") + "</strong><br/>"
				  + warning_pane.pane_text
			wrapMode: Text.WrapAtWordBoundaryOrAnywhere
			anchors.fill: parent
			anchors.margins: error_component.margin
			font.family: constant.font
			font.pixelSize: constant.font_size
			visible: parent.visible
		}

		// Timer to show the pane for a given duration (5 seconds for the moment)
		Timer {
			id: show_timer
			interval: 5000	// Five seconds
			repeat: false
			onTriggered: warning_pane.visible = false
		}

		states: [
			State {
				name: "Showtime"
				when: warning_pane.visible

				StateChangeScript {
					name: show_warning_pane_script
					script: show_timer.start()
				}
			}
		]

		// Text to show in the pane
		property string pane_text
	}

	// Displaying a message
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
				pane = warning_pane
				break;

			default:
				break;
		}

		if (pane === undefined) {
			return;
		}

		pane.pane_text = message
		pane.visible = true;
	}
}
