/// @file tweetentity.hpp
/// @brief Header of TweetEntity
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

#ifndef TWEETENTITY_HPP
#define TWEETENTITY_HPP

#include "../json/jsonobject.hpp"
#include "indexbounds.hpp"

/// @class TweetEntity
/// @brief Base class for all Tweet Entities.
///
/// It contains the indices of the Tweet Entity in the tweet.
class TweetEntity : public JsonObject
{
	Q_OBJECT

	public:
		/// @fn TweetEntity();
		/// @brief Constructor
		TweetEntity();

		/// @fn virtual ~TweetEntity();
		/// @brief Destructor
		virtual ~TweetEntity();

		/// @fn TweetEntity(const TweetEntity & entity);
		/// @brief Copy constructor
		/// @param entity Tweet entity to copy
		TweetEntity(const TweetEntity & hashtag);

		/// @fn const TweetEntity & operator=(const TweetEntity & entity);
		/// @brief Affectation
		/// @param entity Tweet entity to copy
		/// @return Copy of the original entity
		const TweetEntity & operator=(const TweetEntity & hashtag);

		/// @fn virtual QString getDisplayedText(QColor linkColor) = 0;
		/// @brief Building the rich text for the entity
		/// @param linkColor Color for links
		/// @return The tweet entity with rich content
		virtual QString getDisplayedText(QColor linkColor) = 0;

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
		/// @fn void recopie(const TweetEntity & entity);
		/// @brief Copy of a Tweet entity
		/// @param entity Tweet entity to copy
		void recopie(const TweetEntity & entity);

		// indices
		/// @property indices
		/// @brief Bounds of the entity in the tweet.
		///
		/// Represented by the indexes attribute.
		Q_PROPERTY(QVariantList indices
				   READ getIndicesProperty
				   WRITE setIndices
				   NOTIFY indicesChanged)

		/// @brief Name of the property indices.
		static QString INDICES_PN;

		/// @fn QVariantList getIndicesProperty();
		/// @brief Reading method for the property indices
		/// @return indexList
		QVariantList getIndicesProperty();

		/// @fn void setIndices(QVariantList newIndexList);
		/// @brief Writing method for the property indices
		/// @param newIndexList New value for the property indices
		void setIndices(QVariantList newIndexList);

		/// @brief Indexes of the hashtag in the tweet
		IndexBounds indexes;

	signals:
		/// @fn void indicesChanged();
		/// @brief Signal emitted when the property indices has got a new value.
		void indicesChanged();


	public:
		/// @fn IndexBounds getIndices();
		/// @brief Reading indexes
		/// @return indexes
		IndexBounds getIndices();

		/// @fn void setIndices(IndexBounds newIndexes);
		/// @brief Writing indexes
		/// @param newIndexes New value for indexes
		void setIndices(IndexBounds newIndexes);
};

#endif // TWEETENTITY_HPP
