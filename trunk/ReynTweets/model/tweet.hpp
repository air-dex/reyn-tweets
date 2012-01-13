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

#include <QDate>
#include "reyntweetsserializable.hpp"
#include "tweetentities.hpp"
#include "userinfos.hpp"

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
			/// @param tweet Tweet to copy
			Tweet(const Tweet & tweet);

			/// @fn const Tweet & operator=(const Tweet & tweet);
			/// @brief Affectation
			/// @param tweet Tweet to copy
			/// @return Copy of the original tweet
			const Tweet & operator=(const Tweet & tweet);

			/// @fn static void initSystem();
			/// @brief Serialization declaration
			static void initSystem();

		private:
			/// @fn void recopie(const Tweet & tweet);
			/// @brief Copy of a tweet
			/// @param tweet Tweet to copy
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
			/// @fn void fillWithPropertiesMaps();
			/// @brief Filling serializable fields with thecorresponding  property maps
			void fillWithPropertiesMaps();

			/// @fn void updateAllProperties();
			/// @brief Updating all the properties
			void updateAllProperties();

			// entities
			/// @property entities
			/// @brief Tweet Entities
			Q_PROPERTY(QVariantMap entities
					   READ getEntitiesMap
					   WRITE setEntitiesMap)

			/// @brief Map of entities
			QVariantMap entitiesMap;

			/// @fn QVariantMap getEntitiesMap();
			/// @brief Reading the property entities
			/// @return entitiesMap
			QVariantMap getEntitiesMap();

			/// @fn void setEntitiesMap(QVariantMap newEntityMap);
			/// @brief Writing the property entities
			/// @param newEntityMap New value for entities
			void setEntitiesMap(QVariantMap newEntityMap);

			/// @fn void updateEntities();
			/// @brief Updating the property entities
			void updateEntities();

			// in_reply_to_user_id
			/// @property in_reply_to_user_id
			/// @brief Property corresponding to replyToUserID
			Q_PROPERTY(long in_reply_to_user_id
					   READ getInReplyToUserID
					   WRITE setInReplyToUserID)

			/// @fn void updateInReplyToUserID();
			/// @brief Updating the property in_reply_to_user_id
			void updateInReplyToUserID();

			// truncated
			/// @property truncated
			/// @brief Is the tweet truncated ?
			Q_PROPERTY(bool truncated
					   READ isTruncated
					   WRITE setTruncated)

			/// @fn void updateTruncated();
			/// @brief Updating the property truncated
			void updateTruncated();

			// favorited
			/// @property favorited
			/// @brief Is the tweet favorited ?
			Q_PROPERTY(bool favorited
					   READ isFavorited
					   WRITE setFavorited)

			/// @fn void updateFavorited();
			/// @brief Updating the property favorited
			void updateFavorited();

			// retweet_count
			/// @property retweet_count
			/// @brief How many times the tweet has been retweeted ?
			Q_PROPERTY(int retweet_count
					   READ getRetweetCount
					   WRITE setRetweetCount)

			/// @fn void updateRetweetCount();
			/// @brief Updating the property retweet_count
			void updateRetweetCount();

			// in_reply_to_screen_name
			/// @property in_reply_to_screen_name
			/// @brief Screen name corresponding to the user ID in_reply_to_user_id
			Q_PROPERTY(QString in_reply_to_screen_name
					   READ getInReplyToScreenName
					   WRITE setInReplyToScreenName)

			/// @fn void updateInReplyToScreenName();
			/// @brief Updating the property in_reply_to_screen_name
			void updateInReplyToScreenName();

			// created_at
			/// @property created_at
			/// @brief Serializable form of createdAt
			Q_PROPERTY(QDate created_at
					   READ getCreatedAt
					   WRITE setCreatedAt)

			/// @fn void updateCreatedAt();
			/// @brief Updating the property created_at
			void updateCreatedAt();

			// in_reply_to_status_id_str
			/// @property in_reply_to_status_id_str
			/// @brief String form of in_reply_to_status_id
			Q_PROPERTY(QString in_reply_to_status_id_str
					   READ getInReplyToStatusIDstr
					   WRITE setInReplyToStatusIDstr)

			/// @fn void updateInReplyToStatusIDstr();
			/// @brief Updating the property in_reply_to_status_id_str
			void updateInReplyToStatusIDstr();

			// user
			/// @property user
			/// @brief User who wrote the tweet
			Q_PROPERTY(QVariantMap user
					   READ getUserMap
					   WRITE setUserMap)

			/// @brief User under the form of a map
			QVariantMap userMap;

			/// @fn QVariantMap getUserMap();
			/// @brief Reading the property user
			/// @return userMap
			QVariantMap getUserMap();

			/// @fn void setUserMap(QVariantMap newUserMap);
			/// @brief Writing the property user
			/// @param newUserMap New value for user
			void setUserMap(QVariantMap newUserMap);

			/// @fn void updateUser();
			/// @brief Updating the property user
			void updateUser();

			// retweeted
			/// @property retweeted
			/// @brief Is the tweet retweeted ?
			Q_PROPERTY(bool retweeted
					   READ isRetweeted
					   WRITE setRetweeted)

			/// @fn void updateRetweeted();
			/// @brief Updating the property retweeted
			void updateRetweeted();

			// in_reply_to_user_id_str
			/// @property in_reply_to_user_id_str
			/// @brief String version of in_reply_to_user_id
			Q_PROPERTY(QString in_reply_to_user_id_str
					   READ getInReplyToUserIDstr
					   WRITE setInReplyToUserIDstr)

			/// @fn void updateInReplyToUserIDstr();
			/// @brief Updating the property in_reply_to_user_id_str
			void updateInReplyToUserIDstr();

			// id_str
			/// @property id_str
			/// @brief String version of the tweet ID.
			Q_PROPERTY(QString id_str
					   READ getIDstr
					   WRITE setIDstr)

			/// @fn void updateIDstr();
			/// @brief Updating the property id_str
			void updateIDstr();

			// source
			/// @property source
			/// @brief Source of the tweet (Twitter client)
			Q_PROPERTY(QString source
					   READ getSource
					   WRITE setSource)

			/// @fn void updateSource();
			/// @brief Updating the property source
			void updateSource();

			// id
			/// @property id
			/// @brief Tweet ID
			Q_PROPERTY(long id
					   READ getID
					   WRITE setID)

			/// @fn void updateID();
			/// @brief Updating the property id
			void updateID();

			// in_reply_to_status_id
			/// @property in_reply_to_status_id
			/// @brief Property corresponding to replyToTweetID
			Q_PROPERTY(long in_reply_to_status_id
					   READ getInReplyToStatusID
					   WRITE setInReplyToStatusID)

			/// @fn void updateInReplyToStatusID();
			/// @brief Updating the property in_reply_to_status_id
			void updateInReplyToStatusID();

			// text
			/// @property text
			/// @brief Content of the tweet (the famous 140 characters)
			Q_PROPERTY(QString text
					   READ getText
					   WRITE setText)

			/// @fn void updateText();
			/// @brief Updating the property text
			void updateText();

			// sensible
			/// @property sensible
			/// @brief Is the content of the tweet sensible
			Q_PROPERTY(bool sensible
					   READ isSensible
					   WRITE setSensible)

			/// @fn void updateSensible();
			/// @brief Updating the property sensible
			void updateSensible();

			/*
			 * Properties that are not here :
			 * - place
			 * - geo
			 * - coordinates
			 * - contributors
			 */


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
			TweetEntities tweetEntities;

			/// @brief Text of the tweet (the famous 140 characters !)
			QString tweet;

			/// @brief Boolean indicating if the content of the tweet is sensible
			bool sensibleTweet;

			// Retweet management

			/// @brief Boolean indicating if the tweet was retweeted
			bool retweetedTweet;

			/// @brief Number of retweets of this tweet
			int retweetCount;

			// Favorite management

			/// @brief Boolean indicating if the tweet was favorited
			bool favoritedTweet;

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

			// Tweet sources

			/// @brief User who posted the tweet
			UserInfos profile;

			/// @brief Creation date of the tweet
			QDate createdAt;

			/// @brief Client used to post this tweet, just like Reyn Tweets. ;-)
			QString sourceClient;

			// Contributors, geolocalisation and places : NOT FOR THE MOMENT
	/*
			/// @brief contributors
			QString contributors;

			/// @brief coordinates
			QString coordinates;

			/// @brief geo
			QString geo;

			/// @brief place
			QString place;
	//*/
			// Miscanellous

			/// @brief truncated
			bool truncatedTweet;


		/////////////////////////
		// Getters and setters //
		/////////////////////////

		public:
			// entities

			/// @fn TweetEntities getEntities();
			/// @brief Reading entities
			/// @return tweetEntities
			TweetEntities getEntities();

			/// @fn void setEntities(TweetEntities newValue);
			/// @brief Writing entities
			/// @param newValue New value for entities
			void setEntities(TweetEntities newValue);

			// in_reply_to_user_id

			/// @fn long getInReplyToUserID();
			/// @brief Reading in_reply_to_user_id
			/// @return replyToUserID
			long getInReplyToUserID();

			/// @fn void setInReplyToUserID(long newValue);
			/// @brief Writing in_reply_to_user_id
			/// @param newValue New value for in_reply_to_user_id
			void setInReplyToUserID(long newValue);

			// truncated

			/// @fn bool isTruncated();
			/// @brief Reading truncated
			/// @return truncatedTweet
			bool isTruncated();

			/// @fn void setTruncated(bool newValue);
			/// @brief Writing truncated
			/// @param newValue New value for truncated
			void setTruncated(bool newValue);

			// favorited

			/// @fn bool isFavorited();
			/// @brief Reading favorited
			/// @return favoritedTweet
			bool isFavorited();

			/// @fn void setFavorited(bool newValue);
			/// @brief Writing favorited
			/// @param newValue New value for favorited
			void setFavorited(bool newValue);

			// retweet_count

			/// @fn int getRetweetCount();
			/// @brief Reading retweet_count
			/// @return retweetCount
			int getRetweetCount();

			/// @fn void setRetweetCount(int newValue);
			/// @brief Writing retweet_count
			/// @param newValue New value for retweet_count
			void setRetweetCount(int newValue);

			// in_reply_to_screen_name

			/// @fn QString getInReplyToScreenName();
			/// @brief Reading in_reply_to_screen_name
			/// @return replyToScreenName
			QString getInReplyToScreenName();

			/// @fn void setInReplyToScreenName(QString newValue);
			/// @brief Writing in_reply_to_screen_name
			/// @param newValue New value for in_reply_to_screen_name
			void setInReplyToScreenName(QString newValue);

			// created_at

			/// @fn QDate getCreatedAt();
			/// @brief Reading created_at
			/// @return createdAt
			QDate getCreatedAt();

			/// @fn void setCreatedAt(QDate newValue);
			/// @brief Writing created_at
			/// @param newValue New value for created_at
			void setCreatedAt(QDate newValue);

			// in_reply_to_status_id_str

			/// @fn QString getInReplyToStatusIDstr();
			/// @brief Reading in_reply_to_status_id_str
			/// @return replyToTweetIDstr
			QString getInReplyToStatusIDstr();

			/// @fn void setInReplyToStatusIDstr(QString newValue);
			/// @brief Writing in_reply_to_status_id_str
			/// @param newValue New value for in_reply_to_status_id_str
			void setInReplyToStatusIDstr(QString newValue);

			// user

			/// @fn UserInfos getUser();
			/// @brief Reading user
			/// @return profile
			UserInfos getUser();

			/// @fn void setUser(UserInfos newValue);
			/// @brief Writing user
			/// @param newValue New value for user
			void setUser(UserInfos newValue);

			// retweeted

			/// @fn bool isRetweeted();
			/// @brief Reading retweeted
			/// @return retweetedTweet
			bool isRetweeted();

			/// @fn void setRetweeted(bool newValue);
			/// @brief Writing retweeted
			/// @param newValue New value for retweeted
			void setRetweeted(bool newValue);

			// in_reply_to_user_id_str

			/// @fn QString getInReplyToUserIDstr();
			/// @brief Reading in_reply_to_user_id_str
			/// @return replyToUserIDstr
			QString getInReplyToUserIDstr();

			/// @fn void setInReplyToUserIDstr(QString newValue);
			/// @brief Writing in_reply_to_user_id_str
			/// @param newValue New value for in_reply_to_user_id_str
			void setInReplyToUserIDstr(QString newValue);

			// id_str

			/// @fn QString getIDstr();
			/// @brief Reading id_str
			/// @return tweetIDstr
			QString getIDstr();

			/// @fn void setIDstr(QString newValue);
			/// @brief Writing id_str
			/// @param newValue New value for id_str
			void setIDstr(QString newValue);

			// source

			/// @fn QString getSource();
			/// @brief Reading source
			/// @return sourceClient
			QString getSource();

			/// @fn void setSource(QString newValue);
			/// @brief Writing source
			/// @param newValue New value for source
			void setSource(QString newValue);

			// id

			/// @fn long getID();
			/// @brief Reading
			/// @return tweetID
			long getID();

			/// @fn void setID(long newValue);
			/// @brief Writing id
			/// @param newValue New value for id
			void setID(long newValue);

			// in_reply_to_status_id

			/// @fn long getInReplyToStatusID();
			/// @brief Reading in_reply_to_status_id
			/// @return replyToTweetID
			long getInReplyToStatusID();

			/// @fn void setInReplyToStatusID(long newValue);
			/// @brief Writing in_reply_to_status_id
			/// @param newValue New value for in_reply_to_status_id
			void setInReplyToStatusID(long newValue);

			// text

			/// @fn QString getText();
			/// @brief Reading text
			/// @return tweet
			QString getText();

			/// @fn void setText(QString newValue);
			/// @brief Writing text
			/// @param newValue New value for text
			void setText(QString newValue);

			// sensible

			/// @fn bool isSensible();
			/// @brief Reading sensible
			/// @return sensibleTweet
			bool isSensible();

			/// @fn void setSensible(bool newValue);
			/// @brief Writing sensible
			/// @param newValue New value for sensible
			void setSensible(bool newValue);
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
