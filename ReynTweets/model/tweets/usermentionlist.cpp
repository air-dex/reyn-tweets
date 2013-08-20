/// @file usermentionlist.cpp
/// @brief Implementation of UserMentionList
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

#include "usermentionlist.hpp"

// Constructor
UserMentionList::UserMentionList() :
	JsonArray<UserMention>()
{}

// Destructor
UserMentionList::~UserMentionList() {}

// Copy constructor
UserMentionList::UserMentionList(const UserMentionList & list) :
	JsonArray<UserMention>()
{
	recopie(list);
}

// Affrection operator
const UserMentionList & UserMentionList::operator=(const UserMentionList & list) {
	recopie(list);
	return *this;
}

// Serialization initialization
void UserMentionList::initSystem() {
	qRegisterMetaTypeStreamOperators<UserMentionList>("UserMentionList");
	qMetaTypeId<UserMentionList>();
}

// Appending the content of a QJsonValue
void UserMentionList::appendJsonValue(QJsonValue v) {
	if (v.isObject()) {
		UserMention mention;
		mention.fillWithVariant(v.toObject());
		this->append(mention);
	}
}

// Appends an element of the list in a QJsonArray
void UserMentionList::appendJsonArrayElement(QJsonArray & array,
											 UserMention elt) const
{
	array.append(elt.toVariant());
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const UserMentionList & list) {
	return list.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, UserMentionList & list) {
	return list.fillWithStream(in);
}
