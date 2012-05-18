/// @file TryAgainPane.qml
/// @brief Pane to try again something or to quit Reyn Tweets
/// @author Romain Ducher
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

import QtQuick 1.1

TwoButtonsActionPane {
	// Signal sent when the user wants to try again
	signal tryAgain

	id: try_again_pane

	width: constant.reyn_tweets_width
	height: constant.reyn_tweets_height

	Constants { id:constant }

	// Left button
	left_button_text: qsTr("Try again")
	onActLeft: {
		try_again_pane.visible = false;
		tryAgain();
	}

	// Right button
	right_button_text: qsTr("Quit")
	onActRight: Qt.quit();
}
