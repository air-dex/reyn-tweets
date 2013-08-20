/// @file RTDesktopMenu.qml
/// @brief Menu of Reyn Tweets
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
import "../base_components"

Rectangle {
	id: desktop_menu

	// Folder where the icons are stored
	property string icons_folder: "../../..".concat(constant.icon_folder)

	// Reyn Tweets constants
	Constants { id: constant }

	property int margin: constant.margin

	// Dimensions
	width: actions.implicitWidth + 2*margin
	height: actions.implicitHeight + 2*margin
	radius: margin

	// Border properties
	border.color: constant.light_orange_author
	border.width: 1

	// Background Gradation
	gradient: Gradient {
		GradientStop {
			position: 0
			color: constant.light_orange_author
		}

		GradientStop {
			position: 0.5
			color: constant.white
		}

		GradientStop {
			position: 1
			color: constant.light_orange_author
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
			id: hello_action
			legend: qsTr("Say hello")
			onAct: sayHello()
		}

		// Settings of the application
		ActionElement {
			id: settings_action
			legend: qsTr("Settings")
			onAct: setReyn()
		}

		// About Reyn Tweets
		ActionElement {
			id: about_action
			legend: qsTr("About Reyn Tweets")
			onAct: aboutReyn()
		}

		// About Reyn Tweets
		ActionElement {
			id: about_qt
			legend: qsTr("About Qt")
			onAct: aboutQt()
		}

		// Show help
		ActionElement {
			id: help_action
			image_source: desktop_menu.icons_folder.concat("/help.png")
			legend: qsTr("Help")
			onAct: helpReyn()
		}

		// Quit the application
		ActionElement {
			id: quit_action
			image_source: desktop_menu.icons_folder.concat("/close_cross.png")
			legend: qsTr("Quit")
			onAct: quit()
		}
	}

	/////////////
	// Signals //
	/////////////

	// In the same order of the actions
	signal sayHello
	signal setReyn
	signal aboutReyn
	signal aboutQt
	signal helpReyn
	signal quit
}


