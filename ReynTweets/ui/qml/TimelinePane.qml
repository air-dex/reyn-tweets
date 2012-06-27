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
	color: constant.orange_author

	Constants { id: constant }

	// Control behind the pane
	TimelineControl {
		id: control
		onTimelineChanged: timeline_model.syncWithTimeline()
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

					// Destroying the tweet
					destroyTweet.connect(deleteTweet)

					// End of an action
					endTweeting.connect(timeline_pane.endAction)

					// Potential authentication
					needAuthentication.connect(timeline_pane.needAuthentication)

					// For displaying informations
					showInfoMessage.connect(timeline_pane.showInfoMessage)

					// Updating the timeline
					commitTweet.connect(majTweet)
				}

				function deleteTweet(newTweet) {
					control.deleteTweet(index)
				}

				function majTweet(newTweet) {
					control.replaceTweet(newTweet, index)
				}
			}
		}

		model: ListModel {
			id: timeline_model

			// Syncing the timeline control and the data model
			function syncWithTimeline() {
				timeline_model.clear();

				for (var j = 0; j < control.nb_tweets; j++) {
					timeline_model.append({})
				}
			}
		}

		footer: Component {
			Item {
				id: timeline_footer
				width: timeline_view.width
				height: timeline_footer_text.implicitHeight + 2*constant.margin

				Text {
					id: timeline_footer_text
					anchors.horizontalCenter: timeline_footer.horizontalCenter
					anchors.verticalCenter: timeline_footer.verticalCenter
					anchors.margins: constant.margin
					text: qsTr("More...")
					horizontalAlignment: Text.AlignHCenter
					verticalAlignment: Text.AlignVCenter
					font.family: constant.font
					font.pixelSize: constant.font_size
					wrapMode: Text.WrapAtWordBoundaryOrAnywhere
					visible: timeline_view.model.count > 0
				}

				// Click to load more tweets
				MouseArea {
					anchors.fill: parent
					onClicked: timeline_view.loadMore()
				}
			}
		}

		// Loading tweets
		property bool earlyRefreshMode: false
		property bool olderDiscoverMode: false

		// Backup of the index at the top of the flickable surface.
		// Used to be nearly at the same place after getting older tweets
		property int indexBackup

		onMovementStarted: {
			if (timeline_view.atYBeginning && !earlyRefreshMode) {
				// If you are at the top -> get earlier tweets
				earlyRefreshMode = true
			} else if (timeline_view.atYEnd && !olderDiscoverMode) {
				// If you are at the bottom -> get older tweets
				olderDiscoverMode = true
			}
		}

		onMovementEnded: {
			if (timeline_view.atYBeginning && earlyRefreshMode) {
				// If you are at the top -> get earlier tweets
				earlyRefreshMode = false
				timeline_pane.updateTimeline()
			} else if (timeline_view.atYEnd && olderDiscoverMode) {
				// If you are at the bottom -> get older tweets
				olderDiscoverMode = false
				loadMore()
			}
		}

		function backupIndex() {
			indexBackup = timeline_view.indexAt(contentX, contentY)
		}

		// Loading more tweets
		function loadMore() {
			backupIndex()
			control.moreOldHomeTimeline()
		}

		///////////////////////////
		// Scroll bar management //
		///////////////////////////

		ScrollBar {
			id: verticalScrollBar
			width: 5
			height: timeline_view.height
			z: timeline_view.z + 1
			anchors.right: timeline_view.right
			opacity: 1
			orientation: Qt.Vertical
			position: timeline_view.visibleArea.yPosition
			ratio: timeline_view.visibleArea.heightRatio

			Binding {
				when: timeline_view.moving && !verticalScrollBar.dragging

				target: verticalScrollBar
				property: "position"
				value: timeline_view.visibleArea.yPosition
			}

			Binding {
				when: verticalScrollBar.dragging

				target: timeline_view
				property: "contentY"
				value: verticalScrollBar.dragPosition * timeline_view.contentHeight
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

		// For a better placement in the timeline
		control.loadedMoreTweets.connect(timeline_pane.moreTweets)

		// Sync between the timeline and the list model
		control.timelineChanged.connect(timeline_model.syncWithTimeline)
	}

	// Loading the home timeline
	function loadHomeTimeline() {
		control.loadHomeTimeline();
	}

	// Refreshing the home timeline
	function updateTimeline() {
		timeline_view.backupIndex()
		control.refreshHomeTimeline()
	}

	// Refreshing the home timeline
	function updateAfterWrite(newTweet) {
		timeline_view.backupIndex()
		control.refreshHomeTimelineAfterWrite(newTweet)
	}

	// What happened after loading the timeline
	function afterLoading(endOK, endMsg, isFatal) {
		var action, messageDisplayed;

		if (!endOK && isFatal) {
			// Bad and fatal error. Show the quit pane.
			messageDisplayed = qsTr("A fatal error occured while loading the timeline:")
									.concat("\n\n")
									.concat(endMsg)
									.concat("\n\n")
									.concat(qsTr("The application will quit."));
		} else {
			messageDisplayed = endMsg
		}

		refresh_text.state = "pull"
		timeline_view.positionViewAtIndex(timeline_view.indexBackup,
										  ListView.Beginning);
		timeline_pane.endAction(endOK, messageDisplayed, isFatal)
	}

	// Executed after refreshing a timeline
	function moreTweets(nbTweets) {
		timeline_view.indexBackup = timeline_view.indexBackup + nbTweets
	}

	// Going at the top of the timeline
	function goToTop() {
		timeline_view.contentY = 0
	}


	/////////////
	// Signals //
	/////////////

	signal needAuthentication
	signal endAction(bool endOK, string errMsg, bool fatalEnd)

	signal writeReply(string replyScreenName, string replyID)
	signal writeTweet(string text)

	// Showing an information message
	signal showInfoMessage(string infoMsg)
}
