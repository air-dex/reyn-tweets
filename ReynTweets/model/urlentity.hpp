/// @file tweet.hpp
/// @brief Header of Tweet
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

#ifndef URLENTITY_HPP
#define URLENTITY_HPP

#include <QString>
#include "indexbounds.hpp"
#include "reyntweetsserializable.hpp"

class URLEntity : public ReynTweetsSerializable
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
		/// @param entity User to copy
		/// @return Copy of the original entity
		const URLEntity & operator=(const URLEntity & entity);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	private:
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
		/// @fn void fillWithPropertiesMaps();
		/// @brief Filling serializable fields with thecorresponding  property maps
		void fillWithPropertiesMaps();

		/// @fn void updateAllProperties();
		/// @brief Updating all the properties
		void updateAllProperties();

		// url
		/// @property url
		/// @brief Extracted URL
		Q_PROPERTY(QString url
				   READ getURL
				   WRITE setURL)

		/// @fn void updateURL();
		/// @brief Updating the property url
		void updateURL();

		// displayed_url
		/// @property displayed_url
		/// @brief Displayed URL
		Q_PROPERTY(QString displayed_url
				   READ getDisplayedURL
				   WRITE setDisplayedURL)

		/// @fn void updateDisplayedURL();
		/// @brief Updating the property displayed_url
		void updateDisplayedURL();

		// expanded_url
		/// @property expanded_url
		/// @brief Expanded URL
		Q_PROPERTY(QString expanded_url
				   READ getExpandedURL
				   WRITE setExpandedURL)

		/// @fn void updateExpandedURL();
		/// @brief Updating the property expanded_url
		void updateExpandedURL();

		// indices
		/// @property indices
		/// @brief Indexes
		Q_PROPERTY(QVariantList indices
				   READ getIndices
				   WRITE setIndices)

		/// @brief Representation of the property thumb
		QVariantList indexList;

		/// @fn QVariantList getIndices();
		/// @brief Reading method for the property indices
		/// @return indexList
		QVariantList getIndices();

		/// @fn void setIndices(QVariantList newIndexList);
		/// @brief Writing method for the property indices
		/// @param newIndexList New value for the property indices
		void setIndices(QVariantList newIndexList);

		/// @fn void updateIndices();
		/// @brief Updating the property indices
		void updateIndices();


	////////////////////
	// URL management //
	////////////////////

	protected:
		/// @brief Extracted URL
		QString extractedURL;

		/// @brief URL displayed on the tweet
		QString displayedURL;

		/// @brief Full URL (only for t.co URLs)
		QString expandedURL;

		/// @brief Indexes in the tweet
		IndexBounds indexes;


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

		/// @fn IndexBounds getIndexes();
		/// @brief Reading indexes
		/// @return indexes
		IndexBounds getIndexes();

		/// @fn void setIndexes(IndexBounds newIndexes);
		/// @brief Writing indexes
		/// @param newIndexes New value for indexes
		void setIndexes(IndexBounds newIndexes);
};

// Serialization of MediaSizes
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
