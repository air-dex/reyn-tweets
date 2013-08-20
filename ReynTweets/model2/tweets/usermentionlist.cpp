/// @file usermentionlist.cpp
/// @brief Implementation of UserMentionList
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

#include "usermentionlist.hpp"

// Constructor
UserMentionList2::UserMentionList2() :
	JsonArray<UserMention2>()
{}

// Destructor
UserMentionList2::~UserMentionList2() {}

// Copy constructor
UserMentionList2::UserMentionList2(const UserMentionList2 & list) :
	JsonArray<UserMention2>()
{
	recopie(list);
}

// Affrection operator
const UserMentionList & UserMentionList2::operator=(const UserMentionList2 & list) {
	recopie(list);
	return *this;
}

// Serialization initialization
void UserMentionList2::initSystem() {
	qRegisterMetaTypeStreamOperators<UserMentionList2>("UserMentionList2");
	qMetaTypeId<UserMentionList2>();
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const UserMentionList2 & list) {
	return jsonArrayStreamingOut<UserMention2>(out, list);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, UserMentionList2 & list) {
	return jsonArrayStreamingIn<UserMention2>(in, list);
}
