/// @file urlentity.cpp
/// @brief Implementation of URLEntity
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

#include "urlentity.hpp"
#include "../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
URLEntity::URLEntity() :
	ReynTweetsMappable(),
	extractedURL(""),
	displayedURL(""),
	expandedURL(""),
	indexes()
{}

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
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const URLEntity & entity) {
	return jsonStreamingOut(out, entity);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, URLEntity & entity) {
	return jsonStreamingIn(in, entity);
}

///////////////////////////
// Properties management //
///////////////////////////

// Reading method for the property indices
QVariantList URLEntity::getIndicesProperty() {
	return indexes.toVariant();
}

// Writing method for the property indices
void URLEntity::setIndices(QVariantList newIndexList) {
	indexes.fillWithVariant(newIndexList);
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
IndexBounds URLEntity::getIndices() {
	return indexes;
}

// Writing indexes
void URLEntity::setIndices(IndexBounds newIndexes) {
	indexes = newIndexes;
}
