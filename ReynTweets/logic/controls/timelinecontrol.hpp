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

#include "genericcontrol.hpp"
#include "../core/timelines/timeline.hpp"
#include "../core/reyncore.hpp"
#include "listhandlers/timelinehandler.hpp"

/// @class TimelineControl
/// @brief Control behind a TimelinePane
class TimelineControl : public GenericControl
{
	Q_OBJECT

	public:
		/// @fn TimelineControl();
		/// @brief Constructor
		TimelineControl();

		/// @fn static void declareQML();
		/// @brief Declaring TimelineControl to the QML system
		static void declareQML();


		/////////////////////////////
		// Actions on the timeline //
		/////////////////////////////

		/// @fn Q_INVOKABLE void loadTimeline();
		/// @brief Loading the home timeline
		Q_INVOKABLE void loadTimeline();

		/// @fn Q_INVOKABLE void refreshTimeline();
		/// @brief Refreshing the home timeline
		Q_INVOKABLE void refreshTimeline();

		/// @fn Q_INVOKABLE void refreshTimelineAfterWrite(QVariant newTweetVariant);
		/// @brief Refreshing the home timeline after writing a tweet
		/// @param newTweetVariant Newly written tweet under its QVariant form
		Q_INVOKABLE void refreshTimelineAfterWrite(QVariant newTweetVariant);

		/// @fn Q_INVOKABLE void moreOldTimeline();
		/// @brief Getting more old tweets the home timeline
		Q_INVOKABLE void moreOldTimeline();


	signals:
		/*
		/// @fn void timelineChanged();
		/// @brief Signal sent when the timeline property changes
		void timelineChanged();
		//*/

		/// @fn void tweetUpdated(int tweetIndex);
		/// @brief Signal sent when a tweet in the timeline was updated
		/// @param tweetIndex Index of the tweet
		void tweetUpdated(int tweetIndex);

		/// @fn void loadedMoreTweets(int tweetsLoaded);
		/// @brief Signal sent to indicate how many more tweets were loaded
		/// @param tweetsLoaded Number of tweets
		void loadedMoreTweets(int tweetsLoaded);

	protected slots:
		/// @fn void loadTimelineEnded(ProcessWrapper res);
		/// @brief Slot executed after loading a timeline
		/// @param res Result of the load
		void loadTimelineEnded(ProcessWrapper res);

		/// @fn void loadTimelineEnded(ProcessWrapper res);
		/// @brief Slot executed after refreshing a timeline
		/// @param res Result of the load
		void refreshTimelineEnded(ProcessWrapper res);

		/// @fn void refreshTimelineAfterWriteEnded(ProcessWrapper res);
		/// @brief Slot executed after refreshHomeTimelineAfterWrite
		/// @param res Result of the process
		void refreshTimelineAfterWriteEnded(ProcessWrapper res);

		/// @fn void loadTimelineEnded(ProcessWrapper res);
		/// @brief Slot executed after getting older tweets a timeline
		/// @param res Result of the load
		void moreOldTimelineEnded(ProcessWrapper res);

	protected:
		/////////////////////////
		// Timeline management //
		/////////////////////////

		/// @brief Entity handling the timeline
		TimelineHandler tlhandler;

		/// @brief The timeline
		Timeline & timeline;

		// timeline_handler
		/// @property timeline_type
		/// @brief Type of the timeline handled by the control
		Q_PROPERTY(TimelineHandler * timeline_handler
				   READ getTimelineHandler)

		/// @fn Timeline::TimelineType getTimelineHandler();
		/// @brief Reading the property timeline_type
		/// @return timeline.getType();
		TimelineHandler * getTimelineHandler();


		////////////////////////////////////////////////////////////
		// Handling new tweets in the timeline after writing them //
		////////////////////////////////////////////////////////////

		/// @brief New tweet saved while updating after reading.
		QVariant backupedNewTweet;
};

#endif // TIMELINECONTROL_HPP
