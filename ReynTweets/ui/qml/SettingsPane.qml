/// @file SettingsPane.qml
/// @brief Pane displaying settings
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
import "jstools.js" as Tools

Rectangle {
	id: settings_pane

	width: constant.reyn_tweets_width
	height: constant.reyn_tweets_height

	// Generic margin
	property int margin: 5

	// Display constants
	radius: 2*margin
	color: constant.orange_author

	// Reyn Tweets constants
	Constants { id: constant }

	// Control dealing with settings
	SettingsControl {
		id: settings_control
	}

	Text {
		id: header_text
		text: qsTr("Settings")
		horizontalAlignment: Text.AlignHCenter
		anchors.top: settings_pane.top
		anchors.topMargin: margin
		anchors.horizontalCenter: settings_pane.horizontalCenter
		font.family: constant.font
		font.pixelSize: constant.font_size
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
	}

	// Going to the top of the timeline while clicking on the header
	MouseArea {
		anchors.top: parent.top
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: settings_flick.top
		onClicked: settings_flick.contentY = 0
	}

	// Flickable with the rectangle containing all the settings
	Flickable {
		id: settings_flick
		width: parent.width
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.top: header_text.bottom
		anchors.topMargin: margin
		anchors.bottom: cancel_button.top
		anchors.bottomMargin: margin
		clip: true


		contentWidth: settings_board.width
		contentHeight: settings_board.height

		// Pane with all the settings
		Rectangle {
			id: settings_board
			width: settings_pane.width
			height: say_hello.height + 2*margin
			z: settings_flick.z + 1
			color: constant.orange//_author

			// Hello message
			Item {
				id: say_hello
				width: parent.width
				implicitHeight: say_hello_setting.height + say_hello_chars_left.implicitHeight + margin
				anchors.horizontalCenter: parent.horizontalCenter
				anchors.top: settings_board.top
				anchors.topMargin: margin

				// Field to modify it
				FormField {
					id: say_hello_setting
					width: parent.width
					anchors.top: parent.top
					anchors.horizontalCenter: parent.horizontalCenter
					color: settings_board.color

					legend: qsTr("Hello message :")
				}

				// Number of characters that the user can write in this message
				property int say_hello_chars_nb: Tools.getCharactersLeft(say_hello_setting.field_text)

				Text {
					id: say_hello_chars_left
					anchors.right: say_hello_setting.right
					anchors.top: say_hello_setting.bottom
					anchors.topMargin: margin
					anchors.bottom: say_hello.bottom

					text: say_hello.say_hello_chars_nb
					font.family: constant.font
					font.pixelSize: constant.font_small_size
					wrapMode: Text.WrapAtWordBoundaryOrAnywhere
					font.bold: say_hello.say_hello_chars_nb < 0
					color: say_hello.say_hello_chars_nb < 0 ?
							   constant.red
							 : constant.black
				}
			}
		}
	}


	///////////////////////
	// Settings handling //
	///////////////////////

	// Loading configuration in the pane
	function loadSavedConfiguration() {
		say_hello_setting.field_text = settings_control.configuration.current_account.hello_message
	}

	// Writing configuration with settings written in the pane
	function overWriteConfiguration() {
		settings_control.configuration.current_account.hello_message = say_hello_setting.field_text
	}

	Component.onCompleted: {
		// Wiring
		settings_control.actionEnded.connect(settings_pane.endAction)
		settings_control.showInfoMessage.connect(settings_pane.showInfoMessage)
	}

	onVisibleChanged: {
		if (settings_pane.visible) {
			loadSavedConfiguration()
		}
	}

	// Save changes
	RTButton {
		id: commit_button
		anchors.right: cancel_button.left
		anchors.rightMargin: margin
		anchors.verticalCenter: cancel_button.verticalCenter
		button_text: qsTr("OK")
		onClick: {
			commit()
			settings_pane.visible = false
		}
	}

	function commit() {
		overWriteConfiguration()
		settings_control.saveChanges()
	}

	// Cancel changes
	RTButton {
		id: cancel_button
		anchors.rightMargin: margin
		anchors.right: parent.right
		anchors.bottomMargin: margin
		anchors.bottom: parent.bottom
		button_text: qsTr("Cancel")
		onClick: {
			rollback()
			settings_pane.visible = false
		}
	}

	function rollback() {
		loadSavedConfiguration()
	}

	/////////////
	// Signals //
	/////////////

	signal endAction(bool endOK, string errMsg, bool fatalEnd)

	// Showing an information message
	signal showInfoMessage(string infoMsg)
}
