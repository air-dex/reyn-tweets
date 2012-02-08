/// @file medialist.cpp
/// @brief Implementation of Medialist
///
/// Revisions older than r243 was in /trunk/ReynTwets/model
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

#include "medialist.hpp"

// Constructor
MediaList::MediaList() :
	ReynTweetsListable<Media>()
{}

// Destructor
MediaList::~MediaList() {}

// Copy constructor
MediaList::MediaList(const MediaList & list) :
	ReynTweetsListable<Media>()
{
	recopie(list);
}

// Affrection operator
const MediaList & MediaList::operator=(const MediaList & list) {
	recopie(list);
	return *this;
}

// Serialization initialization
void MediaList::initSystem() {
	qRegisterMetaTypeStreamOperators<MediaList>("MediaList");
	qMetaTypeId<MediaList>();
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const MediaList & list) {
	return jsonStreamingOut<Media>(out, list);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, MediaList & list) {
	return jsonStreamingIn<Media>(in, list);
}
