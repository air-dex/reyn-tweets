import QtQuick 1.1

Rectangle {
	/// @brief Distance between the text and the border
	property int margin_value: 5

	/// @brief Radius of buttons round corners
	property int button_radius: 5

	/// @brief Default text for the button
	property string button_text: qsTr("OK")

	/// @brief ID of the button
	id: button

	// Dimnsions
	width: action_text.width + 2*margin_value
	height: action_text.height + 2*margin_value

	/// @brief Signal sent while clicking on the button
	signal click

	// Button design
	// Border colors and interior
	radius: button_radius
	gradient: Gradient {
		GradientStop {
			position: 0
			color: "#ffffff"
		}

		GradientStop {
			position: 1
			color: "#d9781d"
		}
	}
	border.color: "#000000"

	// Anchors
	anchors.right: parent.right
	anchors.rightMargin: margin_value
	anchors.bottom: parent.bottom
	anchors.bottomMargin: margin_value

	// Text written in the button
	Text {
		id: action_text
		text: button_text
		horizontalAlignment: Text.AlignHCenter
		verticalAlignment: Text.AlignVCenter
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		font.family: "Ubuntu"
		font.pixelSize: 14
	}

	// Clickable area of the component
	MouseArea {
		id: click_area
		x: 0
		y: 0
		width: parent.width
		height: parent.height
		anchors.fill: parent
		onClicked: button.click()
	}

	// Wiring between the Mouse Area and the click() signal of the button
	Component.onCompleted: {
		click_area.clicked.connect(button.click)
	}
}
