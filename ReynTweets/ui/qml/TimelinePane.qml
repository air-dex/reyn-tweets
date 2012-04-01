/// @file TimelinePane.qml
/// @brief Pane to show a tweet
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
import ReynTweetsControls 0.1
import ReynTweetsEntities 0.1

/// @class TimelinePane
/// @brief Pane to show a timeline
Rectangle {
	id: timeline_pane
	width: 360
	height: 640

	// Control behind the pane
	TimelineControl {
		id: control
		onTimelineChanged: timeline_model.syncWithTimeline(control.timelineStr);
	}

	// Model of the list
	TimelineModel {
		id: timeline_model
	}

	// List of all the tweets
	ListView {
		id: timeline_view
		anchors.fill: parent

		delegate: Component {
			TweetPane {
				width: timeline_pane.width
				tweet: control.getTweet(index)
			}
		}

		model: timeline_model
	}

	function loadHomeTimeline() {
		control.loadHomeTimeline();
	}
}
