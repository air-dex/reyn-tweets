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
#include <QTextStream>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
UserMention::UserMention() :
	TweetEntity(),
	userID(-1),
	userIDstr("-1"),
	screenName(""),
	userName("")
{}

// Destructor
UserMention::~UserMention() {}

// Copy constructor
UserMention::UserMention(const UserMention & mention) :
	TweetEntity(),
	userID(-1),
	userIDstr("-1"),
	screenName(""),
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


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void UserMention::fillWithJSON(QJsonObject json) {
	// Base class
	TweetEntity::fillWithJSON(json);

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

	// "name" property
	propval = json.value(NAME_PN);

	if (!propval.isUndefined() && propval.isString()) {
		QString uName = propval.toString();
		this->userName = uName;
	}
}

// Getting a QJsonObject representation of the object
QJsonObject UserMention::toJSON() const {
	QJsonObject json = TweetEntity::toJSON();

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

qlonglong UserMention::getID() {
	return userID;
}

void UserMention::setID(qlonglong newID) {
	userID = newID;
	userIDstr = QString::number(userID);
}

// id_str
QString UserMention::ID_STR_PN = "id_str";

QString UserMention::getIDstr() {
	return userIDstr;
}

void UserMention::setIDstr(QString newID) {
	userIDstr = newID;
	userID = userIDstr.toLongLong();
}

// screen_name
QString UserMention::SCREEN_NAME_PN = "screen_name";

QString UserMention::getScreenName() {
	return screenName;
}

void UserMention::setScreenName(QString newScreenName) {
	screenName = newScreenName;
}

// name
QString UserMention::NAME_PN = "name";

QString UserMention::getName() {
	return userName;
}

void UserMention::setName(QString newName) {
	userName = newName;
}


//////////
// Misc //
//////////

// @screenName
QString UserMention::getMention() {
	QString s = "";
	QTextStream t(&s);
	t << '@' << screenName;
	return t.readAll();
}

// Building the rich text for the entity
QString UserMention::getDisplayedText(QColor linkColor) {
	QString mention = getMention();
	QWebPage page;
	QWebFrame * frame = page.mainFrame();

	if (frame) {
		frame->setHtml("<a></a>");
		QWebElement link = frame->documentElement().findFirst("a");

		link.setPlainText(mention);
		link.setAttribute("href", mention);
		link.setStyleProperty("color", linkColor.name());
		link.setStyleProperty("text-align", "right");
		link.setStyleProperty("text-decoration", "none");

		return link.toOuterXml();
	} else {
		// Back to basics : writing a string.
		QString mention = getMention();
		QString s = "";
		QTextStream t(&s);

		t << "<a href=\"" << mention
		  << "style=\"text-decoration: none ; color:\""
		  << linkColor.name() << "\">" << mention << "</a>";

		return t.readAll();
	}
}
