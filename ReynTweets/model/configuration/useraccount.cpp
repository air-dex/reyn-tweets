/// @file useraccount.hpp
/// @brief Implementation of UserAccount
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

#include "useraccount.hpp"
#include "../../tools/utils.hpp"

// Default constructor
UserAccount::UserAccount() :
	accessToken(""),
	tokenSecret(""),
	user("")
{}

// Destructor
UserAccount::~UserAccount() {}

// Copy constructor
UserAccount::UserAccount(const UserAccount & account) {
	recopie(account);
}

// Affectation
const UserAccount & UserAccount::operator=(const UserAccount & account) {
	recopie(account);
	return *this;
}

// Recopying a UserAccount
void UserAccount::recopie(const UserAccount & account) {
	accessToken = account.accessToken;
	tokenSecret = account.tokenSecret;
	user = account.user;
}

// Serialization declaration
void UserAccount::initSystem() {
	qRegisterMetaTypeStreamOperators<UserAccount>("UserAccount");
	qMetaTypeId<UserAccount>();
}


////////////////////
// JSON Streaming //
////////////////////

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const UserAccount & account) {
	return jsonStreamingOut(out, account);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, UserAccount & account) {
	return jsonStreamingIn(in, account);
}
