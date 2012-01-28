import QtQuick 1.1

Rectangle {

	/// @brief Property to determine the width of the input
	property int field_left_margin: text.width

	/// @brief Boolean indicating if the input text has to be hidden
	property bool clear_field: true

	/// @brief Boolean indicating if the cursor of the input text has to be hidden
	property bool cursor_visible: false

	/// @brief Legend of the field
	property string legend: qsTr("text")

	/// @brief Default text in the input
	property string field_text: qsTr("")

	id: form_field
	property int spacing: 10
	width: 360
	height: field_background.height + 2*radius
	radius: 5

	Text {
		id: text
		text: legend
		anchors.left: parent.left
		anchors.leftMargin: radius
		anchors.verticalCenter: parent.verticalCenter
		verticalAlignment: Text.AlignVCenter
		font.family: "Ubuntu"
		font.pixelSize: 14
	}

	Rectangle {
		id: field_background
		height: text.height + 2*radius
		radius: 4
		anchors.verticalCenter: parent.verticalCenter
		anchors.leftMargin: field_left_margin + spacing + radius
		anchors.left: parent.left
		anchors.right: parent.right
		anchors.rightMargin: radius
		border.color: "#000000"
		color: "#ffffff"

		TextInput {
			id: field
			text: field_text
			anchors.leftMargin: parent.radius
			anchors.rightMargin: parent.radius
			anchors.bottomMargin: parent.radius
			anchors.topMargin: parent.radius
			anchors.fill: parent
			echoMode: clear_field ? TextInput.Normal : TextInput.Password
			font.family: "Ubuntu"
			horizontalAlignment: TextEdit.AlignLeft
			font.pixelSize: 14
		}
	}

	function getLegendWidth() { return text.width;}
}
