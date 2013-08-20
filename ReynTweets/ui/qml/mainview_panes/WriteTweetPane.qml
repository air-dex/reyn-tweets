/// @file WriteTweetPane.qml
/// @brief Text entry to write and send a tweet
///
/// It were in the /trunk/ReynTweets/ui/qml folder until r491
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

import QtQuick 2.0
import ReynTweetsComponents 0.2
import "../js/jstools.js" as Tools
import "../js/twitter-text-js-wrapper.js" as TwitterTextJS
import "../base_components"

Rectangle {
	id: write_tweet_pane
	width: 360
	height: 4*margin + announce.height + write_zone.height + tweet_button.height

	// Number of characters which can be written by the user.
	property int chars_left: getCharsLeft()

	// ID of the user that the tweet replies to
	property string in_reply_to_tweet_id: '-1'

	// Screen name of the user that the tweet replies to
	property string in_reply_to_user: ""


	// Background
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
		future_tweet {
			in_reply_to_status_id_str: write_tweet_pane.in_reply_to_tweet_id
			in_reply_to_screen_name: write_tweet_pane.in_reply_to_user
			text: tweet_edit.text
		}
	}

	// Introduction message
	Text {
		id: announce
		color: constant.black
		anchors.top: write_tweet_pane.top
		anchors.left: write_tweet_pane.left
		anchors.topMargin: margin
		anchors.leftMargin: margin
		text: qsTr("What is happening ?")
		font.family: constant.font
		font.pointSize: constant.font_size
		verticalAlignment: Text.AlignVCenter
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
	}

	// How many characters the user can write ?
	Text {
		id: chars_left_indicator
		color: constant.black
		font.family: constant.font
		font.pointSize: constant.font_size
		verticalAlignment: Text.AlignVCenter
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
		anchors.top: write_tweet_pane.top
		anchors.right: write_tweet_pane.right
		anchors.topMargin: margin
		anchors.rightMargin: margin
		text: chars_left + reason

		property string reason
	}

	// The tweet to write
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
			font.pointSize: constant.font_size
		}
	}

	// Click on it to delete what is written !
	RTButton {
		id: delete_button
		anchors.right: tweet_button.left
		anchors.bottom: write_tweet_pane.bottom
		anchors.rightMargin: margin
		anchors.bottomMargin: margin
		button_text: qsTr("Erase")
		onClick: tweet_edit.text = ""
	}

	// Click on it to tweet !
	RTButton {
		id: tweet_button
		anchors.right: write_tweet_pane.right
		anchors.bottom: write_tweet_pane.bottom
		anchors.rightMargin: margin
		anchors.bottomMargin: margin
		button_text: qsTr("Tweet")
		onClick: control.postTweet()
	}

	// Changes depending on the tweet length
	states: [
		// Base state : when the tweet is <= 140 characters

		// When the tweet is too long (> 140 characters)
		State {
			name: "TooLong"
			// Don't use TwitterTextJS.twttr.txt.isInvalidTweet(tweet_edit.text)
			// because it takes real URLs length instead of shortened URLs length.
			when: chars_left < 0

			PropertyChanges {
				target: chars_left_indicator
				color: constant.red
				font.bold: true
				reason: " (".concat(qsTr("too long")).concat(')')
			}

			PropertyChanges {
				target: tweet_button
				onClick: {
					showInfoMessage(qsTr("Your tweet gets more than 140 characters."))
					askTwitLonger()
				}
			}
		},

		// When the tweet gets invalid characters
		State {
			name: "InvalidCharacters"
			when: TwitterTextJS.twttr.txt.isInvalidTweet(tweet_edit.text) === "invalid_characters"

			PropertyChanges {
				target: chars_left_indicator
				color: constant.red
				font.bold: true
				reason: "( " + qsTr("invalid character(s)") + ')'
			}

			PropertyChanges {
				target: tweet_button
				onClick: showInfoMessage(qsTr("Your tweet gets some invalid character(s)."))
			}
		},

		// When the text input is empty
		State {
			name: "Empty"
			when: TwitterTextJS.twttr.txt.isInvalidTweet(tweet_edit.text) === "empty"

			PropertyChanges {
				target: tweet_button
				onClick: showInfoMessage(qsTr("You have to write something to tweet."))
			}
		}
	]

	Component.onCompleted: {
		// Wiring
		control.actionEnded.connect(write_tweet_pane.afterWriting)
		control.authenticationNeeded.connect(write_tweet_pane.afterAuth)
		control.showInfoMessage.connect(write_tweet_pane.showInfoMessage)
		control.tweetPosted.connect(write_tweet_pane.afterPosting)
	}

	// Writing a reply to a tweet
	function writeReply(replyToScreenName, replyToTweetID) {
		tweet_edit.text = '@'.concat(replyToScreenName).concat(' ')
		tweet_edit.cursorPosition = tweet_edit.text.length
		in_reply_to_tweet_id = replyToTweetID
		in_reply_to_user = replyToScreenName
		visible = true

		// TODO for new UI : a box asking if it is a reply for the user
	}

	// Writing a tweet by specifying the text
	function writeTweet(tweetText) {
		tweet_edit.text = tweetText
		tweet_edit.cursorPosition = 0
		visible = true
	}

	// Readjusting the number depending on the URLS contained in the text.
	// In the final tweet, URLs will be shortened with t.co and the corresponding
	// t.co URLs have got fixed lengthes : 21 chars for https URLs, 20 otherwise.
	function getCharsLeft() {
		return Tools.getCharactersLeft(tweet_edit.text);
	}

	// What to do after posting a tweet
	function afterPosting(newTweetVariant) {
		tweet_edit.text = ""
		in_reply_to_tweet_id = "-1"
		write_tweet_pane.updateAfterWrite(newTweetVariant)
	}

	// Posting a Tweet via TwitLonger
	function postViaTwitLonger() {
		control.postViaTwitLonger(tweet_edit.text,
								  in_reply_to_tweet_id,
								  in_reply_to_user)
	}

	function afterWriting(endOK, endMsg, fatalEnd) {
		write_tweet_pane.visible = false
		write_tweet_pane.endWriting(endOK, endMsg, fatalEnd)
	}

	function afterAuth() {
		write_tweet_pane.visible = false
		write_tweet_pane.needAuthentication()
	}


	/////////////
	// Signals //
	/////////////

	// Send when a new authentication is needed
	signal needAuthentication

	// Sent after writing a tweet
	signal endWriting(bool endOK, string endMsg, bool fatalEnd)

	// Sent to update the timeline
	signal updateAfterWrite(variant newTweetVariant)

	// Showing an information message
	signal showInfoMessage(string infoMsg)

	// Asking the user if he want to post the tweet via TwitLonger
	signal askTwitLonger
}
