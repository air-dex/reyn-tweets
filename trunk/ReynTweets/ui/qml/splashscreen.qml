// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
	id: splash_screen_view
	width: splash_screen.width
	height: splash_screen.height

	LaunchingWidget {
		id: splash_screen
	}
}
