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

		/// @fn virtual QJsonObject toVariant() const;
		/// @brief Getting a QJsonObject representation of the object
		/// @return The QJsonObject representation
		virtual QJsonObject toVariant() const;

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
		// large
		/// @property large
		/// @brief Large size for a media
		///
		/// largeSize is the attribute behind the property.
		Q_PROPERTY(MediaSize * large
				   READ getLargePtr
				   WRITE setLarge
				   NOTIFY largeChanged)

		/// @brief Name of the property large.
		static QString LARGE_PN;

		/// @fn MediaSize * getLargePtr();
		/// @brief Reading large
		/// @return &largeSize
		MediaSize * getLargePtr();

		/// @fn void setLarge(MediaSize * newLargeSize);
		/// @brief Writing large
		/// @param newLargeSize New value for largeSize
		void setLarge(MediaSize * newLargeSize);

		// medium
		/// @property medium
		/// @brief Large size for a media
		///
		/// mediumSize is the attribute behind the property.
		Q_PROPERTY(MediaSize * medium
				   READ getMediumPtr
				   WRITE setMedium
				   NOTIFY mediumChanged)

		/// @brief Name of the property medium.
		static QString MEDIUM_PN;

		/// @fn MediaSize * getMediumPtr();
		/// @brief Reading medium
		/// @return &mediumSize
		MediaSize * getMediumPtr();

		/// @fn void setMedium(MediaSize * newMediumSize);
		/// @brief Writing medium
		/// @param newMediumSize New value for mediumSize
		void setMedium(MediaSize * newMediumSize);

		// small
		/// @property small
		/// @brief Large size for a media
		///
		/// smallSize is the attribute behind the property.
		Q_PROPERTY(MediaSize * small
				   READ getSmallPtr
				   WRITE setSmall
				   NOTIFY smallChanged)

		/// @brief Name of the property small.
		static QString SMALL_PN;

		/// @fn MediaSize * getSmallPtr();
		/// @brief Reading small
		/// @return &smallSize
		MediaSize * getSmallPtr();

		/// @fn void setSmall(MediaSize * newSmallSize);
		/// @brief Writing small
		/// @param newSmallSize New value for smallSize
		void setSmall(MediaSize * newSmallSize);

		// thumb
		/// @property thumb
		/// @brief Large size for a media
		///
		/// thumbSize is the attribute behind the property.
		Q_PROPERTY(MediaSize * thumb
				   READ getThumbPtr
				   WRITE setThumb
				   NOTIFY thumbChanged)

		/// @brief Name of the property thumb.
		static QString THUMB_PN;

		/// @fn MediaSize * getThumbPtr();
		/// @brief Reading thumb
		/// @return &thumbSize
		MediaSize * getThumbPtr();

		/// @fn void setThumb(MediaSize newThumbSize);
		/// @brief Writing thumb
		/// @param newThumbSize New value for thumbSize
		void setThumb(MediaSize * newThumbSize);

	signals:
		/// @fn void largeChanged();
		/// @brief Signal emitted when the property large has got a new value.
		void largeChanged();

		/// @fn void mediumChanged();
		/// @brief Signal emitted when the property medium has got a new value.
		void mediumChanged();

		/// @fn void smallChanged();
		/// @brief Signal emitted when the property small has got a new value.
		void smallChanged();

		/// @fn void thumbChanged();
		/// @brief Signal emitted when the property thumb has got a new value.
		void thumbChanged();


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
		// large
		/// @fn MediaSize getLarge();
		/// @brief Reading method for largeSize
		/// @return largeSize
		MediaSize getLarge();

		/// @fn void setLarge(MediaSize newLargeSize);
		/// @brief Writing method for largeSize
		/// @param newLargeSize New value for largeSize
		void setLarge(MediaSize newLargeSize);

		// medium
		/// @fn MediaSize getMedium();
		/// @brief Reading method for mediumSize
		/// @return mediumSize
		MediaSize getMedium();

		/// @fn void setMedium(MediaSize newMediumSize);
		/// @brief Writing method for mediumSize
		/// @param newMediumSize New value for mediumSize
		void setMedium(MediaSize newMediumSize);

		// small
		/// @fn MediaSize getSmall();
		/// @brief Reading method smallSize
		/// @return smallSize
		MediaSize getSmall();

		/// @fn void setSmall(MediaSize newSmallSize);
		/// @brief Writing method for smallSize
		/// @param newSmallSize New value for smallSize
		void setSmall(MediaSize newSmallSize);

		// thumb
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
