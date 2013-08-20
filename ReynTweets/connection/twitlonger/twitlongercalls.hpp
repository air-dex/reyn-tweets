/// @file twitlongercalls.hpp
/// @brief Header of TwitLongerCalls
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

#ifndef TWITLONGERCALLS_HPP
#define TWITLONGERCALLS_HPP

#include "../common/calls/genericcalls.hpp"
#include "twitlongerauthenticator.hpp"
#include "twitlongerconstants.hpp"

/// @class TwitLongerCalls
/// @brief Class managing calls to the TwitLonger API.
class TwitLongerCalls : public GenericCalls
{
	Q_OBJECT

	public:
		/// @fn TwitLongerCalls(QObject * requester);
		/// @brief Constructor
		/// @param requester QObject that asks for something.
		TwitLongerCalls(QObject * requester);

		/// @fn static void setAppTokens(QString appName,
		///								 QByteArray apiKey);
		/// @brief Setting the application's tokens to the twitlongerManager
		/// @param appName New application name
		/// @param apiKey New TwitLonger API key
		static void setAppTokens(QString appName,
								 QByteArray apiKey);

	protected:
		/// @brief Settings of the application on TwitLonger
		static TwitLongerAuthenticator twitlongerManager;


	////////////////////////
	// Calling TwitLonger //
	////////////////////////

	public:
		/// @fn void postOnTwitLonger(QString username,
		///							  QString message,
		///							  qlonglong replyToTweetID = TwitLonger::FAKE_TWEET_ID,
		///							  QString replyToUser = TwitLonger::FAKE_SCREEN_NAME);
		/// @brief Posting the long message on TwitLonger
		/// @param username Name of the user that wants to shorten the tweet
		/// @param message Message to shorten
		/// @param replyToTweetID If the message to shorten is a reply, this
		/// parameter will be the ID of the tweet that the user replies to.
		/// @param replyToUser If the message to shorten is a reply, this
		/// parameter will be the twittos that the tweet replies to.
		void postOnTwitLonger(QString username,
							  QString message,
							  qlonglong replyToTweetID = TwitLonger::FAKE_TWEET_ID,
							  QString replyToUser = TwitLonger::FAKE_SCREEN_NAME);

		/// @fn void updateLongTweet(QString messageID, qlonglong tweetID);
		/// @brief Updating the message informations on TwitLonger.
		/// @param messageID ID of the long message on TwitLonger.
		/// @param tweetID ID of the shortened message on Twitter.
		void updateLongTweet(QString messageID, qlonglong tweetID);
};

#endif // TWITLONGERCALLS_HPP
