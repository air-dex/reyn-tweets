/// @file LoginPane.qml
/// @brief Widget displayed to enter user credentials during authentication.
///
/// The file was known as "LoginComponent.qml" until r220.
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
import QtWebKit 3.0	// For the new one
import ReynTweetsControls 0.2
import "../base_components"

/// @class LoginPane
/// @brief Component for entering user credentials during authentication
Rectangle {
	id: login_pane

	width: 360
	height: 640
	property int margin: 5

	color: constant.orange_author
	radius: login_pane.margin

	Constants { id: constant }

	///////////////////
	// Widget design //
	///////////////////

	WebView {
		id: twitter_page

		anchors {
			top: login_pane.top
			left: login_pane.left
			right: login_pane.right
			bottom: quit_button.top
			margins: login_pane.margin
		}
	}

	// Reloads the authentication page
	RTButton {
		id: reload_button

		anchors {
			right: quit_button.left
			bottom: login_pane.bottom
			margins: login_pane.margin
		}

		button_text: qsTr("Reload")

		onClick: {
			// TODO : just load the html
			twitter_page.reload()
		}
	}

	// Quit the application
	RTButton {
		id: quit_button

		anchors {
			right: login_pane.right
			bottom: login_pane.bottom
			margins: login_pane.margin
		}

		button_text: qsTr("Quit")

		onClick: {
			// TODO: just quit the authentication
			Qt.quit();
		}
	}


	/////////////////////
	// Core management //
	/////////////////////

	// HTML code of the authorizing page generated by Twitter
	property string authorize_html: ""

	// Base URL of the authorize page
	property string base_url: ""

	// Alias on the control
	property AllowControl allow_control

	Component.onCompleted: {
		// Wiring
		twitter_page.urlChanged.connect(goReload)
	}

	states: [
		// Default state : between two user authorizations
		State {
			name: ""

			PropertyChanges {
				target: login_pane
				visible: false
				authorize_html: ""
				base_url: "about:blank"
			}

			PropertyChanges {
				target: twitter_page
				url: "about:blank"
				/*onUrlChanged: {
					goReload()
				}

				onLoadFinished: {}*/
			}

			// Page reloading
			StateChangeScript {
				name: "reload_for_css"

				script: {
					twitter_page.loadFinished.disconnect(postAuthorize)
					twitter_page.urlChanged.disconnect(afterAuth)
					twitter_page.urlChanged.connect(goReload)
				}
			}
		},

		// Reloads the page to display CSS correctly
		// (don't know why it needs a reload to display)
		State {
			name: "reload_state"

			// Do the user authorization once it's reloaded
			PropertyChanges {
				target: twitter_page
/*
				onUrlChanged: {}

				onLoadFinished: postAuthorize()*/
			}

			// Page reloading
			StateChangeScript {
				name: "reload_for_css"

				script: {
					twitter_page.urlChanged.disconnect(goReload)
					twitter_page.loadFinished.connect(postAuthorize)
					twitter_page.reload()
				}
			}
		},

		// User authorization (aka POST authorizing)
		State {
			name: "post_authorizing"

			PropertyChanges {
				target: login_pane
				visible: true
			}

			PropertyChanges {
				target: twitter_page
/*
				onUrlChanged: {
					afterAuth()
				}

				onLoadFinished: {}*/
			}

			StateChangeScript {
				name: "postauthorize_wirings"

				script: {
					twitter_page.loadFinished.disconnect(postAuthorize)
					twitter_page.urlChanged.connect(afterAuth)
				}
			}
		}
	]

	// Displays the page generated by Twitter to Authorize (or deny) Reyn Tweets
	function showAuthPage(html, baseURL) {
		login_pane.authorize_html = html
		login_pane.base_url = baseURL
		loadAuthorizePage()
	}

	// Loading the page to authorize
	function loadAuthorizePage() {
		twitter_page.loadHtml(login_pane.authorize_html,
							  "",
							  login_pane.base_url)
	}

	function goReload() {
		if (twitter_page.url === login_pane.base_url) {
			login_pane.state = "reload_state";
		}
	}

	function postAuthorize() {
		login_pane.state = "post_authorizing";
	}

	function afterAuth() {
		if (allow_control.endAuth(twitter_page.url)) {
			login_pane.state = "";
		}
	}
}
