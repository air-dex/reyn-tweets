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

#include "genericcontrol.hpp"
#include "../reyncore.hpp"
#include "../../model/tweets/tweet.hpp"

/// @class TweetControl
/// @brief Control behind a TweetPane
class TweetControl : public GenericControl
{
	Q_OBJECT

	public:
		/// @fn TweetControl();
		/// @brief Constructor
		TweetControl();

		/// @fn static void declareQML();
		/// @brief Declaring TweetControl to the QML system
		static void declareQML();

		/// @fn void refresh();
		/// @brief Refresh the tweet
		Q_INVOKABLE void refresh();

		/// @fn void retweet();
		/// @brief Retweet the tweet
		Q_INVOKABLE void retweet();

		/// @fn void favorite();
		/// @brief Favorite the tweet
		Q_INVOKABLE void favorite();

		/// @fn void unfavorite();
		/// @brief Unfavorite the tweet
		Q_INVOKABLE void unfavorite();

		/// @fn void deleteTweet();
		/// @brief Delete the tweet
		Q_INVOKABLE void deleteTweet();

		/// @fn Q_INVOKABLE bool isMention();
		/// @brief Method indicating if the tweet mentions the user.
		///	@return true if the user is mentionned, false otherwise.
		Q_INVOKABLE bool isMention();

		/// @fn Q_INVOKABLE void shareByMail();
		/// @brief Sharing a tweet by mail.
		///
		/// The method writes the email and then send it to the email client
		/// thanks to a mailto URI.
		/// On Windows, the different parts of the email (subject, body)
		/// have to be percent encoded. That's why this is done by the Qt
		/// control instead of the QML component (TimelinePane).
		Q_INVOKABLE void shareByMail();


	signals:
		/// @fn void tweetChanged();
		/// @brief Emitted when the tweet property (status attribute) is modified.
		void tweetChanged();

		/// @fn void updateTimeline(QVariant updatedTweet);
		/// @brief Signal sent when a tweet has to be updated in the timeline
		/// @param updatedTweet The updatedTweet after an operation on it.
		void updateTimeline(QVariant updatedTweet);

		/// @fn void destroyTweet();
		/// @brief Emitted if the tweet has to be destroyed
		void destroyTweet();


	protected slots:
		/// @fn void refreshEnd(ProcessWrapper res);
		/// @brief Slot executed after refreshing the tweet
		void refreshEnd(ProcessWrapper res);

		/// @fn void retweetEnd(ProcessWrapper res);
		/// @brief Slot executed after retweeting the tweet
		void retweetEnd(ProcessWrapper res);

		/// @fn void favoriteEnd(ProcessWrapper res);
		/// @brief Slot executed after favoriting the tweet
		void favoriteEnd(ProcessWrapper res);

		/// @fn void unfavoriteEnd(ProcessWrapper res);
		/// @brief Slot executed after unfavoriting the tweet
		void unfavoriteEnd(ProcessWrapper res);

		/// @fn void deleteEnd(ProcessWrapper res);
		/// @brief Slot executed after deleting a tweet
		void deleteEnd(ProcessWrapper res);


	protected:
		////////////////////
		// Tweet handling //
		////////////////////

		/// @brief Tweet entity behind the tweet property
		Tweet * status;

		/// @property tweet
		/// @brief Model of the tweet manipulated by the control.
		///
		/// The status attribute is behind this property
		Q_PROPERTY(Tweet * tweet
				   READ getTweet
				   WRITE setTweet
				   NOTIFY tweetChanged)

		/// @fn Tweet * getTweet();
		/// @brief Reading the tweet property
		/// @return status
		Tweet * getTweet();

		/// @fn void setTweet(Tweet * newStatus);
		/// @brief Writing the tweet property
		/// @param newStatus New value for status.
		void setTweet(Tweet * newStatus);

		/// @property shown_tweet
		/// @brief Tweet that is really displayed on the screen.
		///
		/// When the tweet is a retweet, ReynTweets displays the retweet instead
		/// of the original tweet.
		Q_PROPERTY(Tweet * shown_tweet
				   READ getShownTweet
				   NOTIFY tweetChanged)

		/// @fn Tweet * getShownTweet();
		/// @brief Reading the shown_tweet property
		/// @return status->getRetweetedStatus() if the tweet is a retweet,
		/// status otherwise
		Tweet * getShownTweet();

		/// @property variant_tweet
		/// @brief Variant form of the tweet property for syncing the tweet
		/// displayed by the QML pane (TweetPane) and the corresponding tweet
		/// in the timeline (Qt TimelineControl and the list model of the QML
		/// TimelinePane).
		///
		/// status->toVariant() is behind this property.
		Q_PROPERTY(QVariantMap variant_tweet
				   READ getVariantTweet
				   WRITE setVariantTweet
				   NOTIFY tweetChanged)

		/// @fn QVariant getVariantTweet();
		/// @brief Reading the variant_tweet property
		/// @return status
		QVariantMap getVariantTweet();

		/// @fn void setVariantTweet(QVariant newStatus);
		/// @brief Writing the variant_tweet property
		/// @param newStatus New value for variant_tweet.
		void setVariantTweet(QVariantMap newStatus);
};

#endif // TWEETCONTROL_HPP
