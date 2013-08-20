/// @file user.cpp
/// @brief Implementation of User
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
#include "user.hpp"
#include "../../reyntweetsutils.hpp"

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
	UserInfos(),
	lastTweet()
{
	recopie(user);
}

// Affectation operator
const User & User::operator=(const User & user) {
	recopie(user);
	return *this;
}

// Copy of a User
void User::recopie(const User & user) {
	UserInfos::recopie(user);
	lastTweet = user.lastTweet;
}

// Serialization declaration
void User::initSystem() {
	qRegisterMetaTypeStreamOperators<User>("User");
	qMetaTypeId<User>();
}

// Declaring to the QML components
void User::declareQML() {
	// @uri ReynTweetsComponents
	qmlRegisterType<User>(ReynTweets::QML_LIBRARY_NAME.toLatin1().constData(),
						  ReynTweets::MAJOR_VERSION, ReynTweets::MINOR_VERSION,
						  "User");
}

// Friends serialization operators

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const User & user) {
	return user.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, User & user) {
	return user.fillWithStream(in);
}

// Resets the mappable to a default value
void User::reset() {
	*this = User();
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void User::fillWithVariant(QJsonObject json) {
	UserInfos::fillWithVariant(json);
	this->lastTweet.fillWithVariant(json.value(STATUS_PN).toObject());
}

// Getting a QJsonObject representation of the object
QJsonObject User::toVariant() const {
	QJsonObject json = UserInfos::toVariant();

	json.insert(STATUS_PN, QJsonValue(this->lastTweet.toVariant()));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// status
QString User::STATUS_PN = "status";

Tweet User::getStatus() {
	return lastTweet;
}

Tweet * User::getStatusPtr() {
	return &lastTweet;
}

void User::setStatus(Tweet newLastTweet) {
	lastTweet = newLastTweet;
	emit statusChanged();
}

void User::setStatus(Tweet * newLastTweet) {
	lastTweet = newLastTweet ? *newLastTweet : Tweet();
	emit statusChanged();
}
