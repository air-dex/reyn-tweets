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
void MediaSizes::fillWithJSON(QJsonObject json) {
	// "large" property
	QJsonValue propval = json.value(LARGE_PN);

	if (!propval.isUndefined() && propval.isObject()) {
		QJsonObject mediasize = propval.toObject();
		this->largeSize.fillWithJSON(mediasize);
	}

	// "medium" property
	propval = json.value(MEDIUM_PN);

	if (!propval.isUndefined() && propval.isObject()) {
		QJsonObject mediasize = propval.toObject();
		this->mediumSize.fillWithJSON(mediasize);
	}

	// "small" property
	propval = json.value(SMALL_PN);

	if (!propval.isUndefined() && propval.isObject()) {
		QJsonObject mediasize = propval.toObject();
		this->smallSize.fillWithJSON(mediasize);
	}

	// "thumb" property
	propval = json.value(THUMB_PN);

	if (!propval.isUndefined() && propval.isObject()) {
		QJsonObject mediasize = propval.toObject();
		this->thumbSize.fillWithJSON(mediasize);
	}
}

// Getting a QJsonObject representation of the object
QJsonObject MediaSizes::toJSON() const {
	QJsonObject json;

	json.insert(LARGE_PN, QJsonValue(this->largeSize.toJSON()));
	json.insert(MEDIUM_PN, QJsonValue(this->mediumSize.toJSON()));
	json.insert(SMALL_PN, QJsonValue(this->smallSize.toJSON()));
	json.insert(THUMB_PN, QJsonValue(this->thumbSize.toJSON()));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// Reading method for the property large
QVariantMap MediaSizes::getLargeProperty() {
	return largeSize.toVariant();
}

// Writing method for the property large
void MediaSizes::setLarge(QVariantMap newLargeMap) {
	largeSize.fillWithVariant(newLargeMap);
}

// Reading method for the property medium
QVariantMap MediaSizes::getMediumProperty() {
	return mediumSize.toVariant();
}

// Writing method for the property medium
void MediaSizes::setMedium(QVariantMap newMediumMap) {
	mediumSize.fillWithVariant(newMediumMap);
}

// Reading method for the property small
QVariantMap MediaSizes::getSmallProperty() {
	return smallSize.toVariant();
}

// Writing method for the property small
void MediaSizes::setSmall(QVariantMap newSmallMap) {
	smallSize.fillWithVariant(newSmallMap);
}

// Reading method for the property thumb
QVariantMap MediaSizes::getThumbProperty() {
	return thumbSize.toVariant();
}

// Writing method for the property thumb
void MediaSizes::setThumb(QVariantMap newThumbMap) {
	thumbSize.fillWithVariant(newThumbMap);
}


////////////////////////
// Getter and setters //
////////////////////////

// large
QString MediaSizes::LARGE_PN = "large";

MediaSize MediaSizes::getLarge() {
	return largeSize;
}

void MediaSizes::setLarge(MediaSize newLargeSize) {
	largeSize = newLargeSize;
}

// medium
QString MediaSizes::MEDIUM_PN = "medium";

MediaSize MediaSizes::getMedium() {
	return mediumSize;
}

void MediaSizes::setMedium(MediaSize newMediumSize) {
	mediumSize = newMediumSize;
}

// small
QString MediaSizes::SMALL_PN = "small";

MediaSize MediaSizes::getSmall() {
	return smallSize;
}

void MediaSizes::setSmall(MediaSize newSmallSize) {
	smallSize = newSmallSize;
}

// thumb
QString MediaSizes::THUMB_PN = "thumb";

MediaSize MediaSizes::getThumb() {
	return thumbSize;
}

void MediaSizes::setThumb(MediaSize newThumbSize) {
	thumbSize = newThumbSize;
}
