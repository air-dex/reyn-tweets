/// @file hashtaglist.cpp
/// @brief Implementation of HashtagList
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

#include "hashtaglist.hpp"

// Constructor
HashtagList::HashtagList() :
	JsonArray<Hashtag>()
{}

// Destructor
HashtagList::~HashtagList() {}

// Copy constructor
HashtagList::HashtagList(const HashtagList & list) :
	JsonArray<Hashtag>()
{
	recopie(list);
}

// Affrection operator
const HashtagList & HashtagList::operator=(const HashtagList & list) {
	recopie(list);
	return *this;
}

// Serialization initialization
void HashtagList::initSystem() {
	qRegisterMetaTypeStreamOperators<HashtagList>("HashtagList");
	qMetaTypeId<HashtagList>();
}

// Appending the content of a QJsonValue
void HashtagList::appendJsonValue(QJsonValue v) {
	if (v.isObject()) {
		Hashtag hashtag;
		hashtag.fillWithVariant(v.toObject());
		this->append(hashtag);
	}
}

// Appends an element of the list in a QJsonArray
void HashtagList::appendJsonArrayElement(QJsonArray & array, Hashtag elt) const {
	array.append(elt.toVariant());
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const HashtagList & list) {
	return list.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, HashtagList & list) {
	return list.fillWithStream(in);
}
