/// @file RTDesktopMenu.qml
/// @brief Menu of Reyn Tweets
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
	id: desktop_menu

	// Reyn Tweets constants
	Constants { id: constant }

	property int margin: 5

	// Dimensions
	width: actions.implicitWidth + 2*margin
	height: actions.implicitHeight + 2*margin
	radius: margin

	// Border properties
	border.color: constant.grey
	border.width: 1

	// Background Gradation
	gradient: Gradient {
		GradientStop {
			position: 0
			color: constant.grey
		}

		GradientStop {
			position: 0.5
			color: constant.white
		}

		GradientStop {
			position: 1
			color: constant.grey
		}
	}


	/////////////////////////
	// Actions in the menu //
	/////////////////////////

	Column {
		id: actions
		anchors.fill: parent
		anchors.margins: margin
		spacing: 2*margin

		// Settings of the application
		ActionElement {
			id: settings_action
			legend: qsTr("Settings")
			onAct: console.log("Reyn Tweets settings")
		}

		// About Reyn Tweets
		ActionElement {
			id: about_action
			legend: qsTr("About Reyn Tweets")
			onAct: console.log("Reyn Tweets is an awesome Twitter client.")
		}

		// Show help
		ActionElement {
			id: help_action
			legend: qsTr("Help")
			onAct: console.log("The Beatles rules !")
		}

		// Quit the application
		ActionElement {
			id: quit_action
			image_source: "../../resources/icons/close_cross.png"
			legend: qsTr("Quit")
			onAct: Qt.quit()
		}
	}
}


