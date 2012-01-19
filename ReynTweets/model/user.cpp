/// @file user.cpp
/// @brief Implementation of User
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

#include "user.hpp"
#include "../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
User::User() :
	UserInfos(),
	lastTweet()
{}

// Destructor
User::~User() {}

// Copy constructor
User::User(const User & user) :
	UserInfos()
{
	recopie(user);
}

// Affectation operator
const User & User::operator=(const User & user) {
	recopie(user);
	return *this;
}

// Serialization declaration
void User::initSystem() {
	qRegisterMetaTypeStreamOperators<User>("User");
	qMetaTypeId<User>();
}

// Copy of a User
void User::recopie(const User & user) {
	UserInfos::recopie(user);
	lastTweet = user.lastTweet;
}

// Friends serialization operators

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const User & user) {
	return jsonStreamingOut(out, user);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, User & user) {
	return jsonStreamingIn(in, user);
}


///////////////////////////
// Properties management //
///////////////////////////

// Reading the "status" property
QVariantMap User::getStatusProperty() {
	return lastTweet.toVariant();
}

// Writing the status property
void User::setStatus(QVariantMap statusMap) {
	lastTweet.fillWithVariant(statusMap);
}


/////////////////////////
// Getters and setters //
/////////////////////////

// Getter on the last tweet written by the user
Tweet User::getStatus() {
	return lastTweet;
}

// Setter on the last tweet written by the user
void User::setStatus(Tweet newLastTweet) {
	lastTweet = newLastTweet;
}
