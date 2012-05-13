/// @file MainView.qml
/// @brief Main page for desktop
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

/// @class MainView
/// @brief Main page for desktop
Rectangle {
	id: main_view
	property int margin: 5

	Constants {	id:constant	}

	width: 360
	height: 640

	// Component displayed while launching the application
	WriteTweetPane {
		id: write_tweet
		width: parent.width
		anchors.top: main_view.top
		anchors.horizontalCenter: parent.horizontalCenter
	}

	// Home timeline (subject to future changes)
	TimelinePane {
		id: timeline
		width: parent.width
		anchors.top: write_tweet.bottom
		anchors.topMargin: 0
		anchors.right: main_view.right
		anchors.left: main_view.left
		anchors.bottom: main_view.bottom
	}


	////////////////////////////////////////
	// Components for non successful ends //
	////////////////////////////////////////

	// Component for potential authentications
	LoginComponents {
		id: log_component
		z: main_view.z + 10
		width: parent.width
		anchors.verticalCenter: parent.verticalCenter
		onAllowOK: loadHomeTimeline();
	}

	// Popup to make the user quit the application
	QuitPane {
		id: abort_pane
		z: main_view.z + 10
		width: parent.width
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: false
	}

	// Popup to show a message.
	TransientPane {
		id: info_pane
		//z: main_view.z + 10
		anchors.bottom: main_view.bottom
		anchors.bottomMargin: 10* main_view.margin
		anchors.horizontalCenter: main_view.horizontalCenter

		// Text to show in the pane
		property alias pane_text: info_pane.message
	}

	// Popup to show a warnig and not fatal problem message.
	WarningTransientPane {
		id: warning_pane
		//z: main_view.z + 10
		anchors.top: main_view.top
		anchors.horizontalCenter: main_view.horizontalCenter

		// Text to show in the pane
		property alias pane_text: warning_pane.warning_msg
	}


	////////////////
	// Management //
	////////////////

	Component.onCompleted: {
		// Wiring timeline
		timeline.writeReply.connect(write_tweet.writeReply)
		timeline.writeTweet.connect(write_tweet.writeTweet)
		timeline.endAction.connect(main_view.endAction)
		timeline.needAuthentication.connect(log_component.allowReynTweets)
		timeline.showInfoMessage.connect(main_view.displayInfoMessage)

		// Wiring write_tweet
		write_tweet.needAuthentication.connect(log_component.allowReynTweets)
		write_tweet.endWriting.connect(main_view.endAction)
		write_tweet.updateTimeline.connect(timeline.updateTimeline)
		write_tweet.showInfoMessage.connect(main_view.displayInfoMessage)
	}

	// Loading the home timeline
	function loadHomeTimeline() {
		timeline.loadHomeTimeline();
	}

	// After an action was made
	function endAction(endOK, errMsg, fatalEnd) {
		var pane	// Pane to show the message

		if (endOK) {
			pane = info_pane
		} else if (fatalEnd) {
			pane = abort_pane
		} else {
			pane = warning_pane
		}

		pane.pane_text = errMsg
		pane.visible = true
	}

	function displayInfoMessage(msg) {
		info_pane.pane_text = msg
		info_pane.visible = true
	}
}
