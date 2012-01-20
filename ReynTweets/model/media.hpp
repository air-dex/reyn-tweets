/// @file media.hpp
/// @brief Header of Media
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

#ifndef MEDIA_HPP
#define MEDIA_HPP

#include "mediasizes.hpp"
#include "urlentity.hpp"
#include "reyntweetsserializablelist.hpp"

/// @class Media
/// @brief Media in a tweet.
class Media : public URLEntity
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn Media();
		/// @brief Constructor
		Media();

		/// @fn virtual ~Media();
		/// @brief Destructor
		virtual ~Media();

		/// @fn Media(const Media & media);
		/// @brief Copy constructor
		/// @param media Media to copy
		Media(const Media & media);

		/// @fn const Media & operator=(const Media & media);
		/// @brief Affectation
		/// @param media Media to copy
		/// @return Copy of the original media
		const Media & operator=(const Media & media);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	protected:
		/// @fn void recopie(const Media & media);
		/// @brief Copy of a Media
		/// @param media Media to copy
		void recopie(const Media & media);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const Media & media);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param media Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const Media & media);

		/// @fn friend QDataStream & operator>>(QDataStream & in, Media & media);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param media Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, Media & media);

	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		// id
		/// @property id
		/// @brief User id
		Q_PROPERTY(qlonglong id
				   READ getID
				   WRITE setID)

		// id_str
		/// @property id_str
		/// @brief String version of id
		Q_PROPERTY(QString id_str
				   READ getIDstr
				   WRITE setIDstr)

		// media_url
		/// @property media_url
		/// @brief Media URL
		Q_PROPERTY(QString media_url
				   READ getMediaURL
				   WRITE setMediaURL)

		// media_url_https
		/// @property media_url_https
		/// @brief HTTPS version of media_url
		Q_PROPERTY(QString media_url_https
				   READ getMediaURLhttps
				   WRITE setMediaURLhttps)

		// type
		/// @property type
		/// @brief Media type
		Q_PROPERTY(QString type
				   READ getType
				   WRITE setType)

		// sizes
		/// @property sizes
		/// @brief Different sizes for the media
		Q_PROPERTY(QVariantMap sizes
				   READ getSizesProperty
				   WRITE setSizes)

		/// @fn QVariantList getSizesProperty();
		/// @brief Reading method for the property sizes
		/// @return sizesMap
		QVariantMap getSizesProperty();

		/// @fn void setSizes(QVariantMap newMap);
		/// @brief Writing method for the property sizes
		/// @param newMap New value for the property sizes
		void setSizes(QVariantMap newMap);


	//////////////////////
	// Media management //
	//////////////////////

	protected:
		/// @brief ID of the media
		qlonglong mediaID;

		/// @brief String version of mediaID
		QString mediaIDstr;

		/// @brief Media URL
		QString mediaURL;

		/// @brief Media URL (HTTPS version)
		QString mediaURLhttps;

		/// @brief Type of the media
		QString mediaType;

		/// @brief Media sizes
		MediaSizes mediaSizes;


	////////////////////////
	// Getter and setters //
	////////////////////////

	public:
		/// @fn qlonglong getID();
		/// @brief Reading mediaID
		/// @return mediaID
		qlonglong getID();

		/// @fn void setID(qlonglong newID);
		/// @brief Writing mediaID
		/// @param newID New value for mediaID
		void setID(qlonglong newID);

		/// @fn QString getIDstr();
		/// @brief Reading mediaIDstr
		/// @return mediaIDstr
		QString getIDstr();

		/// @fn void setIDstr(QString newID);
		/// @brief Writing mediaIDstr
		/// @param newID New value for mediaIDstr
		void setIDstr(QString newID);

		/// @fn QString getMediaURL();
		/// @brief Reading method for mediaURL
		/// @return mediaURL
		QString getMediaURL();

		/// @fn void setMediaURL(QString newMediaURL);
		/// @brief Writing mediaURL
		/// @param newMediaURL New value for mediaURL
		void setMediaURL(QString newMediaURL);

		/// @fn QString getMediaURLhttps();
		/// @brief Reading method for mediaURLhttps
		/// @return mediaURLhttps
		QString getMediaURLhttps();

		/// @fn void setMediaURLhttps(QString newMediaURL);
		/// @brief Writing method for mediaURLhttps
		/// @param newMediaURL New value for mediaURLhttps
		void setMediaURLhttps(QString newMediaURL);

		/// @fn QString getType();
		/// @brief Reading method for mediaType
		/// @return mediatype
		QString getType();

		/// @fn void setType(QString newType);
		/// @brief Writing method for mediaType
		/// @param newType New value for mediaType
		void setType(QString newType);

		/// @fn MediaSizes getSizes();
		/// @brief Reading mediaSizes
		/// @return mediaSizes
		MediaSizes getSizes();

		/// @fn void setSizes(MediaSizes newSizes);
		/// @brief Writing mediaSizes
		/// @param newSizes New value for mediaSizes
		void setSizes(MediaSizes newSizes);
};

// Serialization of Media
Q_DECLARE_METATYPE(Media)

/// @fn QDataStream & operator<<(QDataStream & out, const Media & media);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param media Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const Media & media);

/// @fn QDataStream & operator>>(QDataStream & in, Media & media);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param media Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, Media & media);


/// @typedef ReynTweetsSerializableList<Media> MediaList;
/// @brief Shortcut for lists of Media objects
typedef ReynTweetsSerializableList<Media> MediaList;

#endif // MEDIA_HPP
