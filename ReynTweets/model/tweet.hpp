/// @file tweet.hpp
/// @brief Header of Tweet
/// @author Romain Ducher

/*
Copyright 2012 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TWEET_HPP
#define TWEET_HPP

#include "reyntweetsserializable.hpp"
#include "tweetentities.hpp"
#include "user.hpp"

/// @class Tweet
/// @brief Model of a tweet
class Tweet : public ReynTweetsSerializable
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn Tweet();
		/// @brief Default constructor
		Tweet();

		/// @fn virtual ~Tweet();
		/// @brief Destructor
		virtual ~Tweet();

		/// @fn Tweet(const Tweet & tweet);
		/// @brief Copy constructor
		/// @param tweet User to copy
		Tweet(const Tweet & tweet);

		/// @fn const Tweet & operator=(const Tweet & tweet);
		/// @brief Affectation
		/// @param tweet User to copy
		/// @return Copy of the original configuration
		const Tweet & operator=(const Tweet & tweet);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	private:
		/// @fn void recopie(const Tweet & tweet);
		/// @brief Copy of a ReynTweetsConfiguration
		/// @param tweet User to copy
		void recopie(const Tweet & tweet);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const Tweet & tweet);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param tweet Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const Tweet & tweet);

		/// @fn friend QDataStream & operator>>(QDataStream & in, Tweet & tweet);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param tweet Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, Tweet & tweet);


	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:


	//////////////////////
	// Tweet management //
	//////////////////////

	protected:
		// Tweet identity
		/// @brief ID of the tweet
		long tweetID;

		/// @brief String version of tweetID
		QString tweetIDstr;

		// Tweet content

		/// @brief Entities of the tweet
		TweetEntities entities;

		/// @brief Text of the tweet
		QString text;

		/// @brief Boolean indicating if the content of the tweet is sensible
		bool sensibleTweet;

		// Retweet management

		/// @brief Boolean indicating if the tweet was retweeted
		bool retweeted;

		/// @brief Number of retweets of this tweet
		int retweetCount;

		// Favorite management

		/// @brief Boolean indicating if the tweet was favorited
		bool favorited;

		// Reply management

		/// @brief Screen Name of the user which the tweet replies
		QString replyToScreenName;

		/// @brief ID of the user which the tweet replies
		int replyToUserID;

		/// @brief String version of replyToUserID
		QString replyToUserIDstr;

		/// @brief ID of the tweet which the tweet replies
		int replyToTweetID;

		/// @brief String version of replyToTweetID
		QString replyToTweetIDstr;

		// Post management

		/// @brief User who posted the tweet
		User user;

		/// @brief Client used to post this tweet, just like Reyn Tweets. ;-)
		QString source;

		/// @brief Creation date of the tweet
		QDate createdAt;

		// Miscanellous

		/// @brief coordinates
		QString coordinates; ///*/

		/// @brief truncated
		bool truncated; ///*/

		/// @brief contributors
		QString contributors; ///*/

		/// @brief geo
		QString geo; ///*/

		/// @brief place
		QString place; ///*/
};

// Serialization of Tweet
Q_DECLARE_METATYPE(Tweet)

/// @fn QDataStream & operator<<(QDataStream & out, const Tweet & tweet);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param tweet Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const Tweet & tweet);

/// @fn QDataStream & operator>>(QDataStream & in, Tweet & tweet);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param tweet Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, Tweet & tweet);

#endif // TWEET_HPP
