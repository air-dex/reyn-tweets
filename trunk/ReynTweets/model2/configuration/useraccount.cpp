/// @file useraccount.cpp
/// @brief Implementation of UserAccount
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

#include <QtQml>
#include "useraccount.hpp"
#include "../../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
UserAccount2::UserAccount2() :
	JsonObject(),
	accessToken(""),
	tokenSecret(""),
	user(),
	helloMessage("")
{
	blacklistProperties();
}

// Destructor
UserAccount2::~UserAccount2() {}

// Copy constructor
UserAccount2::UserAccount2(const UserAccount2 & account) :
	JsonObject(),
	accessToken(""),
	tokenSecret(""),
	user(),
	helloMessage("")
{
	recopie(account);
}

// Affectation
const UserAccount2 & UserAccount2::operator=(const UserAccount2 & account) {
	recopie(account);
	return *this;
}

// Recopying a UserAccount
void UserAccount2::recopie(const UserAccount2 & account) {
	JsonObject::recopie(account);
	accessToken = account.accessToken;
	tokenSecret = account.tokenSecret;
	user = account.user;
	helloMessage = account.helloMessage;
}

// Serialization declaration
void UserAccount2::initSystem() {
	qRegisterMetaTypeStreamOperators<UserAccount2>("UserAccount");
	qMetaTypeId<UserAccount2>();
}

// Declaring ReynTweetsConfiguration to the QML system
void UserAccount2::declareQML() {
	qmlRegisterType<UserAccount2>("ReynTweetsEntities",
								 0, 2,
								 "UserAccount");
}

// Resets the mappable to a default value
void UserAccount2::reset() {
	*this = UserAccount2();
}


////////////////////
// JSON Streaming //
////////////////////

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const UserAccount2 & account) {
	return account.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, UserAccount2 & account) {
	return account.fillWithStream(in);
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void UserAccount2::fillWithJSON(QJsonObject json) {
	this->accessToken = json.value(ACCESS_TOKEN_PN).toString("").toLatin1();
	this->tokenSecret = json.value(TOKEN_SECRET_PN).toString("").toLatin1();
	this->user.fillWithJSON(json.value(TWITTER_USER_PN).toObject());
	this->helloMessage = json.value(HELLO_MESSAGE_PN).toString("");
}

// QJsonObject representation of the object
QJsonObject UserAccount2::toJSON() const {
	QJsonObject json;

	json.insert(ACCESS_TOKEN_PN, QJsonValue(QString::fromLatin1(this->accessToken)));
	json.insert(TOKEN_SECRET_PN, QJsonValue(QString::fromLatin1(this->tokenSecret)));
	json.insert(TWITTER_USER_PN, QJsonValue(this->user.toJSON()));
	json.insert(HELLO_MESSAGE_PN, QJsonValue(this->helloMessage));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// Blacklisting the "current_user"
void UserAccount2::blacklistProperties() {
	transientProperties.append(QString(QLatin1String("current_user")));
}

// access_token
QString UserAccount2::ACCESS_TOKEN_PN = "access_token";

QByteArray UserAccount2::getAccessToken() {
	return accessToken;
}

void UserAccount2::setAccessToken(QByteArray token) {
	accessToken = token;
}

// token_secret
QString UserAccount2::TOKEN_SECRET_PN = "token_secret";

QByteArray UserAccount2::getTokenSecret() {
	return tokenSecret;
}

void UserAccount2::setTokenSecret(QByteArray secret) {
	tokenSecret = secret;
}

// twitter_user
QString UserAccount2::TWITTER_USER_PN = "twitter_user";

QString UserAccount2::CURRENT_USER_PN = "current_user";

QVariantMap UserAccount2::getUserProperty() {
	return user.toVariant();
}

UserInfos2 * UserAccount2::getUserPtr() {
	return &user;
}

UserInfos2 UserAccount2::getUser() {
	return user;
}

UserInfos2 & UserAccount2::getUserRef() {
	return user;
}

void UserAccount2::setUser(QVariantMap newUserMap) {
	user.fillWithVariant(newUserMap);
	emit currentUserChanged();
}

void UserAccount2::setUser(UserInfos2 u) {
	user = u;
	emit currentUserChanged();
}

void UserAccount2::setUser(UserInfos2 * u) {
	user = u ? *u : UserInfos2();
	emit currentUserChanged();
}

// hello_message
QString UserAccount2::HELLO_MESSAGE_PN = "hello_message";

QString UserAccount2::getHelloMessage() {
	return helloMessage;
}

void UserAccount2::setHelloMessage(QString newMsg) {
	helloMessage = newMsg;
	emit helloMessageChanged();
}
