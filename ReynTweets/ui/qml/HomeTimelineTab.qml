import QtQuick 1.1

Rectangle {
	id: home_timeline_tab

	// Alias on the timeline
	property alias timeline: htl_pane

	// Generic margin
	property int margin: 5

	radius: margin
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
