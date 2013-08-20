/// @file tweet.hpp
/// @brief Header of Tweet.
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012, 2013 Romain Ducher
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

#include <QStringList>
#include <QUrl>
#include "../../tools/reyntweetsdatetime.hpp"
#include "../json/jsonobject.hpp"
#include "tweetentities.hpp"
#include "../users/userinfos.hpp"
#include "retweetinfos.hpp"
#include "../users/contributorlist.hpp"
#include "../geo/coordinates.hpp"
#include "../geo/twitterplace.hpp"

/// @class Tweet
/// @brief Representation of a tweet
/// @see https://dev.twitter.com/docs/platform-objects/tweets
class Tweet : public JsonObject
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

		/// @fn Tweet(const Tweet & status);
		/// @brief Copy constructor
		/// @param status Tweet to copy
		Tweet(const Tweet & status);

		/// @fn const Tweet & operator=(const Tweet & status);
		/// @brief Affectation
		/// @param status Tweet to copy
		/// @return Copy of the original tweet
		const Tweet & operator=(const Tweet & status);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

		/// @fn void reset();
		/// @brief Resets the mappable to a default value
		void reset();

		/// @fn bool operator==(const Tweet & status) const;
		/// @brief Equality between tweets.
		///
		/// Tweets are considered equals if they have got the same ID.
		/// @param status Tweet to compare
		/// @return true if they are equals, false otherwise.
		bool operator==(const Tweet & status) const;

		/////////////////////
		// JSON conversion //
		/////////////////////

		/// @fn virtual void fillWithJSON(QJsonObject json);
		/// @brief Filling the object with a QJsonObject.
		///
		/// The method is virtual because its implementation depends on the
		/// object type.
		/// @param json The QJsonObject used to fill the JsonObject
		virtual void fillWithJSON(QJsonObject json);

		/// @fn virtual QJsonObject toJSON() const;
		/// @brief Getting a QJsonObject representation of the object
		/// @return The QJsonObject representation
		virtual QJsonObject toJSON() const;


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
		// contributors
		/// @property contributors
		/// @brief Tweet Entities
		///
		/// tweetContributors is the attribute beneath this property.
		Q_PROPERTY(QVariantList contributors
				   READ getContributorsProperty
				   WRITE setContributors
				   NOTIFY contributorsChanged)

		/// @brief Name of the property contributors.
		static QString CONTRIBUTORS_PN;

		/// @fn QVariantList getContributorsProperty();
		/// @brief Reading the property contributors
		/// @return entitiesMap
		QVariantList getContributorsProperty();

		/// @fn void setContributors(QVariantList newEntityMap);
		/// @brief Writing the property contributors
		/// @param newEntityMap New value for entities
		void setContributors(QVariantList newEntityMap);

		/// @property tweet_contributors
		/// @brief Tweet Entities
		///
		/// tweetContributors is the attribute beneath this property.
		Q_PROPERTY(ContributorList * tweet_contributors
				   READ getContributorsPtr
				   WRITE setContributors
				   NOTIFY contributorsChanged)

		/// @brief Name of the property tweet_contributors.
		static QString TWEET_CONTRIBUTORS_PN;

		/// @fn ContributorList * getContributorsPtr();
		/// @brief Reading the property tweet_contributors
		/// @return entitiesMap
		ContributorList * getContributorsPtr();

		/// @fn void setContributors(ContributorList * newEntityMap);
		/// @brief Writing the property tweet_contributors
		/// @param newEntityMap New value for entities
		void setContributors(ContributorList * newEntityMap);

		// coordinates
		/// @property coordinates
		/// @brief Coordinates where the tweet was supposed to be posted
		///
		/// tweetCoordinates is the attribute beneath this property.
		Q_PROPERTY(QVariantMap coordinates
				   READ getCoordinatesProperty
				   WRITE setCoordinates
				   NOTIFY coordinatesChanged)

		/// @brief Name of the property coordinates.
		static QString COORDINATES_PN;

		/// @fn QVariantMap getCoordinatesProperty();
		/// @brief Reading the property coordinates
		/// @return tweetCoordinates
		QVariantMap getCoordinatesProperty();

		/// @fn void setCoordinates(QVariantMap newEntityMap);
		/// @brief Writing the property coordinates
		/// @param newEntityMap New value for tweetCoordinates
		void setCoordinates(QVariantMap newEntityMap);

		/// @property tweet_coordinates
		/// @brief Coordinates where the tweet was supposed to be posted
		///
		/// tweetCoordinates is the attribute beneath this property.
		Q_PROPERTY(Coordinates * tweet_coordinates
				   READ getCoordinatesPtr
				   WRITE setCoordinates
				   NOTIFY coordinatesChanged)

		/// @brief Name of the property tweet_coordinates.
		static QString TWEET_COORDINATES_PN;

		/// @fn Coordinates * getCoordinatesPtr();
		/// @brief Reading the property tweet_coordinates
		/// @return tweetCoordinates
		Coordinates * getCoordinatesPtr();

		/// @fn void setCoordinates(Coordinates * newEntityMap);
		/// @brief Writing the property tweet_coordinates
		/// @param newEntityMap New value for tweetCoordinates
		void setCoordinates(Coordinates * newValue);

		// created_at
		/// @property created_at
		/// @brief Serializable form of createdAt
		///
		///  is the attribute beneath this property.
		Q_PROPERTY(QString created_at
				   READ getCreatedAtProperty
				   WRITE setCreatedAt
				   NOTIFY createdAtChanged)

		/// @brief Name of the property .
		static QString CREATED_AT_PN;

		/// @fn QString getCreatedAtProperty();
		/// @brief Reading created_at
		/// @return The value of createdAt
		QString getCreatedAtProperty();

		/// @fn void setCreatedAt(QString newDate);
		/// @brief Writing created_at
		/// @param newDate The new value of createdAt
		void setCreatedAt(QString newDate);

		// current_user_retweet
		/// @property current_user_retweet
		/// @brief Serializable form of retweetInfos
		///
		/// retweetInfos is the attribute beneath this property.
		Q_PROPERTY(QVariantMap current_user_retweet
				   READ getRetweetInfosVariant
				   WRITE setRetweetInfos
				   NOTIFY retweetInfosChanged)

		/// @brief Name of the property current_user_retweet.
		static QString CURRENT_USER_RETWEET_PN;

		/// @property retweet_infos
		/// @brief The retweet to display in a TweetPane
		///
		/// retweetInfos is the attribute beneath this property.
		Q_PROPERTY(RetweetInfos * retweet_infos
				   READ getRetweetInfos
				   WRITE setRetweetInfos
				   NOTIFY retweetInfosChanged)

		/// @brief Name of the property retweet_infos.
		static QString RETWEET_INFOS_PN;

		// entities
		/// @property entities
		/// @brief Tweet Entities
		///
		/// tweetEntities is the attribute beneath this property.
		Q_PROPERTY(QVariantMap entities
				   READ getEntitiesProperty
				   WRITE setEntities
				   NOTIFY entitiesChanged)

		/// @brief Name of the property entities.
		static QString ENTITIES_PN;

		/// @fn QVariantMap getEntitiesProperty();
		/// @brief Reading the property entities
		/// @return entitiesMap
		QVariantMap getEntitiesProperty();

		/// @fn void setEntities(QVariantMap newEntityMap);
		/// @brief Writing the property entities
		/// @param newEntityMap New value for entities
		void setEntities(QVariantMap newEntityMap);

		/// @property tweet_entities
		/// @brief Tweet Entities
		///
		/// tweetEntities is the attribute beneath this property.
		Q_PROPERTY(TweetEntities * tweet_entities
				   READ getEntitiesPtr
				   WRITE setEntities
				   NOTIFY entitiesChanged)

		/// @brief Name of the property entities.
		static QString TWEET_ENTITIES_PN;

		/// @fn TweetEntities * getEntitiesPtr();
		/// @brief Reading the property entities
		/// @return entitiesMap
		TweetEntities * getEntitiesPtr();

		/// @fn void setEntities(TweetEntities * newEntityMap);
		/// @brief Writing the property entities
		/// @param newEntityMap New value for entities
		void setEntities(TweetEntities * newEntityMap);

		// favorite_count
		/// @property favorite_count
		/// @brief How many times the tweet has been favorited ?
		///
		/// favoriteCount is the attribute beneath this property.
		Q_PROPERTY(int favorite_count
				   READ getFavoriteCount
				   WRITE setFavoriteCount
				   NOTIFY favoriteCountChanged)

		/// @brief Name of the property favorite_count.
		static QString FAVORITE_COUNT_PN;

		// favorited
		/// @property favorited
		/// @brief Is the tweet favorited ?
		///
		/// favoritedTweet is the attribute beneath this property.
		Q_PROPERTY(bool favorited
				   READ isFavorited
				   WRITE setFavorited
				   NOTIFY favoritedChanged)

		/// @brief Name of the property favorited.
		static QString FAVORITED_PN;

		// filter_level
		/// @property filter_level
		/// @brief Attribute to filter tweets in Streaming API.
		///
		/// filterLevel is the attribute beneath this property.
		Q_PROPERTY(QString filter_level
				   READ getFilterLevel
				   WRITE setFilterLevel
				   NOTIFY filterLevelChanged)

		/// @brief Name of the property filter_level.
		static QString FILTER_LEVEL_PN;

		// id
		/// @property id
		/// @brief Tweet ID
		///
		/// tweetID is the attribute beneath this property.
		Q_PROPERTY(qlonglong id
				   READ getID
				   WRITE setID
				   NOTIFY idChanged)

		/// @brief Name of the property id.
		static QString ID_PN;

		// id_str
		/// @property id_str
		/// @brief String version of the tweet ID.
		///
		/// tweetIDstr is the attribute beneath this property.
		Q_PROPERTY(QString id_str
				   READ getIDstr
				   WRITE setIDstr
				   NOTIFY idChanged)

		/// @brief Name of the property id_str.
		static QString ID_STR_PN;

		// in_reply_to_screen_name
		/// @property in_reply_to_screen_name
		/// @brief Screen name corresponding to the user ID in_reply_to_user_id
		///
		/// replyToScreenName is the attribute beneath this property.
		Q_PROPERTY(QString in_reply_to_screen_name
				   READ getInReplyToScreenName
				   WRITE setInReplyToScreenName
				   NOTIFY inReplyToScreenNameChanged)

		/// @brief Name of the property in_reply_to_screen_name.
		static QString IN_REPLY_TO_SCREEN_NAME_PN;

		// in_reply_to_status_id
		/// @property in_reply_to_status_id
		/// @brief Property corresponding to replyToTweetID
		///
		/// replyToTweetID is the attribute beneath this property.
		Q_PROPERTY(qlonglong in_reply_to_status_id
				   READ getInReplyToStatusID
				   WRITE setInReplyToStatusID
				   NOTIFY inReplyToStatusIDChanged)

		/// @brief Name of the property in_reply_to_status_id.
		static QString IN_REPLY_TO_STATUS_ID_PN;

		// in_reply_to_status_id_str
		/// @property in_reply_to_status_id_str
		/// @brief String form of in_reply_to_status_id
		///
		/// replyToTweetIDstr is the attribute beneath this property.
		Q_PROPERTY(QString in_reply_to_status_id_str
				   READ getInReplyToStatusIDstr
				   WRITE setInReplyToStatusIDstr
				   NOTIFY inReplyToStatusIDChanged)

		/// @brief Name of the property in_reply_to_status_id_str.
		static QString IN_REPLY_TO_STATUS_ID_STR_PN;

		// in_reply_to_user_id
		/// @property in_reply_to_user_id
		/// @brief Property corresponding to replyToUserID
		///
		/// replyToUserID is the attribute beneath this property.
		Q_PROPERTY(qlonglong in_reply_to_user_id
				   READ getInReplyToUserID
				   WRITE setInReplyToUserID
				   NOTIFY inReplyToUserIDChanged)

		/// @brief Name of the property in_reply_to_user_id.
		static QString IN_REPLY_TO_USER_ID_PN;

		// in_reply_to_user_id_str
		/// @property in_reply_to_user_id_str
		/// @brief String version of in_reply_to_user_id
		///
		/// replyToUserIDstr is the attribute beneath this property.
		Q_PROPERTY(QString in_reply_to_user_id_str
				   READ getInReplyToUserIDstr
				   WRITE setInReplyToUserIDstr
				   NOTIFY inReplyToUserIDChanged)

		/// @brief Name of the property in_reply_to_user_id_str.
		static QString IN_REPLY_TO_USER_ID_STR_PN;

		// lang
		/// @property lang
		/// @brief Idiom used to write the tweet
		///
		/// language is the attribute beneath the property.
		Q_PROPERTY(QString lang
				   READ getLang
				   WRITE setLang
				   NOTIFY langChanged)

		/// @brief Name of the property lang.
		static QString LANG_PN;

		// possibly_sensitive
		/// @property possibly_sensitive
		/// @brief Is the content of the tweet sensible
		///
		/// sensibleTweet is the attribute beneath this property.
		Q_PROPERTY(bool possibly_sensitive
				   READ isPossiblySensitive
				   WRITE setPossiblySensitive
				   NOTIFY possiblySensitiveChanged)

		/// @brief Name of the property possibly_sensitive.
		static QString POSSIBLY_SENSITIVE_PN;

		// place
		/// @property place
		/// @brief Place where the tweet was supposed to be written
		///
		/// tweetPlace is the attribute beneath this property.
		Q_PROPERTY(QVariantMap place
				   READ getPlaceProperty
				   WRITE setPlace
				   NOTIFY placeChanged)

		/// @brief Name of the property place.
		static QString PLACE_PN;

		/// @fn QVariantMap getPlaceProperty();
		/// @brief Reading the property place
		/// @return tweetPlace
		QVariantMap getPlaceProperty();

		/// @fn void setPlace(QVariantMap newEntityMap);
		/// @brief Writing the property place
		/// @param newEntityMap New value for tweetPlace
		void setPlace(QVariantMap newEntityMap);

		/// @property tweet_place
		/// @brief Place where the tweet was supposed to be posted
		///
		/// tweetPlace is the attribute beneath this property.
		Q_PROPERTY(TwitterPlace * tweet_place
				   READ getPlacePtr
				   WRITE setPlace
				   NOTIFY placeChanged)

		/// @brief Name of the property tweet_place.
		static QString TWEET_PLACE_PN;

		/// @fn TwitterPlace * getPlacePtr();
		/// @brief Reading the property tweet_place
		/// @return tweetPlace
		TwitterPlace * getPlacePtr();

		/// @fn void setPlace(TwitterPlace * newEntityMap);
		/// @brief Writing the property tweet_place
		/// @param newEntityMap New value for tweetPlace
		void setPlace(TwitterPlace * newValue);

		// retweet_count
		/// @property retweet_count
		/// @brief How many times the tweet has been retweeted ?
		///
		/// retweetCount is the attribute beneath this property.
		Q_PROPERTY(int retweet_count
				   READ getRetweetCount
				   WRITE setRetweetCount
				   NOTIFY retweetCountChanged)

		/// @brief Name of the property retweet_count.
		static QString RETWEET_COUNT_PN;

		// retweeted
		/// @property retweeted
		/// @brief Is the tweet retweeted by the user of the account ?
		///
		/// <strong>It does not mean that the tweet is a retweet !</strong>
		///
		/// retweetedTweet is the attribute beneath this property.
		Q_PROPERTY(bool retweeted
				   READ isRetweetedByMe
				   WRITE setRetweeted
				   NOTIFY retweetedChanged)

		/// @brief Name of the property retweeted.
		static QString RETWEETED_PN;

		// retweeted_status
		/// @property retweeted_status
		/// @brief Serializable form of retweetedTweet
		///
		///  is the attribute beneath this property.
		Q_PROPERTY(QVariantMap retweeted_status
				   READ getRetweetedStatusVariant
				   WRITE setRetweetedStatus
				   NOTIFY retweetedStatusChanged)

		/// @brief Name of the property retweeted_status.
		static QString RETWEETED_STATUS_PN;

		/// @property retweet
		/// @brief The retweet to display in a TweetPane
		///
		/// retweetSource is the attribute beneath this property.
		Q_PROPERTY(Tweet * retweet
				   READ getRetweetedStatus
				   WRITE setRetweetedStatus
				   NOTIFY retweetedStatusChanged)

		/// @brief Name of the property retweet.
		static QString RETWEET_PN;

		// scopes
		/// @property scopes
		/// @brief Values dealing with the delivery of the tweet
		///
		/// tweetScopes is the attribute beneath this property.
		Q_PROPERTY(QVariantMap scopes
				   READ getScopes
				   WRITE setScopes
				   NOTIFY scopesChanged)

		/// @brief Name of the property scopes.
		static QString SCOPES_PN;

		// source
		/// @property source
		/// @brief Source of the tweet (Twitter client)
		///
		/// sourceClient is the attribute beneath this property.
		Q_PROPERTY(QString source
				   READ getSource
				   WRITE setSource
				   NOTIFY sourceChanged)

		/// @brief Name of the property source.
		static QString SOURCE_PN;

		// text
		/// @property text
		/// @brief Content of the tweet (the famous 140 characters)
		///
		/// tweet is the attribute beneath this property.
		Q_PROPERTY(QString text
				   READ getText
				   WRITE setText
				   NOTIFY textChanged)

		/// @brief Name of the property text.
		static QString TEXT_PN;

		// truncated
		/// @property truncated
		/// @brief Is the tweet truncated ?
		///
		/// truncatedTweet is the attribute beneath this property.
		Q_PROPERTY(bool truncated
				   READ isTruncated
				   WRITE setTruncated
				   NOTIFY truncatedChanged)

		/// @brief Name of the property truncated.
		static QString TRUNCATED_PN;

		// user
		/// @property user
		/// @brief User who wrote the tweet
		///
		/// profile is the attribute beneath this property.
		Q_PROPERTY(QVariantMap user
				   READ getUserProperty
				   WRITE setUser
				   NOTIFY userChanged)

		/// @brief Name of the property user.
		static QString USER_PN;

		/// @fn QVariantMap getUserProperty();
		/// @brief Reading the property user
		/// @return userMap
		QVariantMap getUserProperty();

		/// @fn void setUser(QVariantMap newUserMap);
		/// @brief Writing the property user
		/// @param newUserMap New value for user
		void setUser(QVariantMap newUserMap);

		/// @property author
		/// @brief User who wrote the tweet. Used to get information
		/// to display about the author of the tweet (in a TweetPane).
		///
		/// profile is the attribute beneath this property.
		Q_PROPERTY(UserInfos * author
				   READ getAuthor
				   WRITE setAuthor
				   NOTIFY userChanged)

		/// @brief Name of the property author.
		static QString AUTHOR_PN;

		// withheld_copyright
		/// @property withheld_copyright
		/// @brief Tweet censored due to a DMCA complaint (copyright violation).
		///
		/// WithheldCopyright is the attribute beneath this property.
		Q_PROPERTY(bool withheld_copyright
				   READ isWithheldCopyright
				   WRITE setWithheldCopyright
				   NOTIFY withheldCopyrightChanged)

		/// @brief Name of the property withheld_copyright.
		static QString WITHHELD_COPYRIGHT_PN;

		// withheld_in_countries
		/// @property withheld_in_countries
		/// @brief Countries where the tweet is censored
		///
		/// withheldInCountries is the attribute beneath this property.
		Q_PROPERTY(QStringList withheld_in_countries
				   READ getWithheldInCountries
				   WRITE setWithheldInCountries
				   NOTIFY withheldInCountriesChanged)

		/// @brief Name of the property withheld_in_countries.
		static QString WITHHELD_IN_COUNTRIES_PN;

		// withheld_scope
		/// @property withheld_scope
		/// @brief Indicates what is withheld : the tweet or the user.
		///
		/// withheldScope is the attribute beneath this property.
		Q_PROPERTY(QString withheld_scope
				   READ getWithheldScope
				   WRITE setWithheldScope
				   NOTIFY withheldScopeChanged)

		/// @brief Name of the property withheld_scope.
		static QString WITHHELD_SCOPE_PN;

	signals:
		/// @fn void entitiesChanged();
		/// @brief Emitted when the entities property changes
		void entitiesChanged();

		/// @fn void inReplyToUserIDChanged();
		/// @brief Emitted when the in_reply_to_user_id and
		/// in_reply_to_user_id_str properties change
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

		/// @fn void inReplyToStatusIDChanged();
		/// @brief Emitted when the in_reply_to_status_id_str and
		/// in_reply_to_status_id_str properties change.
		void inReplyToStatusIDChanged();

		/// @fn void userChanged();
		/// @brief Emitted when the user and author properties change
		void userChanged();

		/// @fn void retweetedChanged();
		/// @brief Emitted when the retweeted property changes
		void retweetedChanged();

		/// @fn void sourceChanged();
		/// @brief Emitted when the source property changes
		void sourceChanged();

		/// @fn void idChanged();
		/// @brief Emitted when the id and id_str properties change
		void idChanged();

		/// @fn void textChanged();
		/// @brief Emitted when the text property changes
		void textChanged();

		/// @fn void possiblySensitiveChanged();
		/// @brief Emitted when the possibly_sensitive property changes
		void possiblySensitiveChanged();

		/// @fn void retweetedStatusChanged();
		/// @brief Emitted when the retweeted_status and retweet properties change
		void retweetedStatusChanged();

		/// @fn void retweetInfosChanged();
		/// @brief Emitted when the current_user_retweet and retweet_infos
		/// properties change
		void retweetInfosChanged();

		/// @fn void contributorsChanged();
		/// @brief Emitted when the contributors property changes.
		void contributorsChanged();

		/// @fn void coordinatesChanged();
		/// @brief Emitted when the coordinates property changes.
		void coordinatesChanged();

		/// @fn void favoriteCountChanged();
		/// @brief Emitted when the favorite_count property changes.
		void favoriteCountChanged();

		/// @fn void filterLevelChanged();
		/// @brief Emitted when the filter_level property changes.
		void filterLevelChanged();

		/// @fn void langChanged();
		/// @brief Emitted when the property lang changes.
		void langChanged();

		/// @fn void placeChanged();
		/// @brief Emitted when the property place changes.
		void placeChanged();

		/// @fn void scopesChanged();
		/// @brief Emitted when the property scopes changes.
		void scopesChanged();

		/// @fn void withheldCopyrightChanged();
		/// @brief Emitted when the property withheld_copyright changes.
		void withheldCopyrightChanged();

		/// @fn void withheldInCountriesChanged();
		/// @brief Emitted when the property withheld_in_countries changes.
		void withheldInCountriesChanged();

		/// @fn void withheldScopeChanged();
		/// @brief Emitted when the property withheld_scope changes.
		void withheldScopeChanged();


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
		/// It is a pointer on a tweet to avoid the compiler error C2460 (with
		/// MSVC compilers).
		Tweet * retweetSource;

		/// @brief Informations about a potential retweet of this tweet made by
		/// the user.
		RetweetInfos retweetInfos;

		// Favorite management

		/// @brief Boolean indicating if the tweet was favorited
		bool favoritedTweet;

		/// @brief Number of times of this tweet was favorited
		int favoriteCount;

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

		// Withholding

		/// @brief Tweet censored due to a DMCA complaint (copyright violation).
		bool withheldCopyright;

		/// @brief Countries where the tweet is censored
		QStringList withheldInCountries;

		/// @brief Indicates what is withheld : the tweet or the user.
		QString withheldScope;

		// Miscanellous

		/// @brief truncated
		bool truncatedTweet;

		/// @brief Contributors
		ContributorList tweetContributors;

		/// @brief Coordinates where the tweet was supposed to be posted
		Coordinates tweetCoordinates;

		/// @brief Filter level
		QString filterLevel;

		/// @brief Idiom used to write the tweet
		QString language;

		/// @brief Place where the tweet was supposed to be posted
		TwitterPlace tweetPlace;

		/// @brief Values dealing with the delivery of the tweet
		QVariantMap tweetScopes;


	public:
		/// @fn Tweet * getShownTweet();
		/// @brief Returns the "shown tweet".
		///
		/// The shown tweet is the original tweet. If the Tweet object is a
		/// retweet, the shown tweet will be the retweetSource and if it's not
		/// a retweet, it will be the object.
		/// @return retweetSource if the object is a retweet, this otherwise.
		Tweet * getShownTweet();

		/////////////////////////
		// Getters and setters //
		/////////////////////////

		// contributors
		/// @fn ContributorList getContributors();
		/// @brief Reading contributors
		/// @return tweetContributors
		ContributorList getContributors();

		/// @fn void setContributors(ContributorList newValue);
		/// @brief Writing contributors
		/// @param newValue New value for tweetContributors
		void setContributors(ContributorList newValue);

		// coordinates
		/// @fn Coordinates getCoordinates();
		/// @brief Reading coordinates
		/// @return tweetContributors
		Coordinates getCoordinates();

		/// @fn void setCoordinates(Coordinates newValue);
		/// @brief Writing coordinates
		/// @param newValue New value for tweetContributors
		void setCoordinates(Coordinates newValue);

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

		// lang
		/// @fn QString getLang();
		/// @brief Getter on lang
		/// @return The value of lang
		QString getLang();

		/// @fn void setLang(QString newLang);
		/// @brief Setter on lang
		/// @param newLang The new value of lang
		void setLang(QString newLang);

		// place
		/// @fn TwitterPlace getPlace();
		/// @brief Reading place
		/// @return tweetPlace
		TwitterPlace getPlace();

		/// @fn void setPlace(TwitterPlace newValue);
		/// @brief Writing place
		/// @param newValue New value for tweetPlace
		void setPlace(TwitterPlace newValue);

		// scopes
		/// @fn QVariantMap getScopes();
		/// @brief Reading scopes
		/// @return tweetScopes
		QVariantMap getScopes();

		/// @fn void setScopes(QVariantMap newValue);
		/// @brief Writing scopes
		/// @param newValue New value for tweetScopes
		void setScopes(QVariantMap newValue);

		// truncated
		/// @fn bool isTruncated();
		/// @brief Reading truncated
		/// @return truncatedTweet
		bool isTruncated();

		/// @fn void setTruncated(bool newValue);
		/// @brief Writing truncated
		/// @param newValue New value for truncated
		void setTruncated(bool newValue);

		// favorite_count
		/// @fn int getFavoriteCount();
		/// @brief Reading favorite_count
		/// @return favoriteCount
		int getFavoriteCount();

		/// @fn void setFavoriteCount(int newValue);
		/// @brief Writing favorite_count
		/// @param newValue New value for favoriteCount
		void setFavoriteCount(int newValue);

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
		/// @fn bool isRetweetedByMe();
		/// @brief Reading retweeted
		/// @return retweetedTweet
		bool isRetweetedByMe();

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
		/// @brief Reading id
		///
		/// <strong>Not recommended because of
		/// <a href="https://bugreports.qt-project.org/browse/QTBUG-28560">a bug
		/// on Qt JSON writing numbers. Use the method with the string ID
		/// instead.</a></strong>
		/// @return tweetID
		qlonglong getID();

		/// @fn void setID(qlonglong newValue);
		/// @brief Writing id
		///
		/// <strong>Not recommended because of
		/// <a href="https://bugreports.qt-project.org/browse/QTBUG-28560">a bug
		/// on Qt JSON writing numbers. Use the method with the string ID
		/// instead.</a></strong>
		/// @param newValue New value for id
		void setID(qlonglong newValue);

		// id_str
		/// @fn QString getIDstr();
		/// @brief Reading id_str
		/// @return tweetIDstr
		QString getIDstr();

		/// @fn void setIDstr(QString newValue);
		/// @brief Writing id_str
		/// @param newValue New value for id_str
		void setIDstr(QString newValue);

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

		// possibly_sensible
		/// @fn bool isPossiblySensitive();
		/// @brief Reading possibly_sensitive
		/// @return sensibleTweet
		bool isPossiblySensitive();

		/// @fn void setPossiblySensitive(bool newValue);
		/// @brief Writing possibly_sensitive
		/// @param newValue New value for sensibleTweet
		void setPossiblySensitive(bool newValue);

		// retweeted_status
		/// @fn Tweet * getRetweetedStatus();
		/// @brief Reading retweeted_status
		/// @return retweetSource
		Tweet * getRetweetedStatus();

		/// @fn void setRetweetedStatus(Tweet * retweet);
		/// @brief Writing retweeted_status
		/// @param retweet The new value of the property
		void setRetweetedStatus(Tweet * retweet);

		/// @fn QVariantMap getRetweetedStatusVariant();
		/// @brief Reading retweeted_status
		/// @return retweetSource->toVariant();
		QVariantMap getRetweetedStatusVariant();

		/// @fn void setRetweetedStatus(QVariantMap statusMap);
		/// @brief Writing retweeted_status
		/// @param statusMap The new value of the property
		void setRetweetedStatus(QVariantMap statusMap);

		// retweet_infos
		/// @fn RetweetInfos * getRetweetInfos();
		/// @brief Reading retweet_infos
		/// @return retweetInfos
		RetweetInfos * getRetweetInfos();

		/// @fn void setRetweetInfos(RetweetInfos * newInfos);
		/// @brief Writing retweet_infos
		/// @param newInfos The new value of the property
		void setRetweetInfos(RetweetInfos * newInfos);

		// current_user_retweet
		/// @fn QVariantMap getRetweetInfosVariant();
		/// @brief Reading current_user_retweet
		/// @return retweetInfos.toVariant();
		QVariantMap getRetweetInfosVariant();

		/// @fn void setRetweetInfos(QVariantMap newInfos);
		/// @brief Writing current_user_retweet
		/// @param newInfos The new value of the property
		void setRetweetInfos(QVariantMap newInfos);

		// filter_level
		/// @fn QString getFilterLevel();
		/// @brief Reading filter_level
		/// @return filterLevel
		QString getFilterLevel();

		/// @fn void setFilterLevel(QString newValue);
		/// @brief Writing filter_level
		/// @param newValue New value for filterLevel
		void setFilterLevel(QString newValue);

		// withheld_copyright
		/// @fn bool isWithheldCopyright();
		/// @brief Reading withheld_copyright
		/// @return withheldCopyright
		bool isWithheldCopyright();

		/// @fn void setWithheldCopyright(bool newValue);
		/// @brief Writing withheld_copyright
		/// @param newValue New value for withheldCopyright
		void setWithheldCopyright(bool newValue);

		// withheld_in_countries
		/// @fn QStringList getWithheldInCountries();
		/// @brief Reading withheld_in_countries
		/// @return withheldInCountries
		QStringList getWithheldInCountries();

		/// @fn void setWithheldInCountries(QStringList newValue);
		/// @brief Writing withheld_in_countries
		/// @param newValue New value for withheldInCountries
		void setWithheldInCountries(QStringList newValue);

		// withheld_scope
		/// @fn QString isWithheldScope();
		/// @brief Reading withheld_scope
		/// @return withheldScope
		QString getWithheldScope();

		/// @fn void setWithheldScope(QString newValue);
		/// @brief Writing withheld_scope
		/// @param newValue New value for withheldScope
		void setWithheldScope(QString newValue);


		//////////////////////////////////
		// Methods used by the QML View //
		//////////////////////////////////

		/// @fn Q_INVOKABLE QString getDisplayText();
		/// @brief Getting the content of tweet under the form of a HTML string.
		///
		/// It is used to display the tweet in a QML View.
		///	@return The text to display (in a TweetPane)
		Q_INVOKABLE QString getDisplayText();

		/// @fn Q_INVOKABLE QString getDisplaySource();
		/// @brief Getting the name of the Twitter client used to post the tweet
		/// under the form of a HTML string.
		///
		/// It is used to display the client name in a QML View.
		///	@return The text to display
		Q_INVOKABLE QString getDisplaySource();

		/// @fn Q_INVOKABLE QString whenWasItPosted(bool encloseInHtmlTag = true);
		/// @brief When the tweet was posted ?
		/// @param encloseInHtmlTag Boolean indicating if the date has to be
		/// enclosed in a HTML tag linked to the tweet on twitter.com (default : true).
		///	@return A string telling when it was posted
		Q_INVOKABLE QString whenWasItPosted(bool encloseInHtmlTag = true);

		/// @fn Q_INVOKABLE bool isRetweet() const;
		/// @brief Method indicating if the tweet is a retweet or not
		///	@return true if it is a retweet, false otherwise.
		Q_INVOKABLE bool isRetweet() const;

		/// @fn Q_INVOKABLE bool isReply();
		/// @brief Method indicating if the tweet replies to another one or not.
		///	@return true if it is a reply to a tweet, false otherwise.
		Q_INVOKABLE bool isReply();

		/// @fn Q_INVOKABLE bool isRetweetedByPeople();
		/// @brief Method indicating if the tweet was retweeted by other users.
		///	@return true if it was retweeted, false otherwise.
		Q_INVOKABLE bool isRetweetedByPeople();

		/// @fn Q_INVOKABLE QUrl getTweetURL();
		/// @brief Getting the URL of the tweet on twitter.com
		///	@return URL of the tweet on twitter.com. It lloks like
		/// https://twitter.com/#!/screen_name/status/id
		Q_INVOKABLE QUrl getTweetURL();
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
