/// @file media.hpp
/// @brief Header of Media
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

#ifndef MEDIA_HPP
#define MEDIA_HPP

#include "mediasizes.hpp"
#include "urlentity.hpp"

/// @class Media
/// @brief Media in a tweet.
/// @see https://dev.twitter.com/docs/platform-objects/entities#obj-media
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

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

		/// @fn void reset();
		/// @brief Resets the mappable to a default value
		void reset();

		/// @fn bool operator==(const Media media) const;
		/// @brief Equality between medias.
		///
		/// 2 medias are considered as equal if they have got the same media ID.
		/// @param media The user to compare
		/// @return True if both Medias have got the same ID, false otherwise.
		bool operator==(const Media media) const;

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
		///
		/// mediaID is the attribute behind this property.
		Q_PROPERTY(qlonglong id
				   READ getID
				   WRITE setID
				   NOTIFY idChanged)

		/// @brief Name of the property id.
		static QString ID_PN;

		// id_str
		/// @property id_str
		/// @brief String version of id
		///
		/// mediaIDstr is the attribute behind this property.
		Q_PROPERTY(QString id_str
				   READ getIDstr
				   WRITE setIDstr
				   NOTIFY idChanged)

		/// @brief Name of the property id_str.
		static QString ID_STR_PN;

		// media_url
		/// @property media_url
		/// @brief Media URL
		///
		/// mediaURL is the attribute behind this property.
		Q_PROPERTY(QString media_url
				   READ getMediaURL
				   WRITE setMediaURL
				   NOTIFY mediaURLChanged)

		/// @brief Name of the property media_url.
		static QString MEDIA_URL_PN;

		// media_url_https
		/// @property media_url_https
		/// @brief HTTPS version of media_url
		///
		/// mediaURLhttps is the attribute behind this property.
		Q_PROPERTY(QString media_url_https
				   READ getMediaURLhttps
				   WRITE setMediaURLhttps
				   NOTIFY mediaURLhttpsChanged)

		/// @brief Name of the property media_url_https.
		static QString MEDIA_URL_HTTPS_PN;

		// type
		/// @property type
		/// @brief Media type
		///
		/// mediaType is the attribute behind this property.
		Q_PROPERTY(QString type
				   READ getType
				   WRITE setType
				   NOTIFY typeChanged)

		/// @brief Name of the property type.
		static QString TYPE_PN;

		// sizes
		/// @property sizes
		/// @brief Different sizes for the media
		///
		/// mediaSizes is the attribute behind this property.
		Q_PROPERTY(MediaSizes * sizes
				   READ getSizesPtr
				   WRITE setSizes
				   NOTIFY sizesChanged)

		/// @brief Name of the property sizes.
		static QString SIZES_PN;

		/// @fn MediaSizes * getSizesPtr();
		/// @brief Reading sizes
		/// @return &mediaSizes
		MediaSizes * getSizesPtr();

		/// @fn void setSizes(MediaSizes * newSizes);
		/// @brief Writing sizes
		/// @param newSizes New value for mediaSizes
		void setSizes(MediaSizes * newSizes);

		// source_status_id
		/// @property source_status_id
		/// @brief ID of the original tweet where the media was published
		///
		/// sourceID is the attribute behind this property.
		Q_PROPERTY(qlonglong source_status_id
				   READ getSourceID
				   WRITE setSourceID
				   NOTIFY sourceIDChanged)

		/// @brief Name of the property id.
		static QString SOURCE_STATUS_ID_PN;

		// source_status_id_str
		/// @property source_status_id_str
		/// @brief String version of source_status_id
		///
		/// sourceIDstr is the attribute behind this property.
		Q_PROPERTY(QString source_status_id_str
				   READ getSourceIDstr
				   WRITE setSourceIDstr
				   NOTIFY sourceIDChanged)

		/// @brief Name of the property id_str.
		static QString SOURCE_STATUS_ID_STR_PN;

	signals:
		/// @fn void idChanged();
		/// @brief Signal emitted when the properties id or id_str have got
		/// a new value.
		void idChanged();

		/// @fn void mediaURLChanged();
		/// @brief Signal emitted when the property media_url has got a new value.
		void mediaURLChanged();

		/// @fn void mediaURLhttpsChanged();
		/// @brief Signal emitted when the property media_url_https has got
		/// a new value.
		void mediaURLhttpsChanged();

		/// @fn void typeChanged();
		/// @brief Signal emitted when the property type has got a new value.
		void typeChanged();

		/// @fn void sizesChanged();
		/// @brief Signal emitted when the property sizes has got a new value.
		void sizesChanged();

		/// @fn void sourceIDChanged();
		/// @brief Signal emitted when the properties source_status_id or
		/// source_status_id_str have got a new value.
		void sourceIDChanged();


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

		/// @brief ID of the original tweet where the media was published
		qlonglong sourceID;

		/// @brief String version of sourceIDstr
		QString sourceIDstr;


	////////////////////////
	// Getter and setters //
	////////////////////////

	public:
		// id
		/// @fn qlonglong getID();
		/// @brief Reading mediaID
		///
		/// <strong>Not recommended because of
		/// <a href="https://bugreports.qt-project.org/browse/QTBUG-28560">a bug
		/// on Qt JSON writing numbers. Use the method with the string ID
		/// instead.</a></strong>
		/// @return mediaID
		qlonglong getID();

		/// @fn void setID(qlonglong newID);
		/// @brief Writing mediaID
		///
		/// <strong>Not recommended because of
		/// <a href="https://bugreports.qt-project.org/browse/QTBUG-28560">a bug
		/// on Qt JSON writing numbers. Use the method with the string ID
		/// instead.</a></strong>
		/// @param newID New value for mediaID
		void setID(qlonglong newID);

		// id_str
		/// @fn QString getIDstr();
		/// @brief Reading mediaIDstr
		/// @return mediaIDstr
		QString getIDstr();

		/// @fn void setIDstr(QString newID);
		/// @brief Writing mediaIDstr
		/// @param newID New value for mediaIDstr
		void setIDstr(QString newID);

		// media_url
		/// @fn QString getMediaURL();
		/// @brief Reading method for mediaURL
		/// @return mediaURL
		QString getMediaURL();

		/// @fn void setMediaURL(QString newMediaURL);
		/// @brief Writing mediaURL
		/// @param newMediaURL New value for mediaURL
		void setMediaURL(QString newMediaURL);

		// media_url_https
		/// @fn QString getMediaURLhttps();
		/// @brief Reading method for mediaURLhttps
		/// @return mediaURLhttps
		QString getMediaURLhttps();

		/// @fn void setMediaURLhttps(QString newMediaURL);
		/// @brief Writing method for mediaURLhttps
		/// @param newMediaURL New value for mediaURLhttps
		void setMediaURLhttps(QString newMediaURL);

		// type
		/// @fn QString getType();
		/// @brief Reading method for mediaType
		/// @return mediatype
		QString getType();

		/// @fn void setType(QString newType);
		/// @brief Writing method for mediaType
		/// @param newType New value for mediaType
		void setType(QString newType);

		// sizes
		/// @fn MediaSizes getSizes();
		/// @brief Reading mediaSizes
		/// @return mediaSizes
		MediaSizes getSizes();

		/// @fn void setSizes(MediaSizes newSizes);
		/// @brief Writing mediaSizes
		/// @param newSizes New value for mediaSizes
		void setSizes(MediaSizes newSizes);

		// source_id
		/// @fn qlonglong getSourceID();
		/// @brief Reading source_status_id
		/// @return sourceID
		qlonglong getSourceID();

		/// @fn void setSourceID(qlonglong newID);
		/// @brief Writing source_status_id
		/// @param newID New value for sourceID
		void setSourceID(qlonglong newID);

		// source_id_str
		/// @fn QString getSourceIDstr();
		/// @brief Reading source_status_id_str
		/// @return sourceIDstr
		QString getSourceIDstr();

		/// @fn void setSourceIDstr(QString newID);
		/// @brief Writing source_status_id_str
		/// @param newID New value for sourceIDstr
		void setSourceIDstr(QString newID);
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

#endif // MEDIA_HPP
