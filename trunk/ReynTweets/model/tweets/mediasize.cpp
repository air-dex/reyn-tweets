/// @file mediasize.cpp
/// @brief Implementation of MediaSize
///
/// Revisions older than r243 was in /trunk/ReynTwets/model
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
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

#include "mediasize.hpp"
#include "../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
MediaSize::MediaSize() :
	ReynTweetsMappable(),
	QSize(0,0),
	resizeMedia(NULL_RESIZE)
{}

// Destructor
MediaSize::~MediaSize() {}

// Copy constructor
MediaSize::MediaSize(const MediaSize & size) {
	recopie(size);
}

// Affectation
const MediaSize & MediaSize::operator=(const MediaSize & size) {
	recopie(size);
	return *this;
}

// Copy of a MediaSize
void MediaSize::recopie(const MediaSize & size) {
	ReynTweetsMappable::recopie(size);
	setWidth(size.width());
	setHeight(size.height());
	resizeMedia = size.resizeMedia;
}

// Serialization declaration
void MediaSize::initSystem() {
	qRegisterMetaTypeStreamOperators<MediaSize>("MediaSize");
	qMetaTypeId<MediaSize>();
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const MediaSize & size) {
	return jsonStreamingOut(out, size);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, MediaSize & size) {
	return jsonStreamingIn(in, size);
}

// Resets the mappable to a default value
void MediaSize::reset() {
	*this = MediaSize();
}


///////////////////////////
// Properties management //
///////////////////////////

// Reading method for resize
QString MediaSize::getResizeProperty() {
	return resize2String(resizeMedia);
}

// Writing method for resize
void MediaSize::setResize(QString newResize) {
	resizeMedia = string2Resize(newResize);
}


/////////////////
// Resize enum //
/////////////////

// Conversion of a Resize into a QString.
QString MediaSize::resize2String(MediaSize::Resize resizeValue) {
	switch (resizeValue) {
		case CROP:
			return "crop";

		case FIT:
			return "fit";

		default:
			return "";
	}
}

// Conversion of a QString into a Resize enum.
MediaSize::Resize MediaSize::string2Resize(QString resizeString) {
	if (resizeString == "crop") {
		return CROP;
	} else if (resizeString == "fit") {
		return FIT;
	} else {
		return NULL_RESIZE;
	}
}


/////////////////////
// Size management //
/////////////////////

// Getter on resizeMedia
MediaSize::Resize MediaSize::getResize() {
	return resizeMedia;
}

// Setter on resizeMedia
void MediaSize::setResize(MediaSize::Resize newResize) {
	resizeMedia = newResize;
}
