/// @file mediasizes.cpp
/// @brief Implementation of MediaSizes
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

#include "mediasizes.hpp"
#include <QtQml>

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
MediaSizes::MediaSizes() :
	JsonObject(),
	largeSize(),
	mediumSize(),
	smallSize(),
	thumbSize()
{}

// Destructor
MediaSizes::~MediaSizes() {}

// Copy constructor
MediaSizes::MediaSizes(const MediaSizes & sizes) :
	JsonObject(),
	largeSize(),
	mediumSize(),
	smallSize(),
	thumbSize()
{
	recopie(sizes);
}

// Affectation
const MediaSizes & MediaSizes::operator=(const MediaSizes & sizes) {
	recopie(sizes);
	return *this;
}

// Serialization declaration
void MediaSizes::initSystem() {
	qRegisterMetaTypeStreamOperators<MediaSizes>("MediaSizes");
	qMetaTypeId<MediaSizes>();
}

// Declaring to the QML components
void MediaSizes::declareQML() {
	qmlRegisterType<MediaSizes>("ReynTweetsEntities", 0, 2, "MediaSizes");
}

// Copy of a MediaSizes
void MediaSizes::recopie(const MediaSizes & sizes) {
	JsonObject::recopie(sizes);
	largeSize = sizes.largeSize;
	mediumSize = sizes.mediumSize;
	smallSize = sizes.smallSize;
	thumbSize = sizes.thumbSize;
}

// Resets the mappable to a default value
void MediaSizes::reset() {
	*this = MediaSizes();
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const MediaSizes & sizes) {
	return sizes.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, MediaSizes & sizes) {
	return sizes.fillWithStream(in);
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void MediaSizes::fillWithVariant(QJsonObject json) {
	this->largeSize.fillWithVariant(json.value(LARGE_PN).toObject());
	this->mediumSize.fillWithVariant(json.value(MEDIUM_PN).toObject());
	this->smallSize.fillWithVariant(json.value(SMALL_PN).toObject());
	this->thumbSize.fillWithVariant(json.value(THUMB_PN).toObject());
}

// Getting a QJsonObject representation of the object
QJsonObject MediaSizes::toVariant() const {
	QJsonObject json;

	json.insert(LARGE_PN, QJsonValue(this->largeSize.toVariant()));
	json.insert(MEDIUM_PN, QJsonValue(this->mediumSize.toVariant()));
	json.insert(SMALL_PN, QJsonValue(this->smallSize.toVariant()));
	json.insert(THUMB_PN, QJsonValue(this->thumbSize.toVariant()));

	return json;
}


////////////////////////
// Getter and setters //
////////////////////////

// large
QString MediaSizes::LARGE_PN = "large";

MediaSize MediaSizes::getLarge() {
	return largeSize;
}

MediaSize * MediaSizes::getLargePtr() {
	return &largeSize;
}

void MediaSizes::setLarge(MediaSize newLargeSize) {
	largeSize = newLargeSize;
	emit largeChanged();
}

void MediaSizes::setLarge(MediaSize * newLargeSize) {
	largeSize = newLargeSize ? *newLargeSize : MediaSize();
	emit largeChanged();
}

// medium
QString MediaSizes::MEDIUM_PN = "medium";

MediaSize MediaSizes::getMedium() {
	return mediumSize;
}

MediaSize * MediaSizes::getMediumPtr() {
	return &mediumSize;
}

void MediaSizes::setMedium(MediaSize newMediumSize) {
	mediumSize = newMediumSize;
	emit mediumChanged();
}

void MediaSizes::setMedium(MediaSize * newMediumSize) {
	mediumSize = newMediumSize ? *newMediumSize : MediaSize();
	emit mediumChanged();
}

// small
QString MediaSizes::SMALL_PN = "small";

MediaSize MediaSizes::getSmall() {
	return smallSize;
}

MediaSize * MediaSizes::getSmallPtr() {
	return &smallSize;
}

void MediaSizes::setSmall(MediaSize newSmallSize) {
	smallSize = newSmallSize;
	emit smallChanged();
}

void MediaSizes::setSmall(MediaSize * newSmallSize) {
	smallSize = newSmallSize ? *newSmallSize : MediaSize();
	emit smallChanged();
}

// thumb
QString MediaSizes::THUMB_PN = "thumb";

MediaSize MediaSizes::getThumb() {
	return thumbSize;
}

MediaSize * MediaSizes::getThumbPtr() {
	return &thumbSize;
}

void MediaSizes::setThumb(MediaSize newThumbSize) {
	thumbSize = newThumbSize;
	emit thumbChanged();
}

void MediaSizes::setThumb(MediaSize * newThumbSize) {
	thumbSize = newThumbSize ? *newThumbSize : MediaSize();
	emit thumbChanged();
}
