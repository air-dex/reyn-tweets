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

	// MainView width minus 2 margins on each side
	property int interiorWidth: main_view.width - 2* main_view.margin

	// Component for potential authentications
	LoginComponents {
		id: log_component
		width: parent.width
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: false
		onAllowOK: loadHomeTimeline();
	}

	// Popup to make the user quit the application
	QuitPane {
		id: abort_pane
		width: main_view.interiorWidth
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: false
	}

	// Pane for reauthentications
	TwoButtonsActionPane {
		id: reauth_pane
		width: main_view.interiorWidth
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: false

		// Pane parameters
		pane_text: qsTr("The OAuth tokens was not right. You ought to reauthorize Reyn Tweets again.")
				   + "\n\n" + qsTr("Would to like to authorize Reyn Tweets again ?")

		// Left button
		left_button_text: qsTr("Reauthorize")
		onActLeft: log_component.allowReynTweets()

		// Right button
		right_button_text: qsTr("No")
		onActRight: reauth_pane.visible = false
	}

	// Popup to show a message.
	TransientPane {
		id: info_pane
		anchors.bottom: main_view.bottom
		anchors.bottomMargin: 10* main_view.margin
		anchors.horizontalCenter: main_view.horizontalCenter

		// Text to show in the pane
		property alias pane_text: info_pane.message
	}

	// Popup to show a warnig and not fatal problem message.
	WarningTransientPane {
		id: warning_pane
		anchors.top: main_view.top
		anchors.horizontalCenter: main_view.horizontalCenter

		// Text to show in the pane
		property alias pane_text: warning_pane.warning_msg
	}


	////////////////
	// Management //
	////////////////

	Component.onCompleted: {
		// Wiring log_component
		log_component.showInfoMessage.connect(main_view.displayInfoMessage)

		// Wiring timeline
		timeline.writeReply.connect(write_tweet.writeReply)
		timeline.writeTweet.connect(write_tweet.writeTweet)
		timeline.endAction.connect(main_view.endAction)
		timeline.needAuthentication.connect(needNewAuth)
		timeline.showInfoMessage.connect(main_view.displayInfoMessage)

		// Wiring write_tweet
		write_tweet.needAuthentication.connect(needNewAuth)
		write_tweet.endWriting.connect(main_view.endAction)
		write_tweet.updateAfterWrite.connect(timeline.updateAfterWrite)
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

	// Displaying informations
	function displayInfoMessage(msg) {
		info_pane.pane_text = msg
		info_pane.visible = true
	}

	// New authentication
	function needNewAuth() {
		reauth_pane.visible = true
	}
}
