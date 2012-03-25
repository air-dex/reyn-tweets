/// @file tweet.hpp
/// @brief Header of Tweet.
///
/// Revisions older than r243 was in /trunk/ReynTwets/model
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

#ifndef TWEET_HPP
#define TWEET_HPP

#include "../../tools/reyntweetsdatetime.hpp"
#include "../reyntweetsmappable.hpp"
#include "tweetentities.hpp"
#include "../users/userinfos.hpp"

/// @class Tweet
/// @brief Model of a tweet
class Tweet : public ReynTweetsMappable
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

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

	private:
		/// @fn void recopie(const Tweet & status);
		/// @brief Copy of a tweet
		/// @param status Tweet to copy
		void recopie(const Tweet & status);

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
		/// @fn void blacklistProperties();
		/// @brief Blacklisting the "author" and "retweet" properties (used only
		/// for and by QML views).
		void blacklistProperties();

		// entities
		/// @property entities
		/// @brief Tweet Entities
		Q_PROPERTY(QVariantMap entities
				   READ getEntitiesProperty
				   WRITE setEntities
				   NOTIFY entitiesChanged)

		/// @fn QVariantMap getEntitiesProperty();
		/// @brief Reading the property entities
		/// @return entitiesMap
		QVariantMap getEntitiesProperty();

		/// @fn void setEntities(QVariantMap newEntityMap);
		/// @brief Writing the property entities
		/// @param newEntityMap New value for entities
		void setEntities(QVariantMap newEntityMap);

		// in_reply_to_user_id
		/// @property in_reply_to_user_id
		/// @brief Property corresponding to replyToUserID
		Q_PROPERTY(qlonglong in_reply_to_user_id
				   READ getInReplyToUserID
				   WRITE setInReplyToUserID
				   NOTIFY inReplyToUserIDChanged)

		// truncated
		/// @property truncated
		/// @brief Is the tweet truncated ?
		Q_PROPERTY(bool truncated
				   READ isTruncated
				   WRITE setTruncated
				   NOTIFY truncatedChanged)

		// favorited
		/// @property favorited
		/// @brief Is the tweet favorited ?
		Q_PROPERTY(bool favorited
				   READ isFavorited
				   WRITE setFavorited
				   NOTIFY favoritedChanged)

		// retweet_count
		/// @property retweet_count
		/// @brief How many times the tweet has been retweeted ?
		Q_PROPERTY(int retweet_count
				   READ getRetweetCount
				   WRITE setRetweetCount
				   NOTIFY retweetCountChanged)

		// in_reply_to_screen_name
		/// @property in_reply_to_screen_name
		/// @brief Screen name corresponding to the user ID in_reply_to_user_id
		Q_PROPERTY(QString in_reply_to_screen_name
				   READ getInReplyToScreenName
				   WRITE setInReplyToScreenName
				   NOTIFY inReplyToScreenNameChanged)

		// created_at
		/// @property created_at
		/// @brief Serializable form of createdAt
		Q_PROPERTY(QString created_at
				   READ getCreatedAtProperty
				   WRITE setCreatedAt
				   NOTIFY createdAtChanged)

		/// @fn QString getCreatedAtProperty();
		/// @brief Reading created_at
		/// @return The value of createdAt
		QString getCreatedAtProperty();

		/// @fn void setCreatedAt(QString newDate);
		/// @brief Writing created_at
		/// @param newDate The new value of createdAt
		void setCreatedAt(QString newDate);

		// in_reply_to_status_id_str
		/// @property in_reply_to_status_id_str
		/// @brief String form of in_reply_to_status_id
		Q_PROPERTY(QString in_reply_to_status_id_str
				   READ getInReplyToStatusIDstr
				   WRITE setInReplyToStatusIDstr
				   NOTIFY inReplyToStatusIDstrChanged)

		// user
		/// @property user
		/// @brief User who wrote the tweet
		Q_PROPERTY(QVariantMap user
				   READ getUserProperty
				   WRITE setUser
				   NOTIFY userChanged)

		/// @fn QVariantMap getUserProperty();
		/// @brief Reading the property user
		/// @return userMap
		QVariantMap getUserProperty();

		/// @fn void setUser(QVariantMap newUserMap);
		/// @brief Writing the property user
		/// @param newUserMap New value for user
		void setUser(QVariantMap newUserMap);
//*
		/// @property author
		/// @brief User who wrote the tweet. Used to get information
		/// to display about the author of the tweet (in a TweetPane).
		Q_PROPERTY(UserInfos * author
				   READ getAuthor
				   WRITE setAuthor
				   NOTIFY userChanged)
//*/
		// retweeted
		/// @property retweeted
		/// @brief Is the tweet retweeted ?
		Q_PROPERTY(bool retweeted
				   READ isRetweeted
				   WRITE setRetweeted
				   NOTIFY retweetedChanged)

		// in_reply_to_user_id_str
		/// @property in_reply_to_user_id_str
		/// @brief String version of in_reply_to_user_id
		Q_PROPERTY(QString in_reply_to_user_id_str
				   READ getInReplyToUserIDstr
				   WRITE setInReplyToUserIDstr
				   NOTIFY inReplyToUserIDstrChanged)

		// id_str
		/// @property id_str
		/// @brief String version of the tweet ID.
		Q_PROPERTY(QString id_str
				   READ getIDstr
				   WRITE setIDstr
				   NOTIFY idStrChanged)

		// source
		/// @property source
		/// @brief Source of the tweet (Twitter client)
		Q_PROPERTY(QString source
				   READ getSource
				   WRITE setSource
				   NOTIFY sourceChanged)

		// id
		/// @property id
		/// @brief Tweet ID
		Q_PROPERTY(qlonglong id
				   READ getID
				   WRITE setID
				   NOTIFY idChanged)

		// in_reply_to_status_id
		/// @property in_reply_to_status_id
		/// @brief Property corresponding to replyToTweetID
		Q_PROPERTY(qlonglong in_reply_to_status_id
				   READ getInReplyToStatusID
				   WRITE setInReplyToStatusID
				   NOTIFY inReplyToStatusIDChanged)

		// text
		/// @property text
		/// @brief Content of the tweet (the famous 140 characters)
		Q_PROPERTY(QString text
				   READ getText
				   WRITE setText
				   NOTIFY textChanged)

		// sensible
		/// @property sensible
		/// @brief Is the content of the tweet sensible
		Q_PROPERTY(bool sensible
				   READ isSensible
				   WRITE setSensible
				   NOTIFY sensibleChanged)

		// retweeted_status
		/// @property retweeted_status
		/// @brief Serializable form of retweetedTweet
		Q_PROPERTY(QVariantMap retweeted_status
				   READ getRetweetedStatusProperty
				   WRITE setRetweetedStatus
				   NOTIFY retweetedStatusChanged)

		/// @fn QVariantMap getRetweetedStatusProperty();
		/// @brief Reading retweeted_status
		/// @return lastTweetMap
		QVariantMap getRetweetedStatusProperty();

		/// @fn void setRetweetedStatus(QVariantMap statusMap);
		/// @brief Writing retweeted_status
		/// @param statusMap The new value of the property
		void setRetweetedStatus(QVariantMap statusMap);
//*
		/// @property retweet
		/// @brief The retweet to display in a TweetPane
		Q_PROPERTY(Tweet * retweet
				   READ getRetweetedStatus
				   WRITE setRetweetedStatus
				   NOTIFY retweetedStatusChanged)
//*/
		/*
		 * Properties that are not here :
		 * - place
		 * - geo
		 * - coordinates
		 * - contributors
		 */


	signals:
		/// @fn void entitiesChanged();
		/// @brief Emitted when the entities property changes
		void entitiesChanged();

		/// @fn void inReplyToUserIDChanged();
		/// @brief Emitted when the in_reply_to_user_id property changes
		void inReplyToUserIDChanged();

		/// @fn void truncatedChanged();
		/// @brief Emitted when the truncated property changes
		void truncatedChanged();

		/// @fn void favoritedChanged();
		/// @brief Emitted when the favorited property changes
		void favoritedChanged();

		/// @fn void retweetCountChanged();
		/// @brief Emitted when the retweet_count property changes
		void retweetCountChanged();

		/// @fn void inReplyToScreenNameChanged();
		/// @brief Emitted when the in_reply_to_screen_name property changes
		void inReplyToScreenNameChanged();

		/// @fn void createdAtChanged();
		/// @brief Emitted when the created_at property changes
		void createdAtChanged();

		/// @fn void inReplyToStatusIDstrChanged();
		/// @brief Emitted when the in_reply_to_status_id_str property changes
		void inReplyToStatusIDstrChanged();

		/// @fn void userChanged();
		/// @brief Emitted when the user and author properties change
		void userChanged();

		/// @fn void retweetedChanged();
		/// @brief Emitted when the retweeted property changes
		void retweetedChanged();

		/// @fn void inReplyToUserIDstrChanged();
		/// @brief Emitted when the in_reply_to_user_id_str property changes
		void inReplyToUserIDstrChanged();

		/// @fn void idStrChanged();
		/// @brief Emitted when the id_str property changes
		void idStrChanged();

		/// @fn void sourceChanged();
		/// @brief Emitted when the source property changes
		void sourceChanged();

		/// @fn void idChanged();
		/// @brief Emitted when the id property changes
		void idChanged();

		/// @fn void inReplyToStatusIDChanged();
		/// @brief Emitted when the in_reply_to_status_id property changes
		void inReplyToStatusIDChanged();

		/// @fn void textChanged();
		/// @brief Emitted when the text property changes
		void textChanged();

		/// @fn void sensibleChanged();
		/// @brief Emitted when the sensible property changes
		void sensibleChanged();

		/// @fn void retweetedStatusChanged();
		/// @brief Emitted when the retweeted_status and retweet properties change
		void retweetedStatusChanged();


	//////////////////////
	// Tweet management //
	//////////////////////

	protected:
		// Tweet identity
		/// @brief ID of the tweet
		qlonglong tweetID;

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

		/// @brief Initial tweet if the tweet is retweeted
		///
		/// It is a pointer on a tweet to avoir the compiler error C2460.
		Tweet * retweetSource;

		// Favorite management

		/// @brief Boolean indicating if the tweet was favorited
		bool favoritedTweet;

		// Reply management

		/// @brief Screen Name of the user which the tweet replies
		QString replyToScreenName;

		/// @brief ID of the user which the tweet replies
		qlonglong replyToUserID;

		/// @brief String version of replyToUserID
		QString replyToUserIDstr;

		/// @brief ID of the tweet which the tweet replies
		qlonglong replyToTweetID;

		/// @brief String version of replyToTweetID
		QString replyToTweetIDstr;

		// Tweet sources

		/// @brief User who posted the tweet
		UserInfos profile;

		/// @brief Creation date of the tweet
		ReynTweetsDateTime createdAt;

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
		/// @fn qlonglong getInReplyToUserID();
		/// @brief Reading in_reply_to_user_id
		/// @return replyToUserID
		qlonglong getInReplyToUserID();

		/// @fn void setInReplyToUserID(qlonglong newValue);
		/// @brief Writing in_reply_to_user_id
		/// @param newValue New value for in_reply_to_user_id
		void setInReplyToUserID(qlonglong newValue);

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
		/// @fn ReynTweetsDateTime getCreatedAt();
		/// @brief Reading created_at
		/// @return createdAt
		ReynTweetsDateTime getCreatedAt();

		/// @fn void setCreatedAt(ReynTweetsDateTime newValue);
		/// @brief Writing created_at
		/// @param newValue New value for created_at
		void setCreatedAt(ReynTweetsDateTime newValue);

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

		// author
		/// @fn UserInfos * getAuthor();
		/// @brief Reading author
		/// @return profile
		UserInfos * getAuthor();

		/// @fn void setAuthor(UserInfos * newValue);
		/// @brief Writing author
		/// @param newValue New value for author
		void setAuthor(UserInfos * newValue);

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
		/// @fn qlonglong getID();
		/// @brief Reading
		/// @return tweetID
		qlonglong getID();

		/// @fn void setID(qlonglong newValue);
		/// @brief Writing id
		/// @param newValue New value for id
		void setID(qlonglong newValue);

		// in_reply_to_status_id
		/// @fn qlonglong getInReplyToStatusID();
		/// @brief Reading in_reply_to_status_id
		/// @return replyToTweetID
		qlonglong getInReplyToStatusID();

		/// @fn void setInReplyToStatusID(qlonglong newValue);
		/// @brief Writing in_reply_to_status_id
		/// @param newValue New value for in_reply_to_status_id
		void setInReplyToStatusID(qlonglong newValue);

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

		// retweeted_status
		/// @fn Tweet * getRetweetedStatus();
		/// @brief Reading retweeted_status
		/// @return lastTweetMap
		Tweet * getRetweetedStatus();

		/// @fn void setRetweetedStatus(Tweet * retweet);
		/// @brief Writing retweeted_status
		/// @param retweet The new value of the property
		void setRetweetedStatus(Tweet * retweet);


	//////////////////////////////////
	// Methods used by the QML View //
	//////////////////////////////////

	public slots:
		/// @fn QString getDisplayText();
		/// @brief Getting the content of tweet under the form of a HTML string.
		///
		/// It is used to display the tweet in a QML View.
		///	@return The text to display (in a TweetPane)
		QString getDisplayText();

		/// @fn QString getDisplaySource();
		/// @brief Getting the name of the Twitter client used to post the tweet
		/// under the form of a HTML string.
		///
		/// It is used to display the client name in a QML View.
		///	@return The text to display
		QString getDisplaySource();

		/// @fn QString whenWasItPosted();
		/// @brief When the tweet was posted ?
		///	@return A string telling when it was posted
		QString whenWasItPosted();
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
