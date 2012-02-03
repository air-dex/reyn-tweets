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

	LaunchingWidget {
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
