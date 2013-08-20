/// @file tweetentities.hpp
/// @brief Header of TweetEntities
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2013 Romain Ducher
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

#ifndef TWEETENTITIES2_HPP
#define TWEETENTITIES2_HPP

#include "../json/jsonobject.hpp"
#include "hashtaglist.hpp"
#include "medialist.hpp"
#include "urlentitylist.hpp"
#include "usermentionlist.hpp"


/// @class TweetEntities
/// @brief Entities of a tweet, such as its hashtags, its mentions and its URLs.
/// @see https://dev.twitter.com/docs/platform-objects/entities
class TweetEntities2 : public JsonObject
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn TweetEntities();
		/// @brief Default constructor
		TweetEntities2();

		/// @fn virtual ~TweetEntities();
		/// @brief Destructor
		virtual ~TweetEntities2();

		/// @fn TweetEntities(const TweetEntities & entities);
		/// @brief Copy constructor
		/// @param entities Entities to copy
		TweetEntities2(const TweetEntities2 & entities);

		/// @fn const TweetEntities & operator=(const TweetEntities & entities);
		/// @brief Affectation
		/// @param entities Entities to copy
		/// @return Copy of the original entities
		const TweetEntities2 & operator=(const TweetEntities2 & entities);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn virtual void reset();
		/// @brief Resets the mappable to a default value
		virtual void reset();

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

		/// @fn virtual QJsonObject toJSON();
		/// @brief Getting a QJsonObject representation of the object
		/// @return The QJsonObject representation
		virtual QJsonObject toJSON();

	private:
		/// @fn void recopie(const TweetEntities & entities);
		/// @brief Copy of a TwitterEntities
		/// @param entities Entities to copy
		void recopie(const TweetEntities2 & entities);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const TweetEntities & entities);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param entities Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const TweetEntities2 & entities);

		/// @fn friend QDataStream & operator>>(QDataStream & in, TweetEntities & entities);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param entities Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, TweetEntities2 & entities);


	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		// media
		/// @property media
		/// @brief Medias
		///
		/// medias is the attribute beneath this property.
		Q_PROPERTY(QVariantList media
				   READ getMediaProperty
				   WRITE setMedia)

		/// @brief Name of the property media.
		static QString MEDIA_PN;

		/// @fn QVariantList getMediaProperty();
		/// @brief Reading the property media
		/// @return mediaList
		QVariantList getMediaProperty();

		/// @fn void setMedia(QVariantList newMediaList);
		/// @brief Writing the property media
		/// @param newMediaList New value for the property media
		void setMedia(QVariantList newMediaList);

		// urls
		/// @property urls
		/// @brief URLs written in the tweet
		///
		/// tweetURLs is the attribute beneath this property.
		Q_PROPERTY(QVariantList urls
				   READ getURLsProperty
				   WRITE setURLs)

		/// @brief Name of the property urls.
		static QString URLS_PN;

		/// @fn QVariantList getURLsProperty();
		/// @brief Reading the property urls
		/// @return urlsList
		QVariantList getURLsProperty();

		/// @fn void setURLs(QVariantList newURLList);
		/// @brief Writing the property urls
		/// @param newURLList New value for the property urls
		void setURLs(QVariantList newURLList);

		// user_mentions
		/// @property user_mentions
		/// @brief Users mentionned in the tweet
		///
		/// mentions is the attribute beneath this property.
		Q_PROPERTY(QVariantList user_mentions
				   READ getUserMentionsProperty
				   WRITE setUserMentions)

		/// @brief Name of the property user_mentions.
		static QString USER_MENTIONS_PN;

		/// @fn QVariantList getUserMentionsProperty();
		/// @brief Reading the property user_mentions
		/// @return userMentionsList
		QVariantList getUserMentionsProperty();

		/// @fn void setUserMentions(QVariantList newUserMentionsList);
		/// @brief Writing the property user_mentions
		/// @param newUserMentionsList New value for the property user_mentions
		void setUserMentions(QVariantList newUserMentionsList);

		// hashtags
		/// @property hashtags
		/// @brief Hashtags in the tweet
		///
		/// tweetHashtags is the attribute beneath this property.
		Q_PROPERTY(QVariantList hashtags
				   READ getHashtagsProperty
				   WRITE setHashtags)

		/// @brief Name of the property hashtags.
		static QString HASHTAGS_PN;

		/// @fn QVariantList getHashtagsProperty();
		/// @brief Reading the property hashtags
		/// @return hashtagsList
		QVariantList getHashtagsProperty();

		/// @fn void setHashtags(QVariantList newHashtagsList);
		/// @brief Writing the property hashtags
		/// @param newHashtagsList New value for the property hashtags
		void setHashtags(QVariantList newHashtagsList);


	//////////////
	// Entities //
	//////////////

	protected:
		/// @brief Medias
		MediaList2 medias;

		/// @brief URLs
		URLEntityList2 tweetURLs;

		/// @brief User mentions
		UserMentionList2 mentions;

		/// @brief Hashtags
		HashtagList2 tweetHashtags;


	///////////////
	// Accessors //
	///////////////

	public:
		/// @fn MediaList getMedia();
		/// @brief Reading medias
		/// @return medias
		MediaList2 getMedia();

		/// @fn void setMedia(MediaList newMedia);
		/// @brief Writing medias
		/// @param newMedia New value for medias
		void setMedia(MediaList2 newMedia);

		/// @fn URLEntityList getURLs();
		/// @brief Reading tweetURLs
		/// @return tweetURLs
		URLEntityList2 getURLs();

		/// @fn void setURLs(URLEntityList newURLs);
		/// @brief Writing tweetURLs
		/// @param newURLs New value for tweetURLs
		void setURLs(URLEntityList2 newURLs);

		/// @fn UserMentionList getUserMentions();
		/// @brief Reading userMentions
		/// @return userMentions
		UserMentionList2 getUserMentions();

		/// @fn void setUserMentions(UserMentionList newUserMentions);
		/// @brief Writing userMentions
		/// @param newUserMentions New value for userMentions
		void setUserMentions(UserMentionList2 newUserMentions);

		/// @fn HashtagList getHashtags();
		/// @brief Reading tweetHashtags
		/// @return tweetHashtags
		HashtagList2 getHashtags();

		/// @fn void setHashtags(HashtagList newHashtags);
		/// @brief Writing tweetHashtags
		/// @param newHashtags New value for tweetHashtags
		void setHashtags(HashtagList2 newHashtags);


	//////////////////////////
	// List of all entities //
	//////////////////////////

		/// @fn QList<TweetEntity *> getAllEntitiesList();
		/// @brief Getting a list with pointers on all the Tweet Entities.
		///
		/// The entities are sorted decreasingly with their first index bound
		/// in the tweet.
		/// @return List with pointers on all the entities
		QList<TweetEntity2 *> getAllEntitiesList();

	private:
		/// @fn void insertEntity(TweetEntity & entity,
		///						  QList<TweetEntity *> & entityList);
		/// @brief Inserting an entity in the list of all the entities
		/// @param entity The entity to insert
		/// @param entityList The list to insert the entity
		void insertEntity(TweetEntity2 & entity,
						  QList<TweetEntity2 *> & entityList);
};

// Serialization of TweetEntities
Q_DECLARE_METATYPE(TweetEntities2)

/// @fn QDataStream & operator<<(QDataStream & out, const TweetEntities & entities);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param entities Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const TweetEntities2 & entities);

/// @fn QDataStream & operator>>(QDataStream & in, TweetEntities & entities);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param entities Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, TweetEntities2 & entities);

#endif // TWEETENTITIES_HPP
