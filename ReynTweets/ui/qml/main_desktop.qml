import QtQuick 1.1

Rectangle {
	id: reyn_tweets
	width: 360
	height: 640

	// Component displayed while launching the application
	LaunchingWidget {
		id: splash_screen
		anchors.fill: parent
		visible: false
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
		}
	]

	Component.onCompleted: {
		// Launching the application
		reyn_tweets.state = "Launching";
		splash_screen.launchReynTweets();
	}
}
