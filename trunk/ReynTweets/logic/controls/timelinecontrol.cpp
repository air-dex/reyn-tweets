/// @file timelinecontrol.cpp
/// @brief Implementation of TimelineControl
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

#include <QtDeclarative>
#include "timelinecontrol.hpp"

TimelineControl::TimelineControl() :
	QObject(),
	reyn(this),
	model()
{}

// Declaring TweetControl to the QML system
void TimelineControl::declareQML() {
	qmlRegisterType<TimelineControl>("ReynTweetsControls",
									 0, 1,
									 "TimelineControl");
}


//////////////////////////
// Propoerty management //
/////////////////////////

QDeclarativeListProperty<Tweet> TimelineControl::getTimeline() {
	//return &model;
	return QDeclarativeListProperty<Tweet>(this, model);
}

void TimelineControl::setTimeline(QDeclarativeListProperty<Tweet> tl) {
//	if (tl) {
//		model = *tl;
//	} else {
//		model.clear();
//	}
}

///////////////////////
// Loading timelines //
///////////////////////

// Loading the home timeline
void TimelineControl::loadHomeTimeline() {
	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(loadTimelineEnded(ProcessWrapper)));

	reyn.loadHomeTimeline(-1, -1, false, true, true, false, 0, 3);

	qDebug("loadHomeTimeline");
	//reyn.loadHomeTimeline(170309014415093759, 170311906891014145, false, true, true, false, 0, 3);
}


// After loading a timeline
void TimelineControl::loadTimelineEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return;
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(loadTimelineEnded(ProcessWrapper)));

	CoreResult issue = result.processIssue;
	QVariantList resList = result.results.toList();
	Timeline & statuses = model.getTimelineRef();

	switch (issue) {
		case TIMELINE_RETRIEVED:
			statuses.fillWithVariant(resList);
			model.setTimeline(statuses);
			emit timelineChanged();
			// Process successful
			emit loadEnded(true, QString(), false);
			break;
/*
		case AUTHENTICATION_REQUIRED:
			// An authentication is needed. So let's do it!
			return allowReynTweets();
//*/
		// Problems that can be solved trying later
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
			emit loadEnded(false, result.errorMsg, false);
			break;

		// Problems with configuration file
		case CONFIGURATION_FILE_UNKNOWN:
		case CONFIGURATION_FILE_NOT_OPEN:
		case LOADING_CONFIGURATION_ERROR:

		// Unknown ends
		case UNKNOWN_PROBLEM:

		default:
			emit loadEnded(false, result.errorMsg, true);
			break;
	}
}
