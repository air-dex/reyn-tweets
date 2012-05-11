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

	// Component for potential authentications
	LoginComponent {
		id: log_component
		width: parent.width
		anchors.verticalCenter: parent.verticalCenter
		onAllowOK: loadHomeTimeline();
	}

	// Components for errors
	ErrorComponent {
		id: err_comp
		width: parent.width
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		onTryAgain: loadHomeTimeline();
	}

	Component.onCompleted: {
		// Wiring
		timeline.writeReply.connect(write_tweet.writeReply)
		timeline.writeTweet.connect(write_tweet.writeTweet)
		timeline.endAction.connect(main_view.endAction)
		timeline.needAuthentication.connect(log_component.allowReynTweets)
	}

	// Loading the home timeline
	function loadHomeTimeline() {
		timeline.loadHomeTimeline();
	}

	function endAction(endOK, errMsg, fatalEnd) {
		if (endOK) {
			return;
		}

		var action = fatalEnd ? constant.quit_action : constant.info_msg_action;

		err_comp.displayMessage(action, errMsg)
	}
}
