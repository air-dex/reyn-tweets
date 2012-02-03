// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

GenericActionPane {
	/// @brief Text of the pane
	property string pane_text: qsTr("Yeah ! It's Reyn time !")

	/// @brief Text of the left button
	property string left_button_text: qsTr("Leave it to Reyn !")

	/// @brief Text of the right button
	property int right_button_text: qsTr("Here we go... LARIAT !")

	/// @brief Value for marges
	property int margin_value: 5

	/// @brief Space between the text and the button
	property int spacing: 6*margin_value

	/// @brief Radius of the corners of the component
	property int pane_radius: 10

	/// @brief Signal sent when the user click on the left button
	signal actLeft

	/// @brief Signal sent when the user click on the right button
	signal actRight

	Component.onCompleted: {
		// Wiring
		actLeft.connect(left_button.click)
		actRight.connect(right_button.click)
	}

	id: two_buttons_pane
	width: 360
	height: description_action.height + spacing + action_button.height
	color: "#a4a4a4"
	radius: pane_radius
	opacity: 0.800

	Text {
		id: description_action
		text: two_buttons_pane.pane_text
		font.family: "Ubuntu"
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignLeft
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.top: parent.top
		anchors.topMargin: margin_value
		font.pixelSize: 14
	}

	// Left button
	RTButton {
		id: left_button
		button_text: two_buttons_pane.left_button_text
		anchors.right: right_button.left
		anchors.rightMargin: two_buttons_pane.margin_value
		anchors.bottom: two_buttons_pane.bottom
		anchors.bottomMargin: two_buttons_pane.margin_value
	}

	// Right button
	RTButton {
		id: right_button
		button_text: two_buttons_pane.right_button_text
		anchors.right: two_buttons_pane.right
		anchors.rightMargin: two_buttons_pane.margin_value
		anchors.bottom: two_buttons_pane.bottom
		anchors.bottomMargin: two_buttons_pane.margin_value
	}
}
