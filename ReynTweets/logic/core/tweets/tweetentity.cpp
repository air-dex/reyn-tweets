/// @file tweetentity.cpp
/// @brief Implementation of TweetEntity
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

#include "tweetentity.hpp"

// Constructor
TweetEntity::TweetEntity() :
	JsonObject(),
	indexesHandler(),
	indexes(indexesHandler.getHandledListRef())
{}

// Destructor
TweetEntity::~TweetEntity() {}

// Copy constructor
TweetEntity::TweetEntity(const TweetEntity & entity) :
	JsonObject(),
	indexesHandler(),
	indexes(indexesHandler.getHandledListRef())
{
	this->recopie(entity);
}

// Affectation
const TweetEntity & TweetEntity::operator=(const TweetEntity & entity) {
	this->recopie(entity);
	return *this;
}

// Copy of a Hashtag
void TweetEntity::recopie(const TweetEntity & entity) {
	JsonObject::recopie(entity);
	indexes = entity.indexes;
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void TweetEntity::fillWithVariant(QJsonObject json) {
	this->indexes.fillWithVariant(json.value(INDICES_PN).toArray());
}

// Getting a QJsonObject representation of the JsonObject
QJsonObject TweetEntity::toVariant() const {
	QJsonObject json;

	json.insert(INDICES_PN, QJsonValue(this->indexes.toVariant()));

	return json;
}


////////////////////////
// Getter and setters //
////////////////////////

// indices
QString TweetEntity::INDICES_PN = "indices";

IndexBounds TweetEntity::getIndices() {
	return indexes;
}

IndexBoundsHandler * TweetEntity::getIndicesHandler() {
	return &indexesHandler;
}

void TweetEntity::setIndices(IndexBounds newIndexes) {
	indexes = newIndexes;
	emit indicesChanged();
}
