/// @file TimelinePane.qml
/// @brief Pane to show a timeline
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
import ReynTweetsEntities 0.1

/// @class TimelinePane
/// @brief Pane to show a timeline
Rectangle {
	id: timeline_pane
	width: 360
	height: 640

	Constants { id: constant }

	// Control behind the pane
	TimelineControl {
		id: control
		onAuthenticationNeeded: log_component.allowReynTweets()
		onTimelineChanged: timeline_model.syncWithTimeline(control.tl_length)
	}

	// List of all the tweets
	ListView {
		id: timeline_view
		anchors.fill: parent
		clip: true

		delegate: Component {
			TweetPane {
				//id: delegate_pane
				width: timeline_pane.width
				tweet: control.getTweet(index)

				Component.onCompleted: {
					// When a tweet is quoted or reply to a tweet
					reply.connect(writeReply)
					quote.connect(writeTweet)
				}
			}
		}

		model: TimelineModel { id: timeline_model }

		// Loading tweets
		onMovingChanged: {
			if (timeline_view.atYBeginning) {
				// If you are at the top -> get earlier tweets
				console.log("TODO : get earlier tweets")
			} else if (timeline_view.atYEnd) {
				// If you are at the bottom -> get older tweets
				console.log("TODO : get older tweets")
			}

			timeline_view.returnToBounds()
		}

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
		onTryAgain: control.loadHomeTimeline();
	}

	Component.onCompleted: {
		// Wiring

		// After loading a timeline
		control.loadEnded.connect(afterLoading)
	}

	// Loading the home timeline
	function loadHomeTimeline() {
		control.loadHomeTimeline();
	}

	function afterLoading(endOK, errMsg, isFatal) {
		var action, messageDisplayed;

		if (endOK) {
			// Nothing to do for the moment
			return;
		} else if (isFatal) {
			// Bad and fatal error. Show the quit pane.
			action = constant.quit_action;
			messageDisplayed = qsTr("A fatal error occured while loading the timeline:")
					+ "\n\n"
					+ errMsg
					+ "\n\n"
					+ qsTr("The application will quit.");
		} else {
			action = constant.info_msg_action
			messageDisplayed = errMsg
		}

		err_comp.displayMessage(action, messageDisplayed)
	}

	signal writeReply(string text, string replyID)
	signal writeTweet(string text)
}
