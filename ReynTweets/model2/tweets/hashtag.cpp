/// @file hashtag.cpp
/// @brief Implementation of Hashtag
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

#include "hashtag.hpp"
#include <QTextStream>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
Hashtag2::Hashtag2() :
	TweetEntity2(),
	hashText("")
{}

// Destructor
Hashtag2::~Hashtag2() {}

// Copy constructor
Hashtag2::Hashtag2(const Hashtag2 & hashtag) :
	TweetEntity2(),
	hashText("")
{
	recopie(hashtag);
}

// Affectation
const Hashtag2 & Hashtag2::operator=(const Hashtag2 & hashtag) {
	recopie(hashtag);
	return *this;
}

// Serialization declaration
void Hashtag2::initSystem() {
	qRegisterMetaTypeStreamOperators<Hashtag2>("Hashtag2");
	qMetaTypeId<Hashtag2>();
}

// Copy of a Hashtag
void Hashtag2::recopie(const Hashtag2 & hashtag) {
	TweetEntity2::recopie(hashtag);
	hashText = hashtag.hashText;
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const Hashtag2 & hashtag) {
	return jsonObjectStreamingOut(out, hashtag);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, Hashtag2 & hashtag) {
	return jsonObjectStreamingIn(in, hashtag);
}

// Resets the mappable to a default value
void Hashtag2::reset() {
	*this = Hashtag2();
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void Hashtag2::fillWithJSON(QJsonObject json) {
	// Base class
	TweetEntity2::fillWithJSON(json);

	// "text" property
	QJsonValue propval = json.value(TEXT_PN);

	if (!propval.isUndefined() && propval.isString()) {
		QString text = propval.toString();
		this->hashText = text;
	}
}

// Getting a QJsonObject representation of the object
QJsonObject Hashtag2::toJSON() {
	QJsonObject json = TweetEntity2::toJSON();

	json.insert(TEXT_PN, QJsonValue(this->hashText));

	return json;
}


////////////////////////
// Getter and setters //
////////////////////////

// text
QString Hashtag2::TEXT_PN = "text";

QString Hashtag2::getText() {
	return hashText;
}

void Hashtag2::setText(QString newText) {
	hashText = newText;
}

// #hashText
QString Hashtag2::getHashtag() {
	QString s = "";
	QTextStream t(&s);
	t << '#' << hashText;
	return t.readAll();
}


//////////
// Misc //
//////////

// Building the rich text for the entity
QString Hashtag2::getDisplayedText(QColor linkColor) {
	QString hashtag = getHashtag();
	QWebPage page;
	QWebFrame * frame = page.mainFrame();

	if (frame) {
		frame->setHtml("<a></a>");
		QWebElement link = frame->documentElement().findFirst("a");

		link.setPlainText(hashtag);
		link.setAttribute("href", hashtag);
		link.setStyleProperty("color", linkColor.name());
		link.setStyleProperty("text-decoration", "none");

		return link.toOuterXml();
	} else {
		// Back to basics : writing a string.
		QString s = "";
		QTextStream t(&s);

		t << "<a href=\"" << hashtag
		  << "style=\"text-decoration: none ; color:\""
		  << linkColor.name() << "\">" << hashtag << "</a>";

		return t.readAll();
	}
}
