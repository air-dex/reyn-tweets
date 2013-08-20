/// @file mediasize.cpp
/// @brief Implementation of MediaSize
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

#include "mediasize2.hpp"
#include "../../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
MediaSize2::MediaSize2() :
	JsonObject(),
	QSize(0,0),
	resizeMedia(NULL_RESIZE)
{}

// Destructor
MediaSize2::~MediaSize2() {}

// Copy constructor
MediaSize2::MediaSize2(const MediaSize & size) :
	JsonObject(),
	QSize(0,0),
	resizeMedia(NULL_RESIZE)
{
	recopie(size);
}

// Affectation
const MediaSize2 & MediaSize2::operator=(const MediaSize2 & size) {
	recopie(size);
	return *this;
}

// Copy of a MediaSize
void MediaSize2::recopie(const MediaSize2 & size) {
	JsonObject::recopie(size);
	setWidth(size.width());
	setHeight(size.height());
	resizeMedia = size.resizeMedia;
}

// Serialization declaration
void MediaSize2::initSystem() {
	qRegisterMetaTypeStreamOperators<MediaSize2>("MediaSize2");
	qMetaTypeId<MediaSize2>();
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const MediaSize2 & size) {
	return jsonStreamingOut(out, size);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, MediaSize2 & size) {
	return jsonStreamingIn(in, size);
}

// Resets the mappable to a default value
void MediaSize2::reset() {
	*this = MediaSize2();
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void MediaSize2::fillWithJSON(QJsonObject json) {
	// "w" property
	QJsonValue propval = json.value(W_PN);

	if (!propval.isUndefined() && propval.isDouble()) {
		int w = int( propval.toDouble() );
		this->setWidth(w);
	}

	// "h" property
	propval = json.value(H_PN);

	if (!propval.isUndefined() && propval.isString()) {
		int h = int( propval.toDouble() );
		this->setHeight(h);
	}

	// "resize" property
	propval = json.value(RESIZE_PN);

	if (!propval.isUndefined() && propval.isString()) {
		QString resStr = propval.toString();
		this->setResize(resStr);
	}
}

// Getting a QJsonObject representation of the object
QJsonObject MediaSize2::toJSON() {
	QJsonObject json;

	json.insert(W_PN, QJsonValue(this->width()));
	json.insert(H_PN, QJsonValue(this->height()));
	json.insert(RESIZE_PN, QJsonValue(this->getResizeProperty()));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// w
QString MediaSize2::W_PN = "w";

// h
QString MediaSize2::H_PN = "h";

// resize
QString MediaSize2::RESIZE_PN = "resize";

QString MediaSize2::getResizeProperty() {
	return resize2String(resizeMedia);
}

void MediaSize2::setResize(QString newResize) {
	resizeMedia = string2Resize(newResize);
}


/////////////////
// Resize enum //
/////////////////

// Conversion of a Resize into a QString.
QString MediaSize2::resize2String(MediaSize2::Resize resizeValue) {
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
MediaSize2::Resize MediaSize2::string2Resize(QString resizeString) {
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
MediaSize2::Resize MediaSize2::getResize() {
	return resizeMedia;
}

// Setter on resizeMedia
void MediaSize2::setResize(MediaSize2::Resize newResize) {
	resizeMedia = newResize;
}
