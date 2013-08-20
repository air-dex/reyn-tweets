/// @file usermention.cpp
/// @brief Implementation of UserMention
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

#include "usermention.hpp"
#include <QTextStream>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
UserMention2::UserMention2() :
	TweetEntity2(),
	userID(-1),
	userIDstr("-1"),
	screenName(""),
	userName("")
{}

// Destructor
UserMention2::~UserMention2() {}

// Copy constructor
UserMention2::UserMention2(const UserMention2 & mention) :
	TweetEntity2(),
	userID(-1),
	userIDstr("-1"),
	screenName(""),
	userName("")
{
	recopie(mention);
}

// Affectation
const UserMention2 & UserMention2::operator=(const UserMention2 & mention) {
	recopie(mention);
	return *this;
}

// Serialization declaration
void UserMention2::initSystem() {
	qRegisterMetaTypeStreamOperators<UserMention2>("UserMention2");
	qMetaTypeId<UserMention2>();
}

// Copy of a User Mention
void UserMention2::recopie(const UserMention2 & mention) {
	TweetEntity::recopie(mention);
	userID = mention.userID;
	userIDstr = mention.userIDstr;
	screenName = mention.screenName;
	userName = mention.userName;
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const UserMention2 & mention) {
	return mention.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, UserMention2 & mention) {
	return mention.fillWithStream(in);
}

// Resets the mappable to a default value
void UserMention2::reset() {
	*this = UserMention2();
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void UserMention2::fillWithJSON(QJsonObject json) {
	// Base class
	TweetEntity2::fillWithJSON(json);

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
QJsonObject UserMention2::toJSON() const {
	QJsonObject json = TweetEntity2::toJSON();

	json.insert(ID_PN, QJsonValue(this->userID));
	json.insert(ID_STR_PN, QJsonValue(this->userIDstr));
	json.insert(SCREEN_NAME_PN, QJsonValue(this->screenName));
	json.insert(NAME_PN, QJsonValue(this->userName));

	return json;
}


////////////////////////
// Getter and setters //
////////////////////////

// id
QString UserMention2::ID_PN = "id";

qlonglong UserMention2::getID() {
	return userID;
}

void UserMention2::setID(qlonglong newID) {
	userID = newID;
	userIDstr = QString::number(userID);
}

// id_str
QString UserMention2::ID_STR_PN = "id_str";

QString UserMention2::getIDstr() {
	return userIDstr;
}

void UserMention2::setIDstr(QString newID) {
	userIDstr = newID;
	userID = userIDstr.toLongLong();
}

// screen_name
QString UserMention2::SCREEN_NAME_PN = "screen_name";

QString UserMention2::getScreenName() {
	return screenName;
}

void UserMention2::setScreenName(QString newScreenName) {
	screenName = newScreenName;
}

// name
QString UserMention2::NAME_PN = "name";

QString UserMention2::getName() {
	return userName;
}

void UserMention2::setName(QString newName) {
	userName = newName;
}


//////////
// Misc //
//////////

// @screenName
QString UserMention2::getMention() {
	QString s = "";
	QTextStream t(&s);
	t << '@' << screenName;
	return t.readAll();
}

// Building the rich text for the entity
QString UserMention2::getDisplayedText(QColor linkColor) {
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
