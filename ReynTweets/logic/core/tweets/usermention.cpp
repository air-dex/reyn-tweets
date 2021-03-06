/// @file usermention.cpp
/// @brief Implementation of UserMention
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

#include "usermention.hpp"
#include <QtQml>
#include <QWebElement>
#include "../../../connection/common/utils/parsers/htmlparser.hpp"
#include "../../reyntweetsutils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
UserMention::UserMention() :
	TweetEntity(),
	userID(ReynTweets::FAKE_USER_ID),
	userIDstr(ReynTweets::FAKE_USER_ID_STR),
	screenName(ReynTweets::FAKE_SCREEN_NAME),
	userName("")
{}

// Destructor
UserMention::~UserMention() {}

// Copy constructor
UserMention::UserMention(const UserMention & mention) :
	TweetEntity(),
	userID(ReynTweets::FAKE_USER_ID),
	userIDstr(ReynTweets::FAKE_USER_ID_STR),
	screenName(ReynTweets::FAKE_SCREEN_NAME),
	userName("")
{
	recopie(mention);
}

// Affectation
const UserMention & UserMention::operator=(const UserMention & mention) {
	recopie(mention);
	return *this;
}

// Serialization declaration
void UserMention::initSystem() {
	qRegisterMetaTypeStreamOperators<UserMention>("UserMention");
	qMetaTypeId<UserMention>();
}

// Declaring to the QML components
void UserMention::declareQML() {
	// @uri ReynTweetsComponents
	qmlRegisterType<UserMention>(ReynTweets::QML_LIBRARY_NAME.toLatin1().constData(),
								 ReynTweets::MAJOR_VERSION, ReynTweets::MINOR_VERSION,
								 "UserMention");
}

// Copy of a User Mention
void UserMention::recopie(const UserMention & mention) {
	TweetEntity::recopie(mention);
	userID = mention.userID;
	userIDstr = mention.userIDstr;
	screenName = mention.screenName;
	userName = mention.userName;
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const UserMention & mention) {
	return mention.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, UserMention & mention) {
	return mention.fillWithStream(in);
}

// Resets the mappable to a default value
void UserMention::reset() {
	*this = UserMention();
}

// Equality between mentions.
bool UserMention::operator==(const UserMention mention) const {
	/*
	// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
	return this->mediaID == mention->mediaID;
	//*/

	return this->userIDstr == mention.userIDstr;
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void UserMention::fillWithVariant(QJsonObject json) {
	TweetEntity::fillWithVariant(json);		// Base class
	this->userID = qlonglong(json.value(ID_PN).toDouble(ReynTweets::FAKE_USER_ID));	// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
	this->userIDstr = json.value(ID_STR_PN).toString(ReynTweets::FAKE_USER_ID_STR);
	this->screenName = json.value(SCREEN_NAME_PN).toString("");
	this->userName = json.value(NAME_PN).toString("");
}

// Getting a QJsonObject representation of the object
QJsonObject UserMention::toVariant() const {
	QJsonObject json = TweetEntity::toVariant();

	json.insert(ID_PN, QJsonValue(double(this->userID)));
	json.insert(ID_STR_PN, QJsonValue(this->userIDstr));
	json.insert(SCREEN_NAME_PN, QJsonValue(this->screenName));
	json.insert(NAME_PN, QJsonValue(this->userName));

	return json;
}


////////////////////////
// Getter and setters //
////////////////////////

// id
QString UserMention::ID_PN = "id";

// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
qlonglong UserMention::getID() {
	return userID;
}

// BUGGY : https://bugreports.qt-project.org/browse/QTBUG-28560
void UserMention::setID(qlonglong newID) {
	userID = newID;
	emit idChanged();
}

// id_str
QString UserMention::ID_STR_PN = "id_str";

QString UserMention::getIDstr() {
	return userIDstr;
}

void UserMention::setIDstr(QString newID) {
	userIDstr = newID;
	emit idChanged();
}

// screen_name
QString UserMention::SCREEN_NAME_PN = "screen_name";

QString UserMention::getScreenName() {
	return screenName;
}

void UserMention::setScreenName(QString newScreenName) {
	screenName = newScreenName;
	emit screenNameChanged();
}

// name
QString UserMention::NAME_PN = "name";

QString UserMention::getName() {
	return userName;
}

void UserMention::setName(QString newName) {
	userName = newName;
	emit nameChanged();
}


//////////
// Misc //
//////////

// @screenName
QString UserMention::getMention() {
	QString s = "";
	s.append('@').append(screenName);
	return s;
}

// Building the rich text for the entity
QString UserMention::getDisplayedText(QColor linkColor) {
	QString mention = getMention();

	// Building the HTML link
	QString htmlMention = "";
	htmlMention.append("<a>").append(mention).append("</a>");

	HTMLParser parser;
	bool parseOK = false;
	QWebElement link = parser.parse(htmlMention.toUtf8(), &parseOK);

	if (parseOK) {
		link = link.findFirst("a");
		link.setAttribute("href", mention);
		link.setStyleProperty("color", linkColor.name());
		link.setStyleProperty("text-align", "right");
		link.setStyleProperty("text-decoration", "none");

		return link.toOuterXml();
	} else {
		// Back to basics : writing a string.
		QString s = "";

		s.append("<a href=\"").append(mention)
			.append("style=\"text-decoration: none ; color:\"")
			.append(linkColor.name()).append("\">")
			.append(mention).append("</a>");

		return s;
	}
}
