/// @file mediasize.cpp
/// @brief Implementation of MediaSize
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

#include "mediasize.hpp"
#include "../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
MediaSize::MediaSize() :
	ReynTweetsSerializable(),
	QSize(0,0),
	resizeProperty(""),
	resizeMedia(NULL_RESIZE)
{
	updateAllProperties();
}

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

// Copy of a ReynTweetsConfiguration
void MediaSize::recopie(const MediaSize & size) {
	setWidth(size.width());
	setHeight(size.height());
	resizeMedia = size.resizeMedia;
	updateAllProperties();
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
	jsonStreamingIn(in, size);

	// Updating resizeMedia
	size.fillWithPropertiesMaps();

	return in;
}


///////////////////////////
// Properties management //
///////////////////////////

// Filling serializable fields with thecorresponding  property maps
void MediaSize::fillWithPropertiesMaps() {
	resizeMedia = string2Resize(resizeProperty);
}

// Updating all the properties
void MediaSize::updateAllProperties() {
	updateResize();
}

// Reading method for resize
QString MediaSize::getResizeProperty() {
	return resizeProperty;
}

// Writing method for resize
void MediaSize::setResizeProperty(QString newResize) {
	resizeProperty = newResize;
}

// Updating the property resize
void MediaSize::updateResize() {
	setProperty("resize", QVariant(resize2String(resizeMedia)));
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
	updateResize();
}
