/// @file LaunchingPane.qml
/// @brief Widget displayed at the beginning of the program
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
import ReynTweetsControls 0.1

/// @class LaunchingPane
/// @brief Component used to launch the app
Rectangle {
	id: launching_pane
	width: 360
	height: 640

	Constants {	id:constant	}

	//////////////////////////
	// Design of the Widget //
	//////////////////////////

	property int margin: 5

	// Logo with the name and the icon
	Column {
		id: program_logo
		width: launching_pane.width/3
		spacing: (reyn_tweets_icon.height + program_name_label.height)/6
		anchors.verticalCenterOffset: -footer.height
		anchors.verticalCenter: parent.verticalCenter
		anchors.horizontalCenter: parent.horizontalCenter

		// Icon
		Image {
			id: reyn_tweets_icon
			width: 5 * launching_pane.width /8
			fillMode: Image.PreserveAspectFit
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.top: parent.top
			anchors.topMargin: 0
			source: "../../resources/Logo Reyn Tweets PNG.png"
		}

		// Name of the program
		Text {
			id: program_name_label
			text: "Reyn Tweets"
			font.bold: true
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.bottom: parent.bottom
			font.family: constant.font
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignHCenter
			font.pixelSize: 36
		}
	}

	// Copyright and website of the application
	Column {
		id: footer
		width: launching_pane.width
		spacing: (copyright.height + website.height) / 4

		anchors.horizontalCenter: parent.horizontalCenter
		anchors.bottom: parent.bottom
		anchors.bottomMargin: height/2

		Text {
			id: copyright
			text: '(C) 2012 Romain DUCHER (<a href="https://twitter.com/#!/air_dex"'
				  + ' style="text-decoration: none; color: '+ constant.orange
				  + '">@air_dex</a>)'
			font.family: constant.font
			font.bold: false
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.top: parent.top
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignHCenter
			font.pixelSize: constant.font_size
			onLinkActivated: Qt.openUrlExternally(link)
		}

		Text {
			id: website
			text: qsTr("Website : ") +  '<a href="http://code.google.com/p/reyn-tweets/"'
				  + 'style="text-decoration:none; color: ' + constant.orange
				  + '">http://code.google.com/p/reyn-tweeets/</a>'
			font.family: constant.font
			font.bold: false
			anchors.horizontalCenter: parent.horizontalCenter
			anchors.bottom: parent.bottom
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			font.pixelSize: constant.font_size
			onLinkActivated: Qt.openUrlExternally(link)
		}
	}

	// Popup displayed if the user has to enter its credentials
	LoginPane {
		id: login_popup
		z: 2
		anchors.left: parent.left
		anchors.leftMargin: launching_pane.margin
		anchors.right: parent.right
		anchors.rightMargin: launching_pane.margin
		anchors.verticalCenter: parent.verticalCenter
		visible: false
	}

	// Popup to make the user quit the application
	QuitPane {
		id: abort_pane
		z: 3
		width: launching_pane.width - 2* launching_pane.margin
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: false
	}

	// Popup to try again
	TwoButtonsActionPane {
		id: try_again_pane
		z: 3
		width: launching_pane.width - 2* launching_pane.margin
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: false

		// Left button
		left_button_text: qsTr("Try again")
		onActLeft: {
			try_again_pane.visible = false;
			launching_pane.launchReynTweets();
		}

		// Right button
		right_button_text: qsTr("Quit")
		onActRight: Qt.quit();
	}

	// Popup after denying ReynTweets
	TwoButtonsActionPane {
		id: deny_pane
		z: 3
		width: launching_pane.width - 2* launching_pane.margin
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: false

		// Left button
		left_button_text: qsTr("Yes")
		onActLeft: {
			deny_pane.visible = false;
			abort_pane.pane_text = qsTr("Reyn Tweets will quit. Bye bye !");
			abort_pane.visible = true;
		}

		// Right button
		right_button_text: qsTr("No")
		onActRight: {
			deny_pane.visible = false;
			launching_pane.launchReynTweets();
		}
	}

	////////////////////////////
	// Back office management //
	////////////////////////////

	/// @brief Signal sent after launching the application
	signal endLaunch

	/// @brief Control behind the component
	LaunchingControl {
		id: control
		loginControl: login_popup.ctrl
	}

	Component.onCompleted: {
		// Wiring

		// Displaying login_popup or not
		control.showLoginPopup.connect(setLoginPopupVisible)

		//End of the launching process
		control.launchEnded.connect(afterLaunching)
	}

	/// @fn function launchReynTweets();
	/// @brief Launching the application
	function launchReynTweets() {
		login_popup.state = "UnknownValidity"
		control.launchReynTweets()
	}

	/// @fn function setLoginPopupVisible(visible);
	/// @brief Showing / hiding the login popup
	/// @param visible Boolean indicating if login_popup has to be shown or hidden.
	function setLoginPopupVisible(visible) {
		login_popup.visible = visible;
	}

	/// @fn function afterLaunching(endOK, errMsg, fatal);
	/// @brief What happened after the launching processus
	/// @param endOK Did the process ends successfully ?
	/// @param errMsg Error message
	/// @param fatal Did the process end fatally ?
	function afterLaunching(endOK, errMsg, fatal) {
		var pane;	// Pane where a message will be displayed
		var messageDisplayed = "";

		if (endOK) {	// Successful end
			// Go to the next step
			launching_pane.endLaunch();
			return;
		} else if (fatal) {
			// Bad and fatal error. Show the quit pane.
			pane = abort_pane;
			messageDisplayed = qsTr("A fatal error occured while launching Reyn Tweets:")
					+ "\n\n"
					+ errMsg
					+ "\n\n"
					+ qsTr("The application will quit.");
		} else {
			// Bad end but not fatal.

			// Is it because Reyn Tweets was denied ?
			if (errMsg == qsTr("Reyn Tweets was denied.")) {
				pane = deny_pane;
				messageDisplayed = errMsg + "\n\n"
						+ qsTr("Are you sure that you do not want Reyn Tweets to use your Twitter account ?");
			} else {
				// Display warning popup to ask the user to try again or to quit.
				pane = try_again_pane;
				messageDisplayed = qsTr("An hitch occured while launching Reyn Tweets:")
						+ "\n\n"
						+ errMsg
						+ "\n\n"
						+ qsTr("Do you want to try to launch Reyn Tweets again or to quit ?");
			}
		}

		pane.pane_text = messageDisplayed;
		pane.visible = true;
	}
}
