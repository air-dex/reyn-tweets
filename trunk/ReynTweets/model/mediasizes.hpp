/// @file mediasizes.hpp
/// @brief Header of MediaSizes
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

#ifndef MEDIASIZES_HPP
#define MEDIASIZES_HPP

#include "mediasize.hpp"
#include "reyntweetsserializable.hpp"

class MediaSizes : public ReynTweetsSerializable
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
		/// @param sizes User to copy
		MediaSizes(const MediaSizes & sizes);

		/// @fn const MediaSizes & operator=(const MediaSizes & sizes);
		/// @brief Affectation
		/// @param sizes User to copy
		/// @return Copy of the original media sizes
		const MediaSizes & operator=(const MediaSizes & size);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	private:
		/// @fn void recopie(const MediaSizes & sizes);
		/// @brief Copy of a MediaSizes
		/// @param sizes MediaSizes to copy
		void recopie(const MediaSizes & sizes);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const MediaSizes & size);
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

	private:
		/// @fn void fillWithPropertiesMaps();
		/// @brief Filling serializable fields with thecorresponding  property maps
		void fillWithPropertiesMaps();

		/// @fn void updateAllProperties();
		/// @brief Updating all the properties
		void updateAllProperties();

		// Large size
		/// @property large
		/// @brief Large size for a media
		Q_PROPERTY(QVariantMap large
				   READ getLarge
				   WRITE setLarge)

		/// @brief Representation of the property large
		QVariantMap largeMap;

		/// @fn QVariantMap getLarge();
		/// @brief Reading method for the property large
		/// @return largeMap
		QVariantMap getLarge();

		/// @fn void setLarge(QVariantMap newLargeMap);
		/// @brief Writing method for the property large
		/// @param newLargeMap New value for the property large
		void setLarge(QVariantMap newLargeMap);

		/// @fn void updateLarge();
		/// @brief Updating the property large
		void updateLarge();

		// Medium size
		/// @property medium
		/// @brief Large size for a media
		Q_PROPERTY(QVariantMap medium
				   READ getMedium
				   WRITE setMedium)

		/// @brief Representation of the property medium
		QVariantMap mediumMap;

		/// @fn QVariantMap getMedium();
		/// @brief Reading method for the property medium
		/// @return mediumMap
		QVariantMap getMedium();

		/// @fn void setMedium(QVariantMap newMediumMap);
		/// @brief Writing method for the property medium
		/// @param newMediumMap New value for the property medium
		void setMedium(QVariantMap newMediumMap);

		/// @fn void updateMedium();
		/// @brief Updating the property medium
		void updateMedium();

		// Small size
		/// @property small
		/// @brief Large size for a media
		Q_PROPERTY(QVariantMap small
				   READ getSmall
				   WRITE setSmall)

		/// @brief Representation of the property small
		QVariantMap smallMap;

		/// @fn QVariantMap getSmall();
		/// @brief Reading method for the property small
		/// @return smallMap
		QVariantMap getSmall();

		/// @fn void setSmall(QVariantMap newSmallMap);
		/// @brief Writing method for the property small
		/// @param newSmallMap New value for the property small
		void setSmall(QVariantMap newSmallMap);

		/// @fn void updateSmall();
		/// @brief Updating the property small
		void updateSmall();

		// Thumb size
		/// @property thumb
		/// @brief Large size for a media
		Q_PROPERTY(QVariantMap thumb
				   READ getThumb
				   WRITE setThumb)

		/// @brief Representation of the property thumb
		QVariantMap thumbMap;

		/// @fn QVariantMap getThumb();
		/// @brief Reading method for the property thumb
		/// @return thumbMap
		QVariantMap getThumb();

		/// @fn void setThumb(QVariantMap newThumbMap);
		/// @brief Writing method for the property thumb
		/// @param newThumbMap New value for the property thumb
		void setThumb(QVariantMap newThumbMap);

		/// @fn void updateThumb();
		/// @brief Updating the property thumb
		void updateThumb();


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
		/// @fn MediaSize getLargeSize();
		/// @brief Reading method for largeSize
		/// @return largeSize
		MediaSize getLargeSize();

		/// @fn void setLargeSize(MediaSize newLargeSize);
		/// @brief Writing method for largeSize
		/// @param newLargeSize New value for largeSize
		void setLargeSize(MediaSize newLargeSize);

		/// @fn MediaSize getMediumSize();
		/// @brief Reading method for mediumSize
		/// @return mediumSize
		MediaSize getMediumSize();

		/// @fn void setMediumSize(MediaSize newMediumSize);
		/// @brief Writing method for mediumSize
		/// @param newMediumSize New value for mediumSize
		void setMediumSize(MediaSize newMediumSize);

		/// @fn MediaSize getSmallSize();
		/// @brief Reading method smallSize
		/// @return smallSize
		MediaSize getSmallSize();

		/// @fn void setSmallSize(MediaSize newSmallSize);
		/// @brief Writing method for smallSize
		/// @param newSmallSize New value for smallSize
		void setSmallSize(MediaSize newSmallSize);

		/// @fn MediaSize getThumbSize();
		/// @brief Reading method for thumbSize
		/// @return thumbSize
		MediaSize getThumbSize();

		/// @fn void setThumbSize(MediaSize newThumbSize);
		/// @brief Writing method for thumbSize
		/// @param newThumbSize New value for thumbSize
		void setThumbSize(MediaSize newThumbSize);
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
