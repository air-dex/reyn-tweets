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

// Pane to show a tweet
Rectangle {
	id: tweet_pane

	// Size of a side of an avatar
	property int avatar_side: 50

	// Size of a side of an avatar
	property int margin: 5

	// The tweet displayed in this pane
	property Tweet tweet: control.tweet

	// The tweet displayed in this pane
	property Tweet shown_tweet: tweet

	// Minimal height
	property int min_height: author_text.height + text.height
							 + source_text.height + action_row.height + 8*margin

	width: 360
	height:  min_height
			 + (tweet.isReply() ?
					(reply_info.height + 2*margin)
				  : 0
				)
			 + (tweet.isRetweetedByPeople() ?
					(retweet_info.height + 2*margin)
				  : 0
				)

	// Width of top and bottom borders / pane height.
	property real separator: 2 / tweet_pane.height

	gradient: Gradient {
		GradientStop {
			position: 0
			color: constant.grey
		}

		GradientStop {
			position: separator
			color: constant.white
		}

		GradientStop {
			position: 1-separator
			color: constant.white
		}

		GradientStop {
			position: 1
			color: constant.grey
		}
	}

	Constants { id:constant }

	Component.onCompleted: {
		// Treatments if it is a retweet
		if (tweet.isRetweet()) {
			tweet_pane.state = "Retweet"
		}

		// Treatments if it is a retweet
		if (tweet.isRetweetedByPeople()) {
			retweet_info.visible = true
			retweet_info.anchors.topMargin = 2*margin
		}

		// Treatments if it is a reply
		if (tweet.isReply()) {
			tweet_pane.state = "Reply"
		}
	}

	// Control behind the pane
	TweetControl { id: control }

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
			source: shown_tweet.author.profile_image_url
			MouseArea {
				id: avatar_mouse_area
				anchors.fill: parent
				onClicked: console.log("TODO : Show @" + shown_tweet.author.screen_name)
			}
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
			MouseArea {
				anchors.fill: parent
				onClicked: console.log("TODO : Show @" + tweet.author.screen_name)
			}
		}
	}

	// Label displaying the author of the tweet
	Text {
		id: author_text
		text: wrapEntity('@' + shown_tweet.author.screen_name)
		font.bold: true
		font.underline: false
		verticalAlignment: Text.AlignVCenter
		font.family: constant.font
		font.pixelSize: constant.font_size
		anchors.topMargin: margin
		anchors.top: parent.top
		anchors.left: avatar_zone.right
		// More margin to not move if it is a retweet.
		anchors.leftMargin: 2*margin + tweet_pane.avatar_side /4
		onLinkActivated: console.log('TODO : show user @' + shown_tweet.author.screen_name)
	}

	// Label displaying when the tweet was posted
	Text {
		id: date_text
		text: shown_tweet.whenWasItPosted();
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
		text: shown_tweet.getDisplayText();
		textFormat: Text.RichText
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
		font.family: constant.font
		font.pixelSize: constant.font_size
		anchors.left: author_text.left
		anchors.leftMargin: 0
		anchors.top: author_text.bottom
		anchors.topMargin: 2*margin
		anchors.right: tweet_pane.right
		anchors.rightMargin: margin
		onLinkActivated: {
			if (link.length <= 0) return;

			switch (link[0]) {
				case '#':
					// It is an hashtag. Launch a search about it !
					console.log("Rechercher le hashtag " + link)
					break;

				case '@':
					// It is a mentionned used. Show him !
					console.log("Voir l'utilisateur " + link)
					break;

				default:
					// It is an URL. Show its content in a browser !
					Qt.openUrlExternally(link)
					break;
			}
		}
	}

	// Source of the tweet
	Text {
		id: source_text
		text: "via " + shown_tweet.getDisplaySource()
		font.italic: true
		font.family: constant.font
		font.pixelSize: constant.font_size
		anchors.left: author_text.left
		anchors.leftMargin: 0
		anchors.top: text.bottom
		anchors.topMargin: 2*margin
		anchors.right: tweet_pane.right
		anchors.rightMargin: margin
		onLinkActivated: Qt.openUrlExternally(link)
	}

	// Reply informations
	Text {
		id: reply_info
		text: qsTr("In reply to ") + wrapEntity('@' + shown_tweet.in_reply_to_screen_name)
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
		visible: false
		font.family: constant.font
		font.pixelSize: constant.font_size
		anchors.left: author_text.left
		anchors.leftMargin: 0
		anchors.top: source_text.bottom
		anchors.topMargin: 0
		anchors.right: tweet_pane.right
		anchors.rightMargin: margin
		onLinkActivated: {
			// Showing who replied
			console.log("TODO : qui a répondu ?")
		}
	}

	// Retweet informations
	Text {
		id: retweet_info
		text: retweetInfoText();
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
		visible: false
		font.family: constant.font
		font.pixelSize: constant.font_size
		anchors.left: author_text.left
		anchors.leftMargin: 0
		anchors.top: source_text.bottom
		anchors.topMargin: 0
		anchors.right: tweet_pane.right
		anchors.rightMargin: margin
		onLinkActivated: {
			// Showing people that have retweeted
			console.log("TODO : qui a retweeté ?")
		}

		function retweetInfoText() {
			// TODO : be perfect !
			var text = qsTr("Retweeted by ")
			text = text + tweet.author.screen_name

			// Nb of people that retweeted
			var nbRetweeters = shown_tweet.retweet_count

			if (nbRetweeters > 0) {
				var peopleString = (nbRetweeters - 1 == 1) ? qsTr("person") : qsTr("people")
				text = text + qsTr(" and ") + nbRetweeters + qsTr(" other ") + peopleString + '.'
			}

			return text
		}
	}

	// Row with actions on the tweet
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
				target: tweet_pane
				shown_tweet: tweet.retweet
			}

			// Displaying the retweet author's avatar
			PropertyChanges {
				target: avatar_zone
				side: tweet_pane.avatar_side * 6/5
			}

			// Kept to load the image if necessary
			PropertyChanges {
				target: retweeter_avatar
				visible: true
				source: tweet.author.profile_image_url
			}

			// New author and new margin to not move the QML Component
			PropertyChanges {
				target: author_text
				anchors.leftMargin: 2*margin
			}
		},
		State {
			// The tweet is a reply
			name: "Reply"

			// Showing reply text
			PropertyChanges {
				target: reply_info
				visible: true
				anchors.topMargin: 2*margin
			}

			// Putting retweet_info under reply_info
			PropertyChanges {
				target: retweet_info
				anchors.top: reply_info.bottom
			}
		},
		State {
			// The tweet is a direct message (DM)
			name: "DirectMessage"
		}
	]

	// Function to wrap words into an HTML tag
	function wrapEntity(entity) {
		var beginTag = '<a style="text-decoration: none; color: ';
		var hrefTag = '" href="';
		var closeTag = '">';
		var endTag = '</a>';
		return beginTag + shown_tweet.author.profile_link_color
				+ hrefTag + entity + closeTag + entity + endTag;
	}

	////////////////
	// Management //
	////////////////

	signal reply
	signal retweet
	signal quote
	signal favorite
	signal unfavorite
}
