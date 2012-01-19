/// @file usermention.cpp
/// @brief Implementation of UserMention
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

#include "usermention.hpp"
#include "../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
UserMention::UserMention() :
	ReynTweetsMappable(),
	userID(-1),
	userIDstr("-1"),
	screenName(""),
	userName(""),
	indexes()
{}

// Destructor
UserMention::~UserMention() {}

// Copy constructor
UserMention::UserMention(const UserMention & mention) {
	recopie(mention);
}

// Affectation
const UserMention & UserMention::operator=(const UserMention & mention) {
	recopie(mention);
	return *this;
}

// Serialization declaration
void UserMention::initSystem() {
	qRegisterMetaTypeStreamOperators<UserMention>("UserMention");
	qMetaTypeId<UserMention>();
}

// Copy of a User Mention
void UserMention::recopie(const UserMention & mention) {
	userID = mention.userID;
	userIDstr = mention.userIDstr;
	screenName = mention.screenName;
	userName = mention.userName;
	indexes = mention.indexes;
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const UserMention & mention) {
	return jsonStreamingOut(out, mention);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, UserMention & mention) {
	return jsonStreamingIn(in, mention);
}


///////////////////////////
// Properties management //
///////////////////////////

// Reading method for the property indices
QVariantList UserMention::getIndicesProperty() {
	return indexes.toVariant();
}

// Writing method for the property indices
void UserMention::setIndices(QVariantList newIndexList) {
	indexes.fillWithVariant(newIndexList);
}


////////////////////////
// Getter and setters //
////////////////////////

// Reading userID
long UserMention::getID() {
	return userID;
}

// Writing userID
void UserMention::setID(long newID) {
	userID = newID;
}

// Reading userIDstr
QString UserMention::getIDstr() {
	return userIDstr;
}

// Writing userIDstr
void UserMention::setIDstr(QString newID) {
	userIDstr = newID;
}

// Reading method for screenName
QString UserMention::getScreenName() {
	return screenName;
}

// Writing displayedURL
void UserMention::setScreenName(QString newScreenName) {
	screenName = newScreenName;
}

// Reading method for userName
QString UserMention::getName() {
	return userName;
}

// Writing method for userName
void UserMention::setName(QString newName) {
	userName = newName;
}

// Reading indexes
IndexBounds UserMention::getIndices() {
	return indexes;
}

// Writing indexes
void UserMention::setIndices(IndexBounds newIndexes) {
	indexes = newIndexes;
}
