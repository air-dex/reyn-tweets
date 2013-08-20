/// @file medialist.cpp
/// @brief Implementation of Medialist
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

#include "medialist.hpp"

// Constructor
MediaList2::MediaList2() :
	JsonArray<Media2>()
{}

// Destructor
MediaList2::~MediaList2() {}

// Copy constructor
MediaList2::MediaList2(const MediaList2 & list) :
	JsonArray<Media2>()
{
	recopie(list);
}

// Affrection operator
const MediaList & MediaList2::operator=(const MediaList2 & list) {
	recopie(list);
	return *this;
}

// Serialization initialization
void MediaList2::initSystem() {
	qRegisterMetaTypeStreamOperators<MediaList2>("MediaList2");
	qMetaTypeId<MediaList2>();
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const MediaList2 & list) {
	return jsonArrayStreamingOut<Media2>(out, list);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, MediaList2 & list) {
	return jsonArrayStreamingIn<Media2>(in, list);
}
