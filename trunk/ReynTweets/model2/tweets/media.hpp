/// @file media.hpp
/// @brief Header of Media
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

#ifndef MEDIA2_HPP
#define MEDIA2_HPP

#include "mediasizes.hpp"
#include "urlentity.hpp"

/// @class Media
/// @brief Media in a tweet.
/// @see https://dev.twitter.com/docs/platform-objects/entities#obj-media
class Media2 : public URLEntity2
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn Media();
		/// @brief Constructor
		Media2();

		/// @fn virtual ~Media();
		/// @brief Destructor
		virtual ~Media2();

		/// @fn Media(const Media & media);
		/// @brief Copy constructor
		/// @param media Media to copy
		Media2(const Media2 & media);

		/// @fn const Media & operator=(const Media & media);
		/// @brief Affectation
		/// @param media Media to copy
		/// @return Copy of the original media
		const Media2 & operator=(const Media2 & media);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn void reset();
		/// @brief Resets the mappable to a default value
		void reset();

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

	protected:
		/// @fn void recopie(const Media & media);
		/// @brief Copy of a Media
		/// @param media Media to copy
		void recopie(const Media2 & media);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const Media & media);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param media Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const Media2 & media);

		/// @fn friend QDataStream & operator>>(QDataStream & in, Media & media);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param media Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, Media2 & media);

	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		// id
		/// @property id
		/// @brief User id
		///
		/// mediaID is the attribute behind this property.
		Q_PROPERTY(qlonglong id
				   READ getID
				   WRITE setID)

		/// @brief Name of the property id.
		static QString ID_PN;

		// id_str
		/// @property id_str
		/// @brief String version of id
		///
		/// mediaIDstr is the attribute behind this property.
		Q_PROPERTY(QString id_str
				   READ getIDstr
				   WRITE setIDstr)

		/// @brief Name of the property id_str.
		static QString ID_STR_PN;

		// media_url
		/// @property media_url
		/// @brief Media URL
		///
		/// mediaURL is the attribute behind this property.
		Q_PROPERTY(QString media_url
				   READ getMediaURL
				   WRITE setMediaURL)

		/// @brief Name of the property media_url.
		static QString MEDIA_URL_PN;

		// media_url_https
		/// @property media_url_https
		/// @brief HTTPS version of media_url
		///
		/// mediaURLhttps is the attribute behind this property.
		Q_PROPERTY(QString media_url_https
				   READ getMediaURLhttps
				   WRITE setMediaURLhttps)

		/// @brief Name of the property media_url_https.
		static QString MEDIA_URL_HTTPS_PN;

		// type
		/// @property type
		/// @brief Media type
		///
		/// mediaType is the attribute behind this property.
		Q_PROPERTY(QString type
				   READ getType
				   WRITE setType)

		/// @brief Name of the property type.
		static QString TYPE_PN;

		// sizes
		/// @property sizes
		/// @brief Different sizes for the media
		///
		/// mediaSizes is the attribute behind this property.
		Q_PROPERTY(QVariantMap sizes
				   READ getSizesProperty
				   WRITE setSizes)

		/// @brief Name of the property sizes.
		static QString SIZES_PN;

		/// @fn QVariantList getSizesProperty();
		/// @brief Reading method for the property sizes
		/// @return sizesMap
		QVariantMap getSizesProperty();

		/// @fn void setSizes(QVariantMap newMap);
		/// @brief Writing method for the property sizes
		/// @param newMap New value for the property sizes
		void setSizes(QVariantMap newMap);

		// source_status_id
		/// @property source_status_id
		/// @brief ID of the original tweet where the media was published
		///
		/// sourceID is the attribute behind this property.
		Q_PROPERTY(qlonglong source_status_id
				   READ getSourceID
				   WRITE setSourceID)

		/// @brief Name of the property id.
		static QString SOURCE_STATUS_ID_PN;

		// source_status_id_str
		/// @property source_status_id_str
		/// @brief String version of source_status_id
		///
		/// sourceIDstr is the attribute behind this property.
		Q_PROPERTY(QString source_status_id_str
				   READ getSourceIDstr
				   WRITE setSourceIDstr)

		/// @brief Name of the property id_str.
		static QString SOURCE_STATUS_ID_STR_PN;


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
		MediaSizes2 mediaSizes;

		/// @brief ID of the original tweet where the media was published
		qlonglong sourceID;

		/// @brief String version of sourceIDstr
		QString sourceIDstr;


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
		MediaSizes2 getSizes();

		/// @fn void setSizes(MediaSizes newSizes);
		/// @brief Writing mediaSizes
		/// @param newSizes New value for mediaSizes
		void setSizes(MediaSizes2 newSizes);

		/// @fn qlonglong getID();
		/// @brief Reading source_status_id
		/// @return sourceID
		qlonglong getSourceID();

		/// @fn void setID(qlonglong newID);
		/// @brief Writing source_status_id
		/// @param newID New value for sourceID
		void setSourceID(qlonglong newID);

		/// @fn QString getIDstr();
		/// @brief Reading source_status_id_str
		/// @return sourceIDstr
		QString getSourceIDstr();

		/// @fn void setIDstr(QString newID);
		/// @brief Writing source_status_id_str
		/// @param newID New value for sourceIDstr
		void setSourceIDstr(QString newID);
};

// Serialization of Media
Q_DECLARE_METATYPE(Media2)

/// @fn QDataStream & operator<<(QDataStream & out, const Media & media);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param media Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const Media2 & media);

/// @fn QDataStream & operator>>(QDataStream & in, Media & media);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param media Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, Media2 & media);

#endif // MEDIA_HPP
