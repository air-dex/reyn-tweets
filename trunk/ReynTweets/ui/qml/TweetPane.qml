/// @file TweetPane.qml
/// @brief Pane to show a tweet
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

/// @class TweetPane
/// @brief Pane to show a tweet
Rectangle {
	id: tweet_pane

	// Size of a side of an avatar
	property int avatar_side: 50

	// Size of a side of an avatar
	property int margin: 5

	// The tweet displayed in this pane
	property Tweet tweet: control.tweet

	width: 360
	height: 150
 border.width: 2
 border.color: "#000000"

	Constants { id:constant }

	Component.onCompleted: {
		// Treatments if it is a retweet
		if (tweet.isRetweet()) {
			console.log("Le tweet #" + tweet.id_str + " est un retweet")
			tweet_pane.state = "Retweet"
		}
	}

	// Control behind the pane
	TweetControl {
		id: control
	}

	// Square with avatars
	Item {
		id: avatar_zone

		// Size of a size of the item
		property int side: tweet_pane.avatar_side

		z: 0
		width: side
		height: side
		anchors.top: parent.top
		anchors.topMargin: margin
		anchors.left: parent.left
		anchors.leftMargin: margin

		// Tweet author's avatar
		Image {
			id: tweet_author_avatar
			z: avatar_zone.z
			width: tweet_pane.avatar_side
			height: tweet_pane.avatar_side
			anchors.top: parent.top
			anchors.topMargin: 0
			anchors.left: parent.left
			anchors.leftMargin: 0
			source: tweet.author.profile_image_url
		}

		// Retweeter's avatar if it is a retweet
		Image {
			id: retweeter_avatar
			z: avatar_zone.z + 1
			width: tweet_pane.avatar_side * 3/5
			height: tweet_pane.avatar_side * 3/5
			anchors.bottom: parent.bottom
			anchors.bottomMargin: 0
			anchors.right: parent.right
			anchors.rightMargin: 0
			visible: false
		}
	}

	// Label displaying the author of the tweet
	Text {
		id: author_text
		text:  tweet.author.screen_name
		verticalAlignment: Text.AlignVCenter
		font.family: constant.font
		font.pixelSize: constant.font_size
		anchors.topMargin: margin
		anchors.top: parent.top
		anchors.left: avatar_zone.right
		// More margin to not move if it is a retweet.
		anchors.leftMargin: 2*margin + tweet_pane.avatar_side /4
	}

	// Label displaying when the tweet was posted
	Text {
		id: date_text
		text: tweet.whenWasItPosted();
		anchors.left: author_text.right
		anchors.leftMargin: margin
		font.family: constant.font
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignRight
		anchors.top: parent.top
		anchors.topMargin: margin
		anchors.right: parent.right
		anchors.rightMargin: margin
		font.pixelSize: constant.font_size
	}

	// Content of the tweet
	Text {
		id: text
		text: tweet.getDisplayText();
		font.family: constant.font
		font.pixelSize: constant.font_size
		anchors.left: author_text.left
		anchors.leftMargin: 0
		anchors.top: author_text.bottom
		anchors.topMargin: 2*margin
		anchors.right: tweet_pane.right
		anchors.rightMargin: margin
	}

	// Source of the tweet
	Text {
		id: source_text
		text: tweet.getDisplaySource();
		color: "#757575"
		font.italic: true
		font.family: constant.font
		font.pixelSize: constant.font_size
		anchors.left: author_text.left
		anchors.leftMargin: 0
		anchors.top: text.bottom
		anchors.topMargin: 2*margin
		anchors.right: tweet_pane.right
		anchors.rightMargin: margin
	}

	Row {
		id: action_row
		spacing: margin
		height: reply_action.height
		anchors.right: parent.right
		anchors.rightMargin: margin
		anchors.bottom: parent.bottom
		anchors.bottomMargin: margin
		anchors.left: parent.left
		anchors.leftMargin: margin

		Text {
			id: reply_action
			text: qsTr("Reply")
			font.family: constant.font
			font.pixelSize: constant.font_size

			MouseArea {
				id: reply_act
				anchors.fill: parent
				onClicked: control.reply();
			}
		}

		Text {
			id: retweet_action
			text: qsTr("Retweet")
			font.family: constant.font
			font.pixelSize: constant.font_size

			MouseArea {
				id: retweet_act
				anchors.fill: parent
				onClicked: control.retweet();
			}
		}

		Text {
			id: quote_action
			text: qsTr("Quote")
			font.family: constant.font
			font.pixelSize: constant.font_size

			MouseArea {
				id: quote_act
				anchors.fill: parent
				onClicked: control.quote();
			}
		}

		Text {
			id: favorite_action
			text: tweet.favorited ? qsTr("Unfavorite") : qsTr("Favorite")
			font.family: constant.font
			font.pixelSize: constant.font_size

			MouseArea {
				id: favorite_act
				anchors.fill: parent
				onClicked: {
					if (tweet.favorited) {
						control.unfavorite()
					} else {
						control.favorite()
					}
				}
			}
		}
	}

	states: [
		// Base state : classic tweet

		State {
			// The tweet is a retweet
			name: "Retweet"

			// Displaying the retweet author's avatar
			PropertyChanges {
				target: avatar_zone
				side: tweet_pane.avatar_side * 6/5
			}

			PropertyChanges {
				target: tweet_author_avatar
				source: tweet.retweet.author.profile_image_url
			}

			PropertyChanges {
				target: retweeter_avatar
				visible: true
				source: tweet.author.profile_image_url
			}

			// New author and new margin to not move the QML Component
			PropertyChanges {
				target: author_text
				text: tweet.retweet.author.screen_name
				anchors.leftMargin: 2*margin
			}

			// New date
			PropertyChanges {
				target: date_text
				text: tweet.retweet.whenWasItPosted();
			}

			// New text (i.e. not beginning by "RT @qqn: ")
			PropertyChanges {
				target: text
				text: tweet.retweet.getDisplayText();
			}

			// Original source of the retweet
			PropertyChanges {
				target: source_text
				text: tweet.retweet.getDisplaySource();
			}
		},
		State {
			// The tweet is a reply
			name: "Reply"
		},
		State {
			// The tweet is a direct message (DM)
			name: "DirectMessage"
		}
	]

	////////////////
	// Management //
	////////////////

	signal reply
	signal retweet
	signal quote
	signal favorite
	signal unfavorite
}
