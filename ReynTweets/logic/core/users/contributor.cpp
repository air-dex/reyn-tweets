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
#include "../../reyntweetsutils.hpp"

// Constructor
Contributor::Contributor() :
	JsonObject(),
	userID(ReynTweets::FAKE_USER_ID),
	userIDstr(ReynTweets::FAKE_USER_ID_STR),
	screenName("")
{}

// Destructor
Contributor::~Contributor() {}

// Copy constructor
Contributor::Contributor(const Contributor & contributor) :
	JsonObject(),
	userID(ReynTweets::FAKE_USER_ID),
	userIDstr(ReynTweets::FAKE_USER_ID_STR),
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
void Contributor::fillWithVariant(QJsonObject json) {
	this->userID = qlonglong(json.value(ID_PN).toDouble(ReynTweets::FAKE_USER_ID));	// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
	this->userIDstr = json.value(ID_STR_PN).toString(ReynTweets::FAKE_USER_ID_STR);
	this->screenName = json.value(SCREEN_NAME_PN).toString("");
}

// Getting a QJsonObject representation of the object
QJsonObject Contributor::toVariant() const {
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

// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
qlonglong Contributor::getID() {
	return userID;
}

// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
void Contributor::setID(qlonglong newID) {
	userID = newID;
	emit idChanged();
}

// id_str
QString Contributor::ID_STR_PN = "id_str";

QString Contributor::getIDstr() {
	return userIDstr;
}

void Contributor::setIDstr(QString newID) {
	userIDstr = newID;
	emit idChanged();
}

// screen_name
QString Contributor::SCREEN_NAME_PN = "screen_name";

QString Contributor::getScreenName() {
	return screenName;
}

void Contributor::setScreenName(QString newScreenName) {
	screenName = newScreenName;
	emit screenNameChanged();
}


//////////
// Misc //
//////////

// Equality between contributors
bool Contributor::operator==(const Contributor & contributor) const {
	/*
	// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
	return this->userID == contributor->userID;
	//*/

	return this->userIDstr == contributor.userIDstr;
}

// Testing if a Contributor is null
bool Contributor::isNull() const {
	const Contributor c;
	return *this == c;
}
