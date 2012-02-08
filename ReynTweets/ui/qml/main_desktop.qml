/// @file main_desktop.qml
/// @brief Main QML file for the desktop version of Reyn Tweets.
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

Rectangle {
	id: reyn_tweets
	width: 360
	height: 640

	// Component displayed while launching the application
	Text {
		id: mockup
		text: "You can tweet now !"
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignHCenter
		font.family: "Ubuntu"
		visible: false
		font.pixelSize: 14
	}

	LaunchingPane {
		id: splash_screen
		anchors.fill: parent
		visible: false
		onEndLaunch: reyn_tweets.state = "Tweeting";
	}


	states: [
		State {
			// Launching the application
			name: "Launching"

			PropertyChanges {
				target: splash_screen
				visible: true
			}
		},
		State {
			name: "Tweeting"

			PropertyChanges {
				target: splash_screen
				visible: false
			}

		   PropertyChanges {
			   target: mockup
			   visible: true
		   }
		}
	]

	Component.onCompleted: {
		// Launching the application
		reyn_tweets.state = "Launching";
		splash_screen.launchReynTweets();
	}
}
