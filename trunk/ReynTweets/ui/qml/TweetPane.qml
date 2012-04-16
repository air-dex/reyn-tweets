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
	property Tweet tweet

	// The tweet displayed in this pane
	property Tweet shown_tweet: tweet

	property UserInfos me: settings_control.configuration.current_account.current_user

	property string separator_color: constant.very_light_grey

	property string middle_color: constant.white

	// Minimal height
	property int min_height: author_text.height + text.height
							 + source_text.height + action_row.height + 9*margin

	property bool iam_author: shown_tweet.author.id_str ==
							  settings_control.configuration.current_account.current_user.id_str

	width: 360
	height:  min_height
			 + (shown_tweet.isReply() ?
					(reply_info.height + margin)
				  : 0
				)
			 + (shown_tweet.isRetweetedByPeople() || tweet.isRetweet() ?
					(retweet_info.height + margin)
				  : 0
				)

	// Width of top and bottom borders / pane height.
	property real separator: 2 / tweet_pane.height

	gradient: Gradient {
		GradientStop {
			position: 0
			color: constant.black
		}

		GradientStop {
			position: separator
			color: separator_color
		}

		GradientStop {
			position: 0.5
			color: middle_color
		}

		GradientStop {
			position: 1-separator
			color: separator_color
		}

		GradientStop {
			position: 1
			color: constant.black
		}
	}

	Constants { id:constant }

	// Control behind the pane
	TweetControl {
		id: control
		tweet: tweet_pane.tweet
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
		anchors.topMargin: 2*margin
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
		elide: Text.ElideRight
		font.bold: true
		font.underline: false
		verticalAlignment: Text.AlignVCenter
		font.family: constant.font
		font.pixelSize: constant.font_size
		anchors.topMargin: 2*margin
		anchors.top: parent.top
		anchors.left: avatar_zone.right
		// More margin to not move if it is a retweet.
		anchors.leftMargin: 2*margin + tweet_pane.avatar_side /4
		anchors.right: date_text.left
		anchors.rightMargin: 2*margin
		onLinkActivated: console.log('TODO : show user @' + shown_tweet.author.screen_name)
	}

	// Label displaying when the tweet was posted
	Text {
		id: date_text
		text: shown_tweet.whenWasItPosted();
		textFormat: Text.RichText
		font.family: constant.font
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignRight
		anchors.top: parent.top
		anchors.topMargin: 2*margin
		anchors.right: parent.right
		anchors.rightMargin: margin
		font.pixelSize: constant.font_size
		onLinkActivated: Qt.openUrlExternally(link)
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
					console.log("TODO : search hashtag " + link)
					break;

				case '@':
					// It is a mentionned used. Show him !
					console.log("TODO : show user " + link)
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
		font.pixelSize: constant.font_small_size
		anchors.left: author_text.left
		anchors.leftMargin: 0
		anchors.top: text.bottom
		anchors.topMargin: margin
		anchors.right: tweet_pane.right
		anchors.rightMargin: margin
		onLinkActivated: Qt.openUrlExternally(link)
	}

	// Reply informations
	Text {
		id: reply_info
		text: buildImageTag("../../resources/icons/reply_on.png")
			  + ' ' + qsTr("In reply to ")
			  + wrapEntity('@' + shown_tweet.in_reply_to_screen_name)
			  + '. ' + wrapEntity(qsTr("Show conversation")) + '.'
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
		visible: false
		font.family: constant.font
		font.pixelSize: constant.font_small_size
		anchors.left: author_text.left
		anchors.leftMargin: 0
		anchors.top: source_text.bottom
		anchors.topMargin: 0
		anchors.right: tweet_pane.right
		anchors.rightMargin: margin
		onLinkActivated: {
			if (link.length <= 0) return;

			switch (link[0]) {
				case '@':
					// It is a mentionned used. Show him !
					console.log("TODO : show " + link)
					break;

				default:
					// It is an URL. Show its content in a browser !
					console.log("TODO : show the conversation")
					break;
			}
		}
	}

	// Retweet informations
	Text {
		id: retweet_info
		text: buildImageTag("../../resources/icons/retweet_"
							+ retweet_action.rt_suffix + ".png")
			  + ' ' + retweetInfoText();
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
		visible: false
		font.family: constant.font
		font.pixelSize: constant.font_small_size
		anchors.left: author_text.left
		anchors.leftMargin: 0
		anchors.top: source_text.bottom
		anchors.topMargin: 0
		anchors.right: tweet_pane.right
		anchors.rightMargin: margin
		onLinkActivated: {
			if (link.length <= 0) return;

			switch (link[0]) {
				case '@':
					// The retweeter was mentionned. Show him !
					console.log("TODO : show " + link)
					break;

				default:
					// Show other people that have retweeted
					console.log("TODO : who retweeted ?")
					break;
			}
		}

		// Text to announce the retweeters
		function retweetInfoText() {
			var message = qsTr("Retweeted by")

			// Nb of other people that retweeted
			var nbOtherRetweeters = shown_tweet.retweet_count
			var spottedAsRetweeter = false

			// Catching the potential retweeter if it is a retweet
			if (tweet.isRetweet()) {
				// There is at least one retweeter : the one that bring it to the TL.
				var myID = settings_control.configuration.current_account.current_user.id_str

				var iamTheRetweeter = (myID == tweet.author.id_str)
				spottedAsRetweeter = iamTheRetweeter

				if (iamTheRetweeter) {
					message = message + ' ' + qsTr("me")
				} else {
					message = message + ' '
							+ wrapEntity('@' + tweet.author.screen_name)
					nbOtherRetweeters--
				}
			}

			// Did I retweet this ? No need to tell it again if I am the retweeter.
			if (tweet.retweeted && !spottedAsRetweeter) {
				if (tweet.isRetweet()) {
					// The author of the retweet is already written. Let's write a comma after its name
					message = message + ','
				}

				message = message + ' ' + qsTr("me")
				spottedAsRetweeter = true
			}

			// Writing if other people retweeted
			if (nbOtherRetweeters > 0) {
				// Enclosing in a tag to show retweeters
				message = message + ' <a href="showRTers" style="color: '
						+ shown_tweet.author.profile_link_color
						+ ' ; text-decoration: none">'

				// People already written in var message
				var peopleAlreadyCaught = shown_tweet.retweet_count - nbOtherRetweeters
				var singularForOtherRTers = (nbOtherRetweeters == 1)

				if (peopleAlreadyCaught > 0) {
					var otherString = singularForOtherRTers ? qsTr("other") : qsTr("others")
					message = message + qsTr("and") + ' ' + nbOtherRetweeters
							+ ' ' + otherString
				} else {
					message = message + nbOtherRetweeters
				}

				var peopleString = singularForOtherRTers ? qsTr("person") : qsTr("people")
				message = message + ' ' + peopleString + '</a>'
			}

			message = message + '.'

			return message
		}
	}

	SettingsControl { id: settings_control }

	// Row with actions on the tweet
	Row {
		id: action_row
		spacing: 2*margin
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 2*margin
		anchors.horizontalCenter: parent.horizontalCenter

		// Reply
		ActionElement {
			id: reply_action
			image_source: "../../resources/icons/reply_off.png"
			legend: qsTr("Reply")
			onAct: {
				reply('@' + shown_tweet.author.screen_name + ' ',
					  shown_tweet.id_str)
			}

			property string reply_switch: "off"
		}

		// Delete tweet
		ActionElement {
			id: delete_action
			image_source: "../../resources/icons/wastebin.png"
			legend: qsTr("Delete")
			onAct: {
				console.log("TODO : delete the tweet (or not)")
			}

			property string rt_suffix: tweet.retweeted ? "on" : "off"

			visible: iam_author
		}

		// Retweet
		ActionElement {
			id: retweet_action
			image_source: "../../resources/icons/retweet_" + rt_suffix + "2.png"
			legend: (tweet.retweeted) ? qsTr("Retweeted") : qsTr("Retweet")
			onAct: {
				console.log("TODO : retweet the tweet (or not)")
				//control.retweet();
			}

			property string rt_suffix: tweet.retweeted ? "on" : "off"

			visible: !iam_author
		}

		// Quote
		ActionElement {
			id: quote_action
			image_source: "../../resources/icons/quote.png"
			legend: qsTr("Quote")
			onAct: {
				quote('RT @' + tweet.author.screen_name + ' ' + shown_tweet.text);
			}

			visible: !iam_author
		}

		// Favorite
		ActionElement {
			id: favorite_action
			image_source: "../../resources/icons/favorite_" + fav_suffix + ".png"
			legend: (tweet.favorited) ? qsTr("Favorited") : qsTr("Favorite")
			onAct: {
				if (tweet.favorited) {
					control.unfavorite()
				} else {
					control.favorite()
				}
			}

			property string fav_suffix: tweet.favorited ? "on" : "off"
		}
	}

	// TODO : for treatments like authentication and errors

	states: [
		// Base state : classic tweet

		// The tweet is a retweet
		State {
			// The tweet is a retweet
			name: "Retweet"
			when: tweet.isRetweet()

			// Displaying the retweet author's avatar
			PropertyChanges {
				target: tweet_pane
				shown_tweet: tweet.retweet
				restoreEntryValues: false
			}

			// Displaying the retweet author's avatar
			PropertyChanges {
				target: avatar_zone
				side: tweet_pane.avatar_side * 6/5
				restoreEntryValues: false
			}

			// Kept to load the image if necessary
			PropertyChanges {
				target: retweeter_avatar
				visible: true
				source: tweet.author.profile_image_url
				restoreEntryValues: false
			}

			// New author and new margin to not move the QML Component
			PropertyChanges {
				target: author_text
				anchors.leftMargin: 2*margin
				restoreEntryValues: false
			}
		},

		// The tweet is a reply to a user
		State {
			// The tweet is a reply
			name: "Reply"

			// Showing reply text
			PropertyChanges {
				target: reply_info
				visible: true
				anchors.topMargin: margin
				restoreEntryValues: false
			}

			// Putting retweet_info under reply_info
			PropertyChanges {
				target: retweet_info
				anchors.top: reply_info.bottom
				restoreEntryValues: false
			}
		},

		// The tweet is a direct message to the user
		State {
			// The tweet is a direct message (DM)
			name: "DirectMessage"

			PropertyChanges {
				target: tweet_pane
				separator_color: constant.blue_dm
				middle_color: constant.light_blue_dm
				restoreEntryValues: false
			}
		},

		// Tweet mentionning the user
		State {
			// The tweet is a mention
			name: "Mention"

			PropertyChanges {
				target: tweet_pane
				separator_color: constant.green_mention
				middle_color: constant.light_green_mention
				restoreEntryValues: false
			}
		}
	]

	Component.onCompleted: {
		// TODO : Direct Messages

		// Detects automatically if it's a retweet (put in "Retweet" state)

		// Treatments if it is a reply
		if (shown_tweet.isReply()) {
			tweet_pane.state = "Reply"
		}


		// Treatments if it is a retweet
		if (shown_tweet.isRetweetedByPeople()
				|| tweet_pane.state == "Retweet")
		{
			// The retweeter is not in retweet_count. So there is a problem if
			// the author of the retweet is the only retweeter.
			retweet_info.visible = true
			retweet_info.anchors.topMargin = margin
		}

		//console.log("Le tweet " + shown_tweet.id_str + " est-il une mention ?")
		if (control.isMention()) {
			//console.log("Le tweet " + shown_tweet.id_str + " est une mention.")
			tweet_pane.state = "Mention"
		}
	}

	// Function to wrap words into an HTML tag
	function wrapEntity(entity) {
		var beginTag = '<a style="text-decoration: none; color: ';
		var hrefTag = '" href="';
		var closeTag = '">';
		var endTag = '</a>';
		return beginTag + shown_tweet.author.profile_link_color
				+ hrefTag + entity + closeTag + entity + endTag;
	}

	function buildImageTag(imageSrc) {
		return '<img src="' + imageSrc + '">'
	}


	////////////////
	// Management //
	////////////////

	// Sends base to write
	signal reply(string screenName, string replyToTweetID)
	signal quote(string text)
}
