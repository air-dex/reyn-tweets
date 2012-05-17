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

#include "../../model/tweets/tweet.hpp"
#include "../reyncore.hpp"
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
        /// @fn void tweetPosted(QVariant newTweetVariant);
        /// @brief Signal sent if the tweet was posted successfully
        /// @param newTweetVariant Posted tweet under a QVariant form.
        void tweetPosted(QVariant newTweetVariant);

    protected slots:
        /// @fn void postTweetEnded(ProcessWrapper res);
        /// @brief Slot executed after posting a tweet.
        /// @param res Result of the post
        void postTweetEnded(ProcessWrapper res);
};

#endif // WRITETWEETCONTROL_HPP
