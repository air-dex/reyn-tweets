/// @file mediasizes.hpp
/// @brief Header of MediaSizes
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

#ifndef MEDIASIZES_HPP
#define MEDIASIZES_HPP

#include "mediasize.hpp"

/// @class MediaSizes
/// @brief Different sizes possible for a Media object
/// @see https://dev.twitter.com/docs/platform-objects/entities#obj-sizes
class MediaSizes : public JsonObject
{
	Q_OBJECT

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn MediaSizes();
		/// @brief Constructor
		MediaSizes();

		/// @fn virtual ~MediaSizes();
		/// @brief Destructor
		virtual ~MediaSizes();

		/// @fn MediaSizes(const MediaSizes & sizes);
		/// @brief Copy constructor
		/// @param sizes Sizes to copy
		MediaSizes(const MediaSizes & sizes);

		/// @fn const MediaSizes & operator=(const MediaSizes & sizes);
		/// @brief Affectation
		/// @param sizes Sizes to copy
		/// @return Copy of the original media sizes
		const MediaSizes & operator=(const MediaSizes & size);

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

	private:
		/// @fn void recopie(const MediaSizes & sizes);
		/// @brief Copy of a MediaSizes
		/// @param sizes MediaSizes to copy
		void recopie(const MediaSizes & sizes);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const MediaSizes & sizes);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param sizes Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const MediaSizes & sizes);

		/// @fn friend QDataStream & operator>>(QDataStream & in, MediaSizes & sizes);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param sizes Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, MediaSizes & sizes);

	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		// Large size
		/// @property large
		/// @brief Large size for a media
		///
		/// largeSize is the attribute behind the property.
		Q_PROPERTY(QVariantMap large
				   READ getLargeProperty
				   WRITE setLarge)

		/// @brief Name of the property large.
		static QString LARGE_PN;

		/// @fn QVariantMap getLargeProperty();
		/// @brief Reading method for the property large
		/// @return largeMap
		QVariantMap getLargeProperty();

		/// @fn void setLarge(QVariantMap newLargeMap);
		/// @brief Writing method for the property large
		/// @param newLargeMap New value for the property large
		void setLarge(QVariantMap newLargeMap);

		// Medium size
		/// @property medium
		/// @brief Large size for a media
		///
		/// mediumSize is the attribute behind the property.
		Q_PROPERTY(QVariantMap medium
				   READ getMediumProperty
				   WRITE setMedium)

		/// @brief Name of the property medium.
		static QString MEDIUM_PN;

		/// @fn QVariantMap getMediumProperty();
		/// @brief Reading method for the property medium
		/// @return mediumMap
		QVariantMap getMediumProperty();

		/// @fn void setMedium(QVariantMap newMediumMap);
		/// @brief Writing method for the property medium
		/// @param newMediumMap New value for the property medium
		void setMedium(QVariantMap newMediumMap);

		// Small size
		/// @property small
		/// @brief Large size for a media
		///
		/// smallSize is the attribute behind the property.
		Q_PROPERTY(QVariantMap small
				   READ getSmallProperty
				   WRITE setSmall)

		/// @brief Name of the property small.
		static QString SMALL_PN;

		/// @fn QVariantMap getSmallProperty();
		/// @brief Reading method for the property small
		/// @return smallMap
		QVariantMap getSmallProperty();

		/// @fn void setSmall(QVariantMap newSmallMap);
		/// @brief Writing method for the property small
		/// @param newSmallMap New value for the property small
		void setSmall(QVariantMap newSmallMap);

		// Thumb size
		/// @property thumb
		/// @brief Large size for a media
		///
		/// thumbSize is the attribute behind the property.
		Q_PROPERTY(QVariantMap thumb
				   READ getThumbProperty
				   WRITE setThumb)

		/// @brief Name of the property thumb.
		static QString THUMB_PN;

		/// @fn QVariantMap getThumbProperty();
		/// @brief Reading method for the property thumb
		/// @return thumbMap
		QVariantMap getThumbProperty();

		/// @fn void setThumb(QVariantMap newThumbMap);
		/// @brief Writing method for the property thumb
		/// @param newThumbMap New value for the property thumb
		void setThumb(QVariantMap newThumbMap);


	/////////////////
	// Media sizes //
	/////////////////

	protected:
		/// @brief Large size
		MediaSize largeSize;

		/// @brief Medium size
		MediaSize mediumSize;

		/// @brief Small size
		MediaSize smallSize;

		/// @brief Thumb size
		MediaSize thumbSize;


	////////////////////////
	// Getter and setters //
	////////////////////////

	public:
		/// @fn MediaSize getLarge();
		/// @brief Reading method for largeSize
		/// @return largeSize
		MediaSize getLarge();

		/// @fn void setLarge(MediaSize newLargeSize);
		/// @brief Writing method for largeSize
		/// @param newLargeSize New value for largeSize
		void setLarge(MediaSize newLargeSize);

		/// @fn MediaSize getMedium();
		/// @brief Reading method for mediumSize
		/// @return mediumSize
		MediaSize getMedium();

		/// @fn void setMedium(MediaSize newMediumSize);
		/// @brief Writing method for mediumSize
		/// @param newMediumSize New value for mediumSize
		void setMedium(MediaSize newMediumSize);

		/// @fn MediaSize getSmall();
		/// @brief Reading method smallSize
		/// @return smallSize
		MediaSize getSmall();

		/// @fn void setSmall(MediaSize newSmallSize);
		/// @brief Writing method for smallSize
		/// @param newSmallSize New value for smallSize
		void setSmall(MediaSize newSmallSize);

		/// @fn MediaSize getThumb();
		/// @brief Reading method for thumbSize
		/// @return thumbSize
		MediaSize getThumb();

		/// @fn void setThumb(MediaSize newThumbSize);
		/// @brief Writing method for thumbSize
		/// @param newThumbSize New value for thumbSize
		void setThumb(MediaSize newThumbSize);
};

// Serialization of MediaSizes
Q_DECLARE_METATYPE(MediaSizes)

/// @fn QDataStream & operator<<(QDataStream & out, const MediaSizes & sizes);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param sizes Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const MediaSizes & sizes);

/// @fn QDataStream & operator>>(QDataStream & in, MediaSizes & sizes);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param sizes Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, MediaSizes & sizes);

#endif // MEDIASIZES_HPP
