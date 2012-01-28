import QtQuick 1.1

Rectangle {
	id: reyn_tweets
	width: 360
	height: 640

	property int margin: 5

	// Wiring the function exectuted after Reyn Tweets was launched.
	Component.onCompleted: {
		splash_screen.endLaunch.connect(endStart)
	}

	LaunchingWidget {
		id: splash_screen
		anchors.fill: reyn_tweets
		visible: true
	}

	function endStart(startOK, errMsg, fatal) {
		if (startOK) {
			// Keep on
			reyn_tweets.state = "MainState"
		} else {
			// Problem : show popup
			reyn_tweets.state = "FailLaunchingState"
			fail_launching_pane.pane_text = errMsg;
		}
	}

	// Pane displayed if a problem occurs while launching the application.
	QuitPane {
		id: fail_launching_pane
		anchors.rightMargin: margin
		anchors.leftMargin: margin
		anchors.right: parent.right
		anchors.left: parent.left
		anchors.verticalCenter: parent.verticalCenter
	}

	states: [
		State {
			name: "FailLaunchingState"

			PropertyChanges {
				target: splash_screen
				visible: false
			}

			PropertyChanges {
				target: main_view
				visible: false
			}

			PropertyChanges {
				target: fail_launching_pane
				visible: true
			}
		},

		State {
			name: "MainState"

			PropertyChanges {
				target: splash_screen
				visible: false
			}

			PropertyChanges {
				target: main_view
				visible: true
			}

			PropertyChanges {
				target: fail_launching_pane
				visible: false
			}
		}
	]
}
