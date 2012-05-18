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
			source: "../../resources/Logo Reyn Tweets PNG.png"
		}

		// Name of the program
		Text {
			id: program_name_label
			text: "Reyn Tweets"
			font.bold: true
			anchors.horizontalCenter: parent.horizontalCenter
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
			horizontalAlignment: Text.AlignHCenter
			verticalAlignment: Text.AlignVCenter
			font.pixelSize: constant.font_size
			onLinkActivated: Qt.openUrlExternally(link)
		}
	}

	////////////////////////////////////////
	// Components for non successful ends //
	////////////////////////////////////////

	// Component for potential authentications
	LoginComponents {
		id: log_component
		z: launching_pane.z + 10
		width: parent.width
		anchors.verticalCenter: parent.verticalCenter
		onAllowOK: launching_pane.endLaunch();
	}

	// Popup to show a message.
	TransientPane {
		id: info_pane
		z: launching_pane.z + 10
		width: parent.width
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 10* launching_pane.margin
		anchors.horizontalCenter: parent.horizontalCenter

		// Text to show in the pane
		property alias pane_text: info_pane.message
	}

	// Components for errors

	// Popup to make the user quit the application
	QuitPane {
		id: abort_pane
		z: launching_pane.z + 10
		width: parent.width
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: false
	}

	// Popup to try again
	TryAgainPane {
		id: try_again_pane
		z: launching_pane.z + 10
		width: parent.width
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: false
		onTryAgain: control.launchReynTweets();
	}


	////////////////////////////
	// Back office management //
	////////////////////////////

	/// @brief Signal sent after launching the application
	signal endLaunch

	/// @brief Control behind the component
	LaunchingControl {
		id: control
		onAuthenticationNeeded: log_component.allowReynTweets();
	}

	Component.onCompleted: {
		// Wiring
		control.actionEnded.connect(afterLaunching)

		// Wiring log_component
		log_component.allowKO.connect(afterAllowing)
		log_component.showInfoMessage.connect(displayInfoMessage)
	}

	/// @fn function launchReynTweets();
	/// @brief Launching the application
	function launchReynTweets() {
		control.launchReynTweets()
	}

	// After a potential authentication process
	function afterAllowing(errMsg, fatal) {
		afterLaunching(false, errMsg, fatal)
	}

	/// @fn function afterLaunching(endOK, errMsg, fatal);
	/// @brief What happened after the launching processus
	/// @param endOK Did the process ends successfully ?
	/// @param errMsg Error message
	/// @param fatal Did the process end fatally ?
	function afterLaunching(endOK, errMsg, fatal) {
		var messageDisplayed = "";
		var pane;	// Pane where a message will be displayed

		if (endOK) {	// Successful end
			// Go to the next step
			pane = info_pane
			messageDisplayed = errMsg
			launching_pane.endLaunch();
		} else if (fatal) {
			// Bad and fatal error. Show the quit pane.
			pane = abort_pane
			messageDisplayed = qsTr("A fatal error occured while launching Reyn Tweets:")
					+ "\n\n"
					+ errMsg
					+ "\n\n"
					+ qsTr("The application will quit.");
		} else {
			// Bad end but not fatal.

			// Display warning popup to ask the user to try again or to quit.
			pane = try_again_pane
			messageDisplayed = qsTr("An hitch occured while launching Reyn Tweets:")
					+ "\n\n"
					+ errMsg
					+ "\n\n"
					+ qsTr("Do you want to try to launch Reyn Tweets again or to quit ?");
		}

		pane.pane_text = messageDisplayed;
		pane.visible = true
	}

	// Displaying informations
	function displayInfoMessage(msg) {
		info_pane.pane_text = msg
		info_pane.visible = true
	}
}
