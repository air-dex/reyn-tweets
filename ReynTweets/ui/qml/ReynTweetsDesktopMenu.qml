// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Rectangle {
	width: menu_list.width
	height: menu_list.height

	Constants {id: constant}

	ListView {
		id: menu_list
		anchors.fill: parent

		delegate: Component {
			Rectangle {
				Text {
					id: menu_id
					anchors.fill: parent
					text: description
					font.pixelSize: constant.font_size
					font.family: constant.font

					MouseArea {
						anchors.fill: parent
						onClicked: console.log("coucou")
					}
				}
			}
		}

		model: ListModel {
			ListElement {
				description: "bonjour"
			}
			ListElement {
				description: "bonsoir"
			}
		}
	}
}
