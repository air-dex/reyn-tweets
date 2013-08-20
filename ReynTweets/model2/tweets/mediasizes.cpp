/// @file mediasizes.cpp
/// @brief Implementation of MediaSizes
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

#include "mediasizes.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
MediaSizes2::MediaSizes2() :
	JsonObject(),
	largeSize(),
	mediumSize(),
	smallSize(),
	thumbSize()
{}

// Destructor
MediaSizes2::~MediaSizes2() {}

// Copy constructor
MediaSizes2::MediaSizes2(const MediaSizes2 & sizes) :
	JsonObject(),
	largeSize(),
	mediumSize(),
	smallSize(),
	thumbSize()
{
	recopie(sizes);
}

// Affectation
const MediaSizes2 & MediaSizes2::operator=(const MediaSizes2 & sizes) {
	recopie(sizes);
	return *this;
}

// Serialization declaration
void MediaSizes2::initSystem() {
	qRegisterMetaTypeStreamOperators<MediaSizes2>("MediaSizes2");
	qMetaTypeId<MediaSizes2>();
}

// Copy of a MediaSizes
void MediaSizes2::recopie(const MediaSizes & sizes) {
	JsonObject::recopie(sizes);
	largeSize = sizes.largeSize;
	mediumSize = sizes.mediumSize;
	smallSize = sizes.smallSize;
	thumbSize = sizes.thumbSize;
}

// Resets the mappable to a default value
void MediaSizes2::reset() {
	*this = MediaSizes2();
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const MediaSizes2 & sizes) {
	return jsonObjectStreamingOut(out, sizes);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, MediaSizes2 & sizes) {
	return jsonObjectStreamingIn(in, sizes);
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void MediaSizes2::fillWithJSON(QJsonObject json) {
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
QJsonObject MediaSizes2::toJSON() {
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
QVariantMap MediaSizes2::getLargeProperty() {
	return largeSize.toVariant();
}

// Writing method for the property large
void MediaSizes2::setLarge(QVariantMap newLargeMap) {
	largeSize.fillWithVariant(newLargeMap);
}

// Reading method for the property medium
QVariantMap MediaSizes2::getMediumProperty() {
	return mediumSize.toVariant();
}

// Writing method for the property medium
void MediaSizes2::setMedium(QVariantMap newMediumMap) {
	mediumSize.fillWithVariant(newMediumMap);
}

// Reading method for the property small
QVariantMap MediaSizes2::getSmallProperty() {
	return smallSize.toVariant();
}

// Writing method for the property small
void MediaSizes2::setSmall(QVariantMap newSmallMap) {
	smallSize.fillWithVariant(newSmallMap);
}

// Reading method for the property thumb
QVariantMap MediaSizes2::getThumbProperty() {
	return thumbSize.toVariant();
}

// Writing method for the property thumb
void MediaSizes2::setThumb(QVariantMap newThumbMap) {
	thumbSize.fillWithVariant(newThumbMap);
}


////////////////////////
// Getter and setters //
////////////////////////

// large
QString MediaSizes2::LARGE_PN = "large";

MediaSize2 MediaSizes2::getLarge() {
	return largeSize;
}

void MediaSizes2::setLarge(MediaSize2 newLargeSize) {
	largeSize = newLargeSize;
}

// medium
QString MediaSizes2::MEDIUM_PN = "medium";

MediaSize2 MediaSizes2::getMedium() {
	return mediumSize;
}

void MediaSizes2::setMedium(MediaSize2 newMediumSize) {
	mediumSize = newMediumSize;
}

// small
QString MediaSizes2::SMALL_PN = "small";

MediaSize2 MediaSizes2::getSmall() {
	return smallSize;
}

void MediaSizes2::setSmall(MediaSize2 newSmallSize) {
	smallSize = newSmallSize;
}

// thumb
QString MediaSizes2::THUMB_PN = "thumb";

MediaSize2 MediaSizes2::getThumb() {
	return thumbSize;
}

void MediaSizes2::setThumb(MediaSize2 newThumbSize) {
	thumbSize = newThumbSize;
}
