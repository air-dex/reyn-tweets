/// @file hashtag.cpp
/// @brief Implementation of Hashtag
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

#include "hashtag.hpp"
#include "../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
Hashtag::Hashtag() :
	ReynTweetsMappable(),
	hashText(),
	indexes()
{}

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
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const Hashtag & hashtag) {
	return jsonStreamingOut(out, hashtag);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, Hashtag & hashtag) {
	return jsonStreamingIn(in, hashtag);
}


///////////////////////////
// Properties management //
///////////////////////////

// Reading method for the property indices
QVariantList Hashtag::getIndicesProperty() {
	return indexes.toVariant();
}

// Writing method for the property indices
void Hashtag::setIndices(QVariantList newIndexList) {
	indexes.fillWithVariant(newIndexList);
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
IndexBounds Hashtag::getIndices() {
	return indexes;
}

// Writing indexes
void Hashtag::setIndices(IndexBounds newIndexes) {
	indexes = newIndexes;
}
