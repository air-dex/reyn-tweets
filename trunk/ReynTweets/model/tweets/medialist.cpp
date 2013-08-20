/// @file medialist.cpp
/// @brief Implementation of Medialist
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

#include "medialist.hpp"

// Constructor
MediaList::MediaList() :
	JsonArray<Media>()
{}

// Destructor
MediaList::~MediaList() {}

// Copy constructor
MediaList::MediaList(const MediaList & list) :
	JsonArray<Media>()
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

// Appending the content of a QJsonValue
void MediaList::appendJsonValue(QJsonValue v) {
	if (v.isObject()) {
		Media media;
		media.fillWithVariant(v.toObject());
		this->append(media);
	}
}

// Appends an element of the list in a QJsonArray
void MediaList::appendJsonArrayElement(QJsonArray & array, Media elt) const {
	array.append(elt.toVariant());
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const MediaList & list) {
	return list.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, MediaList & list) {
	return list.fillWithStream(in);
}
