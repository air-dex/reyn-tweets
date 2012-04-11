/// @file usermention.cpp
/// @brief Implementation of UserMention
///
/// Revisions older than r243 was in /trunk/ReynTwets/model
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
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

#include <QTextStream>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include "usermention.hpp"
#include "../tools/utils.hpp"

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
UserMention::UserMention(const UserMention & mention) {
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
	return jsonStreamingOut(out, mention);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, UserMention & mention) {
	return jsonStreamingIn(in, mention);
}


////////////////////////
// Getter and setters //
////////////////////////

// Reading userID
qlonglong UserMention::getID() {
	return userID;
}

// Writing userID
void UserMention::setID(qlonglong newID) {
	userID = newID;
}

// Reading userIDstr
QString UserMention::getIDstr() {
	return userIDstr;
}

// Writing userIDstr
void UserMention::setIDstr(QString newID) {
	userIDstr = newID;
}

// Reading method for screenName
QString UserMention::getScreenName() {
	return screenName;
}

// Writing displayedURL
void UserMention::setScreenName(QString newScreenName) {
	screenName = newScreenName;
}

// Reading method for userName
QString UserMention::getName() {
	return userName;
}

// Writing method for userName
void UserMention::setName(QString newName) {
	userName = newName;
}


//////////
// Misc //
//////////

// #hashText
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
