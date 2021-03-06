/// @file TweetPane.qml
/// @brief Pane to show a tweet
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
import ReynTweetsComponents 0.3
import "../base_components"

// Pane to show a tweet
Rectangle {
	id: tweet_pane

	// Size of a side of an avatar
	property int avatar_side: 50

	// Size of a side of an avatar
	property int margin: constant.margin

	// The tweet displayed in this pane
	readonly property alias tweet: control.tweet

	// Tweet
	readonly property alias shown_tweet: control.shown_tweet

	// Model of the tweet
	property alias tweet_model: control.tweet_model

	// User behind the timeline
	property UserInfos current_user: settings_control.configuration.user_account.current_user

	// Minimal height
	property int min_height: author_identity.height + author_screen_name.height
							 + text.height + source_text.height
							 + action_row.height + 10*margin

	// Is the user the author of the tweet ?
	property bool iam_author: shown_tweet.user.id_str === current_user.id_str

	// Type of the timeline where the tweet is displayed
	property alias timeline_type: control.timeline_type

	// Folder where the icons are stored
	property string icons_folder: "../../..".concat(constant.icon_folder)

	width: constant.reyn_tweets_width
	height:  min_height
			 + (shown_tweet.isReply() ?
					(reply_info.height + margin)
				  : 0
				)
			 + (shown_tweet.isRetweetedByPeople() || shown_tweet.retweeted || tweet.isRetweet() ?
					(retweet_info.height + margin)
				  : 0
				)

	// Constants of Reyn Tweets
	Constants { id:constant }

	// Control behind the pane
	TweetControl {
		id: control
		onTweetChanged: {
			tweet_pane.state = "Scratch"
			displayTweet()
		}
	}

	// Background of the tweet

	// Background colors of the tweet
	property string separator_color: constant.very_light_grey
	property string middle_color: constant.white

	// Width of top and bottom borders / pane height.
	property real separator: 2 / tweet_pane.height

	// Background Gradation
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
			source: shown_tweet.user.profile_image_url
			MouseArea {
				id: avatar_mouse_area
				anchors.fill: parent
				onClicked: {
					Qt.openUrlExternally("https://twitter.com/#!/" + shown_tweet.user.screen_name)	// MOCKUP
					console.log("TODO : Show @" + shown_tweet.user.screen_name)
				}
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
				onClicked: {
					Qt.openUrlExternally("https://twitter.com/#!/" + tweet.user.screen_name)	// MOCKUP
					console.log("TODO : Show @" + tweet.user.screen_name)
				}
			}
		}
	}

	// More actions (refresh and share)
	Row {
		id: more_zone
		anchors.top: avatar_zone.bottom
		anchors.topMargin: margin
		anchors.horizontalCenter: avatar_zone.horizontalCenter
		spacing: 2*margin

		// Image to refresh the tweet
		Image {
			id: refresh_tweet
			source: tweet_pane.icons_folder.concat("/refresh.png")

			// Click to refresh the tweet
			MouseArea {
				anchors.fill: parent
				onClicked: control.refresh();
			}
		}

		// Image to share the tweet (by mail)
		Image {
			id: share_tweet
			source: tweet_pane.icons_folder.concat("/share.png")

			// Click to refresh the tweet
			MouseArea {
				anchors.fill: parent
				onClicked: control.shareByMail()
			}
		}
	}

	// Label displaying the tweet author's identity
	Text {
		id: author_identity
		text: wrapEntity(shown_tweet.user.name)
		textFormat: Text.RichText
		elide: Text.ElideRight
		font.bold: true
		font.underline: false
		verticalAlignment: Text.AlignVCenter
		font.family: constant.font
		font.pointSize: constant.font_size
		anchors.topMargin: 2*margin
		anchors.top: parent.top
		anchors.left: avatar_zone.right
		// More margin to not move if it is a retweet.
		anchors.leftMargin: 2*margin + tweet_pane.avatar_side /4
		anchors.right: date_text.left
		anchors.rightMargin: 2*margin
		onLinkActivated: {
			Qt.openUrlExternally("https://twitter.com/#!/" + shown_tweet.user.screen_name)	// MOCKUP
			console.log('TODO : show user ' + shown_tweet.user.name)
		}
	}

	// Label displaying the tweet author's screen name
	Text {
		id: author_screen_name
		text: wrapEntity('@'.concat(shown_tweet.user.screen_name))
		textFormat: Text.RichText
		elide: Text.ElideRight
		//font.bold: true
		font.underline: false
		verticalAlignment: Text.AlignVCenter
		font.family: constant.font
		font.pointSize: constant.font_size_xs
		anchors.topMargin: margin
		anchors.top: author_identity.bottom
		anchors.left: author_identity.left
		anchors.right: author_identity.right
		onLinkActivated: {
			Qt.openUrlExternally("https://twitter.com/#!/" + shown_tweet.user.screen_name)	// MOCKUP
			console.log('TODO : show user @' + shown_tweet.user.screen_name)
		}
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
		font.pointSize: constant.font_size
		onLinkActivated: Qt.openUrlExternally(link)
	}

	// Content of the tweet
	Text {
		id: text
		text: shown_tweet.getDisplayText();
		textFormat: Text.RichText
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
		font.family: constant.font
		font.pointSize: constant.font_size
		anchors.left: author_identity.left
		anchors.leftMargin: 0
		anchors.top: author_screen_name.bottom
		anchors.topMargin: 2*margin
		anchors.right: tweet_pane.right
		anchors.rightMargin: margin
		onLinkActivated: {
			if (link.length <= 0) return;

			switch (link[0]) {
				case '#':
					// It is an hashtag. Launch a search about it !
					Qt.openUrlExternally("http://twitter.com/#!/search/\%23" + link.substr(1))	// MOCKUP
					console.log("TODO : search hashtag " + link)
					break;

				case '@':
					// It is a mentionned used. Show him !
					Qt.openUrlExternally("https://twitter.com/#!/" + link.substr(1))	// MOCKUP
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
		text: "via ".concat(shown_tweet.getDisplaySource())
		textFormat: Text.RichText

		font {
			family: constant.font
			pointSize: constant.font_size_s
			italic: true
		}

		anchors {
			left: author_identity.left
			top: text.bottom
			right: tweet_pane.right
			leftMargin: 0
			topMargin: margin
			rightMargin: margin
		}

		onLinkActivated: Qt.openUrlExternally(link)
	}

	// Reply informations
	Text {
		id: reply_info
		text: buildImageTag(tweet_pane.icons_folder.concat("/reply_on.png"))
			.concat(' ').concat(qsTr("In reply to "))
			.concat(wrapEntity('@' + shown_tweet.in_reply_to_screen_name))
			.concat('. ').concat(wrapEntity(qsTr("Show conversation")))
			.concat('.')
		textFormat: Text.RichText
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
		visible: false
		font.family: constant.font
		font.pointSize: constant.font_size_s
		anchors.left: author_identity.left
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
					Qt.openUrlExternally("https://twitter.com/#!/" + link.substr(1))	// MOCKUP
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
		text: retweetInfoText();
		textFormat: Text.RichText
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
		visible: false
		font.family: constant.font
		font.pointSize: constant.font_size_s
		anchors.left: author_identity.left
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
					Qt.openUrlExternally("https://twitter.com/#!/" + link.substr(1))	// MOCKUP
					console.log("TODO : show " + link)
					break;

				default:
					// Show other people that have retweeted
					console.log("TODO : who retweeted ?")
					break;
			}
		}

		property string icon_source: tweet_pane.icons_folder.concat("/retweet_off.png")

		// Text to announce the retweeters
		function retweetInfoText() {
			// The beginning (icon + first words)
			var message = buildImageTag(retweet_info.icon_source)
			message = message.concat(' ').concat(qsTr("Retweeted by"))


			// Known people who retweeted
			var knownPeopleArray = new Array()
			var spottedAsRetweeter = false

			// Nb of other people that retweeted
			var nbOtherRetweeters = shown_tweet.retweet_count

			// 1°) The official retweeter
			if (tweet.isRetweet()) {
				var myID = current_user.id_str
				var name;

				if (myID === tweet.user.id_str) {
					name = qsTr("me")
					spottedAsRetweeter = true
				} else {
					name = wrapEntity('@' + tweet.user.screen_name)
					nbOtherRetweeters = nbOtherRetweeters - 1
				}

				knownPeopleArray.push(name);
			}

			// 2°) Me if I retweeted the tweet.
			// No need to tell it again if I am the the official retweeter.
			if (tweet.retweeted && !spottedAsRetweeter) {
				knownPeopleArray.push(qsTr("me"))
				spottedAsRetweeter = true
			}

			// Writing known retweeters
			var separator

			if (nbOtherRetweeters > 0) {
				// First retweeters, separated by a comma
				separator = ", "
			} else {
				// The two only retweeters : "1°) and 2°)"
				separator = ' '.concat(qsTr("and")).concat(' ')
			}

			message = message.concat(' ').concat(knownPeopleArray.join(separator))


			// If other people retweeted
			if (nbOtherRetweeters > 0) {
				// Enclosing in a tag to show retweeters
				message = message.concat(' <a href="showRTers" style="color: ')
				message = message.concat(shown_tweet.user.profile_link_color)
				message = message.concat(' ; text-decoration: none">')

				var theseAreOtherRetweeters = knownPeopleArray.length > 0

				// No "and" if nobody was written before.
				if (theseAreOtherRetweeters) {
					message = message.concat(qsTr("and")).concat(' ')
				}

				// Writing the number of other people
				message = message.concat(nbOtherRetweeters.toString())
				message = message.concat(' ')

				var otherString;	// String whose content is "other(s)"
				var peopleString;	// String whose content is "person(s)"

				// Singular or plural ?
				if (nbOtherRetweeters == 1) {
					// one other person
					otherString = qsTr("other")
					peopleString = qsTr("person")
				} else {
					// other people
					otherString = qsTr("others")
					peopleString = qsTr("people")
				}

				// Writing "other(s)" if necessary
				if (theseAreOtherRetweeters) {
					message = message.concat(otherString).concat(' ')
				}

				message = message.concat(peopleString)

				// Closing the tag
				message = message.concat('</a>')
			}

			message = message.concat('.')

			return message
		}
	}

	// Getting the settings
	SettingsControl { id: settings_control }

	// Row with actions on the tweet
	Row {
		id: action_row
		spacing: margin
		anchors.bottom: parent.bottom
		anchors.bottomMargin: 2*margin
		anchors.horizontalCenter: parent.horizontalCenter

		// Reply
		ActionElement {
			id: reply_action
			image_source: tweet_pane.icons_folder.concat("/reply_off.png")
			legend: qsTr("Reply")
			onAct: reply(shown_tweet.user.screen_name, shown_tweet.id_str)

			property string reply_switch: "off"
		}

		// Delete tweet
		ActionElement {
			id: delete_action
			image_source: tweet_pane.icons_folder.concat("/wastebin.png")
			legend: qsTr("Delete")
			onAct: {
				control.deleteTweet();
			}

			visible: iam_author
		}

		// Retweet
		ActionElement {
			id: retweet_action
			image_source: tweet_pane.icons_folder.concat("/retweet_off2.png")
			legend: shown_tweet.retweeted ? qsTr("Retweeted") : qsTr("Retweet")
			onAct: {
				if (shown_tweet.retweeted) {
					control.deleteTweet();
				} else {
					control.retweet();
				}
			}

			visible: !iam_author
		}

		// Quote
		ActionElement {
			id: quote_action
			image_source: tweet_pane.icons_folder.concat("/quote.png")
			legend: qsTr("Quote")
			onAct: {
				quote('RT @'.concat(shown_tweet.user.screen_name).concat(': ').concat(shown_tweet.getPlainDisplayText()));
			}
		}

		// Favorite
		ActionElement {
			id: favorite_action
			image_source: tweet_pane.icons_folder.concat("/favorite_").concat(fav_suffix).concat(".png")
			legend: shown_tweet.favorited ? qsTr("Favorited") : qsTr("Favorite")
			onAct: {
				if (shown_tweet.favorited) {
					control.unfavorite()
				} else {
					control.favorite()
				}
			}

			property string fav_suffix: shown_tweet.favorited ? "on" : "off"
		}
	}

	states: [
		// Base state : classic tweet
		State {
			name: "Scratch"

			StateChangeScript {
				name: "base_script"
				script: resetToStart();
			}
		},

		// The tweet is a retweet
		State {
			name: "Retweet"

			StateChangeScript {
				name: "retweet_script"
				script: {
					// Displaying the retweet author's avatar
					avatar_zone.side = tweet_pane.avatar_side * 6/5

					// Kept to load the image if necessary
					retweeter_avatar.visible = true
					retweeter_avatar.source = tweet.user.profile_image_url

					// New author and new margin to not move the QML Component
					author_identity.anchors.leftMargin = 2*margin
				}
			}
		},

		// The tweet was retweeted by the user
		State {
			name: "RetweetedByMe"

			StateChangeScript {
				name: "rt_by_me_script"
				script: {
					retweet_action.legend = qsTr("Retweeted");
					retweet_action.image_source = tweet_pane.icons_folder.concat("/retweet_on2.png")
					retweet_info.icon_source = tweet_pane.icons_folder.concat("/retweet_on.png")
				}
			}
		},

		// The tweet was not retweeted by the user
		State {
			name: "NotRetweetedByMe"

			StateChangeScript {
				name: "not_rt_by_me_script"
				script: {
					retweet_action.legend = qsTr("Retweet");
					retweet_action.image_source = tweet_pane.icons_folder.concat("/retweet_off2.png")
					retweet_info.icon_source = tweet_pane.icons_folder.concat("/retweet_off.png")
				}
			}
		},

		// The tweet was retweeted by the user
		State {
			name: "FavoritedByMe"

			StateChangeScript {
				name: "rt_fav_me_script"
				script: {
					favorite_action.legend = qsTr("Favorited");
					retweet_action.image_source = tweet_pane.icons_folder.concat("/retweet_on2.png")
					retweet_info.icon_source = tweet_pane.icons_folder.concat("/retweet_on.png")
				}
			}
		},

		// The tweet was not retweeted by the user
		State {
			name: "NotFavoritedByMe"

			StateChangeScript {
				name: "not_fav_by_me_script"
				script: {
					retweet_action.legend = qsTr("Favorite");
					retweet_action.image_source = tweet_pane.icons_folder.concat("/retweet_off2.png")
					retweet_info.icon_source = tweet_pane.icons_folder.concat("/retweet_off.png")
				}
			}
		},

		// The tweet is a reply to a user
		State {
			// The tweet is a reply
			name: "Reply"

			StateChangeScript {
				name: "reply_script"
				script: {
					// Showing reply text
					reply_info.visible = true;
					reply_info.anchors.topMargin = margin;

					// Putting retweet_info under reply_info
					retweet_info.anchors.top = reply_info.bottom;
				}
			}
		},

		// The tweet is a direct message to the user
		State {
			// The tweet is a direct message (DM)
			name: "DirectMessage"

			StateChangeScript {
				name: "dm_script"
				script: {
					tweet_pane.separator_color = constant.blue_dm;
					tweet_pane.middle_color = constant.light_blue_dm;
				}
			}
		},

		// Tweet mentionning the user
		State {
			// The tweet is a mention
			name: "Mention"

			StateChangeScript {
				name: "mention_script"
				script: {
					tweet_pane.separator_color = constant.green_mention;
					tweet_pane.middle_color = constant.light_green_mention;
				}
			}
		},

		// Tweet whose author is the user
		State {
			// The tweet is a mention
			name: "Author"

			StateChangeScript {
				name: "author_script"
				script: {
					tweet_pane.separator_color = constant.orange_author;
					tweet_pane.middle_color = constant.light_orange_author;
				}
			}
		}
	]

	Component.onCompleted: {
		// Wiring
		control.destroyTweet.connect(tweet_pane.destroyTweet)
		control.actionEnded.connect(tweet_pane.endTweeting)
		control.authenticationNeeded.connect(tweet_pane.needAuthentication)
		control.showInfoMessage.connect(tweet_pane.showInfoMessage)
		control.updateTimeline.connect(tweet_pane.commitTweet)

		displayTweet();
	}

	function displayTweet() {
		// TODO when new features : Direct Messages

		// Detects automatically if it's a retweet (put in "Retweet" state)
		if (tweet_pane.tweet.isRetweet()) {
			tweet_pane.state = "Retweet"
		}

		// Was it retweeted by the user ?
		var prefix = tweet.retweeted ? "" : "Not"
		tweet_pane.state = prefix + "RetweetedByMe"

		// Treatments if it is a reply
		if (shown_tweet.isReply()) {
			tweet_pane.state = "Reply"
		}

		// Treatments if it is a retweet
		if (shown_tweet.isRetweetedByPeople()
				|| tweet_pane.tweet.isRetweet()
				|| shown_tweet.retweeted)
		{
			// The retweeter is not in retweet_count. So there is a problem if
			// the author of the retweet is the only retweeter.
			retweet_info.visible = true
			retweet_info.anchors.topMargin = margin
		}

		if (control.isMention()) {
			tweet_pane.state = "Mention"
		}

		if (iam_author)  {
			tweet_pane.state = "Author"
		}
	}

	function resetToStart() {
		avatar_zone.side = tweet_pane.avatar_side
		retweeter_avatar.visible = false
		retweeter_avatar.source = ""
		author_identity.anchors.leftMargin = 2*margin + tweet_pane.avatar_side /4
		reply_info.visible = false
		reply_info.anchors.topMargin = 0
		retweet_info.visible = false
		retweet_info.anchors.top = source_text.bottom
		tweet_pane.separator_color = constant.very_light_grey
		tweet_pane.middle_color = constant.white
	}

	// Function to wrap words into an HTML tag
	function wrapEntity(entity) {
		var beginTag = '<a style="text-decoration: none; color: ';
		var hrefTag = '" href="';
		var closeTag = '">';
		var endTag = '</a>';

		return beginTag + shown_tweet.user.profile_link_color
				+ hrefTag + entity + closeTag + entity + endTag;
	}

	function buildImageTag(imageSrc) {
		return '<img src="' + imageSrc + '">'
	}

	/////////////
	// Signals //
	/////////////

	// Reply to a tweet
	signal reply(string screenName, string replyToTweetID)

	// Quoting a tweet
	signal quote(string text)

	// Destroying a tweet
	signal destroyTweet(variant destroyTweet)

	// Launch an authentication
	signal needAuthentication

	// After an action was made
	signal endTweeting(bool endOK, string endMsg, bool fatalEnd)

	// Showing an information message
	signal showInfoMessage(string infoMsg)

	// Updating a tweet in the timeline
	signal commitTweet(variant status)
}
