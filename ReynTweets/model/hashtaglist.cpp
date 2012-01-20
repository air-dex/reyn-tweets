/// @file hashtaglist.cpp
/// @brief Implementation of HashtagList
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

#include "hashtaglist.hpp"

// Constructor
HashtagList::HashtagList() :
	ReynTweetsListable<Hashtag>()
{}

// Destructor
HashtagList::~HashtagList() {}

// Copy constructor
HashtagList::HashtagList(const HashtagList & list) :
	ReynTweetsListable<Hashtag>()
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

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const HashtagList & list) {
	return jsonStreamingOut<Hashtag>(out, list);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, HashtagList & list) {
	return jsonStreamingIn<Hashtag>(in, list);
}
