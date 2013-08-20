/// @file urlentity.hpp
/// @brief Header of URLEntity
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

#ifndef URLENTITY_HPP
#define URLENTITY_HPP

#include <QString>
#include "tweetentity.hpp"

/// @class URLEntity
/// @brief URL in a tweet
/// @see https://dev.twitter.com/docs/platform-objects/entities#obj-url
class URLEntity : public TweetEntity
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn URLEntity();
		/// @brief Constructor
		URLEntity();

		/// @fn virtual ~URLEntity();
		/// @brief Destructor
		virtual ~URLEntity();

		/// @fn URLEntity(const URLEntity & entity);
		/// @brief Copy constructor
		/// @param entity URLEntity to copy
		URLEntity(const URLEntity & entity);

		/// @fn const URLEntity & operator=(const URLEntity & entity);
		/// @brief Affectation
		/// @param entity Entity to copy
		/// @return Copy of the original entity
		const URLEntity & operator=(const URLEntity & entity);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

		/// @fn QString getDisplayedText(QColor linkColor);
		/// @brief Building the rich text for the url.
		///
		/// Overrides the QString TweetEntity::getDisplayedText(); method
		/// @param linkColor Color for links
		/// @return An HTML tag to open the URL in a browser
		QString getDisplayedText(QColor linkColor);

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


	protected:
		/// @fn void recopie(const URLEntity & entity);
		/// @brief Copy of a URLEntity
		/// @param entity URLEntity to copy
		void recopie(const URLEntity & entity);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const URLEntity & entity);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param entity Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const URLEntity & entity);

		/// @fn friend QDataStream & operator>>(QDataStream & in, URLEntity & entity);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param entity Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, URLEntity & entity);

	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		// url
		/// @property url
		/// @brief Extracted URL
		///
		/// The extractedURL attribute is behind this property.
		Q_PROPERTY(QString url
				   READ getURL
				   WRITE setURL)

		/// @brief Name of the property url.
		static QString URL_PN;

		// displayed_url
		/// @property displayed_url
		/// @brief Displayed URL
		///
		/// The displayedURL attribute is behind this property.
		Q_PROPERTY(QString displayed_url
				   READ getDisplayedURL
				   WRITE setDisplayedURL)

		/// @brief Name of the property displayed_url.
		static QString DISPLAYED_URL_PN;

		// expanded_url
		/// @property expanded_url
		/// @brief Expanded URL
		///
		/// The expandedURL attribute is behind this property.
		Q_PROPERTY(QString expanded_url
				   READ getExpandedURL
				   WRITE setExpandedURL)

		/// @brief Name of the property expanded_url.
		static QString EXPANDED_URL_PN;


	////////////////////
	// URL management //
	////////////////////

	protected:
		/// @brief Extracted URL
		QString extractedURL;

		/// @brief URL displayed on the tweet (only for t.co URLs)
		QString displayedURL;

		/// @brief Full URL (only for t.co URLs)
		QString expandedURL;


	////////////////////////
	// Getter and setters //
	////////////////////////

	public:
		/// @fn QString getURL();
		/// @brief Reading extractedURL
		/// @return extractedURL
		QString getURL();

		/// @fn void setURL(QString newURL);
		/// @brief Writing extractedURL
		/// @param newURL New value for extractedURL
		void setURL(QString newURL);

		/// @fn QString getDisplayedURL();
		/// @brief Reading method for displayedURL
		/// @return displayedURL
		QString getDisplayedURL();

		/// @fn void setDisplayedURL(QString newURL);
		/// @brief Writing displayedURL
		/// @param newURL New value for displayedURL
		void setDisplayedURL(QString newURL);

		/// @fn QString getExpandedURL();
		/// @brief Reading method for expandedURL
		/// @return expandedURL
		QString getExpandedURL();

		/// @fn void setExpandedURL(QString newURL);
		/// @brief Writing method for expandedURL
		/// @param newURL New value for expandedURL
		void setExpandedURL(QString newURL);
};

// Serialization of URLEntity
Q_DECLARE_METATYPE(URLEntity)

/// @fn QDataStream & operator<<(QDataStream & out, const URLEntity & entity);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param entity Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const URLEntity & entity);

/// @fn QDataStream & operator>>(QDataStream & in, URLEntity & entity);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param entity Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, URLEntity & entity);

#endif // URLENTITY_HPP
