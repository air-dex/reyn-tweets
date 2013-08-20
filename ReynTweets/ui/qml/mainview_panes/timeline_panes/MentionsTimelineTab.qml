/// @file MentionsTimelineTab.qml
/// @brief Tab with mentions timeline
///
/// It were in the /trunk/ReynTweets/ui/qml folder until r491
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

import QtQuick 2.0
import ReynTweetsComponents 0.2
import "../../base_components"

Rectangle {
	id: mentions_timeline_tab

	// Alias on the timeline
	property alias timeline: mentions_pane

	// Generic margin
	property int margin: constant.margin

	radius: 2*margin
	color: constant.orange_author

	Constants { id: constant }

	Text {
		id: header_text
		text: qsTr("Mentions")
		horizontalAlignment: Text.AlignHCenter
		anchors.top: mentions_timeline_tab.top
		anchors.topMargin: margin
		anchors.horizontalCenter: mentions_timeline_tab.horizontalCenter
		font.family: constant.font
		font.pointSize: constant.font_size
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
	}

	// Going to the top of the timeline while clicking on the header
	MouseArea {
		anchors.top: parent.top
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: mentions_pane.top
		onClicked: timeline.goToTop()
	}

	TimelinePane {
		id: mentions_pane
		width: parent.width
		timeline_type: TimelineHandler.MENTIONS
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.bottom: parent.bottom
		anchors.top: header_text.bottom
		anchors.topMargin: margin
	}

	Component.onCompleted: {
		// Wiring timeline
		mentions_timeline_tab.writeReply.connect(mentions_pane.writeReply)
		mentions_timeline_tab.writeTweet.connect(mentions_pane.writeTweet)
		mentions_timeline_tab.endAction.connect(mentions_pane.endAction)
		mentions_timeline_tab.needAuthentication.connect(mentions_pane.needAuthentication)
		mentions_timeline_tab.showInfoMessage.connect(mentions_pane.showInfoMessage)
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
