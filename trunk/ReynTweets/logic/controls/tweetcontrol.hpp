/// @file tweetcontrol.hpp
/// @brief Header of TweetControl
///
/// Revisions of the file older than r204 are in /trunk/ReynTweets/controls
/// r204 is in /trunk/ReynTweets/logic
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

#ifndef TWEETCONTROL_HPP
#define TWEETCONTROL_HPP

#include <QObject>
#include "../reyncore.hpp"
#include "../../model/tweets/tweet.hpp"

/// @class TweetControl
/// @brief Control behind a TweetPane
class TweetControl : public QObject
{
	Q_OBJECT

	public:
		/// @fn TweetControl();
		/// @brief Constructor
		TweetControl();

		/// @fn static void declareQML();
		/// @brief Declaring TweetControl to the QML system
		static void declareQML();

		/// @fn void retweet();
		/// @brief Retweet the tweet
		Q_INVOKABLE void retweet();

		/// @fn void favorite();
		/// @brief Favorite the tweet
		Q_INVOKABLE void favorite();

		/// @fn void unfavorite();
		/// @brief Unfavorite the tweet
		Q_INVOKABLE void unfavorite();

		/// @fn Q_INVOKABLE bool isMention();
		/// @brief Method indicating if the tweet mentions the user.
		///	@return true if the user is mentionned, false otherwise.
		Q_INVOKABLE bool isMention();


	signals:
		/// @fn void tweetChanged();
		/// @brief Emitted when the tweet property (status attribute) is modified.
		void tweetChanged();

		void tweetUpdated();

		void tweetRetweeted();

		/// @fn void tweetChanged(bool launchOK,
		///						  QString errorMsg,
		///						  bool isFatal);
		/// @brief Signal sent after an operation made by the control.
		/// @param launchOK Did the process end successfully ?
		/// @param errorMsg Error message
		/// @param isFatal Did the process end with a fatal error ?
		void tweetEnded(bool launchOK,
						QString errorMsg,
						bool isFatal);

		/// @fn void authenticationNeeded();
		/// @brief Signal sent if Reyn Tweets has to be allowed again
		void authenticationNeeded();

		/// @fn void updateTimeline(Tweet * updatedTweet);
		/// @brief Signal sent when a tweet has to be updated in the timeline
		void updateTimeline(QVariant updatedTweet);


	protected slots:
		/// @fn void retweetEnd(ProcessWrapper res);
		/// @brief Slot executed after retweeting the tweet
		void retweetEnd(ProcessWrapper res);

		/// @fn void favoriteEnd(ProcessWrapper res);
		/// @brief Slot executed after favoriting the tweet
		void favoriteEnd(ProcessWrapper res);

		/// @fn void unfavoriteEnd(ProcessWrapper res);
		/// @brief Slot executed after unfavoriting the tweet
		void unfavoriteEnd(ProcessWrapper res);

	protected:
		/// @brief Entity which realizes treatments
		ReynCore reyn;

		/// @property tweet
		/// @brief Model of the tweet manipulated by the control.
		Q_PROPERTY(Tweet * tweet
				   READ getTweet
				   WRITE setTweet
				   NOTIFY tweetChanged)

		/// @brief Tweet entity behind the tweet property
		Tweet status;

		/// @fn Tweet * getTweet();
		/// @brief Reading the tweet property
		/// @return status
		Tweet * getTweet();

		/// @fn void setTweet(Tweet * newStatus);
		/// @brief Writing the tweet property
		/// @param newStatus New value for status.
		void setTweet(Tweet * newStatus);
};

#endif // TWEETCONTROL_HPP
