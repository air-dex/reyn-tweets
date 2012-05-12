/// @file LoginComponents.qml
/// @brief Component with items for authentication
///
/// Known as LoginComponent until r372. The LoginComponent which existed until
/// r220 is now known as LoginPane.
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
import ReynTweetsControls 0.1

Item {
	id: login_component

	property int margin: 5

	signal allowOK
	signal allowKO(string errMsg, bool isfatal)

	// Control whose role is to allow Reyn Tweets then saving it the configuration
	AllowControl {
		id: control
		login_control: login_popup.ctrl
	}

	// Popup displayed when the user has to enter its credentials
	LoginPane {
		id: login_popup
		z: 2
		anchors.left: parent.left
		anchors.leftMargin: login_component.margin
		anchors.right: parent.right
		anchors.rightMargin: login_component.margin
		anchors.verticalCenter: parent.verticalCenter
		visible: false
	}

	// Popup after denying ReynTweets
	TwoButtonsActionPane {
		id: deny_pane
		z: 3
		width: login_component.width - 2* login_component.margin
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: false

		pane_text: qsTr("Reyn Tweets was denied.") + "\n\n"
				   + qsTr("Are you sure that you do not want Reyn Tweets to use your Twitter account ?");

		// Left button
		left_button_text: qsTr("Yes")
		onActLeft: {
			deny_pane.visible = false;
			abort_pane.visible = true;
		}

		// Right button
		right_button_text: qsTr("No")
		onActRight: {
			deny_pane.visible = false;
			control.allowReynTweets();
		}
	}

	// Popup to make the user quit the application
	QuitPane {
		id: abort_pane
		z: 3
		width: login_component.width - 2* login_component.margin
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.verticalCenter: parent.verticalCenter
		visible: false
		pane_text: qsTr("Reyn Tweets will quit. Bye bye !")
	}

	Component.onCompleted: {
		// Wiring between the control and its view
		control.showLoginPopup.connect(setLoginPopupVisible)
		control.allowEnded.connect(afterAllowing)
	}

	// Allowing Reyn Tweets
	function allowReynTweets() {
		login_popup.state = "UnknownValidity"
		control.allowReynTweets();
	}

	/// @fn function setLoginPopupVisible(visible);
	/// @brief Showing / hiding the login popup
	/// @param visible Boolean indicating if login_popup has to be shown or hidden.
	function setLoginPopupVisible(visible) {
		login_popup.visible = visible;
	}

	/// @fn function afterLaunching(endOK, errMsg, fatal);
	/// @brief What happened after the allowing processus
	/// @param endOK Did the process ends successfully ?
	/// @param errMsg Error message
	/// @param fatal Did the process end fatally ?
	function afterAllowing(endOK, errMsg, fatal) {
		if (endOK) {	// Successful end
			// Tell that's ended
			allowOK();
		} else if (!fatal && errMsg == qsTr("Reyn Tweets was denied.")) {
			// Asking the user if he is sure that he wants to deny Reny Tweets
			deny_pane.visible = true;
		} else {
			// Sending the error
			allowKO(errMsg, fatal)
		}
	}
}
