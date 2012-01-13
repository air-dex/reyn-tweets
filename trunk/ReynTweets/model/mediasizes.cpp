/// @file mediasizes.cpp
/// @brief Implementation of MediaSizes
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

#include "mediasizes.hpp"
#include "../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
MediaSizes::MediaSizes() :
	ReynTweetsSerializable(),
	largeMap(),
	mediumMap(),
	smallMap(),
	thumbMap(),
	largeSize(),
	mediumSize(),
	smallSize(),
	thumbSize()
{
	updateAllProperties();
}

// Destructor
MediaSizes::~MediaSizes() {}

// Copy constructor
MediaSizes::MediaSizes(const MediaSizes & sizes) {
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
	largeSize = sizes.largeSize;
	mediumSize = sizes.mediumSize;
	smallSize = sizes.smallSize;
	thumbSize = sizes.thumbSize;
	updateAllProperties();
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const MediaSizes & sizes) {
	return jsonStreamingOut(out, sizes);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, MediaSizes & sizes) {
	jsonStreamingIn(in, sizes);

	// Updating resizeMedia
	sizes.fillWithPropertiesMaps();

	return in;
}


///////////////////////////
// Properties management //
///////////////////////////

// Filling serializable fields with thecorresponding  property maps
void MediaSizes::fillWithPropertiesMaps() {
	largeSize.fillWithMap(largeMap);
	mediumSize.fillWithMap(mediumMap);
	smallSize.fillWithMap(smallMap);
	thumbSize.fillWithMap(thumbMap);
}

// Updating all the properties
void MediaSizes::updateAllProperties() {
	updateLarge();
	updateMedium();
	updateSmall();
	updateThumb();
}

// Reading method for the property large
QVariantMap MediaSizes::getLarge() {
	return largeMap;
}

// Writing method for the property large
void MediaSizes::setLarge(QVariantMap newLargeMap) {
	largeMap = newLargeMap;
}

// Updating the property large
void MediaSizes::updateLarge() {
	setProperty("large", QVariant(largeSize.toMap()));
}

// Reading method for the property medium
QVariantMap MediaSizes::getMedium() {
	return mediumMap;
}

// Writing method for the property medium
void MediaSizes::setMedium(QVariantMap newMediumMap) {
	mediumMap = newMediumMap;
}

// Updating the property medium
void MediaSizes::updateMedium() {
	setProperty("medium", QVariant(mediumSize.toMap()));
}

// Reading method for the property small
QVariantMap MediaSizes::getSmall() {
	return smallMap;
}

// Writing method for the property small
void MediaSizes::setSmall(QVariantMap newSmallMap) {
	smallMap = newSmallMap;
}

// Updating the property small
void MediaSizes::updateSmall() {
	setProperty("small", QVariant(smallSize.toMap()));
}

// Reading method for the property thumb
QVariantMap MediaSizes::getThumb() {
	return thumbMap;
}

// Writing method for the property thumb
void MediaSizes::setThumb(QVariantMap newThumbMap) {
	thumbMap = newThumbMap;
}

// Updating the property thumb
void MediaSizes::updateThumb() {
	setProperty("thumb", QVariant(thumbSize.toMap()));
}


////////////////////////
// Getter and setters //
////////////////////////

// Reading method for largeSize
MediaSize MediaSizes::getLargeSize() {
	return largeSize;
}

// Writing method for largeSize
void MediaSizes::setLargeSize(MediaSize newLargeSize) {
	largeSize = newLargeSize;
	updateLarge();
}

// Reading method for mediumSize
MediaSize MediaSizes::getMediumSize() {
	return mediumSize;
}

// Writing method for mediumSize
void MediaSizes::setMediumSize(MediaSize newMediumSize) {
	mediumSize = newMediumSize;
	updateMedium();
}

// Reading method smallSize
MediaSize MediaSizes::getSmallSize() {
	return smallSize;
}

// Writing method for smallSize
void MediaSizes::setSmallSize(MediaSize newSmallSize) {
	smallSize = newSmallSize;
	updateSmall();
}

// Reading method for thumbSize
MediaSize MediaSizes::getThumbSize() {
	return thumbSize;
}

// Writing method for thumbSize
void MediaSizes::setThumbSize(MediaSize newThumbSize) {
	thumbSize = newThumbSize;
	updateThumb();
}
