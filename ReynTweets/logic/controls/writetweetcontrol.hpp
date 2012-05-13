/// @file writetweetcontrol.hpp
/// @brief Header of WriteTweetControl
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

#ifndef WRITETWEETCONTROL_HPP
#define WRITETWEETCONTROL_HPP

#include <QObject>
#include "../../model/tweets/tweet.hpp"
#include "../reyncore.hpp"

/// @class WriteTweetControl
/// @brief Control behind a pane used for writing and posting tweets.
class WriteTweetControl : public QObject
{
	Q_OBJECT

	public:
		/// @fn WriteTweetControl();
		/// @brief Constructor
		WriteTweetControl();

		/// @fn static void declareQML();
		/// @brief Declaring TweetControl to the QML system
		static void declareQML();

		/// @fn Q_INVOKABLE void postTweet(QString tweet,
		///								   QString inReplyToTweetID = -1);
		/// @brief Posting a tweet without medias
		/// @param tweet The text of the tweet
		/// @param inReplyToTweetID ID of the tweet
		Q_INVOKABLE void postTweet(QString tweet,
								   QString inReplyToTweetID = "-1");


	signals:
		/// @fn void tweetPosted();
		/// @brief Signal sent if the tweet was posted successfully
		void tweetPosted();

		/// @fn void postEnded(bool launchOK,
		///					   QString errorMsg,
		///					   bool isFatal);
		/// @brief Signal sent after posting the tweet
		/// @param launchOK Did the launching process end successfully ?
		/// @param errorMsg Error message
		/// @param isFatal Did the launching process end with a fatal error ?
		void postEnded(bool launchOK,
					   QString errorMsg,
					   bool isFatal);

		/// @fn void authenticationNeeded();
		/// @brief Signal sent if Reyn Tweets has to be allowed again
		void authenticationNeeded();

        /// @fn void showInfoMessage(QString message);
        /// @brief Signal sent for announcing something, often at the beginning
        /// of an action
        /// @param message Thye message to display.
        void showInfoMessage(QString message);

	protected slots:
		/// @fn void postTweetEnded(ProcessWrapper res);
		/// @brief Slot executed after posting a tweet.
		/// @param res Result of the post
		void postTweetEnded(ProcessWrapper res);

	protected:
		/// @brief Heart of Reyn Tweets
		ReynCore reyn;

        /// @brief Boolean indicating if the control is in a process
        bool processing;
};

#endif // WRITETWEETCONTROL_HPP
