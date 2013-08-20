/// @file AccountPane.qml
/// @brief Pane displaying informations about Reyn Tweets
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
import ReynTweetsControls 0.2
import ReynTweetsEntities 0.2
import "../base_components"

Rectangle {
	id: about_pane

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
		text: qsTr("About Reyn Tweets")
		horizontalAlignment: Text.AlignHCenter
		anchors.top: about_pane.top
		anchors.topMargin: margin
		anchors.horizontalCenter: about_pane.horizontalCenter
		font.family: constant.font
		font.pointSize: constant.font_size
		wrapMode: Text.WrapAtWordBoundaryOrAnywhere
	}

	// Going to the top of the timeline while clicking on the header
	MouseArea {
		anchors.top: parent.top
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.bottom: about_flick.top
		onClicked: about_flick.contentY = 0
	}

	// Flickable with the rectangle containing all the settings
	Flickable {
		id: about_flick
		width: parent.width
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.top: header_text.bottom
		anchors.topMargin: margin
		anchors.bottom: ok_button.top
		anchors.bottomMargin: margin
		clip: true


		contentWidth: about_board.width
		contentHeight: about_board.height

		// Pane with all the settings
		Rectangle {
			id: about_board
			width: about_pane.width
			height: 10*margin + reyn_tweets_icon.height
					+ program_name_label.height + version_label.height
					+ copyright_label.height + body_label.height
					+ website_label.height

			z: about_flick.z + 1
			color: constant.white

			// Icon
			Image {
				id: reyn_tweets_icon

				anchors.top: parent.top
				anchors.topMargin: margin
				anchors.horizontalCenter: parent.horizontalCenter

				sourceSize.width: 5* about_board.width /8

				fillMode: Image.PreserveAspectFit
				source: "../../../resources/Logo Reyn Tweets PNG.png"

				width: sourceSize.width
			}

			// Name of the program
			Text {
				id: program_name_label
				width: parent.width - 2*margin

				anchors.top: reyn_tweets_icon.bottom
				anchors.topMargin: margin
				anchors.horizontalCenter: parent.horizontalCenter

				text: "Reyn Tweets"
				font.bold: true
				font.family: constant.font
				font.pointSize: constant.font_size_title
				verticalAlignment: Text.AlignVCenter
				horizontalAlignment: Text.AlignHCenter
			}

			// Version of the program
			Text {
				id: version_label
				width: parent.width - 2*margin

				anchors.top: program_name_label.bottom
				anchors.topMargin: margin
				anchors.horizontalCenter: parent.horizontalCenter

				text: "Version ".concat(constant.getVersion())
				font.family: constant.font
				font.pointSize: constant.font_size
				verticalAlignment: Text.AlignVCenter
				horizontalAlignment: Text.AlignHCenter
			}

			// Text for website
			Text {
				id: website_label
				width: parent.width - 2*margin

				anchors.top: version_label.bottom
				anchors.topMargin: 2*margin
				anchors.horizontalCenter: parent.horizontalCenter

				text: qsTr("Website : ").concat('<a href="http://code.google.com/p/reyn-tweets/"')
					.concat('style="text-decoration:none; color: ')
					.concat(constant.orange)
					.concat('">http://code.google.com/p/reyn-tweeets/</a>')
				font.family: constant.font
				font.bold: false
				horizontalAlignment: Text.AlignHCenter
				verticalAlignment: Text.AlignVCenter
				font.pointSize: constant.font_size
				onLinkActivated: Qt.openUrlExternally(link)
			}

			// Body
			Text {
				id: body_label
				width: parent.width - 2*margin

				anchors.horizontalCenter: parent.horizontalCenter
				anchors.top: website_label.bottom
				anchors.topMargin: 2*margin

				text: qsTr('Reyn Tweets is an open source Twitter client for \
Windows and Linux written in Qt.')
				.concat('<br/><br/>')
				.concat(qsTr('Reyn Tweets is free software: you can redistribute \
it and/or modify it under the terms of the GNU Lesser General Public License as \
published by the Free Software Foundation, either version 3 of the License, or \
(at your option) any later version.'))
				.concat('<br/><br/>')
				.concat(qsTr('Reyn Tweets is distributed in the hope that it \
will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of \
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General \
Public License for more details.'))
				.concat('<br/><br/>')
				.concat(qsTr('You should have received a copy of the GNU Lesser \
General Public License along with Reyn Tweets. If not, see '))
.concat('<a style="text-decoration:none; color: ').concat(constant.orange)
.concat('" href="http://www.gnu.org/licenses/">http://www.gnu.org/licenses/</a>.')
				textFormat: Text.RichText
				font.family: constant.font
				font.bold: false
				verticalAlignment: Text.AlignVCenter
				horizontalAlignment: Text.AlignHCenter
				font.pointSize: constant.font_size
				onLinkActivated: Qt.openUrlExternally(link)
				wrapMode: Text.WrapAtWordBoundaryOrAnywhere
			}

			// Text for copyright
			Text {
				id: copyright_label
				width: parent.width - 2*margin

				anchors.horizontalCenter: parent.horizontalCenter
				anchors.top: body_label.bottom
				anchors.topMargin: 2*margin

				text: '(C) 2012 Romain DUCHER (<a href="https://twitter.com/#!/air_dex" \
					   style="text-decoration: none; color: '.concat(constant.orange)
					  .concat('">@air_dex</a>)')
				font.family: constant.font
				font.bold: false
				verticalAlignment: Text.AlignVCenter
				horizontalAlignment: Text.AlignHCenter
				font.pointSize: constant.font_size_s
				onLinkActivated: Qt.openUrlExternally(link)
			}
		}
	}

	// Quit the page
	RTButton {
		id: ok_button
		border_color: constant.orange_author
		anchors.rightMargin: margin
		anchors.right: parent.right
		anchors.bottomMargin: margin
		anchors.bottom: parent.bottom
		button_text: qsTr("OK")
		onClick: about_pane.visible = false
	}
}
