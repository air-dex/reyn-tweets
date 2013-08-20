/// @file tweetentities.hpp
/// @brief Header of TweetEntities
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

#ifndef TWEETENTITIES_HPP
#define TWEETENTITIES_HPP

#include "../json/jsonobject.hpp"
#include "../../controls/listhandlers/hashtagshandler.hpp"
#include "../../controls/listhandlers/mediashandler.hpp"
#include "../../controls/listhandlers/mentionshandler.hpp"
#include "../../controls/listhandlers/urlshandler.hpp"


/// @class TweetEntities
/// @brief Entities of a tweet, such as its hashtags, its mentions and its URLs.
/// @see https://dev.twitter.com/docs/platform-objects/entities
class TweetEntities : public JsonObject
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn TweetEntities();
		/// @brief Default constructor
		TweetEntities();

		/// @fn virtual ~TweetEntities();
		/// @brief Destructor
		virtual ~TweetEntities();

		/// @fn TweetEntities(const TweetEntities & entities);
		/// @brief Copy constructor
		/// @param entities Entities to copy
		TweetEntities(const TweetEntities & entities);

		/// @fn const TweetEntities & operator=(const TweetEntities & entities);
		/// @brief Affectation
		/// @param entities Entities to copy
		/// @return Copy of the original entities
		const TweetEntities & operator=(const TweetEntities & entities);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

		/// @fn virtual void reset();
		/// @brief Resets the mappable to a default value
		virtual void reset();

		/////////////////////
		// JSON conversion //
		/////////////////////

		/// @fn virtual void fillWithVariant(QJsonObject json);
		/// @brief Filling the object with a QJsonObject.
		///
		/// The method is virtual because its implementation depends on the
		/// object type.
		/// @param json The QJsonObject used to fill the JsonObject
		virtual void fillWithVariant(QJsonObject json);

		/// @fn virtual QJsonObject toVariant() const;
		/// @brief Getting a QJsonObject representation of the object
		/// @return The QJsonObject representation
		virtual QJsonObject toVariant() const;

	private:
		/// @fn void recopie(const TweetEntities & entities);
		/// @brief Copy of a TwitterEntities
		/// @param entities Entities to copy
		void recopie(const TweetEntities & entities);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const TweetEntities & entities);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param entities Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const TweetEntities & entities);

		/// @fn friend QDataStream & operator>>(QDataStream & in, TweetEntities & entities);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param entities Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, TweetEntities & entities);


	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		// media
		/// @property media
		/// @brief Medias
		///
		/// mediasHandler is the attribute beneath this property.
		Q_PROPERTY(MediasHandler * media
				   READ getMediasHandler
				   NOTIFY mediaChanged)

		/// @brief Name of the property media.
		static QString MEDIA_PN;

		/// @brief Handler for medias
		MediasHandler mediasHandler;

		/// @fn MediasHandler * getMediasHandler();
		/// @brief Reading the property media
		/// @return mediaList
		MediasHandler * getMediasHandler();

		// urls
		/// @property urls
		/// @brief URLs written in the tweet
		///
		/// urlsHandler is the attribute beneath this property.
		Q_PROPERTY(UrlsHandler * urls
				   READ getURLsHandler
				   NOTIFY urlsChanged)

		/// @brief Name of the property urls.
		static QString URLS_PN;

		/// @brief Handler for urls
		UrlsHandler urlsHandler;

		/// @fn UrlsHandler * getURLsHandler();
		/// @brief Reading the property urls
		/// @return urlsList
		UrlsHandler * getURLsHandler();

		// user_mentions
		/// @property user_mentions
		/// @brief Users mentionned in the tweet
		///
		/// mentionsHandler is the attribute beneath this property.
		Q_PROPERTY(MentionsHandler * user_mentions
				   READ getMentionsHandler
				   NOTIFY userMentionsChanged)

		/// @brief Name of the property user_mentions.
		static QString USER_MENTIONS_PN;

		/// @brief Handler for user_mentions
		MentionsHandler mentionsHandler;

		/// @fn MentionsHandler * getMentionsHandler();
		/// @brief Reading the property user_mentions
		/// @return userMentionsList
		MentionsHandler * getMentionsHandler();

		// hashtags
		/// @property hashtags
		/// @brief Hashtags in the tweet
		///
		/// hashtagsHandler is the attribute beneath this property.
		Q_PROPERTY(HashtagsHandler * hashtags
				   READ getHashtagsHandler
				   NOTIFY hashtagsChanged)

		/// @brief Name of the property hashtags.
		static QString HASHTAGS_PN;

		/// @brief Handler for hashtags
		HashtagsHandler hashtagsHandler;

		/// @fn HashtagsHandler * getHashtagsHandler();
		/// @brief Reading the property hashtags
		/// @return hashtagsList
		HashtagsHandler * getHashtagsHandler();

	signals:
		/// @fn void mediaChanged();
		/// @brief Signal emitted when the property media has got a new value.
		void mediaChanged();

		/// @fn void urlsChanged();
		/// @brief Signal emitted when the property urls has got a new value.
		void urlsChanged();

		/// @fn void userMentionsChanged();
		/// @brief Signal emitted when the property user_mentions has got
		/// a new value.
		void userMentionsChanged();

		/// @fn void hashtagsChanged();
		/// @brief Signal emitted when the property hashtags has got a new value.
		void hashtagsChanged();


	//////////////
	// Entities //
	//////////////

	protected:
		/// @brief Medias
		MediaList & medias;

		/// @brief URLs
		URLEntityList & tweetURLs;

		/// @brief User mentions
		UserMentionList & mentions;

		/// @brief Hashtags
		HashtagList & tweetHashtags;


	///////////////
	// Accessors //
	///////////////

	public:
		/// @fn MediaList getMedia();
		/// @brief Reading medias
		/// @return medias
		MediaList getMedia();

		/// @fn void setMedia(MediaList newMedia);
		/// @brief Writing medias
		/// @param newMedia New value for medias
		void setMedia(MediaList newMedia);

		/// @fn URLEntityList getURLs();
		/// @brief Reading tweetURLs
		/// @return tweetURLs
		URLEntityList getURLs();

		/// @fn void setURLs(URLEntityList newURLs);
		/// @brief Writing tweetURLs
		/// @param newURLs New value for tweetURLs
		void setURLs(URLEntityList newURLs);

		/// @fn UserMentionList getUserMentions();
		/// @brief Reading userMentions
		/// @return userMentions
		UserMentionList getUserMentions();

		/// @fn void setUserMentions(UserMentionList newUserMentions);
		/// @brief Writing userMentions
		/// @param newUserMentions New value for userMentions
		void setUserMentions(UserMentionList newUserMentions);

		/// @fn HashtagList getHashtags();
		/// @brief Reading tweetHashtags
		/// @return tweetHashtags
		HashtagList getHashtags();

		/// @fn void setHashtags(HashtagList newHashtags);
		/// @brief Writing tweetHashtags
		/// @param newHashtags New value for tweetHashtags
		void setHashtags(HashtagList newHashtags);


	//////////////////////////
	// List of all entities //
	//////////////////////////

		/// @fn QList<TweetEntity *> getAllEntitiesList();
		/// @brief Getting a list with pointers on all the Tweet Entities.
		///
		/// The entities are sorted decreasingly with their first index bound
		/// in the tweet.
		/// @return List with pointers on all the entities
		QList<TweetEntity *> getAllEntitiesList();

	private:
		/// @fn void insertEntity(TweetEntity & entity,
		///						  QList<TweetEntity *> & entityList);
		/// @brief Inserting an entity in the list of all the entities
		/// @param entity The entity to insert
		/// @param entityList The list to insert the entity
		void insertEntity(TweetEntity & entity,
						  QList<TweetEntity *> & entityList);
};

// Serialization of TweetEntities
Q_DECLARE_METATYPE(TweetEntities)

/// @fn QDataStream & operator<<(QDataStream & out, const TweetEntities & entities);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param entities Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const TweetEntities & entities);

/// @fn QDataStream & operator>>(QDataStream & in, TweetEntities & entities);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param entities Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, TweetEntities & entities);

#endif // TWEETENTITIES_HPP
