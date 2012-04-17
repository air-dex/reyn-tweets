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

		/// @fn Q_INVOKABLE void loadHomeTimeline();
		/// @brief Loading the home timeline
		Q_INVOKABLE void loadHomeTimeline();

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


	signals:
		/// @fn void timelineChanged();
		/// @brief Signal sent when the timeline property changes
		void timelineChanged();

		/// @fn void loadEnded(bool launchOK,
		///					   QString errorMsg,
		///					   bool isFatal);
		/// @brief Signal sent after launching
		/// @param launchOK Did the launching process end successfully ?
		/// @param errorMsg Error message
		/// @param isFatal Did the launching process end with a fatal error ?
		void loadEnded(bool launchOK,
					   QString errorMsg,
					   bool isFatal);

		/// @fn void authenticationNeeded();
		/// @brief Signal sent if Reyn Tweets has to be allowed again
		void authenticationNeeded();

	protected slots:
		/// @fn void loadTimelineEnded(ProcessWrapper res);
		/// @brief Slot executed after loading a timeline
		/// @param res Result of the load
		void loadTimelineEnded(ProcessWrapper res);

	protected:
		/// @brief Heart of Reyn Tweets
		ReynCore reyn;

		/// @brief The timeline
		Timeline timeline;

		/// @brief Length of the timeline. Used by QML for the list model.
		Q_PROPERTY(int tl_length
				   READ getTimelineLength
				   NOTIFY timelineChanged)

		/// @fn Timeline getTimelineLength();
		/// @brief Reading the property tl_length
		int getTimelineLength();
};

#endif // TIMELINECONTROL_HPP
