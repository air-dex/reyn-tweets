/// @file LoginPane.qml
/// @brief Widget displayed to enter user credentials during authentication.
///
/// The file was known as "LoginComponent.qml" until r220.
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
import "jstools.js" as Tools

/// @class LoginPane
/// @brief Component for entering user credentials during authentication
Rectangle {
	// Marging and spacing
	property int margin: 5
	property int spacing: 5

	/// @brief Height without invalid_password_text
	property int min_height: form_column.height + show_password_row.height + 2*margin + 2*spacing + auth_button.height

	/// @brief Property used to access to the control behind the pane
	property LoginControl ctrl: control

	Constants {	id:constant	}

	id: login_pane
	width: 360
	height: min_height
	color: constant.grey
	radius: 5

	Component.onCompleted: {
		// Wiring for authorizing or denying the application
		authorize.connect(control.authorizeReynTweets)
		deny.connect(control.denyReynTweets)
	}

	/// @brief Control behind the pane
	LoginControl {
		id: control
		onInvalidCredentials: login_pane.state = "invalid_password"
	}

	/// @fn signal authorize(string username, string password)
	/// @brief Sinal sent to allow Reyn Tweets to use a Twitter account.
	/// @param username User login (username or e-mail)
	/// @param password User's password
	signal authorize(string username, string password)

	/// @fn signal deny(string username, string password)
	/// @brief Sinal sent to deny Reyn Tweets.
	/// @param username User login (username or e-mail)
	/// @param password User's password
	signal deny(string username, string password)

	// Text displayed if the password is invalid
	Text {
		id: invalid_password_text
		color: "#ff0000"
		text: qsTr("Username or password invalid. Try again.")
		anchors.rightMargin: margin
		anchors.right: parent.right
		anchors.leftMargin: margin
		anchors.left: parent.left
		anchors.topMargin: margin
		anchors.top: parent.top
		font.bold: true
		font.family: constant.font
		font.pixelSize: constant.font_size
		visible: false
	}

	// Form to entre the user credentials
	Column {
		id: form_column

		anchors.rightMargin: margin
		anchors.leftMargin: margin
		anchors.right: parent.right
		anchors.left: parent.left
		spacing: login_pane.spacing
		height: login_field.height + form_column.spacing + password_field.height
		anchors.topMargin: margin
		anchors.top: parent.top

		// Field for username
		FormField {
			id: login_field
			color: login_pane.color
			clear_field: true
			anchors.right: parent.right
			anchors.left: parent.left
			legend: qsTr("Username or email:")
			field_left_margin: Tools.max(login_field.getLegendWidth(),
										 password_field.getLegendWidth())
		}

		// Field for password
		FormField {
			id: password_field
			color: login_pane.color
			clear_field: false
			anchors.left: parent.left
			anchors.right: parent.right
			legend: qsTr("Password:")
			field_left_margin: Tools.max(login_field.getLegendWidth(),
										 password_field.getLegendWidth())
		}
	}

	// Row to show (or to hide) the password
	Row {
		id: show_password_row
		height: legend.height
		anchors.leftMargin: margin
		anchors.left: parent.left
		anchors.rightMargin: margin
		anchors.right: parent.right
		anchors.top: form_column.bottom
		anchors.topMargin: login_pane.spacing
		spacing: login_pane.margin

		// Clickable check box
		Rectangle {
			property string hide_color: "#ffffff"
			property string show_color: constant.orange

			id: check_box
			width: legend.height
			height: width
			anchors.bottom: parent.bottom
			anchors.bottomMargin: 0
			anchors.top: parent.top
			anchors.topMargin: 0
			color:  password_field.clear_field ? show_color : hide_color
			border.width: 1
			border.color: "#000000"
			radius: 5

			MouseArea {
				id: toggle
				anchors.fill: parent
				onClicked: {
					password_field.clear_field = !password_field.clear_field
				}
			}
		}

		Text {
			id: legend
			text: qsTr("Show password")
			font.family: constant.font
			verticalAlignment: Text.AlignVCenter
			font.pixelSize: constant.font_size
		}
	}

	// Buttons to authorize or to deny Reyn Tweets
	RTButton {
		id: auth_button
		anchors.rightMargin: spacing
		anchors.right: deny_button.left
		button_text: qsTr("Authorize")
		anchors.bottomMargin: margin
		anchors.bottom: parent.bottom
		onClick: authorize(login_field.field_text, password_field.field_text)
	}

	RTButton {
		id: deny_button
		anchors.right: login_pane.right
		anchors.rightMargin: margin
		anchors.bottomMargin: margin
		anchors.bottom: parent.bottom
		button_text: qsTr("No, thanks")
		onClick: deny(login_field.field_text, password_field.field_text)
	}

	// States of the Component
	states: [
		State {
			// When the credentials are invalid
			name: "invalid_password"
			PropertyChanges {
				target: invalid_password_text
				visible: true
			}

			PropertyChanges {
				target: form_column
				anchors.top: invalid_password_text.bottom
				anchors.topMargin: spacing
			}

			PropertyChanges {
				target: login_pane
				height: min_height + spacing + invalid_password_text.height
			}
		},
		State {
			// When the validity of credentials is unknown
			name: "UnknownValidity"
			PropertyChanges {
				target: invalid_password_text
				visible: false
			}

			PropertyChanges {
				target: form_column
				anchors.topMargin: spacing
				anchors.top: login_pane.top
			}

			PropertyChanges {
				target: login_pane
				height: min_height
			}
		}
	]
}
