/// @file media.cpp
/// @brief Implementation of Media
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

#include "media.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
Media2::Media2() :
	URLEntity2(),
	mediaID(-1),
	mediaIDstr("-1"),
	mediaURL(""),
	mediaURLhttps(""),
	mediaType(""),
	mediaSizes(),
	sourceID(-1),
	sourceIDstr("-1")
{}

// Destructor
Media2::~Media2() {}

// Copy constructor
Media2::Media2(const Media2 & media) :
	URLEntity2(),
	mediaID(-1),
	mediaIDstr("-1"),
	mediaURL(""),
	mediaURLhttps(""),
	mediaType(""),
	mediaSizes(),
	sourceID(-1),
	sourceIDstr("-1")
{
	recopie(media);
}

// Affectation
const Media2 & Media2::operator=(const Media2 & media) {
	recopie(media);
	return *this;
}

// Serialization declaration
void Media2::initSystem() {
	qRegisterMetaTypeStreamOperators<Media2>("Media2");
	qMetaTypeId<Media2>();
}

// Copy of a Media
void Media2::recopie(const Media2 & media) {
	URLEntity2::recopie(media);	// Don't forget the base class !
	this->mediaID = media.mediaID;
	this->mediaIDstr = media.mediaIDstr;
	this->mediaURL = media.mediaURL;
	this->mediaURLhttps = media.mediaURLhttps;
	this->mediaType = media.mediaType;
	this->mediaSizes = media.mediaSizes;
	this->sourceID = media.sourceID;
	this->sourceIDstr = media.sourceIDstr;
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const Media2 & media) {
	return media.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, Media2 & media) {
	return media.fillWithStream(in);
}

// Resets the mappable to a default value
void Media2::reset() {
	*this = Media2();
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void Media2::fillWithJSON(QJsonObject json) {
	// Base class
	URLEntity2::fillWithJSON(json);

	// "id" property
	QJsonValue propval = json.value(ID_PN);

	if (!propval.isUndefined() && propval.isDouble()) {
		qlonglong id = qlonglong(propval.toDouble());
		this->mediaID = id;
	}

	// "id_str" property
	propval = json.value(ID_STR_PN);

	if (!propval.isUndefined() && propval.isString()) {
		QString idStr = propval.toString();
		this->mediaIDstr = idStr;
	}

	// "media_url" property
	propval = json.value(MEDIA_URL_PN);

	if (!propval.isUndefined() && propval.isString()) {
		QString url = propval.toString();
		this->mediaURL = url;
	}

	// "media_url_https" property
	propval = json.value(MEDIA_URL_HTTPS_PN);

	if (!propval.isUndefined() && propval.isString()) {
		QString url = propval.toString();
		this->mediaURLhttps = url;
	}

	// "type" property
	propval = json.value(TYPE_PN);

	if (!propval.isUndefined() && propval.isString()) {
		QString type = propval.toString();
		this->mediaType = type;
	}

	// "sizes" property
	propval = json.value(SIZES_PN);

	if (!propval.isUndefined() && propval.isObject()) {
		QJsonObject sizes = propval.toObject();
		this->mediaSizes.fillWithJSON(sizes);
	}

	// "source_status_id" property
	QJsonValue propval = json.value(SOURCE_STATUS_ID_PN);

	if (!propval.isUndefined() && propval.isDouble()) {
		qlonglong id = qlonglong(propval.toDouble());
		this->sourceID = id;
	}

	// "source_status_id_str" property
	propval = json.value(SOURCE_STATUS_ID_STR_PN);

	if (!propval.isUndefined() && propval.isString()) {
		QString idStr = propval.toString();
		this->sourceIDstr = idStr;
	}
}

// Getting a QJsonObject representation of the object
QJsonObject Media2::toJSON() const {
	QJsonObject json = URLEntity2::toJSON();	// Don't forget the base class !

	json.insert(ID_PN, QJsonValue(this->mediaID));
	json.insert(ID_STR_PN, QJsonValue(this->mediaIDstr));
	json.insert(MEDIA_URL_PN, QJsonValue(this->mediaURL));
	json.insert(MEDIA_URL_HTTPS_PN, QJsonValue(this->mediaURLhttps));
	json.insert(TYPE_PN, QJsonValue(this->mediaType));
	json.insert(SIZES_PN, QJsonValue(this->mediaSizes.toJSON()));
	json.insert(SOURCE_STATUS_ID_PN, QJsonValue(this->sourceID));
	json.insert(SOURCE_STATUS_ID_STR_PN, QJsonValue(this->sourceIDstr));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// Reading method for the property sizes
QVariantMap Media2::getSizesProperty() {
	return mediaSizes.toVariant();
}

// Writing method for the property sizes
void Media2::setSizes(QVariantMap newMap) {
	mediaSizes.fillWithVariant(newMap);
}


////////////////////////
// Getter and setters //
////////////////////////

// id
QString Media2::ID_PN = "id";

qlonglong Media2::getID() {
	return mediaID;
}

void Media2::setID(qlonglong newID) {
	mediaID = newID;
	mediaIDstr = QString::number(mediaID);
}

// id_str
QString Media2::ID_STR_PN = "id_str";

QString Media2::getIDstr() {
	return mediaIDstr;
}

void Media2::setIDstr(QString newID) {
	mediaIDstr = newID;
	mediaID = mediaIDstr.toLongLong();
}

// media_url
QString Media2::MEDIA_URL_PN = "media_url";

QString Media2::getMediaURL() {
	return mediaURL;
}

void Media2::setMediaURL(QString newMediaURL) {
	mediaURL = newMediaURL;
}

// media_url_https
QString Media2::MEDIA_URL_HTTPS_PN = "media_url_https";

QString Media2::getMediaURLhttps() {
	return mediaURLhttps;
}

void Media2::setMediaURLhttps(QString newMediaURL) {
	mediaURLhttps = newMediaURL;
}

// type
QString Media2::TYPE_PN = "type";

QString Media2::getType() {
	return mediaType;
}

void Media2::setType(QString newType) {
	mediaType = newType;
}

// sizes
QString Media2::SIZES_PN = "sizes";

MediaSizes2 Media2::getSizes() {
	return mediaSizes;
}

void Media2::setSizes(MediaSizes2 newSizes) {
	mediaSizes = newSizes;
}

// source_status_id
QString Media2::SOURCE_STATUS_ID_PN = "source_status_id";

qlonglong Media2::getSourceID() {
	return sourceID;
}

void Media2::setSourceID(qlonglong newID) {
	sourceID = newID;
	sourceIDstr = QString::number(sourceID);
}

// source_status_id_str
QString Media2::SOURCE_STATUS_ID_STR_PN = "source_status_id_str";

QString Media2::getSourceIDstr() {
	return sourceIDstr;
}

void Media2::setSourceIDstr(QString newID) {
	sourceIDstr = newID;
	sourceID = sourceIDstr.toLongLong();
}
