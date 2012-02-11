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
		/// @fn explicit TweetControl();
		/// @brief Constructor
		explicit TweetControl();

		/// @fn static void declareQML();
		/// @brief Declaring TweetControl to the QML system
		static void declareQML();

	signals:

	public slots:
		/// @fn void reply();
		/// @brief Reply to the tweet
		void reply();

		/// @fn void retweet();
		/// @brief Retweet the tweet
		void retweet();

		/// @fn void quote();
		/// @brief Quote the tweet (old retweet method)
		void quote();

		/// @fn void favorite();
		/// @brief Favorite the tweet
		void favorite();

		/// @fn void unfavorite();
		/// @brief Unfavorite the tweet
		void unfavorite();

	protected slots:
		/// @fn void replyEnd(ProcessWrapper res);
		/// @brief Slot executed after replying to the tweet
		void replyEnd(ProcessWrapper res);

		/// @fn void retweetEnd(ProcessWrapper res);
		/// @brief Slot executed after retweeting the tweet
		void retweetEnd(ProcessWrapper res);

		/// @fn void quoteEnd(ProcessWrapper res);
		/// @brief Slot executed after quoting the tweet (old retweet method)
		void quoteEnd(ProcessWrapper res);

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
		Q_PROPERTY(Tweet tweet
				   READ getTweet
				   WRITE setTweet)

		/// @brief Tweet entity behind the tweet property
		Tweet status;

		/// @fn Tweet getTweet();
		/// @brief Reading the tweet property
		/// @return status
		Tweet getTweet();

		/// @fn void setTweet(Tweet newStatus);
		/// @brief Writing the tweet property
		/// @param newStatus New value for status.
		void setTweet(Tweet newStatus);
};

#endif // TWEETCONTROL_HPP
