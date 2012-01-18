/// @file useraccount.cpp
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

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
UserAccount::UserAccount() :
	ReynTweetsMappable(),
	accessToken(""),
	tokenSecret(""),
	user()
{
	syncProperties();
}

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
	syncProperties();
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
	jsonStreamingIn(in, account);

	// Updating the user
	account.syncMembers();

	return in;
}


///////////////////////////
// Properties management //
///////////////////////////

// Filling serializable fields with thecorresponding  property maps
void UserAccount::syncMembers() {
	syncUserMember();
}

// Updating all the properties
void UserAccount::syncProperties() {
	syncUserProperty();
}

// Reading the property twitter_user
QVariantMap UserAccount::getUserMap() {
	return userMap;
}

// Writing the property twitter_user
void UserAccount::setUserMap(QVariantMap newUserMap) {
	userMap = newUserMap;
}

// Updates the property p_user
void UserAccount::syncUserProperty() {
	setUserMap(user.toVariant());
}

// Updates the property p_user
void UserAccount::syncUserMember() {
	user.fillWithVariant(userMap);
}


//////////////////////////////
// Configuration management //
//////////////////////////////

// Getter on accessToken
QByteArray UserAccount::getAccessToken() {
	qDebug(QByteArray("UserAccount::getAccessToken contenu : ").append(accessToken).data());
	qDebug(QByteArray("UserAccount::getAccessToken return : ").append(QByteArray::fromBase64(accessToken)).data());
	return QByteArray::fromBase64(accessToken);
}

// Setter on accessToken
void UserAccount::setAccessToken(QByteArray token) {
	accessToken = token.toBase64();
}

// Getter on tokenSecret
QByteArray UserAccount::getTokenSecret() {
	qDebug(QByteArray("UserAccount::getTokenSecret contenu : ").append(tokenSecret).data());
	qDebug(QByteArray("UserAccount::getTokenSecret return : ").append(QByteArray::fromBase64(tokenSecret)).data());
	return QByteArray::fromBase64(tokenSecret);
}

// Setter on tokenSecret
void UserAccount::setTokenSecret(QByteArray secret) {
	tokenSecret = secret.toBase64();
}

// Getter on user
User UserAccount::getUser() {
	return user;
}

// Setter on user
void UserAccount::setUser(User u) {
	user = u;
	syncUserProperty();
}
