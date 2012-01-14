/// @file mediasize.hpp
/// @brief Header of MediaSize
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

#ifndef MEDIASIZE_HPP
#define MEDIASIZE_HPP

#include <QSize>
#include "reyntweetsmappable.hpp"

class MediaSize : public ReynTweetsMappable, public QSize
{
	Q_OBJECT

	/////////////////
	// Resize enum //
	/////////////////

	public:
		/// @enum Resize
		/// @brief Enum indicating how the media is resized for a given size.
		enum Resize {
			/// @brief Invalid resize
			NULL_RESIZE,

			/// @brief The media is cropped
			CROP,

			/// @brief The media is fit
			FIT
		};
		Q_ENUMS(Resize)

		/// @fn QString resize2String(Resize resizeValue);
		/// @brief Conversion of a Resize into a QString.
		/// @param resizeValue Resize enum value.
		/// @return The corresponding QString value.
		QString resize2String(Resize resizeValue);

		/// @fn Resize string2Resize(QString resizeString);
		/// @brief Conversion of a QString into a Resize enum.
		/// @param resizeString QString value.
		/// @return The corresponding Resize enum value.
		Resize string2Resize(QString resizeString);

	//////////////////////////////
	// Serialization management //
	//////////////////////////////

	public:
		/// @fn MediaSize();
		/// @brief Constructor
		MediaSize();

		/// @fn virtual ~MediaSize();
		/// @brief Destructor
		virtual ~MediaSize();

		/// @fn MediaSize(const MediaSize & size);
		/// @brief Copy constructor
		/// @param size User to copy
		MediaSize(const MediaSize & size);

		/// @fn const MediaSize & operator=(const MediaSize & size);
		/// @brief Affectation
		/// @param size User to copy
		/// @return Copy of the original media size
		const MediaSize & operator=(const MediaSize & size);

		/// @fn static void initSystem();
		/// @brief Serialization declaration
		static void initSystem();

	private:
		/// @fn void recopie(const MediaSize & size);
		/// @brief Copy of a MediaSize
		/// @param size MediaSize to copy
		void recopie(const MediaSize & size);

		// Friends serialization operators

		/// @fn friend QDataStream & operator<<(QDataStream & out, const MediaSize & size);
		/// @brief Output stream operator for serialization
		/// @param out The output stream
		/// @param size Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator<<(QDataStream & out, const MediaSize & size);

		/// @fn friend QDataStream & operator>>(QDataStream & in, MediaSize & size);
		/// @brief Input stream operator for serialization
		/// @param in The input stream
		/// @param size Object to put in the stream
		/// @return The stream with the object
		friend QDataStream & operator>>(QDataStream & in, MediaSize & size);

	///////////////////////////
	// Properties management //
	///////////////////////////

	protected:
		/// @fn void fillWithPropertiesMaps();
		/// @brief Filling serializable fields with thecorresponding  property maps
		void syncMembers();

		/// @fn void updateAllProperties();
		/// @brief Updating all the properties
		void syncProperties();

		/// @property w
		/// @brief Width
		Q_PROPERTY(int w
				   READ width
				   WRITE setWidth)

		/// @property h
		/// @brief Height
		Q_PROPERTY(int h
				   READ height
				   WRITE setHeight)

		/// @property resize
		/// @brief How the media is resized. It is the String form of resizeMedia.
		Q_PROPERTY(QString resize
				   READ getResizeProperty
				   WRITE setResizeProperty)

		/// @brief Representation of resize
		QString resizeProperty;

		/// @fn QString getResizeProperty();
		/// @brief Reading method for resize
		/// @return resizeProperty
		QString getResizeProperty();

		/// @fn void setResizeProperty(QString newResize);
		/// @brief Writing method for resize
		/// @param newResize New value for resizeProperty
		void setResizeProperty(QString newResize);

		/// @fn void updateResize();
		/// @brief Updating the property resize
		void syncResizeProperty();

		/// @fn void updateResize();
		/// @brief Updating resizeMedia
		void syncResizeMember();

	/////////////////////
	// Size management //
	/////////////////////

	protected:
		/// @brief How the media is resized
		Resize resizeMedia;

	public:
		/// @fn Resize getResizeProperty();
		/// @brief Getter on resizeMedia
		/// @return resizeMedia
		Resize getResize();

		/// @fn void setResize(Resize newResize);
		/// @brief Setter on resizeMedia
		/// @param newResize New value for resizeProperty
		void setResize(Resize newResize);
};

// Serialization of MediaSize
Q_DECLARE_METATYPE(MediaSize)

/// @fn QDataStream & operator<<(QDataStream & out, const MediaSize & size);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param size Object to put in the stream
/// @return The stream with the object
QDataStream & operator<<(QDataStream & out, const MediaSize & size);

/// @fn QDataStream & operator>>(QDataStream & in, MediaSize & size);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param size Object to put in the stream
/// @return The stream with the object
QDataStream & operator>>(QDataStream & in, MediaSize & size);

#endif // MEDIASIZE_HPP
