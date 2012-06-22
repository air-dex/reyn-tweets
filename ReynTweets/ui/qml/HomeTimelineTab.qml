/// @file HomeTimelineTab.qml
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

Rectangle {
	id: home_timeline_tab

	// Alias on the timeline
	property alias timeline: htl_pane

	// Generic margin
	property int margin: 5

	radius: 2*margin
	color: constant.orange_author

	Constants { id: constant }

	Text {
		id: header_text
		text: qsTr("Home timeline")
		horizontalAlignment: Text.AlignHCenter
		anchors.top: home_timeline_tab.top
		anchors.topMargin: margin
		anchors.horizontalCenter: home_timeline_tab.horizontalCenter
		font.family: constant.font
		font.pixelSize: constant.font_size
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
	}

	// Going to the top of the timeline while clicking on the header
	MouseArea {
		anchors.top: parent.top
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: htl_pane.top
		onClicked: timeline.goToTop()
	}

	TimelinePane {
		id: htl_pane
		width: parent.width
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.bottom: parent.bottom
		anchors.top: header_text.bottom
		anchors.topMargin: margin
	}

	Component.onCompleted: {
		// Wiring timeline
		home_timeline_tab.writeReply.connect(htl_pane.writeReply)
		home_timeline_tab.writeTweet.connect(htl_pane.writeTweet)
		home_timeline_tab.endAction.connect(htl_pane.endAction)
		home_timeline_tab.needAuthentication.connect(htl_pane.needAuthentication)
		home_timeline_tab.showInfoMessage.connect(htl_pane.showInfoMessage)
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
