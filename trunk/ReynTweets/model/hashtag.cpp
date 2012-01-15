/// @file hashtag.cpp
/// @brief Implementation of Hashtag
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

#include "hashtag.hpp"
#include "../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
Hashtag::Hashtag() :
	ReynTweetsMappable(),
	indexList(),
	hashText(),
	indexes()
{
	syncProperties();
}

// Destructor
Hashtag::~Hashtag() {}

// Copy constructor
Hashtag::Hashtag(const Hashtag & hashtag) {
	recopie(hashtag);
}

// Affectation
const Hashtag & Hashtag::operator=(const Hashtag & hashtag) {
	recopie(hashtag);
	return *this;
}

// Serialization declaration
void Hashtag::initSystem() {
	qRegisterMetaTypeStreamOperators<Hashtag>("Hashtag");
	qMetaTypeId<Hashtag>();
}

// Copy of a Hashtag
void Hashtag::recopie(const Hashtag & hashtag) {
	hashText = hashtag.hashText;
	indexes = hashtag.indexes;
	syncProperties();
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const Hashtag & hashtag) {
	return jsonStreamingOut(out, hashtag);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, Hashtag & hashtag) {
	jsonStreamingIn(in, hashtag);

	// Updating indexes
	hashtag.syncMembers();

	return in;
}

///////////////////////////
// Properties management //
///////////////////////////

// Filling serializable fields with the corresponding property maps
void Hashtag::syncMembers() {
	syncIndicesMember();
}

// Updating all the properties
void Hashtag::syncProperties() {
	syncIndicesProperty();
}

// Reading method for the property indices
QVariantList Hashtag::getIndices() {
	return indexList;
}

// Writing method for the property indices
void Hashtag::setIndices(QVariantList newIndexList) {
	indexList = newIndexList;
}

// Updating the property indices
void Hashtag::syncIndicesProperty() {
	setIndices(indexes.toVariant());
}

// Updating the property indices
void Hashtag::syncIndicesMember() {
	indexes.fillWithVariant(indexList);
}


////////////////////////
// Getter and setters //
////////////////////////

// Reading hashText
QString Hashtag::getText() {
	return hashText;
}

// Writing hashText
void Hashtag::setText(QString newText) {
	hashText = newText;
}

// Reading indexes
IndexBounds Hashtag::getIndexes() {
	return indexes;
}

// Writing indexes
void Hashtag::setIndexes(IndexBounds newIndexes) {
	indexes = newIndexes;
}
