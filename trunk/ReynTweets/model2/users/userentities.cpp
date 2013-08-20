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
	qmlRegisterType<UserEntities>("ReynTweetsEntities",
								  0, 2,
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
void UserEntities::fillWithJSON(QJsonObject json) {
	// url
	QJsonValue propval = json.value(URL_PN);

	if(!propval.isUndefined() && propval.isObject()) {
		QJsonObject entities = propval.toObject();
		this->userURL.fillWithJSON(entities);
	}

	// description
	propval = json.value(DESCRIPTION_PN);

	if(!propval.isUndefined() && propval.isObject()) {
		QJsonObject entities = propval.toObject();
		this->userDescription.fillWithJSON(entities);
	}
}

// QJsonObject representation of the object
QJsonObject UserEntities::toJSON() const {
	QJsonObject json;

	json.insert(URL_PN, QJsonValue(this->userURL.toJSON()));
	json.insert(DESCRIPTION_PN, QJsonValue(this->userDescription.toJSON()));

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

QString UserEntities::URL_ENT_PN = "url_ent";

TweetEntities2 UserEntities::getURL() {
	return userURL;
}

QVariantMap UserEntities::getURLProperty() {
	return userURL.toVariant();
}

TweetEntities2 * UserEntities::getURLptr() {
	return &userURL;
}

void UserEntities::setURL(QVariantMap newValue) {
	userURL.fillWithVariant(newValue);
	emit urlChanged();
}

void UserEntities::setURL(TweetEntities2 * newValue) {
	userURL = newValue ? *newValue : TweetEntities2();
	emit urlChanged();
}

void UserEntities::setURL(TweetEntities2 newValue) {
	userURL = newValue;
	emit urlChanged();
}

// description
QString UserEntities::DESCRIPTION_PN = "description";

QString UserEntities::DESCRIPTION_ENT_PN = "description_ent";

TweetEntities2 UserEntities::getDescription() {
	return userDescription;
}

QVariantMap UserEntities::getDescriptionProperty() {
	return userDescription.toVariant();
}

TweetEntities2 * UserEntities::getDescriptionptr() {
	return &userDescription;
}

void UserEntities::setDescription(QVariantMap newValue) {
	userDescription.fillWithVariant(newValue);
	emit descriptionChanged();
}

void UserEntities::setDescription(TweetEntities2 * newValue) {
	userDescription = newValue ? *newValue : TweetEntities2();
	emit descriptionChanged();
}

void UserEntities::setDescription(TweetEntities2 newValue) {
	userDescription = newValue;
	emit descriptionChanged();
}
