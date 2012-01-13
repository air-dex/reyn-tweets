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

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
UserAccount::UserAccount() :
	accessToken(""),
	tokenSecret(""),
	user()
{
	updateAllProperties();
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
	updateAllProperties();
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
	account.fillWithPropertiesMaps();
}


///////////////////////////
// Properties management //
///////////////////////////

// Filling serializable fields with thecorresponding  property maps
void UserAccount::fillWithPropertiesMaps() {
	UserAccount.fillWithMap(userMap);
}

// Updating all the properties
void UserAccount::updateAllProperties() {
	updateAccessTokenProperty();
	updateTokenSecretProperty();
	updateUserProperty();
}

// Updates the property p_accessToken
void UserAccount::updateAccessTokenProperty() {
	setProperty("access_token", QVariant(accessToken));
}

// Updates the property p_tokenScret
void UserAccount::updateTokenSecretProperty() {
	setProperty("token_secret", QVariant(tokenSecret));
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
void UserAccount::updateUserProperty() {
	setUserMap(user.toMap());
}


//////////////////////////////
// Configuration management //
//////////////////////////////

// Getter on accessToken
QByteArray UserAccount::getAccessToken() {
	return accessToken;
}

// Setter on accessToken
void UserAccount::setAccessToken(QByteArray token) {
	accessToken = token;
}

// Getter on tokenSecret
QByteArray UserAccount::getTokenSecret() {
	return tokenSecret;
}

// Setter on tokenSecret
void UserAccount::setTokenSecret(QByteArray secret) {
	tokenSecret = secret;
}

// Getter on user
User UserAccount::getUser() {
	return user;
}

// Setter on user
void UserAccount::setUser(User u) {
	user = u;
	updateUserProperty();
}
