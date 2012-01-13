/// @file tweetentities.hpp
/// @brief Header of TweetEntities
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

#ifndef TWEETENTITIES_HPP
#define TWEETENTITIES_HPP

#include <QList>
#include "hashtag.hpp"
#include "media.hpp"
#include "reyntweetsserializable.hpp"
#include "urlentity.hpp"
#include "usermention.hpp"

/// @class TweetEntities
/// @brief Entities of a tweet, such as its hashtags, its mentions and its URLs.
class TweetEntities : public ReynTweetsSerializable
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
		/// @fn void fillWithPropertiesMaps();
		/// @brief Filling serializable fields with thecorresponding  property maps
		void fillWithPropertiesMaps();

		/// @fn void updateAllProperties();
		/// @brief Updating all the properties
		void updateAllProperties();

		// media
		/// @property media
		/// @brief Medias
		Q_PROPERTY(QVariantList media
				   READ getMediaList
				   WRITE setMediaList)

		/// @brief List of Medias under the form of maps.
		QVariantList mediaList;

		/// @fn QVariantList getMediaList();
		/// @brief Reading the property media
		/// @return mediaList
		QVariantList getMediaList();

		/// @fn void setMediaList(QVariantList newMediaList);
		/// @brief Writing the property media
		/// @param newMediaList New value for the property media
		void setMediaList(QVariantList newMediaList);

		/// @fn void updateMedia();
		/// @brief Updating the property media
		void updateMedia();

		// urls
		/// @property urls
		/// @brief URLs written in the tweet
		Q_PROPERTY(QVariantList urls
				   READ getURLList
				   WRITE setURLList)

		/// @brief List of urls under the form of maps.
		QVariantList urlsList;

		/// @fn QVariantList getURLList();
		/// @brief Reading the property urls
		/// @return urlsList
		QVariantList getURLList();

		/// @fn void setURLList(QVariantList newURLList);
		/// @brief Writing the property urls
		/// @param newURLList New value for the property urls
		void setURLList(QVariantList newURLList);

		/// @fn void updateURLs();
		/// @brief Updating the property urls
		void updateURLs();

		// user_mentions
		/// @property user_mentions
		/// @brief Users mentionned in the tweet
		Q_PROPERTY(QVariantList user_mentions
				   READ getUserMentionsList
				   WRITE setUserMentionsList)

		/// @brief List of user mentions under the form of maps.
		QVariantList userMentionsList;

		/// @fn QVariantList getUserMentionsList();
		/// @brief Reading the property user_mentions
		/// @return userMentionsList
		QVariantList getUserMentionsList();

		/// @fn void setUserMentionsList(QVariantList newUserMentionsList);
		/// @brief Writing the property user_mentions
		/// @param newUserMentionsList New value for the property user_mentions
		void setUserMentionsList(QVariantList newUserMentionsList);

		/// @fn void updateUserMentions();
		/// @brief Updating the property user_mentions
		void updateUserMentions();

		// hashtags
		/// @property hashtags
		/// @brief Hashtags in the tweet
		Q_PROPERTY(QVariantList hashtags
				   READ getList
				   WRITE setList)

		/// @brief List of hashtags under the form of maps.
		QVariantList hashtagsList;

		/// @fn QVariantList getHashtagsList();
		/// @brief Reading the property hashtags
		/// @return hashtagsList
		QVariantList getHashtagsList();

		/// @fn void setHashtagsList(QVariantList newHashtagsList);
		/// @brief Writing the property hashtags
		/// @param newHashtagsList New value for the property hashtags
		void setHashtagsList(QVariantList newHashtagsList);

		/// @fn void updateHashtags();
		/// @brief Updating the property hashtags
		void updateHashtags();


	//////////////
	// Entities //
	//////////////

	protected:
		/// @brief Medias
		QList<Media> medias;

		/// @brief URLs
		QList<URLEntity> tweetURLs;

		/// @brief User mentions
		QList<UserMention> userMentions;

		/// @brief Hashtags
		QList<Hashtag> tweetHashtags;


	///////////////
	// Accessors //
	///////////////

	public:
		/// @fn QList<Media> getMedia();
		/// @brief Reading medias
		/// @return medias
		QList<Media> getMedia();

		/// @fn void setMedia(QList<Media> newMedia);
		/// @brief Writing medias
		/// @param newMedia New value for medias
		void setMedia(QList<Media> newMedia);

		/// @fn QList<URLEntity> getURLs();
		/// @brief Reading tweetURLs
		/// @return tweetURLs
		QList<URLEntity> getURLs();

		/// @fn void setURLs(QList<URLEntity> newURLs);
		/// @brief Writing tweetURLs
		/// @param newURLs New value for tweetURLs
		void setURLs(QList<URLEntity> newURLs);

		/// @fn QList<UserMention> getUserMentions();
		/// @brief Reading userMentions
		/// @return userMentions
		QList<UserMention> getUserMentions();

		/// @fn void setUserMentions(QList<UserMention> newUserMentions);
		/// @brief Writing userMentions
		/// @param newUserMentions New value for userMentions
		void setUserMentions(QList<UserMention> newUserMentions);

		/// @fn QList<Hashtag> getHashtags();
		/// @brief Reading tweetHashtags
		/// @return tweetHashtags
		QList<Hashtag> getHashtags();

		/// @fn void setHashtagsList(QList<Hashtag> newHashtags);
		/// @brief Writing tweetHashtags
		/// @param newHashtags New value for tweetHashtags
		void setHashtagsList(QList<Hashtag> newHashtags);
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

//////////
// Util //
//////////
/// @fn template <class T> QList<T> fillWithList(QVariantList entities);
/// @brief Converting a QVariantList serialized by QJSON into a list of
/// entities whose class is represented by the template parameter T.
/// @param entities List to convert
/// @return The corresponding list of entities
template <class T>
QList<T> fillWithList(QVariantList entities);

#endif // TWEETENTITIES_HPP
