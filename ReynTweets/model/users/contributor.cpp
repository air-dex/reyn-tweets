/// @file contributor.cpp
/// @brief Implementation of Contributor
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

#include "contributor.hpp"
#include <QtQml>

// Constructor
Contributor::Contributor() :
	JsonObject(),
	userID(-1),
	userIDstr("-1"),
	screenName("")
{}

// Destructor
Contributor::~Contributor() {}

// Copy constructor
Contributor::Contributor(const Contributor & contributor) :
	JsonObject(),
	userID(-1),
	userIDstr("-1"),
	screenName("")
{
	recopie(contributor);
}

// Affectation
const Contributor & Contributor::operator=(const Contributor & contributor) {
	recopie(contributor);
	return *this;
}

// Serialization declaration
void Contributor::initSystem() {
	qRegisterMetaTypeStreamOperators<Contributor>("Contributor");
	qMetaTypeId<Contributor>();
}

// Declaring to the QML components
void Contributor::declareQML() {
	qmlRegisterType<Contributor>("ReynTweetsEntities",
								 0, 2,
								 "Contributor");
}

// Copy of a User Mention
void Contributor::recopie(const Contributor & contributor) {
	JsonObject::recopie(contributor);
	userID = contributor.userID;
	userIDstr = contributor.userIDstr;
	screenName = contributor.screenName;
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const Contributor & contributor) {
	return contributor.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, Contributor & contributor) {
	return contributor.fillWithStream(in);
}

// Resets the mappable to a default value
void Contributor::reset() {
	*this = Contributor();
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void Contributor::fillWithJSON(QJsonObject json) {
	// "id" property
	QJsonValue propval = json.value(ID_PN);

	if (!propval.isUndefined() && propval.isDouble()) {
		qlonglong id = (qlonglong) propval.toDouble();
		this->userID = id;
	}

	// "id_str" property
	propval = json.value(ID_STR_PN);

	if (!propval.isUndefined() && propval.isString()) {
		QString idStr = propval.toString();
		this->userIDstr = idStr;
	}

	// "screen_name" property
	propval = json.value(SCREEN_NAME_PN);

	if (!propval.isUndefined() && propval.isString()) {
		QString scrName = propval.toString();
		this->screenName = scrName;
	}
}

// Getting a QJsonObject representation of the object
QJsonObject Contributor::toJSON() const {
	QJsonObject json;

	if (!this->isNull()) {
		json.insert(ID_PN, QJsonValue(double(this->userID)));
		json.insert(ID_STR_PN, QJsonValue(this->userIDstr));
		json.insert(SCREEN_NAME_PN, QJsonValue(this->screenName));
	}

	return json;
}


////////////////////////
// Getter and setters //
////////////////////////

// id
QString Contributor::ID_PN = "id";

qlonglong Contributor::getID() {
	return userID;
}

void Contributor::setID(qlonglong newID) {
	userID = newID;
	userIDstr = QString::number(userID);
}

// id_str
QString Contributor::ID_STR_PN = "id_str";

QString Contributor::getIDstr() {
	return userIDstr;
}

void Contributor::setIDstr(QString newID) {
	userIDstr = newID;
	userID = userIDstr.toLongLong();
}

// screen_name
QString Contributor::SCREEN_NAME_PN = "screen_name";

QString Contributor::getScreenName() {
	return screenName;
}

void Contributor::setScreenName(QString newScreenName) {
	screenName = newScreenName;
}


//////////
// Misc //
//////////

// Equality between contributors
bool Contributor::operator==(const Contributor & contributor) const {
	return this->userID == contributor.userID;
}

// Testing if a Contributor is null
bool Contributor::isNull() const {
	const Contributor c;
	return *this == c;
}
