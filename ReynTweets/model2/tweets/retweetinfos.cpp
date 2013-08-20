/// @file retweetinfos.cpp
/// @brief Implementation of RetweetInfos
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

#include "retweetinfos.hpp"

// Default constructor
RetweetInfos2::RetweetInfos2() :
	JsonObject(),
	retweetID(-1),
	retweetIDstr("-1")
{}

// Destructor
RetweetInfos2::~RetweetInfos2() {}

// Copy constructor
RetweetInfos2::RetweetInfos2(const RetweetInfos2 & infos) :
	JsonObject(),
	retweetID(-1),
	retweetIDstr("-1")
{
	recopie(infos);
}

// Affectation
const RetweetInfos2 & RetweetInfos2::operator=(const RetweetInfos2 & infos) {
	recopie(infos);
	return *this;
}

// Serialization declaration
void RetweetInfos2::initSystem() {
	qRegisterMetaTypeStreamOperators<RetweetInfos2>("RetweetInfos2");
	qMetaTypeId<RetweetInfos2>();
}

// Resets the mappable to a default value
void RetweetInfos2::reset() {
	*this = RetweetInfos();
}

// Equality between RetweetInfos.
bool RetweetInfos2::operator==(const RetweetInfos2 & infos) {
	return retweetID == infos.retweetID;
}

// Copy of a RetweetInfos
void RetweetInfos2::recopie(const RetweetInfos2 & infos) {
	retweetID = infos.retweetID;
	retweetIDstr = infos.retweetIDstr;
}

// Friends serialization operators

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const RetweetInfos & infos) {
	return jsonStreamingOut(out, infos);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, RetweetInfos & infos) {
	return jsonStreamingIn(in, infos);
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void RetweetInfos2::fillWithJSON(QJsonObject json) {
	// "id" property
	QJsonValue propval = json.value(ID_PN);

	if (!propval.isUndefined() && propval.isDouble()) {
		qlonglong id = qlonglong(propval.toDouble());
		this->retweetID = id;
	}

	// "id_str" property
	propval = json.value(ID_STR_PN);

	if (!propval.isUndefined() && propval.isString()) {
		QString idStr = propval.toString();
		this->retweetIDstr = idStr;
	}
}

// Getting a QJsonObject representation of the object
QJsonObject RetweetInfos2::toJSON() {
	QJsonObject json;

	json.insert(ID_PN, QJsonValue(this->retweetID));
	json.insert(ID_STR_PN, QJsonValue(this->retweetIDstr));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// id
QString RetweetInfos2::ID_PN = "id";

qlonglong RetweetInfos2::getID() {
	return retweetID;
}

void RetweetInfos2::setID(qlonglong newValue) {
	retweetID = newValue;
	retweetIDstr = QString::number(newValue);
	emit idChanged();
}

// id_str
QString RetweetInfos2::ID_STR_PN = "id_str";

QString RetweetInfos2::getIDstr() {
	return retweetIDstr;
}

void RetweetInfos2::setIDstr(QString newValue) {
	retweetIDstr = newValue;
	retweetID = newValue.toLongLong();
	emit idChanged();
}
