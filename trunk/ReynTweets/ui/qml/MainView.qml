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
	property int icon_bar_size: 30

	Constants {	id:constant	}

	width: constant.reyn_tweets_width
	height: constant.reyn_tweets_height

	////////////
	// Header //
	////////////

	// First bar with menu
	Item {
		id: header
		width: parent.width
		height: menu_icon.height + 2*margin
		anchors.top: main_view.top
		anchors.horizontalCenter: parent.horizontalCenter

		Image {
			id: menu_icon
			source: "../../resources/Logo Reyn Tweets PNG.png"
			anchors.left: parent.left
			anchors.leftMargin: margin
			anchors.verticalCenter: parent.verticalCenter
			sourceSize.height: icon_bar_size
			fillMode: Image.PreserveAspectFit

			MouseArea {
				anchors.fill: parent
				onClicked: menu.visible = !menu.visible
			}
		}

		Image {
			id: close_icon
			source: "../../resources/icons/close_cross.png"
			anchors.right: parent.right
			anchors.rightMargin: margin
			anchors.verticalCenter: parent.verticalCenter

			MouseArea {
				anchors.fill: parent
				onClicked: Qt.quit()
			}
		}
	}

	// The menu
	RTDesktopMenu {
		id: menu
		z: write_tweet.z + 1
		anchors.left: parent.left
		anchors.top: header.bottom
		visible: false
	}

	// Second bar with actions
	Item {
		id: icon_bar
		width: parent.width
		height: write_icon.height + 2*margin
		anchors.top: header.bottom
		anchors.horizontalCenter: parent.horizontalCenter

		Image {
			id: write_icon
			source: "../../resources/icons/stylo.png"
			anchors.right: parent.right
			anchors.rightMargin: margin
			anchors.verticalCenter: parent.verticalCenter

			MouseArea {
				anchors.fill: parent
				onClicked: write_tweet.visible = !write_tweet.visible
			}
		}
	}


	/////////////////////
	// Writing a tweet //
	/////////////////////

	// Pane to write a tweet
	WriteTweetPane {
		id: write_tweet
		z: htl_tab.z + 1
		width: parent.width
		anchors.top: icon_bar.bottom
		anchors.horizontalCenter: parent.horizontalCenter
		visible: false
	}

	// Pane displayed to show a tweet via TwitLonger
	TwoButtonsActionPane {
		id: twitlonger_pane
		width: main_view.interiorWidth
		z: main_view.z + 5
		opacity: 1
		visible: false
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter

		pane_text: qsTr("Your tweet is too long. Would you post it with TwitLonger ?")

		// Left button
		left_button_text: qsTr("Yes")
		onActLeft: {
			write_tweet.postViaTwitLonger()
			twitlonger_pane.visible = false
		}

		// Right button
		right_button_text: qsTr("No")
		onActRight: twitlonger_pane.visible = false

		// Slot executed when TwitLonger was asked
		function twitLongerAsked() {
			twitlonger_pane.visible = true
		}
	}


	////////////////////
	// Showing tweets //
	////////////////////
	property alias timeline: htl_tab.timeline

	// Home timeline (subject to future changes)
	HomeTimelineTab {
		id: htl_tab
		width: parent.width
		anchors.top: write_tweet.visible ? write_tweet.bottom : icon_bar.bottom
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
		visible: false
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter

		// Pane parameters
		pane_text: qsTr("The OAuth tokens was not right. You ought to reauthorize Reyn Tweets again.")
				   .concat("\n\n").concat(qsTr("Would to like to authorize Reyn Tweets again ?"))

		// Left button
		left_button_text: qsTr("Reauthorize")
		onActLeft: {
			reauth_pane.visible = false
			log_component.allowReynTweets()
		}

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
		write_tweet.askTwitLonger.connect(twitlonger_pane.twitLongerAsked)

		// Wiring twitlonger_pane
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
