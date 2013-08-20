/// @file urlentitylist.cpp
/// @brief Implementation of URLEntityList
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

#include "urlentitylist.hpp"

// Constructor
URLEntityList::URLEntityList() :
	JsonArray<URLEntity>()
{}

// Destructor
URLEntityList::~URLEntityList() {}

// Copy constructor
URLEntityList::URLEntityList(const URLEntityList & list) :
	JsonArray<URLEntity>()
{
	recopie(list);
}

// Affrection operator
const URLEntityList & URLEntityList::operator=(const URLEntityList & list) {
	recopie(list);
	return *this;
}

// Serialization initialization
void URLEntityList::initSystem() {
	qRegisterMetaTypeStreamOperators<URLEntityList>("URLEntityList");
	qMetaTypeId<URLEntityList>();
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const URLEntityList & list) {
	return list.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, URLEntityList & list) {
	return list.fillWithStream(in);
}
