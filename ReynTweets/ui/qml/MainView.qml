/// @file MainView.qml
/// @brief Main page for desktop
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

/// @class MainView
/// @brief Main page for desktop
Rectangle {
	id: main_view
	property int margin: 5

	function loadHomeTimeline() {
		timeline.loadHomeTimeline();
	}

	width: 360
	height: 640

	// Component displayed while launching the application
	Text {
		id: mockup
		text: "You can tweet now !"
		anchors.top: parent.top
		anchors.horizontalCenter: parent.horizontalCenter
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		font.family: "Ubuntu"
		visible: true
		font.pixelSize: 14
	}

	TimelinePane {
		id: timeline
		anchors.top: mockup.bottom
		anchors.topMargin: 0
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.bottom: parent.bottom
	}
}
