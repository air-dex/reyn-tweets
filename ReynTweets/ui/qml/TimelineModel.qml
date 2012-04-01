/// @file TimelineModel.qml
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

/// @class TimelineModel
/// @brief Model of a TimelinePane
ListModel {
	id: timeline_model

	function toJSObject(tweet) {
		var tweetObj;
		eval("tweetObj = " + tweet);
		return tweetObj;
	}

	function syncWithTimeline(timeline) {
		timeline_model.clear();

		console.log("Longeur de la TL :" + timeline.length)

		for (var i = 0; i < timeline.length; i++) {
			var element = {};
/*
			var object = toJSObject(timeline[i])

			element = {
				obj: object,
				str: timeline[i]
			}
//*/
			timeline_model.append(element)
		}

		console.log("Sync finie")
	}
}
