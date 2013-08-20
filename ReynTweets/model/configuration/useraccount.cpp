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
UserAccount::UserAccount() :
	JsonObject(),
	accessToken(""),
	tokenSecret(""),
	user(),
	helloMessage("")
{
	blacklistProperties();
}

// Destructor
UserAccount::~UserAccount() {}

// Copy constructor
UserAccount::UserAccount(const UserAccount & account) :
	JsonObject(),
	accessToken(""),
	tokenSecret(""),
	user(),
	helloMessage("")
{
	recopie(account);
}

// Affectation
const UserAccount & UserAccount::operator=(const UserAccount & account) {
	recopie(account);
	return *this;
}

// Recopying a UserAccount
void UserAccount::recopie(const UserAccount & account) {
	JsonObject::recopie(account);
	accessToken = account.accessToken;
	tokenSecret = account.tokenSecret;
	user = account.user;
	helloMessage = account.helloMessage;
}

// Serialization declaration
void UserAccount::initSystem() {
	qRegisterMetaTypeStreamOperators<UserAccount>("UserAccount");
	qMetaTypeId<UserAccount>();
}

// Declaring ReynTweetsConfiguration to the QML system
void UserAccount::declareQML() {
	qmlRegisterType<UserAccount>("ReynTweetsEntities",
								 0, 2,
								 "UserAccount");
}

// Resets the mappable to a default value
void UserAccount::reset() {
	*this = UserAccount();
}


////////////////////
// JSON Streaming //
////////////////////

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const UserAccount & account) {
	return account.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, UserAccount & account) {
	return account.fillWithStream(in);
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void UserAccount::fillWithJSON(QJsonObject json) {
	this->accessToken = json.value(ACCESS_TOKEN_PN).toString("").toLatin1();
	this->tokenSecret = json.value(TOKEN_SECRET_PN).toString("").toLatin1();
	this->user.fillWithJSON(json.value(TWITTER_USER_PN).toObject());
	this->helloMessage = json.value(HELLO_MESSAGE_PN).toString("");
}

// QJsonObject representation of the object
QJsonObject UserAccount::toJSON() const {
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
void UserAccount::blacklistProperties() {
	transientProperties.append(QString(QLatin1String("current_user")));
}

// access_token
QString UserAccount::ACCESS_TOKEN_PN = "access_token";

QByteArray UserAccount::getAccessToken() {
	return accessToken;
}

void UserAccount::setAccessToken(QByteArray token) {
	accessToken = token;
}

// token_secret
QString UserAccount::TOKEN_SECRET_PN = "token_secret";

QByteArray UserAccount::getTokenSecret() {
	return tokenSecret;
}

void UserAccount::setTokenSecret(QByteArray secret) {
	tokenSecret = secret;
}

// twitter_user
QString UserAccount::TWITTER_USER_PN = "twitter_user";

QString UserAccount::CURRENT_USER_PN = "current_user";

QVariantMap UserAccount::getUserProperty() {
	return user.toVariant();
}

UserInfos * UserAccount::getUserPtr() {
	return &user;
}

UserInfos UserAccount::getUser() {
	return user;
}

UserInfos & UserAccount::getUserRef() {
	return user;
}

void UserAccount::setUser(QVariantMap newUserMap) {
	user.fillWithVariant(newUserMap);
	emit currentUserChanged();
}

void UserAccount::setUser(UserInfos u) {
	user = u;
	emit currentUserChanged();
}

void UserAccount::setUser(UserInfos * u) {
	user = u ? *u : UserInfos();
	emit currentUserChanged();
}

// hello_message
QString UserAccount::HELLO_MESSAGE_PN = "hello_message";

QString UserAccount::getHelloMessage() {
	return helloMessage;
}

void UserAccount::setHelloMessage(QString newMsg) {
	helloMessage = newMsg;
	emit helloMessageChanged();
}
