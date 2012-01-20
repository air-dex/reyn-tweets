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

#include "hashtaglist.hpp"
#include "medialist.hpp"
#include "reyntweetsmappable.hpp"
#include "urlentitylist.hpp"
#include "usermentionlist.hpp"


/// @class TweetEntities
/// @brief Entities of a tweet, such as its hashtags, its mentions and its URLs.
class TweetEntities : public ReynTweetsMappable
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
		// media
		/// @property media
		/// @brief Medias
		Q_PROPERTY(QVariantList media
				   READ getMediaProperty
				   WRITE setMedia)

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
		Q_PROPERTY(QVariantList urls
				   READ getURLsProperty
				   WRITE setURLs)

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
		Q_PROPERTY(QVariantList user_mentions
				   READ getUserMentionsProperty
				   WRITE setUserMentions)

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
		Q_PROPERTY(QVariantList hashtags
				   READ getHashtagsProperty
				   WRITE setHashtags)

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
		MediaList medias;

		/// @brief URLs
		URLEntityList tweetURLs;

		/// @brief User mentions
		UserMentionList mentions;

		/// @brief Hashtags
		HashtagList tweetHashtags;


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
