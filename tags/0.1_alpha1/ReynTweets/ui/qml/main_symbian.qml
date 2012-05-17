/// @file main_symbian.qml
/// @brief Main QML file for the Symbian version of Reyn Tweets.
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

import QtQuick 1.1
import com.nokia.symbian 1.1

PageStackWindow {
	id: window
	initialPage: MainPage {tools: toolBarLayout}
	showStatusBar: true
	showToolBar: true

	ToolBarLayout {
		id: toolBarLayout
		ToolButton {
			flat: true
			iconSource: "toolbar-back"
			onClicked: window.pageStack.depth <= 1 ? Qt.quit() : window.pageStack.pop()
		}
	}
}
