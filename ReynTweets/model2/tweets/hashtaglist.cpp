/// @file hashtaglist.cpp
/// @brief Implementation of HashtagList
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

#include "hashtaglist.hpp"

// Constructor
HashtagList2::HashtagList2() :
	JsonArray<Hashtag2>()
{}

// Destructor
HashtagList2::~HashtagList2() {}

// Copy constructor
HashtagList2::HashtagList2(const HashtagList2 & list) :
	JsonArray<Hashtag2>()
{
	recopie(list);
}

// Affrection operator
const HashtagList2 & HashtagList2::operator=(const HashtagList2 & list) {
	recopie(list);
	return *this;
}

// Serialization initialization
void HashtagList2::initSystem() {
	qRegisterMetaTypeStreamOperators<HashtagList2>("HashtagList2");
	qMetaTypeId<HashtagList2>();
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const HashtagList2 & list) {
	return list.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, HashtagList2 & list) {
	return list.fillWithStream(in);
}
