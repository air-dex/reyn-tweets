/// @file userentities.cpp
/// @brief Implementation of UserEntities
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

#include "userentities.hpp"
#include <QtQml>
#include "../../reyntweetsutils.hpp"

/////////////
// Coplien //
/////////////

// Default constructor
UserEntities::UserEntities() :
	JsonObject(),
	userURL(),
	userDescription()
{}

// Destructor
UserEntities::~UserEntities() {}

// Copy constructor
UserEntities::UserEntities(const UserEntities & entities) :
	JsonObject(),
	userURL(),
	userDescription()
{
	this->recopie(entities);
}

// Affectation
const UserEntities & UserEntities::operator=(const UserEntities & entities)
{
	this->recopie(entities);
	return *this;
}

// Copy of a UserEntities
void UserEntities::recopie(const UserEntities & entities) {
	JsonObject::recopie(entities);
	this->userURL = entities.userURL;
	this->userDescription = entities.userDescription;
}


// Serialization declaration
void UserEntities::initSystem() {
	qRegisterMetaTypeStreamOperators<UserEntities>("UserEntities");
	qMetaTypeId<UserEntities>();
}

// Declaring to the QML system
void UserEntities::declareQML() {
	// @uri ReynTweetsComponents
	qmlRegisterType<UserEntities>(ReynTweets::QML_LIBRARY_NAME.toLatin1().constData(),
								  ReynTweets::MAJOR_VERSION, ReynTweets::MINOR_VERSION,
								  "UserEntities");
}

// Reset
void UserEntities::reset() {
	*this = UserEntities();
}

/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void UserEntities::fillWithVariant(QJsonObject json) {
	this->userURL.fillWithVariant(json.value(URL_PN).toObject());
	this->userDescription.fillWithVariant(json.value(DESCRIPTION_PN).toObject());
}

// QJsonObject representation of the object
QJsonObject UserEntities::toVariant() const {
	QJsonObject json;

	json.insert(URL_PN, QJsonValue(this->userURL.toVariant()));
	json.insert(DESCRIPTION_PN, QJsonValue(this->userDescription.toVariant()));

	return json;
}

/////////////////////////////////////
// Friends serialization operators //
/////////////////////////////////////

QDataStream & operator<<(QDataStream & out, const UserEntities & entities) {
	return entities.writeInStream(out);
}

QDataStream & operator>>(QDataStream & in, UserEntities & entities) {
	return entities.fillWithStream(in);
}


///////////////////////////
// Properties management //
///////////////////////////

// url
QString UserEntities::URL_PN = "url";

TweetEntities UserEntities::getURL() {
	return userURL;
}

TweetEntities * UserEntities::getURLPtr() {
	return &userURL;
}

void UserEntities::setURL(TweetEntities * newValue) {
	userURL = newValue ? *newValue : TweetEntities();
	emit urlChanged();
}

void UserEntities::setURL(TweetEntities newValue) {
	userURL = newValue;
	emit urlChanged();
}

// description
QString UserEntities::DESCRIPTION_PN = "description";

TweetEntities UserEntities::getDescription() {
	return userDescription;
}

TweetEntities * UserEntities::getDescriptionPtr() {
	return &userDescription;
}

void UserEntities::setDescription(TweetEntities * newValue) {
	userDescription = newValue ? *newValue : TweetEntities();
	emit descriptionChanged();
}

void UserEntities::setDescription(TweetEntities newValue) {
	userDescription = newValue;
	emit descriptionChanged();
}
