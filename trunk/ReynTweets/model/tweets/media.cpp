/// @file media.cpp
/// @brief Implementation of Media
///
/// Revisions older than r243 was in /trunk/ReynTwets/model
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

#include "media.hpp"
#include "../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
Media::Media() :
	URLEntity(),
	mediaID(-1),
	mediaIDstr("-1"),
	mediaURL(""),
	mediaURLhttps(""),
	mediaType(""),
	mediaSizes()
{}

// Destructor
Media::~Media() {}

// Copy constructor
Media::Media(const Media & media) {
	recopie(media);
}

// Affectation
const Media & Media::operator=(const Media & media) {
	recopie(media);
	return *this;
}

// Serialization declaration
void Media::initSystem() {
	qRegisterMetaTypeStreamOperators<Media>("Media");
	qMetaTypeId<Media>();
}

// Copy of a Media
void Media::recopie(const Media & media) {
	URLEntity::recopie(media);	// Don't forget the base class !
	mediaID = media.mediaID;
	mediaIDstr = media.mediaIDstr;
	mediaURL = media.mediaURL;
	mediaURLhttps = media.mediaURLhttps;
	mediaType = media.mediaType;
	mediaSizes = media.mediaSizes;
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const Media & media) {
	return jsonStreamingOut(out, media);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, Media & media) {
	return jsonStreamingIn(in, media);
}


///////////////////////////
// Properties management //
///////////////////////////

// Reading method for the property sizes
QVariantMap Media::getSizesProperty() {
	return mediaSizes.toVariant();
}

// Writing method for the property sizes
void Media::setSizes(QVariantMap newMap) {
	mediaSizes.fillWithVariant(newMap);
}


////////////////////////
// Getter and setters //
////////////////////////

// Reading mediaID
qlonglong Media::getID() {
	return mediaID;
}

// Writing mediaID
void Media::setID(qlonglong newID) {
	mediaID = newID;
}

// Reading mediaIDstr
QString Media::getIDstr() {
	return mediaIDstr;
}

// Writing mediaIDstr
void Media::setIDstr(QString newID) {
	mediaIDstr = newID;
}

// Reading method for mediaURL
QString Media::getMediaURL() {
	return mediaURL;
}

// Writing mediaURL
void Media::setMediaURL(QString newMediaURL) {
	mediaURL = newMediaURL;
}

// Reading method for mediaURLhttps
QString Media::getMediaURLhttps() {
	return mediaURLhttps;
}

// Writing method for mediaURLhttps
void Media::setMediaURLhttps(QString newMediaURL) {
	mediaURLhttps = newMediaURL;
}

// Reading method for mediaType
QString Media::getType() {
	return mediaType;
}

// Writing method for mediaType
void Media::setType(QString newType) {
	mediaType = newType;
}

// Reading mediaSizes
MediaSizes Media::getSizes() {
	return mediaSizes;
}

// Writing mediaSizes
void Media::setSizes(MediaSizes newSizes) {
	mediaSizes = newSizes;
}
