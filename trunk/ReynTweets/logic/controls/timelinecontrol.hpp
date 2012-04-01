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
#include <QDeclarativeListProperty>
#include "../../model/timelines/timelinemodel.hpp"
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

		Q_INVOKABLE Tweet * getTweet(int index) {
			if (index >= 0 && index < model.size()) {
				return model.at(index);
			} else {
				return new Tweet;
			}

		}

	signals:
		/// @fn void timelineChanged();
		/// @brief Signal sent when the timeline property changes
		void timelineChanged();

		/// @fn void launchEnded(bool launchOK,
		///						 QString errorMsg = "",
		///						 bool isFatal = false);
		/// @brief Signal sent after launching
		/// @param launchOK Did the launching process end successfully ?
		/// @param errorMsg Error message
		/// @param isFatal Did the launching process end with a fatal error ?
		void loadEnded(bool launchOK,
						 QString errorMsg,
						 bool isFatal);

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
		Q_PROPERTY(QDeclarativeListProperty<Tweet> timeline
				   READ getTimeline
				   WRITE setTimeline
				   NOTIFY timelineChanged)

		/// @fn Timeline getTimeline();
		/// @brief Reading the property timeline
		QDeclarativeListProperty<Tweet> getTimeline();

		/// @fn void setTimeline(Timeline tl);
		/// @brief Writing the property timeline
		void setTimeline(QDeclarativeListProperty<Tweet> tl);

		/// @fn void setTimeline(Timeline tl);
		/// @brief Writing the property timeline
		void setTimeline(TimelineModel * tl);

		TimelineModel model;

		/// @brief Timeline to display
		Q_PROPERTY(QVariant timelineStr
				   READ getTimelineStr
				   NOTIFY timelineChanged)

		/// @fn Timeline getTimeline();
		/// @brief Reading the property timeline
		QVariant getTimelineStr() {
			QStringList res;

			for (int var = 0; var < model.size(); ++var) {
				Tweet * t = model.at(var);
				res.append(t->toString());
			}

			return res;
		}
};

#endif // TIMELINECONTROL_HPP
