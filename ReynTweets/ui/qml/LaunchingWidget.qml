/// @file launchingWidget.qml
/// @brief Widget displayed at the beginning of the program
/// @author Romain DUCHER

/*
Copyright 2012 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

import QtQuick 1.1
import ReynTweetsControls 0.1

/// @class LaunchingWidget
/// @brief Component used to launch the app
Rectangle {
	id: main_screen
	width: 360
	height: 640

	//////////////////////////
	// Design of the Widget //
	//////////////////////////

	// Logo with the name and the icon
	Column {
		id: program_logo
		width: main_screen.width/3
		//height: reyn_tweets_icon.height + program_name_label.height
		spacing: (reyn_tweets_icon.height + program_name_label.height)/6
		anchors.verticalCenterOffset: -bottom.height
		anchors.verticalCenter: parent.verticalCenter
		anchors.horizontalCenter: parent.horizontalCenter

		Image {
			id: reyn_tweets_icon
			width: 5 * main_screen.width /8
			fillMode: Image.PreserveAspectFit
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.top: parent.top
			anchors.topMargin: 0
			source: "../../resources/Logo Reyn Tweets PNG.png"
		}

		Text {
			id: program_name_label
			text: "Reyn Tweets"
			font.bold: true
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.bottom: parent.bottom
			font.family: "Ubuntu"
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignHCenter
			font.pixelSize: 36
		}
	}

	// Copyright and website of the application
	Column {
		id: bottom
		width: main_screen.width
		spacing: (copyright.height + website.height) / 4

		anchors.horizontalCenter: parent.horizontalCenter
		anchors.bottom: parent.bottom
		anchors.bottomMargin: height/2

		Text {
			id: copyright
			text: "(C) 2012 Romain DUCHER (@air_dex)"
			font.family: "Ubuntu"
			font.bold: false
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.top: parent.top
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignHCenter
			font.pixelSize: 14
		}

		Text {
			id: website
			text: qsTr("Website : http://code.google.com/p/reyn-tweeets")
			font.family: "Ubuntu"
			font.bold: false
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.bottom: parent.bottom
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			font.pixelSize: 14
		}
	}

	// Popup displayed if the user has to enter its credentials
	LoginComponent {
		id: login_popup
		anchors.left: parent.left
		anchors.leftMargin: main_screen.margin
		anchors.right: parent.right
		anchors.rightMargin: main_screen.margin
		z: 2
		anchors.verticalCenter: parent.verticalCenter
	}

	// Popup to make the user quit the application
	QuitPane {
		id: abort_pane
		z: 3
		width: main_screen.width - 2* main_screen.margin
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: false
	}

	// Popup to try again
	TwoButtonsActionPane {
		id: try_again_pane
		z: 3
		width: main_screen.width - 2* main_screen.margin
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: false

		// Left button
		left_button_text: qsTr("Try again")
		onActLeft: {
			main_screen.state = "TryAgainPopupInvisible";
			control.launchReynTweets();
		}

		// Right button
		right_button_text: qsTr("Quit")
		onActRight: Qt.quit();
	}

	////////////////////////////
	// Back office management //
	////////////////////////////

	states: [
		State {
			name: "LoginPopupVisible"

			PropertyChanges {
				target: login_popup
				visible: true
			}
		},
		State {
			name: "LoginPopupInvisible"

			PropertyChanges {
				target: login_popup
				visible: false
			}
		},
		State {
			name: "AbortPopupVisible"

			PropertyChanges {
				target: abort_pane
				visible: true
			}
		},
		State {
			name: "TryAgainPopupVisible"

			PropertyChanges {
				target: try_again_pane
				visible: true
			}
		},
		State {
			name: "TryAgainPopupInvisible"

			PropertyChanges {
				target: try_again_pane
				visible: false
			}
		}
	]

	/// @brief Signal sent after launching the application
	signal endLaunch(bool launchOK, string errMsg, bool fatal)

	/// @brief Control behind the component
	LaunchingControl {
		id: control
		loginControl: login_popup.getControl();
	}

	Component.onCompleted: {
		// Wiring

		// Displaying login_popup or not
		control.showLoginPopup.connect(setLoginPopupVisible)

		//End of the launching process
		control.launchEnded.connect(afterLaunching)
	}

	// Launching the application
	function launchReynTweets() {
		control.launchReynTweets()
	}

	function setLoginPopupVisible(visible) {
		var newState = visible ? "LoginPopupVisible" : "LoginPopupInvisible";
		main_screen.state = newState;
	}

	// What happened after the launching processus
	function afterLaunching(endOK, errMsg, fatal) {
		var messageDisplayed = "";

		if (endOK) {	// Successful end
			// Go to the next step
		} else if (fatal) {		// Bad and fatal error. Show the quit pane.
			// Show the quit pane.
			messageDisplayed = qsTr("A fatal error occured while launching Reyn Tweets:\n\n")
					+ errMsg
					+ qsTr("\n\nThe application will quit.");
			abort_pane.pane_text = messageDisplayed;
			main_screen.state = "AbortPopupVisible";
		} else {	// Bad end but not fatal.
			// Display warning popup to ask the user to try again or to quit.
			messageDisplayed = qsTr("An hitch occured while launching Reyn Tweets:\n\n")
					+ errMsg
					+ qsTr("\n\nDo you want to try to launch Reyn Tweets again or to quit ?");
			try_again_pane.pane_text = messageDisplayed;
			main_screen.state = "TryAgainPopupVisible";
		}
	}
}
