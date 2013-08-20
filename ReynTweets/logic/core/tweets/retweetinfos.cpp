/// @file retweetinfos.cpp
/// @brief Implementation of RetweetInfos
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

#include "retweetinfos.hpp"

#include <QtQml>
#include "../../reyntweetsutils.hpp"

// Default constructor
RetweetInfos::RetweetInfos() :
	JsonObject(),
	retweetID(ReynTweets::FAKE_TWEET_ID),
	retweetIDstr(ReynTweets::FAKE_TWEET_ID_STR)
{}

// Destructor
RetweetInfos::~RetweetInfos() {}

// Copy constructor
RetweetInfos::RetweetInfos(const RetweetInfos & infos) :
	JsonObject(),
	retweetID(ReynTweets::FAKE_TWEET_ID),
	retweetIDstr(ReynTweets::FAKE_TWEET_ID_STR)
{
	recopie(infos);
}

// Affectation
const RetweetInfos & RetweetInfos::operator=(const RetweetInfos & infos) {
	recopie(infos);
	return *this;
}

// Serialization declaration
void RetweetInfos::initSystem() {
	qRegisterMetaTypeStreamOperators<RetweetInfos>("RetweetInfos");
	qMetaTypeId<RetweetInfos>();
}

// Declaring to the QML components
void RetweetInfos::declareQML() {
	qmlRegisterType<RetweetInfos>("ReynTweetsEntities", 0, 2,"RetweetInfos");
}

// Resets the mappable to a default value
void RetweetInfos::reset() {
	*this = RetweetInfos();
}

// Equality between RetweetInfos.
bool RetweetInfos::operator==(const RetweetInfos & infos) {
	/*
	// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
	return this->retweetID == infos->retweetID;
	//*/

	return retweetIDstr == infos.retweetIDstr;
}

// Copy of a RetweetInfos
void RetweetInfos::recopie(const RetweetInfos & infos) {
	retweetID = infos.retweetID;
	retweetIDstr = infos.retweetIDstr;
}


/////////////////////////////////////
// Friends serialization operators //
/////////////////////////////////////

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const RetweetInfos & infos) {
	return infos.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, RetweetInfos & infos) {
	return infos.fillWithStream(in);
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void RetweetInfos::fillWithVariant(QJsonObject json) {
	this->retweetID = qlonglong(json.value(ID_PN).toDouble(ReynTweets::FAKE_TWEET_ID));	// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
	this->retweetIDstr = json.value(ID_STR_PN).toString(ReynTweets::FAKE_TWEET_ID_STR);
}

// Getting a QJsonObject representation of the object
QJsonObject RetweetInfos::toVariant() const {
	QJsonObject json;

	json.insert(ID_PN, QJsonValue(double(this->retweetID)));
	json.insert(ID_STR_PN, QJsonValue(this->retweetIDstr));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// id
QString RetweetInfos::ID_PN = "id";

// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
qlonglong RetweetInfos::getID() {
	return retweetID;
}

// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
void RetweetInfos::setID(qlonglong newValue) {
	retweetID = newValue;
	emit idChanged();
}

// id_str
QString RetweetInfos::ID_STR_PN = "id_str";

QString RetweetInfos::getIDstr() {
	return retweetIDstr;
}

void RetweetInfos::setIDstr(QString newValue) {
	retweetIDstr = newValue;
	emit idChanged();
}
