/// @file mediasize.cpp
/// @brief Implementation of MediaSize
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

#include "mediasize.hpp"
#include <QtQml>

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
MediaSize::MediaSize() :
	JsonObject(),
	QSize(0,0),
	resizeMedia(NULL_RESIZE)
{}

// Destructor
MediaSize::~MediaSize() {}

// Copy constructor
MediaSize::MediaSize(const MediaSize & size) :
	JsonObject(),
	QSize(0,0),
	resizeMedia(NULL_RESIZE)
{
	recopie(size);
}

// Affectation
const MediaSize & MediaSize::operator=(const MediaSize & size) {
	recopie(size);
	return *this;
}

// Copy of a MediaSize
void MediaSize::recopie(const MediaSize & size) {
	JsonObject::recopie(size);
	setWidth(size.width());
	setHeight(size.height());
	resizeMedia = size.resizeMedia;
}

// Serialization declaration
void MediaSize::initSystem() {
	qRegisterMetaTypeStreamOperators<MediaSize>("MediaSize");
	qMetaTypeId<MediaSize>();
}

// Declaring to the QML components
void MediaSize::declareQML() {
	qmlRegisterType<MediaSize>("ReynTweetsEntities", 0, 2, "MediaSize");
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const MediaSize & size) {
	return size.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, MediaSize & size) {
	return size.fillWithStream(in);
}

// Resets the mappable to a default value
void MediaSize::reset() {
	*this = MediaSize();
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void MediaSize::fillWithVariant(QJsonObject json) {
	this->setWidth(int(json.value(W_PN).toDouble(0)));
	this->setHeight(int(json.value(H_PN).toDouble(0)));
	this->setResize(json.value(RESIZE_PN).toString(""));
}

// Getting a QJsonObject representation of the object
QJsonObject MediaSize::toVariant() const {
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
QString MediaSize::W_PN = "w";

void MediaSize::setWidth(int w) {
	QSize::setWidth(w);
	emit widthChanged();
}

// h
QString MediaSize::H_PN = "h";

void MediaSize::setHeight(int h) {
	QSize::setWidth(h);
	emit heightChanged();
}

// resize
QString MediaSize::RESIZE_PN = "resize";

QString MediaSize::getResizeProperty() const {
	return resize2String(resizeMedia);
}

void MediaSize::setResize(QString newResize) {
	resizeMedia = string2Resize(newResize);
	emit resizeChanged();
}


/////////////////
// Resize enum //
/////////////////

// Conversion of a Resize into a QString.
QString MediaSize::resize2String(MediaSize::Resize resizeValue) const {
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
