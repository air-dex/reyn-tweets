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

#include "../core/tweets/tweet.hpp"
#include "../core/reyncore.hpp"
#include "genericcontrol.hpp"

/// @class WriteTweetControl
/// @brief Control behind a pane used for writing and posting tweets.
class WriteTweetControl : public GenericControl
{
	Q_OBJECT

	public:
		/// @fn WriteTweetControl();
		/// @brief Constructor
		WriteTweetControl();

		/// @fn static void declareQML();
		/// @brief Declaring WriteTweetControl to the QML system
		static void declareQML();

		/// @fn Q_INVOKABLE void postTweet();
		/// @brief Posting a tweet without medias
		Q_INVOKABLE void postTweet();

		/// @fn Q_INVOKABLE void postViaTwitLonger();
		/// @brief Posting a long tweet using TwitLonger
		Q_INVOKABLE void postViaTwitLonger();

	protected:
		// Tweet to update (future_tweet)
		/// @property future_tweet
		/// @brief Backend tweet getting all the informations that will be sent
		/// to Twitter while posting it.
		///
		/// futureStatus is the attribute beneath this property.
		Q_PROPERTY(Tweet * future_tweet
				   READ getFutureTweet
				   NOTIFY futureTweetChanged)

		/// @brief Backend tweet getting all the informations that will be sent
		/// to Twitter while posting it.
		Tweet futureStatus;

		/// @fn Tweet * getFutureTweet();
		/// @brief Reading future_tweet
		/// @return A pointer on futureStatus
		Tweet * getFutureTweet();


	signals:
		/// @fn void tweetPosted(QVariant newTweetVariant);
		/// @brief Signal sent if the tweet was posted successfully
		/// @param newTweetVariant Posted tweet under a QVariant form.
		void tweetPosted(QVariant newTweetVariant);

		/// @fn void futureTweetChanged();
		/// @brief Emitted when the future_tweet property changes its value.
		void futureTweetChanged();

	protected slots:
		/// @fn void postTweetEnded(ProcessWrapper res);
		/// @brief Slot executed after posting a tweet.
		/// @param res Result of the post
		void postTweetEnded(ProcessWrapper res);

		/// @fn void postViaTwitLongerEnded(ProcessWrapper res);
		/// @brief Slot executed after postViaTwitLonger.
		/// @param res Result of the post
		void postViaTwitLongerEnded(ProcessWrapper res);
};

#endif // WRITETWEETCONTROL_HPP
