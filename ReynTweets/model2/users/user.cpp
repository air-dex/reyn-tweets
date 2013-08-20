/// @file user.cpp
/// @brief Implementation of User
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2013 Romain Ducher
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
#include "../../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
User2::User2() :
	UserInfos2(),
	lastTweet()
{}

// Destructor
User2::~User2() {}

// Copy constructor
User2::User2(const User2 & user) :
	UserInfos2()
{
	recopie(user);
}

// Affectation operator
const User2 & User2::operator=(const User2 & user) {
	recopie(user);
	return *this;
}

// Copy of a User
void User2::recopie(const User2 & user) {
	UserInfos2::recopie(user);
	lastTweet = user.lastTweet;
}

// Serialization declaration
void User2::initSystem() {
	qRegisterMetaTypeStreamOperators<User2>("User2");
	qMetaTypeId<User2>();
}

// Declaring to the QML components
void User2::declareQML() {
	qmlRegisterType<User2>("ReynTweetsEntities",
						  0, 2,
						  "User2");
}

// Friends serialization operators

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const User2 & user) {
	return user.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, User2 & user) {
	return user.fillWithStream(in);
}

// Resets the mappable to a default value
void User2::reset() {
	*this = User2();
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void User2::fillWithJSON(QJsonObject json) {
	UserInfos2::fillWithJSON(json);
	this->lastTweet.fillWithJSON(json.value(STATUS_PN).toObject());
}

// Getting a QJsonObject representation of the object
QJsonObject User2::toJSON() const {
	QJsonObject json = UserInfos2::toJSON();

	json.insert(STATUS_PN, QJsonValue(this->lastTweet.toJSON()));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// status
QString User2::STATUS_PN = "status";

QString User2::LAST_STATUS_PN = "last_status";

Tweet2 User2::getStatus() {
	return lastTweet;
}

QVariantMap User2::getStatusProperty() {
	// Return an empty QVariantMap for a default tweet to avoid stack problems
	return lastTweet.getID() == -1 ?
				QVariantMap()
			  : lastTweet.toVariant();
}

Tweet2 * User2::getStatusPtr() {
	return &lastTweet;
}

void User2::setStatus(QVariantMap statusMap) {
	lastTweet.fillWithVariant(statusMap);
	emit statusChanged();
}

void User2::setStatus(Tweet2 newLastTweet) {
	lastTweet = newLastTweet;
	emit statusChanged();
}

void User2::setStatus(Tweet2 * newLastTweet) {
	lastTweet = newLastTweet ? *newLastTweet : Tweet2();
	emit statusChanged();
}
