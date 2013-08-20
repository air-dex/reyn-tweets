/// @file tweetentity.cpp
/// @brief Implementation of TweetEntity
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

#include "tweetentity.hpp"

// Constructor
TweetEntity2::TweetEntity2() :
	JsonObject(),
	indexes()
{}

// Destructor
TweetEntity2::~TweetEntity2() {}

// Copy constructor
TweetEntity2::TweetEntity2(const TweetEntity2 & entity) :
	JsonObject()
{
	this->recopie(entity);
}

// Affectation
const TweetEntity2 & TweetEntity2::operator=(const TweetEntity2 & entity) {
	this->recopie(entity);
	return *this;
}

// Copy of a Hashtag
void TweetEntity2::recopie(const TweetEntity2 & entity) {
	JsonObject::recopie(entity);
	indexes = entity.indexes;
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void TweetEntity2::fillWithJSON(QJsonObject json) {
	// "indices" property
	QJsonValue propval = json.value(INDICES_PN);

	if (!propval.isUndefined() && propval.isArray()) {
		QJsonArray bounds = propval.toArray();
		this->indexes.fillWithJSON(bounds);
	}
}

// Getting a QJsonObject representation of the JsonObject
QJsonObject TweetEntity2::toJSON() const {
	QJsonObject json;

	json.insert(INDICES_PN, QJsonValue(this->indexes.toJSON()));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// Reading method for the property indices
QVariantList TweetEntity2::getIndicesProperty() {
	return indexes.toVariant();
}

// Writing method for the property indices
void TweetEntity2::setIndices(QVariantList newIndexList) {
	indexes.fillWithVariant(newIndexList);
}


////////////////////////
// Getter and setters //
////////////////////////

// indices
QString TweetEntity2::INDICES_PN = "indices";

IndexBounds2 TweetEntity2::getIndices() {
	return indexes;
}

void TweetEntity2::setIndices(IndexBounds2 newIndexes) {
	indexes = newIndexes;
}
