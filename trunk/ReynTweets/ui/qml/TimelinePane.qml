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

	// Text announcing what to do to refesh the timeline
	Text {
		id: refresh_text
		text: ""
		horizontalAlignment: Text.AlignHCenter
		anchors.top: timeline_pane.top
		anchors.horizontalCenter: timeline_pane.horizontalCenter
		font.family: constant.font
		font.pixelSize: constant.font_size
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere

		states: [
			State {
				name: "pull"
				when: !timeline_view.earlyRefreshMode
				PropertyChanges {
					target: refresh_text
					text: qsTr("Pull down to refresh")
				}
			},
			State {
				name: "release"
				when: timeline_view.earlyRefreshMode
				PropertyChanges {
					target: refresh_text
					text: qsTr("Release to refresh")
				}
			}
		]
	}

	// List of all the tweets
	ListView {
		id: timeline_view
		z: refresh_text.z + 1
		anchors.fill: parent
		clip: true

		delegate: Component {
			TweetPane {
				width: timeline_pane.width
				tweet: control.getTweet(index)

				Component.onCompleted: {
					// When a tweet is quoted or reply to a tweet
					reply.connect(writeReply)
					quote.connect(writeTweet)

					// Updating the timeline
					updateTweet.connect(updateTL)

					// Destroying the tweet
					destroyTweet.connect(deleteTweet)

					// End of an action
					endTweeting.connect(timeline_pane.endAction)

					// Potential authentication
					needAuthentication.connect(timeline_pane.needAuthentication)

					// For displaying informations
					showInfoMessage.connect(timeline_pane.showInfoMessage)
				}

				function updateTL(newTweet) {
					control.replaceTweet(newTweet, index)
				}

				function deleteTweet(newTweet) {
					control.deleteTweet(index)
				}
			}
		}

		model: TimelineModel { id: timeline_model }

		footer: Component {
			Text {
				id: timeline_footer
				text: qsTr("More...")
				horizontalAlignment: Text.AlignHCenter
				font.family: constant.font
				font.pixelSize: constant.font_size
				wrapMode: Text.WrapAtWordBoundaryOrAnywhere
				visible: timeline_view.model.count > 0
			}
		}

		// Loading tweets
		property bool earlyRefreshMode: false
		property bool canUpdate: false

		property bool olderDiscoverMode: false

		onMovementStarted: {
			if (timeline_view.atYBeginning && !earlyRefreshMode) {
				// If you are at the top -> get earlier tweets
				earlyRefreshMode = true
			} else if (timeline_view.atYEnd && !olderDiscoverMode) {
				// If you are at the bottom -> get older tweets
				olderDiscoverMode = true
			}

			//timeline_view.returnToBounds()
		}

		onMovementEnded: {
			if (timeline_view.atYBeginning && earlyRefreshMode) {
				// If you are at the top -> get earlier tweets
				earlyRefreshMode = false
				control.refreshHomeTimeline()
			} else if (timeline_view.atYEnd && olderDiscoverMode) {
				// If you are at the bottom -> get older tweets
				olderDiscoverMode = false
				control.moreOldHomeTimeline()
			}
		}
	}


	Component.onCompleted: {
		// Wiring

		// After loading a timeline
		control.actionEnded.connect(afterLoading)

		// For authentications
		control.authenticationNeeded.connect(needAuthentication)

		// For displaying informations
		control.showInfoMessage.connect(timeline_pane.showInfoMessage)


	}

	// Loading the home timeline
	function loadHomeTimeline() {
		control.loadHomeTimeline();
	}

	// Refreshing the home timeline
	function updateTimeline() {
		console.log("REFRESH !")
		control.refreshHomeTimeline()
	}

	// What happened after loading the timeline
	function afterLoading(endOK, errMsg, isFatal) {
		var action, messageDisplayed;

		if (endOK) {
			messageDisplayed = errMsg
		} else if (isFatal) {
			// Bad and fatal error. Show the quit pane.
			messageDisplayed = qsTr("A fatal error occured while loading the timeline:")
					+ "\n\n"
					+ errMsg
					+ "\n\n"
					+ qsTr("The application will quit.");
		} else {
			messageDisplayed = errMsg
		}

		refresh_text.state = "pull"
		timeline_pane.endAction(endOK, messageDisplayed, isFatal)
	}

	signal needAuthentication
	signal endAction(bool endOK, string errMsg, bool fatalEnd)

	signal writeReply(string text, string replyID)
	signal writeTweet(string text)

	// Showing an information message
	signal showInfoMessage(string infoMsg)
}
