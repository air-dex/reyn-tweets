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
#include "../../model/timelines/timeline.hpp"
#include "../reyncore.hpp"

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

		/// @fn Q_INVOKABLE void loadHomeTimeline();
		/// @brief Loading the home timeline
		Q_INVOKABLE void loadHomeTimeline();

		/// @fn Q_INVOKABLE void refreshHomeTimeline();
		/// @brief Refreshing the home timeline
		Q_INVOKABLE void refreshHomeTimeline();

		/// @fn Q_INVOKABLE void refreshHomeTimelineAfterWrite(QVariant newTweetVariant);
		/// @brief Refreshing the home timeline after writing a tweet
		/// @param newTweetVariant Newly written tweet under its QVariant form
		Q_INVOKABLE void refreshHomeTimelineAfterWrite(QVariant newTweetVariant);

		/// @fn Q_INVOKABLE void moreOldHomeTimeline();
		/// @brief Getting more old tweets the home timeline
		Q_INVOKABLE void moreOldHomeTimeline();

		/// @fn Q_INVOKABLE Tweet * getTweet(int tweetIndex);
		/// @brief Getting a pointer on a tweet in the timeline.
		///
		/// Used by QML delegates of the ListView in the TimelinePane
		/// to attribute a tweet to TweetPane in the delegate in the list.
		/// @param tweetIndex Index of the tweet in the timeline
		/// @return The tweet &#135;tweetIndex in the timeline if the index
		/// is ok, a default tweet otherwise.
		Q_INVOKABLE Tweet * getTweet(int tweetIndex);

		/// @fn Q_INVOKABLE void replaceTweet(QVariant updatedTweet, int tweetIndex);
		/// @brief Replacing a tweet in a timeline
		///
		/// It can be used after retweeting a tweet, for example.
		/// @param updatedTweet New value of the tweet
		/// @param tweetIndex Index of the tweet in the timeline
		Q_INVOKABLE void replaceTweet(QVariant updatedTweet, int tweetIndex);

		/// @fn Q_INVOKABLE void deleteTweet(int tweetIndex);
		/// @brief Deleting a tweet in a timeline
		///
		/// It can be used after retweeting a tweet, for example.
		/// @param tweetIndex Index of the tweet in the timeline
		Q_INVOKABLE void deleteTweet(int tweetIndex);


	signals:
		/// @fn void timelineChanged();
		/// @brief Signal sent when the timeline property changes
		void timelineChanged();

		/// @fn void timelineChanged();
		/// @brief Signal sent when the timeline_type property changes
		void timelineTypeChanged();

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

		/// @brief The timeline
		Timeline timeline;

		/// @property nb_tweets
		/// @brief Number of tweets in the timeline (timeline.size()).
		Q_PROPERTY(int nb_tweets
				   READ getTimelineLength
				   NOTIFY timelineChanged)

		/// @fn Timeline getTimelineLength();
		/// @brief Reading the property nb_tweets
		/// @return timeline.length();
		int getTimelineLength();

		/// @property timeline_type
		/// @brief Type of the timeline handled by the control
		Q_PROPERTY(Timeline::TimelineType timeline_type
				   READ getTimelineType
				   WRITE setTimelineType
				   NOTIFY timelineTypeChanged)

		/// @fn Timeline::TimelineType getTimelineType();
		/// @brief Reading the property timeline_type
		/// @return timeline.getType();
		Timeline::TimelineType getTimelineType();

		/// @fn void setTimelineType(Timeline::TimelineType newType);
		/// @brief Writing the property timeline_type
		/// @param newType New type for the timeline
		void setTimelineType(Timeline::TimelineType newType);


		////////////////////////////////////////////////////////////
		// Handling new tweets in the timeline after writing them //
		////////////////////////////////////////////////////////////

		/// @brief New tweet saved while updating after reading.
		QVariant backupedNewTweet;

		/// @fn void insertInTimeline(Timeline & tl, Tweet newTweet);
		/// @brief Insert a tweet in a timeline.
		///
		/// This method is used to insert a newly written tweet in the
		/// home timeline while refreshing it.
		/// @param tl The timeline
		/// @param newTweet The tweet
		void insertInTimeline(Timeline & tl, Tweet newTweet);
};

#endif // TIMELINECONTROL_HPP
