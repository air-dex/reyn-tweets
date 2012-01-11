/// @file tweet.cpp
/// @brief Implementation of Tweet
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

#include "urlentity.hpp"
#include "../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
URLEntity::URLEntity() :
	ReynTweetsSerializable(),
	extractedURL(""),
	displayedURL(""),
	expandedURL(""),
	indexes()
{
	updateAllProperties();
}

// Destructor
URLEntity::~URLEntity() {}

// Copy constructor
URLEntity::URLEntity(const URLEntity & entity) {
	recopie(entity);
}

// Affectation
const URLEntity & URLEntity::operator=(const URLEntity & entity) {
	recopie(entity);
	return *this;
}

// Serialization declaration
void URLEntity::initSystem() {
	qRegisterMetaTypeStreamOperators<URLEntity>("URLEntity");
	qMetaTypeId<URLEntity>();
}

// Copy of a URLEntity
void URLEntity::recopie(const URLEntity & entity) {
	extractedURL = entity.extractedURL;
	displayedURL = entity.displayedURL;
	expandedURL = entity.expandedURL;
	indexes = entity.indexes;
	updateAllProperties();
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const URLEntity & entity) {
	return jsonStreamingOut(out, entity);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, URLEntity & entity) {
	jsonStreamingIn(in, entity);

	// Updating indexes
	sizes.fillWithPropertiesMaps();

	return in;
}

///////////////////////////
// Properties management //
///////////////////////////

// Filling serializable fields with thecorresponding  property maps
void URLEntity::fillWithPropertiesMaps() {
	indexes.fillWithVariantList(indexList);
}

// Updating all the properties
void URLEntity::updateAllProperties() {
	updateURL();
	updateDisplayedURL();
	updateExpandedURL();
	updateIndices();
}

// Updating the property url
void URLEntity::updateURL() {
	setProperty("url", QVariant(extractedURL));
}

// Updating the property displayed_url
void URLEntity::updateDisplayedURL() {
	setProperty("displayed_url", QVariant(displayedURL));
}

// Updating the property expanded_url
void URLEntity::updateExpandedURL() {
	setProperty("expanded_url", QVariant(expandedURL));
}

// Reading method for the property indices
QVariantList URLEntity::getIndices() {
	return indexList;
}

// Writing method for the property indices
void URLEntity::setIndices(QVariantList newIndexList) {
	indexList = newIndexList;
}

// Updating the property indices
void URLEntity::updateIndices() {
	setProperty("indices", QVariant(indexes.toVariantList()));
}


////////////////////////
// Getter and setters //
////////////////////////

// Reading extractedURL
QString URLEntity::getURL() {
	return extractedURL;
}

// Writing extractedURL
void URLEntity::setURL(QString newURL) {
	extractedURL = newURL;
}

// Reading method for displayedURL
QString URLEntity::getDisplayedURL() {
	return displayedURL;
}

// Writing displayedURL
void URLEntity::setDisplayedURL(QString newURL) {
	displayedURL = newURL;
}

// Reading method for expandedURL
QString URLEntity::getExpandedURL() {
	return expandedURL;
}

// Writing method for expandedURL
void URLEntity::setExpandedURL(QString newURL) {
	expandedURL = newURL;
}

// Reading indexes
IndexBounds URLEntity::getIndexes() {
	return indexes;
}

// Writing indexes
void URLEntity::setIndexes(IndexBounds newIndexes) {
	indexes = newIndexes;
	updateIndices();
}
