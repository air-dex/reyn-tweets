/// @file ScrollBar.qml
/// @brief Scroll bar for Reyn Tweets.
///
/// It were in the /trunk/ReynTweets/ui/qml folder until r491
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

import QtQuick 2.0
import ReynTweetsComponents 0.3

Item {
	id: scroll_bar

	// Relative position of the content of what you scroll. If you scroll
	// horizontally, position = contentX / contentWidth and if you scroll
	// vertically, position = contentY / contentHeight
	property real position

	// % of what you scrolled that you may see if what you scroll don't have to
	// be scrolled in the opposite direction. If you scroll
	// horizontally, ratio = width / contentWidth and if you scroll
	// vertically, ratio = height / contentHeight
	property real ratio

	// Reyn Tweets constants
	Constants { id: constant }

	Rectangle {
		id: background
		anchors.fill: parent

		color: constant.white
		opacity: 0.1

		// Showing the scroll bar when the mouse is on it
		MouseArea {
			id: hover_zone
			anchors.fill: parent
			hoverEnabled: true
		}
	}

	// Scroller, i.e. the rectangle that the user will drag.
	Rectangle {
		id: scroller
		z: background.z + 1
		color: constant.orange
		opacity: 1

		// Area to drag scroller
		MouseArea {
			id: drag_zone
			anchors.fill: scroller
			drag.target: scroller
			onPositionChanged: {
				// Updating the position of what is scrolled

				var newPosse = 0

				if (orientation == Qt.Vertical) {
					newPosse = parseFloat(scroller.y) / parseFloat(background.height)
				} else if (orientation == Qt.Horizontal) {
					newPosse = parseFloat(scroller.x) / parseFloat(background.width)
				}

				scroll_bar.position = newPosse
			}

			// Show the scroll bar when the mouse is on it
			states: [
				State {
					name: "drag_and_hover"
					when: hover_zone.containsMouse || scroll_bar.dragging
					PropertyChanges {
						target: scroller
						opacity: 1
					}
				}
			]
		}

		// Show the scroll bar when the mouse is on it
		states: [
			State {
				name: "hovered"
				when: hover_zone.containsMouse
				PropertyChanges {
					target: scroller
					opacity: 1
				}

				PropertyChanges {
					target: scroll_bar
					width: 3*scroll_bar.minWidth
				}
			}
		]
	}

	Component.onCompleted: scroll_bar.minWidth = scroll_bar.width


	//////////////////////////
	// Orientation handling //
	//////////////////////////

	// Orientation of the bar (horizontal, vertical)
	property variant orientation : Qt.Vertical

	states: [
		// When the bar is oriented vertically
		State {
			name: "vertical"
			when: orientation == Qt.Vertical

			PropertyChanges {
				target: scroll_bar
				dragPosition: parseFloat(scroller.y) / parseFloat(background.height)
			}

			PropertyChanges {
				target: background
				radius: width / 2
			}

			// Placing the scroller
			PropertyChanges {
				target: scroller
				anchors.horizontalCenter: background.horizontalCenter

				y: scroll_bar.position * background.height
				width: scroll_bar.width - 2
				height: scroll_bar.ratio * background.height
				radius: scroller.width / 2
			}

			// Configuring how to drag the scroller
			PropertyChanges {
				target: drag_zone
				drag.axis: Drag.YAxis
				drag.minimumY: 0
				drag.maximumY: background.height - scroller.height
			}
		},

		// When the bar is oriented horizontally
		State {
			name: "horizontal"
			when: orientation == Qt.Horizontal

			PropertyChanges {
				target: scroll_bar
				dragPosition: parseFloat(scroller.x) / parseFloat(background.width)
			}

			PropertyChanges {
				target: background
				radius: height / 2
			}

			// Placing the scroller
			PropertyChanges {
				target: scroller
				anchors.verticalCenter: background.verticalCenter

				x: scroll_bar.position * background.width
				height: scroll_bar.height - 2
				width: scroll_bar.ratio * background.width
				radius: scroller.height / 2
			}

			// Configuring how to drag the scroller
			PropertyChanges {
				target: drag_zone
				drag.axis: Drag.XAxis
				drag.minimumX: 0
				drag.maximumX: background.width - scroller.width
			}
		}
	]


	////////////////////
	// Hover handling //
	////////////////////

	// Minimal width
	property int minWidth

	// Boolean telling if the scroller is dragged
	property alias mouseIn: hover_zone.containsMouse


	///////////////////
	// Drag handling //
	///////////////////

	// Boolean telling if the scroller is dragged
	property bool dragging: drag_zone.drag.active

	property real dragPosition
}
