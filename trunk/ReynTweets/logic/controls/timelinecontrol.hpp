/// @file timelinecontrol.hpp
/// @brief Header of TimelineControl
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

#ifndef TIMELINECONTROL_HPP
#define TIMELINECONTROL_HPP

#include <QObject>
#include "../../model/timelines/timeline.hpp"
#include "../reyncore.hpp"

/// @class TimelineControl
/// @brief Control behind a TimelinePane
class TimelineControl : public QObject
{
	Q_OBJECT

	public:
		/// @fn TimelineControl();
		/// @brief Constructor
		TimelineControl();

		/// @fn static void declareQML();
		/// @brief Declaring TweetControl to the QML system
		static void declareQML();

	signals:
		/// @fn void timelineChanged();
		/// @brief Signal sent when the timeline property changes
		void timelineChanged();

	public slots:
		/// @fn void loadHomeTimeline();
		/// @brief Loading the home timeline
		void loadHomeTimeline();

	protected slots:
		/// @fn void loadTimelineEnded(ProcessWrapper res);
		/// @brief Slot executed after loading a timeline
		/// @param res Result of the load
		void loadTimelineEnded(ProcessWrapper res);

	protected:
		/// @brief Heart of Reyn Tweets
		ReynCore reyn;

		/// @brief Timeline to display
		Q_PROPERTY(Timeline timeline
				   READ getTimeline
				   WRITE setTimeline
				   NOTIFY timelineChanged)

		/// @fn Timeline getTimeline();
		/// @brief Reading the property timeline
		Timeline getTimeline();

		/// @fn void setTimeline(Timeline tl);
		/// @brief Writing the property timeline
		void setTimeline(Timeline tl);

		/// @brief Attribute behind the property timeline
		Timeline statuses;

};

#endif // TIMELINECONTROL_HPP
