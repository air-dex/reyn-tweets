/// @file twitterplace.cpp
/// @brief Implementation of TwitterPlace
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

#include "twitterplace.hpp"
#include <QtQml>
#include "../../reyntweetsutils.hpp"

// Constructor
TwitterPlace::TwitterPlace() :
	JsonObject(),
	placeMetadata(),
	placePolygon(),
	land(""),
	landCode(""),
	fullName(""),
	placeID(ReynTweets::FAKE_PLACE_ID),
	placeName(""),
	placeType(""),
	metadataURL("")
{}

// Destructor
TwitterPlace::~TwitterPlace() {}

// Copy constructor
TwitterPlace::TwitterPlace(const TwitterPlace & place) :
	JsonObject(),
	placeMetadata(),
	placePolygon(),
	land(""),
	landCode(""),
	fullName(""),
	placeID(ReynTweets::FAKE_PLACE_ID),
	placeName(""),
	placeType(""),
	metadataURL("")
{
	recopie(place);
}

// Affectation
const TwitterPlace & TwitterPlace::operator=(const TwitterPlace & place)
{
	recopie(place);
	return *this;
}

// Copy of a TwitterPlace
void TwitterPlace::recopie(const TwitterPlace & place) {
	JsonObject::recopie(place);
	this->placeMetadata = place.placeMetadata;
	this->placePolygon = place.placePolygon;
	this->land = place.land;
	this->landCode = place.landCode;
	this->fullName = place.fullName;
	this->placeID = place.placeID;
	this->placeName = place.placeName;
	this->placeType = place.placeType;
	this->metadataURL = place.metadataURL;
}

// Serialization declaration
void TwitterPlace::initSystem() {
	qRegisterMetaTypeStreamOperators<TwitterPlace>("TwitterPlace");
	qMetaTypeId<TwitterPlace>();
}

// Declaring to the QML components
void TwitterPlace::declareQML() {
	// @uri ReynTweetsComponents
	qmlRegisterType<TwitterPlace>(ReynTweets::QML_LIBRARY_NAME.toLatin1().constData(),
								  ReynTweets::MAJOR_VERSION, ReynTweets::MINOR_VERSION,
								  "TwitterPlace");
}

// Resets to a default value
void TwitterPlace::reset() {
	*this = TwitterPlace();
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void TwitterPlace::fillWithVariant(QJsonObject json) {
	this->placeMetadata = json.value(ATTRIBUTES_PN).toObject().toVariantMap();
	this->placePolygon.fillWithVariant(json.value(BOUNDING_BOX_PN).toObject());
	this->land = json.value(COUNTRY_PN).toString("");
	this->landCode = json.value(COUNTRY_CODE_PN).toString("");
	this->fullName = json.value(FULL_NAME_PN).toString("");
	this->placeID = json.value(ID_PN).toString(ReynTweets::FAKE_PLACE_ID);
	this->placeName = json.value(NAME_PN).toString("");
	this->placeType = json.value(PLACE_TYPE_PN).toString("");
	this->metadataURL = json.value(URL_PN).toString("");
}

// QJsonObject representation of the object
QJsonObject TwitterPlace::toVariant() const {
	QJsonObject json;

	json.insert(ATTRIBUTES_PN, QJsonValue::fromVariant(this->placeMetadata));
	json.insert(BOUNDING_BOX_PN, QJsonValue(this->placePolygon.toVariant()));
	json.insert(COUNTRY_PN, QJsonValue(this->land));
	json.insert(COUNTRY_CODE_PN, QJsonValue(this->landCode));
	json.insert(FULL_NAME_PN, QJsonValue(this->fullName));
	json.insert(ID_PN, QJsonValue(this->placeID));
	json.insert(NAME_PN, QJsonValue(this->placeName));
	json.insert(PLACE_TYPE_PN, QJsonValue(this->placeType));
	json.insert(URL_PN, QJsonValue(this->metadataURL));

	return json;
}


/////////////////////////////////////
// Friends serialization operators //
/////////////////////////////////////

// Output stream
QDataStream & operator<<(QDataStream & out, const TwitterPlace & place) {
	return place.writeInStream(out);
}

// Input stream
QDataStream & operator>>(QDataStream & in, TwitterPlace & place) {
	return place.fillWithStream(in);
}

///////////////////////////
// Properties management //
///////////////////////////

// attributes
QString TwitterPlace::ATTRIBUTES_PN = "attributes";

QVariantMap TwitterPlace::getAttributes() {
	return this->placeMetadata;
}

void TwitterPlace::setAttributes(QVariantMap newValue) {
	this->placeMetadata = newValue;
	emit attributesChanged();
}

// bounding_box
QString TwitterPlace::BOUNDING_BOX_PN = "bounding_box";

GeoBoundingBox TwitterPlace::getBoundingBox() {
	return placePolygon;
}

GeoBoundingBox * TwitterPlace::getBoundingBoxPtr() {
	return &placePolygon;
}

void TwitterPlace::setBoundingBox(GeoBoundingBox newValue) {
	this->placePolygon = newValue;
	emit boundingBoxChanged();
}

void TwitterPlace::setBoundingBox(GeoBoundingBox * newValue) {
	this->placePolygon = newValue ? *newValue : GeoBoundingBox();
	emit boundingBoxChanged();
}


// country
QString TwitterPlace::COUNTRY_PN = "country";

QString TwitterPlace::getCountry() {
	return this->land;
}

void TwitterPlace::setCountry(QString newValue) {
	this->land = newValue;
	emit countryChanged();
}


// country_code
QString TwitterPlace::COUNTRY_CODE_PN = "country_code";

QString TwitterPlace::getCountryCode() {
	return this->landCode;
}

void TwitterPlace::setCountryCode(QString newValue) {
	this->landCode = newValue;
	emit countryCodeChanged();
}


// full_name
QString TwitterPlace::FULL_NAME_PN = "full_name";

QString TwitterPlace::getFullName() {
	return this->fullName;
}

void TwitterPlace::setFullName(QString newValue) {
	this->fullName = newValue;
	emit fullNameChanged();
}

// id
QString TwitterPlace::ID_PN = "id";

QString TwitterPlace::getID() {
	return this->placeID;
}

void TwitterPlace::setID(QString newValue) {
	this->placeID = newValue;
	emit idChanged();
}


// name
QString TwitterPlace::NAME_PN = "name";

QString TwitterPlace::getName() {
	return this->placeName;
}

void TwitterPlace::setName(QString newValue) {
	this->placeName = newValue;
	emit nameChanged();
}


// place_type
QString TwitterPlace::PLACE_TYPE_PN = "place_type";

QString TwitterPlace::getPlaceType() {
	return this->placeType;
}

void TwitterPlace::setPlaceType(QString newValue) {
	this->placeType = newValue;
	emit placeTypeChanged();
}


// url
QString TwitterPlace::URL_PN = "url";

QString TwitterPlace::getURL() {
	return this->metadataURL;
}

void TwitterPlace::setURL(QString newValue) {
	this->metadataURL = newValue;
	emit urlChanged();
}
