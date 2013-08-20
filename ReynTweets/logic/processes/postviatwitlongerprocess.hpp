/// @file postviatwitlongerprocess.cpp
/// @brief Header of PostViaTwitLongerProcess
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

#ifndef POSTVIATWITLONGERPROCESS_HPP
#define POSTVIATWITLONGERPROCESS_HPP

#include "genericprocess.hpp"
#include "../../connection/twitter/reyntwittercalls.hpp"
#include "../../connection/twitlonger/twitlongercalls.hpp"
#include "../core/tweets/tweet.hpp"

/// @class PostViaTwitLongerProcess
/// @brief Process consisting in posting a tweet which is longer than
/// 140 characters with <a href="http://www.twitlonger.com">TwitLonger</a>.
///
/// This process is composed of three steps :<ol>
/// <li>Shorten the tweet with TwitLonger. The application sends to TwitLonger
/// informations such as :<ul>
///		<li>The too long message (of course)</li>
///		<li>The user that wants to shorten its tweet</li>
///		<li>Informations about Reyn Tweets</li>
///		<li>Informations about the reply if the tweet to shorten is a reply.</li>
///		</ul>
/// TwitLonger sends back informations about the shortened tweet. Among them,
/// there is the ID of the long message on TwitLonger.</li>
/// <li>Posting the shortened tweet on Twitter. This is a classic posting.</li>
/// <li>Updating the long message on TwitLonger with informations about the
/// tweet that Reyn Tweets has just posted on Twitter.</li>
/// </ol>
class PostViaTwitLongerProcess : public GenericProcess
{
	Q_OBJECT

	public:
		/// @fn PostViaTwitLongerProcess(QString status,
		///								 QString userScreenName,
		///								 QString replyTostatusID = "-1",
		///								 QString replyToUserScreenName = "",
		///								 bool userIDonly = true,
		///								 float lat = -361,
		///								 float lon = -361,
		///								 QString place = "",
		///								 bool showCoord = false);
		/// @brief Constructor
		/// @param status Text of the tweet
		/// @param userScreenName Screen name of the author of the tweet
		/// @param replyTostatusID If the tweet is a reply, this parameter is
		/// the ID of the tweet that this tweet replies to.
		/// @param replyToUserScreenName If the tweet is a reply, this parameter
		/// is the screen name of the tweet that this tweet replies to.
		/// @param userIDonly In tweets, giving only the ID of the author (true).
		/// @param lat For geolocation, your longitude.
		/// @param lon For geolocation, your latitude.
		/// @param place For geolocation, ID of the place where the tweet
		/// is supposed to be sent
		/// @param showCoord Displaying the coordonates of the tweet
		/// with a pin on a map
		PostViaTwitLongerProcess(QString status,
								 QString userScreenName,
								 QString replyTostatusID = "-1",
								 QString replyToUserScreenName = "",
								 bool userIDonly = true,
								 float lat = -361,
								 float lon = -361,
								 QString place = "",
								 bool showCoord = false);

		/// @fn PostViaTwitLongerProcess(QString status,
		///								 QString userScreenName,
		///								 qlonglong replyTostatusID = -1,
		///								 QString replyToUserScreenName = "",
		///								 bool userIDonly = true,
		///								 float lat = -361,
		///								 float lon = -361,
		///								 QString place = "",
		///								 bool showCoord = false);
		/// @brief Constructor
		/// @param status Text of the tweet
		/// @param userScreenName Screen name of the author of the tweet
		/// @param replyTostatusID If the tweet is a reply, this parameter is
		/// the ID of the tweet that this tweet replies to.
		/// @param replyToUserScreenName If the tweet is a reply, this parameter
		/// is the screen name of the tweet that this tweet replies to.
		/// @param userIDonly In tweets, giving only the ID of the author (true).
		/// @param lat For geolocation, your longitude.
		/// @param lon For geolocation, your latitude.
		/// @param place For geolocation, ID of the place where the tweet
		/// is supposed to be sent
		/// @param showCoord Displaying the coordonates of the tweet
		/// with a pin on a map
		PostViaTwitLongerProcess(QString status,
								 QString userScreenName,
								 qlonglong replyTostatusID = -1,
								 QString replyToUserScreenName = "",
								 bool userIDonly = true,
								 float lat = -361,
								 float lon = -361,
								 QString place = "",
								 bool showCoord = false);

		/// @fn void startProcess();
		/// @brief Starting the process by posting the message to TwitLonger.
		void startProcess();


	protected:
		///////////
		// Calls //
		///////////

		/// @brief Twitter API wrapper
		ReynTwitterCalls twitter;

		/// @brief TwitLonger API wrapper
		TwitLongerCalls twitlonger;


		////////////////
		// Parameters //
		////////////////

		/// @brief Text to post
		QString tweet;

		/// @brief Screen name of the user who wants to shorten its tweet
		QString username;

		/// @brief ID of the tweet that this status replies to
		qlonglong replyToTweetID;

		/// @brief Screen name of the user that this status replies to
		QString replyToUser;

		/// @brief Only include the userID in the "user" field of a tweet
		bool trimUser;

		/// @brief Longitude of the tweet
		float longitude;

		/// @brief Latitude of the tweet
		float latitude;

		/// @brief place where the tweet was supposed to be sent
		QString reversePlace;

		/// @brief Displaying coordonates on a map
		bool displayCoord;


		///////////////////////////
		// Internal informations //
		///////////////////////////

		/// @brief Boolean indicating if the message to shorten is enough short
		/// to be posted directly on Twitter.
		bool enoughShortMessage;

		/// @brief Shortened text to send to Twitter
		QString shortenedTweet;

		/// @brief ID of the long message on TwitLonger
		QString messageID;

		/// @brief Tweet posted on Twitter
		Tweet postedTweet;


	/////////////////
	// The process //
	/////////////////

		/// @fn void postToTwitLonger();
		/// @brief Posting the long tweet to TwitLonger
		void postToTwitLonger();

		/// @fn void postTweet();
		/// @brief Posting the shortened tweet to Twitter
		void postTweet();

		/// @fn void updateTweetOnTwitLonger();
		/// @brief Updating the tweet informations on TwitLonger
		void updateTweetOnTwitLonger();

	protected slots:
		/// @fn void postToTwitLongerEnded(ResultWrapper res);
		/// @brief After posting to TwitLonger
		/// @param res Result from the TwitLonger API
		void postToTwitLongerEnded(ResultWrapper res);

		/// @fn void postTweetEnded(ResultWrapper res);
		/// @brief After posting to Twitter
		/// @param res Result from the Twitter API
		void postTweetEnded(ResultWrapper res);

		/// @fn void updateTweetOnTwitLongerEnded(ResultWrapper res);
		/// @brief After updating the tweet informations on TwitLonger
		/// @param res Result from the TwitLonger API
		void updateTweetOnTwitLongerEnded(ResultWrapper res);
};

#endif // POSTVIATWITLONGERPROCESS_HPP
