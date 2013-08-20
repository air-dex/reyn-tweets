/// @file media.cpp
/// @brief Implementation of Media
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

#include "media.hpp"
#include <QtQml>

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
	mediaSizes(),
	sourceID(-1),
	sourceIDstr("-1")
{}

// Destructor
Media::~Media() {}

// Copy constructor
Media::Media(const Media & media) :
	URLEntity(),
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
const Media & Media::operator=(const Media & media) {
	recopie(media);
	return *this;
}

// Serialization declaration
void Media::initSystem() {
	qRegisterMetaTypeStreamOperators<Media>("Media");
	qMetaTypeId<Media>();
}

// Declaring to the QML components
void Media::declareQML() {
	qmlRegisterType<Media>("ReynTweetsEntities", 0, 2, "Media");
}

// Copy of a Media
void Media::recopie(const Media & media) {
	URLEntity::recopie(media);	// Don't forget the base class !
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
QDataStream & operator<<(QDataStream & out, const Media & media) {
	return media.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, Media & media) {
	return media.fillWithStream(in);
}

// Resets the mappable to a default value
void Media::reset() {
	*this = Media();
}

// Equality between medias.
bool Media::operator==(const Media media) const {
	/*
	// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
	return this->mediaID == media->mediaID;
	//*/

	return this->mediaIDstr == media.mediaIDstr;
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void Media::fillWithVariant(QJsonObject json) {
	URLEntity::fillWithVariant(json);	// Base class
	this->mediaID = qlonglong(json.value(ID_PN).toDouble(-1));	// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
	this->mediaIDstr = json.value(ID_STR_PN).toString("-1");
	this->mediaURL = json.value(MEDIA_URL_PN).toString("");
	this->mediaURLhttps = json.value(MEDIA_URL_HTTPS_PN).toString("");
	this->mediaType = json.value(TYPE_PN).toString("");
	this->mediaSizes.fillWithVariant(json.value(SIZES_PN).toObject());
	this->sourceID = qlonglong(json.value(SOURCE_STATUS_ID_PN).toDouble(-1));	// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
	this->sourceIDstr = json.value(SOURCE_STATUS_ID_STR_PN).toString("-1");
}

// Getting a QJsonObject representation of the object
QJsonObject Media::toVariant() const {
	QJsonObject json = URLEntity::toVariant();	// Don't forget the base class !

	json.insert(ID_PN, QJsonValue(double(this->mediaID)));
	json.insert(ID_STR_PN, QJsonValue(this->mediaIDstr));
	json.insert(MEDIA_URL_PN, QJsonValue(this->mediaURL));
	json.insert(MEDIA_URL_HTTPS_PN, QJsonValue(this->mediaURLhttps));
	json.insert(TYPE_PN, QJsonValue(this->mediaType));
	json.insert(SIZES_PN, QJsonValue(this->mediaSizes.toVariant()));
	json.insert(SOURCE_STATUS_ID_PN, QJsonValue(double(this->sourceID)));
	json.insert(SOURCE_STATUS_ID_STR_PN, QJsonValue(this->sourceIDstr));

	return json;
}


////////////////////////
// Getter and setters //
////////////////////////

// id
QString Media::ID_PN = "id";

// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
qlonglong Media::getID() {
	return mediaID;
}

// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
void Media::setID(qlonglong newID) {
	mediaID = newID;
	emit idChanged();
}

// id_str
QString Media::ID_STR_PN = "id_str";

QString Media::getIDstr() {
	return mediaIDstr;
}

void Media::setIDstr(QString newID) {
	mediaIDstr = newID;
	emit idChanged();
}

// media_url
QString Media::MEDIA_URL_PN = "media_url";

QString Media::getMediaURL() {
	return mediaURL;
}

void Media::setMediaURL(QString newMediaURL) {
	mediaURL = newMediaURL;
	emit mediaURLChanged();
}

// media_url_https
QString Media::MEDIA_URL_HTTPS_PN = "media_url_https";

QString Media::getMediaURLhttps() {
	return mediaURLhttps;
}

void Media::setMediaURLhttps(QString newMediaURL) {
	mediaURLhttps = newMediaURL;
	emit mediaURLhttpsChanged();
}

// type
QString Media::TYPE_PN = "type";

QString Media::getType() {
	return mediaType;
}

void Media::setType(QString newType) {
	mediaType = newType;
	emit typeChanged();
}

// sizes
QString Media::SIZES_PN = "sizes";

MediaSizes Media::getSizes() {
	return mediaSizes;
}

MediaSizes * Media::getSizesPtr() {
	return &mediaSizes;
}

void Media::setSizes(MediaSizes newSizes) {
	mediaSizes = newSizes;
	emit sizesChanged();
}

void Media::setSizes(MediaSizes * newSizes) {
	mediaSizes = newSizes ? *newSizes : MediaSizes();
	emit sizesChanged();
}

// source_status_id
QString Media::SOURCE_STATUS_ID_PN = "source_status_id";

qlonglong Media::getSourceID() {
	return sourceID;
}

void Media::setSourceID(qlonglong newID) {
	sourceID = newID;
	sourceIDstr = QString::number(sourceID);
	emit sourceIDChanged();
}

// source_status_id_str
QString Media::SOURCE_STATUS_ID_STR_PN = "source_status_id_str";

QString Media::getSourceIDstr() {
	return sourceIDstr;
}

void Media::setSourceIDstr(QString newID) {
	sourceIDstr = newID;
	sourceID = sourceIDstr.toLongLong();
	emit sourceIDChanged();
}
