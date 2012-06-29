/// @file mediasizes.cpp
/// @brief Implementation of MediaSizes
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

#include "mediasizes.hpp"
#include "../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
MediaSizes::MediaSizes() :
	ReynTweetsMappable(),
	largeSize(),
	mediumSize(),
	smallSize(),
	thumbSize()
{}

// Destructor
MediaSizes::~MediaSizes() {}

// Copy constructor
MediaSizes::MediaSizes(const MediaSizes & sizes) :
    ReynTweetsMappable()
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
	ReynTweetsMappable::recopie(sizes);
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
	return jsonStreamingOut(out, sizes);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, MediaSizes & sizes) {
	return jsonStreamingIn(in, sizes);
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

// Reading method for largeSize
MediaSize MediaSizes::getLarge() {
	return largeSize;
}

// Writing method for largeSize
void MediaSizes::setLarge(MediaSize newLargeSize) {
	largeSize = newLargeSize;
}

// Reading method for mediumSize
MediaSize MediaSizes::getMedium() {
	return mediumSize;
}

// Writing method for mediumSize
void MediaSizes::setMedium(MediaSize newMediumSize) {
	mediumSize = newMediumSize;
}

// Reading method smallSize
MediaSize MediaSizes::getSmall() {
	return smallSize;
}

// Writing method for smallSize
void MediaSizes::setSmall(MediaSize newSmallSize) {
	smallSize = newSmallSize;
}

// Reading method for thumbSize
MediaSize MediaSizes::getThumb() {
	return thumbSize;
}

// Writing method for thumbSize
void MediaSizes::setThumb(MediaSize newThumbSize) {
	thumbSize = newThumbSize;
}
