/// @file twitterplace.hpp
/// @brief Header of TwitterPlace
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

#ifndef TWITTERPLACE_HPP
#define TWITTERPLACE_HPP

#include <QVariantMap>
#include "../json/jsonobject.hpp"
#include "geoboundingbox.hpp"

/// @class TwitterPlace
/// @brief Class for representing a random place in the world
/// @see https://dev.twitter.com/docs/platform-objects/places
class TwitterPlace : public JsonObject
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn TwitterPlace();
		/// @brief Constructor
		TwitterPlace();

		/// @fn virtual ~TwitterPlace();
		/// @brief Destructor
		virtual ~TwitterPlace();

		/// @fn TwitterPlace(const TwitterPlace & place);
		/// @brief Copy constructor
		/// @param place TwitterPlace to copy
		TwitterPlace(const TwitterPlace & place);

		/// @fn const TwitterPlace & operator=(const TwitterPlace & place);
		/// @brief Affectation
		/// @param place TwitterPlace to copy
		/// @return Copy of the original place
		const TwitterPlace & operator=(const TwitterPlace & place);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

		/// @fn void reset();
		/// @brief Resets the mappable to a default value
		void reset();

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

		/// @fn virtual QJsonObject toVariant();
		/// @brief Getting a QJsonObject representation of the object
		/// @return The QJsonObject representation
		virtual QJsonObject toVariant() const;


	private:
		/// @fn void recopie(const TwitterPlace & place);
		/// @brief Copy of a TwitterPlace
		/// @param place TwitterPlace to copy
		void recopie(const TwitterPlace & place);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out,
		///										const TwitterPlace & place);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param place Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out,
										const TwitterPlace & place);

		/// @fn friend QDataStream & operator>>(QDataStream & in,
		///										TwitterPlace & place);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param place Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in,
										TwitterPlace & place);

	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		// attributes
		/// @property attributes.
		/// @brief Metadatas about the place.
		///
		/// placeMetadata is the attribute beneath the property.
		Q_PROPERTY(QVariantMap attributes
				   READ getAttributes
				   WRITE setAttributes
				   NOTIFY attributesChanged)

		/// @brief Name of the property attributes.
		static QString ATTRIBUTES_PN;

		// bounding_box
		/// @property bounding_box
		/// @brief Coordinates of the place
		///
		/// placePolygon is the attribute beneath the property.
		Q_PROPERTY(GeoBoundingBox * bounding_box
				   READ getBoundingBoxPtr
				   WRITE setBoundingBox
				   NOTIFY boundingBoxChanged)

		/// @brief Name of the property bounding_box.
		static QString BOUNDING_BOX_PN;

		// country
		/// @property country
		/// @brief Country where the place is located.
		///
		/// land is the attribute beneath the property.
		Q_PROPERTY(QString country
				   READ getCountry
				   WRITE setCountry
				   NOTIFY countryChanged)

		/// @brief Name of the property country.
		static QString COUNTRY_PN;

		// country_code
		/// @property country_code
		/// @brief Country where the place is located.
		///
		/// landCode is the attribute beneath the property.
		Q_PROPERTY(QString country_code
				   READ getCountryCode
				   WRITE setCountryCode
				   NOTIFY countryCodeChanged)

		/// @brief Name of the property country_code.
		static QString COUNTRY_CODE_PN;

		// full_name
		/// @property full_name
		/// @brief Full name of the place.
		///
		/// fullName is the attribute beneath the property.
		Q_PROPERTY(QString full_name
				   READ getFullName
				   WRITE setFullName
				   NOTIFY fullNameChanged)

		/// @brief Name of the property full_name.
		static QString FULL_NAME_PN;

		// id
		/// @property id
		/// @brief ID of the place.
		///
		/// placeID is the attribute beneath the property.
		Q_PROPERTY(QString id
				   READ getID
				   WRITE setID
				   NOTIFY idChanged)

		/// @brief Name of the property id.
		static QString ID_PN;

		// name
		/// @property name
		/// @brief Common name of the place.
		///
		/// placeName is the attribute beneath the property.
		Q_PROPERTY(QString name
				   READ getName
				   WRITE setName
				   NOTIFY nameChanged)

		/// @brief Name of the property name.
		static QString NAME_PN;

		// place_type
		/// @property place_type
		/// @brief Type of place (ex. city)
		///
		/// placeType is the attribute beneath the property.
		Q_PROPERTY(QString place_type
				   READ getPlaceType
				   WRITE setPlaceType
				   NOTIFY placeTypeChanged)

		/// @brief Name of the property place_type.
		static QString PLACE_TYPE_PN;

		// url
		/// @property url
		/// @brief URL for additional metadatas.
		///
		/// metadataURL is the attribute beneath the property.
		Q_PROPERTY(QString url
				   READ getURL
				   WRITE setURL
				   NOTIFY urlChanged)

		/// @brief Name of the property url.
		static QString URL_PN;

	signals:
		/// @fn void attributesChanged();
		/// @brief Signal emitted when the "attributes" property has just
		/// changed its value.
		void attributesChanged();

		/// @fn void boundingBoxChanged();
		/// @brief Signal emitted when the "bounding_box" property has just
		/// changed its value.
		void boundingBoxChanged();

		/// @fn void countryChanged();
		/// @brief Signal emitted when the "country" property has just
		/// changed its value.
		void countryChanged();

		/// @fn void countryCodeChanged();
		/// @brief Signal emitted when the "country_code" property has just
		/// changed its value.
		void countryCodeChanged();

		/// @fn void fullNameChanged();
		/// @brief Signal emitted when the "full_name" property has just
		/// changed its value.
		void fullNameChanged();

		/// @fn void idChanged();
		/// @brief Signal emitted when the "id" property has just
		/// changed its value.
		void idChanged();

		/// @fn void nameChanged();
		/// @brief Signal emitted when the "name" property has just
		/// changed its value.
		void nameChanged();

		/// @fn void placeTypeChanged();
		/// @brief Signal emitted when the "place_type" property has just
		/// changed its value.
		void placeTypeChanged();

		/// @fn void urlChanged();
		/// @brief Signal emitted when the "url" property has just
		/// changed its value.
		void urlChanged();


	//////////////////////
	// Place management //
	//////////////////////

	protected:
		/// @brief Metadatas about the place.
		QVariantMap placeMetadata;

		/// @brief Bounding box with the coordinates of the place.
		GeoBoundingBox placePolygon;

		/// @brief Country of the place.
		QString land;

		/// @brief Code for the country of the place.
		QString landCode;

		/// @brief Full name of the place
		QString fullName;

		/// @brief ID of the place.
		///
		/// <strong>It is not a number (integer or qlonglong).</strong>
		QString placeID;

		/// @brief Common name of the place
		QString placeName;

		/// @brief Type of the place
		QString placeType;

		/// @brief URL for metadatas
		QString metadataURL;


	////////////////////////
	// Getter and setters //
	////////////////////////

	public:
		// attributes
		/// @fn QVariantMap getAttributes();
		/// @brief Reading attributes
		/// @return placeMetadata
		QVariantMap getAttributes();

		/// @fn void setAttributes(QVariantMap newValue);
		/// @brief Writing attributes
		/// @param newValue New value for placeMetadata
		void setAttributes(QVariantMap newValue);

		// bounding_box
		/// @fn GeoBoundingBox * getBoundingBox();
		/// @brief Reading bounding_box
		/// @return placePolygon.
		GeoBoundingBox getBoundingBox();

		/// @fn GeoBoundingBox * getBoundingBoxPtr();
		/// @brief Reading bounding_box
		/// @return A pointer on placePolygon.
		GeoBoundingBox * getBoundingBoxPtr();

		/// @fn void setBoundingBox(GeoBoundingBox newValue);
		/// @brief Writing bounding_box
		/// @param newValue New value for placePolygon.
		void setBoundingBox(GeoBoundingBox newValue);

		/// @fn void setBoundingBox(GeoBoundingBox * newValue);
		/// @brief Writing bounding_box
		/// @param newValue New value for placePolygon.
		void setBoundingBox(GeoBoundingBox * newValue);

		// country
		/// @fn QString getCountry();
		/// @brief Reading country.
		/// @return land
		QString getCountry();

		/// @fn void setCountry(QString newValue);
		/// @brief Writing country.
		/// @param newValue New value for land.
		void setCountry(QString newValue);

		// country_code
		/// @fn QString getCountryCode();
		/// @brief Reading country_code.
		/// @return landCode
		QString getCountryCode();

		/// @fn void setCountryCode(QString newValue);
		/// @brief Writing country_code.
		/// @param newValue New value for landCode.
		void setCountryCode(QString newValue);

		// full_name
		/// @fn QString getFullName();
		/// @brief Reading full_name.
		/// @return fullName
		QString getFullName();

		/// @fn void setFullName(QString newValue);
		/// @brief Writing full_name.
		/// @param newValue New value for fullName.
		void setFullName(QString newValue);

		// id
		/// @fn QString getID();
		/// @brief Reading id.
		/// @return placeID
		QString getID();

		/// @fn void setID(QString newValue);
		/// @brief Writing id.
		/// @param newValue New value for placeID.
		void setID(QString newValue);

		// name
		/// @fn QString getName();
		/// @brief Reading name.
		/// @return placeName
		QString getName();

		/// @fn void setName(QString newValue);
		/// @brief Writing name.
		/// @param newValue New value for placeName.
		void setName(QString newValue);

		// place_type
		/// @fn QString getPlaceType();
		/// @brief Reading place_type.
		/// @return placeType
		QString getPlaceType();

		/// @fn void setPlaceType(QString newValue);
		/// @brief Writing place_type.
		/// @param newValue New value for placeType.
		void setPlaceType(QString newValue);

		// url
		/// @fn QString getURL();
		/// @brief Reading url.
		/// @return metadataURL
		QString getURL();

		/// @fn void setURL(QString newValue);
		/// @brief Writing url.
		/// @param newValue New value for metadataURL.
		void setURL(QString newValue);

};
// Serialization of TwitterPlace
Q_DECLARE_METATYPE(TwitterPlace)

/// @fn QDataStream & operator<<(QDataStream & out, const TwitterPlace & place);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param place Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const TwitterPlace & place);

/// @fn QDataStream & operator>>(QDataStream & in, TwitterPlace & place);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param place Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, TwitterPlace & place);

#endif // TWITTERPLACE_HPP
