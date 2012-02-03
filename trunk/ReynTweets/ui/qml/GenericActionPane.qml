import QtQuick 1.1

// Pane with one button
Rectangle {
	/// @brief Text of the pane
	property string pane_text: qsTr("Yeah ! It's Reyn time !")

	/// @brief Text in the button
	property string button_text: qsTr("Leave it to Reyn !")

	/// @brief Value for marges
	property int margin_value: 5

	/// @brief Space between the text and the button
	property int spacing: 6*margin_value

	/// @brief Radius of the corners of the component
	property int pane_radius: 10

	/// @brief Signal sent whene th user click on the button
	signal act

	Component.onCompleted: {
		// Wiring
		action_button.click.connect(act)
	}

	id: action_pane
	width: 360
	height: description_action.height + spacing + action_button.height
	color: "#a4a4a4"
	radius: pane_radius
	opacity: 0.800

	Text {
		id: description_action
		width: action_pane.width - 2* action_pane.margin_value
		text: action_pane.pane_text
		font.family: "Ubuntu"
		verticalAlignment: Text.AlignVCenter
		horizontalAlignment: Text.AlignLeft
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.top: parent.top
		anchors.topMargin: margin_value
		font.pixelSize: 14
		elide: Text.ElideRight
	}

	// Custom button
	RTButton {
		id: action_button
		button_text: action_pane.button_text
		anchors.right: parent.right
		anchors.rightMargin: margin_value
		anchors.bottom: parent.bottom
		anchors.bottomMargin: margin_value
	}
}
