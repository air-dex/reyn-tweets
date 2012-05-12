/// @file TransientPane.qml
/// @brief Pane that remains visible for a given duration (default : 5s)
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

Rectangle {
	id: transient_pane
	width: transient_message.width + 2* transient_pane.margin
	height: transient_message.height + 2* transient_pane.margin

	color: constant.black
	visible: false

	property int margin: 5

	// Text to show in the pane
	property alias message: transient_message.text

	// How many seconds does the pane remain visible ?
	property int secondsDisplayed: 5

	Constants { id:constant }

	Text {
		id: transient_message
		text: transient_pane.pane_text
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		font.family: constant.font
		font.pixelSize: constant.font_small_size
		color: constant.white
		visible: parent.visible
	}

	// Timer to show the pane for a given duration (5 seconds for the moment)
	Timer {
		id: show_timer
		interval: secondsDisplayed * 1000	// Five seconds
		repeat: false
		onTriggered: transient_pane.visible = false
	}

	states: [
		// Showing the pane
		State {
			name: "Showtime"
			when: transient_pane.visible

			StateChangeScript {
				name: show_warning_pane_script
				script: show_timer.restart()
			}
		}
	]
}
