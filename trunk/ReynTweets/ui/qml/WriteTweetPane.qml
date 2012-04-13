/// @file WriteTweetPane.qml
/// @brief Text entry to write and send a tweet
///
/// @author Romain Ducher
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

Rectangle {
	id: write_tweet_pane
	width: 360
	height: 4*margin + announce.height + write_zone.height + tweet_button.height

	property int chars_left: 140 - tweet_edit.text.length

	property bool too_long_tweet: tweet_edit.text.length > 140

	gradient: Gradient {
		GradientStop {
			position: 0
			color: constant.white
		}

		GradientStop {
			position: write_zone.y / write_tweet_pane.height
			color: constant.grey
		}

		GradientStop {
			position: (write_zone.y + write_zone.height) / write_tweet_pane.height
			color: constant.grey
		}

		GradientStop {
			position: 1
			color: constant.white
		}
	}

	property int margin: 5

	Constants { id: constant }

	WriteTweetControl {
		id: control
		onTweetPosted: console.log("Tweet posted")
		onPostEnded: console.log("Post posted")
	}

	Text {
		id: announce
		color: constant.black
		anchors.top: write_tweet_pane.top
		anchors.left: write_tweet_pane.left
		anchors.topMargin: margin
		anchors.leftMargin: margin
		text: qsTr("What's up ?")
		font.family: constant.font
		font.pixelSize: constant.font_size
		verticalAlignment: Text.AlignVCenter
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
	}

	Text {
		id: chars_left_indicator
		color: constant.black
		font.family: constant.font
		font.pixelSize: constant.font_size
		verticalAlignment: Text.AlignVCenter
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
		anchors.top: write_tweet_pane.top
		anchors.right: write_tweet_pane.right
		anchors.topMargin: margin
		anchors.rightMargin: margin
		text: chars_left
	}

	Rectangle {
		id: write_zone
		width: parent.width - 2*margin
		height: tweet_edit.paintedHeight + 2*margin
		color: constant.white
		border.color: constant.black
		radius: margin
		border.width: 1
		anchors.top: announce.bottom
		anchors.left: write_tweet_pane.left
		anchors.right: write_tweet_pane.right
		anchors.margins: margin

		TextEdit {
			id: tweet_edit
			width: parent.width - 2*margin
			anchors.fill: parent
			anchors.margins: margin
			focus: true
			text: ""
			cursorVisible: true
			selectionColor: constant.orange
			textFormat: TextEdit.PlainText
			wrapMode: TextEdit.WrapAtWordBoundaryOrAnywhere
			font.family: constant.font
			font.pixelSize: constant.font_size
		}
	}

	RTButton {
		id: tweet_button
		anchors.right: write_tweet_pane.right
		anchors.bottom: write_tweet_pane.bottom
		anchors.rightMargin: margin
		anchors.bottomMargin: margin
		button_text: qsTr("Tweet")
		onClick: control.postTweet(tweet_edit.text)
	}

	// Changes depending on the tweet length
	states: [
		// Base state : when the tweet is <= 140 characters

		// When the tweet is too long (> 140 characters)
		State {
			name: "TooLong"
			when: tweet_edit.text.length > 140

			PropertyChanges {
				target: chars_left_indicator
				color: constant.red
				text: chars_left + ' (TL)'
				font.bold: true
			}

			PropertyChanges {
				target: tweet_button
				onClick: console.log("Tweet too long. Cannot tweet.")
			}
		}
	]
}
