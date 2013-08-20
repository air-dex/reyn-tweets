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
	qmlRegisterType<User>("ReynTweetsEntities",
						  0, 2,
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
void User::fillWithJSON(QJsonObject json) {
	UserInfos::fillWithJSON(json);
	this->lastTweet.fillWithJSON(json.value(STATUS_PN).toObject());
}

// Getting a QJsonObject representation of the object
QJsonObject User::toJSON() const {
	QJsonObject json = UserInfos::toJSON();

	json.insert(STATUS_PN, QJsonValue(this->lastTweet.toJSON()));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// status
QString User::STATUS_PN = "status";

QString User::LAST_STATUS_PN = "last_status";

Tweet User::getStatus() {
	return lastTweet;
}

QVariantMap User::getStatusProperty() {
	// Return an empty QVariantMap for a default tweet to avoid stack problems
	return lastTweet.getIDstr() == "-1" ?
				QVariantMap()
			  : lastTweet.toVariant();
}

Tweet * User::getStatusPtr() {
	return &lastTweet;
}

void User::setStatus(QVariantMap statusMap) {
	lastTweet.fillWithVariant(statusMap);
	emit statusChanged();
}

void User::setStatus(Tweet newLastTweet) {
	lastTweet = newLastTweet;
	emit statusChanged();
}

void User::setStatus(Tweet * newLastTweet) {
	lastTweet = newLastTweet ? *newLastTweet : Tweet();
	emit statusChanged();
}
