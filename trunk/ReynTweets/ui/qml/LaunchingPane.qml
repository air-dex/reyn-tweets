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

	// Component for potential authentications
	LoginComponent {
		id: log_component
		width: parent.width
		anchors.verticalCenter: parent.verticalCenter
		onAllowOK: launching_pane.endLaunch();
	}

	// Components for errors
	ErrorComponent {
		id: err_comp
		width: parent.width
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
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
		control.launchEnded.connect(afterLaunching)
		log_component.allowKO.connect(afterAllowing)
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
		var action;	// Pane where a message will be displayed
		var messageDisplayed = "";

		if (endOK) {	// Successful end
			// Go to the next step
			launching_pane.endLaunch();
			return;
		} else if (fatal) {
			// Bad and fatal error. Show the quit pane.
			action = constant.quit_action;
			messageDisplayed = qsTr("A fatal error occured while launching Reyn Tweets:")
					+ "\n\n"
					+ errMsg
					+ "\n\n"
					+ qsTr("The application will quit.");
		} else {
			// Bad end but not fatal.

			// Display warning popup to ask the user to try again or to quit.
			action = constant.try_again_action;
			messageDisplayed = qsTr("An hitch occured while launching Reyn Tweets:")
					+ "\n\n"
					+ errMsg
					+ "\n\n"
					+ qsTr("Do you want to try to launch Reyn Tweets again or to quit ?");
		}

		err_comp.displayMessage(action, messageDisplayed)
	}
}