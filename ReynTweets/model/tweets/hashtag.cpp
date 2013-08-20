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
Hashtag::Hashtag() :
	TweetEntity(),
	hashText("")
{}

// Destructor
Hashtag::~Hashtag() {}

// Copy constructor
Hashtag::Hashtag(const Hashtag & hashtag) :
	TweetEntity(),
	hashText("")
{
	recopie(hashtag);
}

// Affectation
const Hashtag & Hashtag::operator=(const Hashtag & hashtag) {
	recopie(hashtag);
	return *this;
}

// Serialization declaration
void Hashtag::initSystem() {
	qRegisterMetaTypeStreamOperators<Hashtag>("Hashtag");
	qMetaTypeId<Hashtag>();
}

// Copy of a Hashtag
void Hashtag::recopie(const Hashtag & hashtag) {
	TweetEntity::recopie(hashtag);
	hashText = hashtag.hashText;
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const Hashtag & hashtag) {
	return hashtag.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, Hashtag & hashtag) {
	return hashtag.fillWithStream(in);
}

// Resets the mappable to a default value
void Hashtag::reset() {
	*this = Hashtag();
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void Hashtag::fillWithJSON(QJsonObject json) {
	// Base class
	TweetEntity::fillWithJSON(json);

	// "text" property
	QJsonValue propval = json.value(TEXT_PN);

	if (!propval.isUndefined() && propval.isString()) {
		QString text = propval.toString();
		this->hashText = text;
	}
}

// Getting a QJsonObject representation of the object
QJsonObject Hashtag::toJSON() const {
	QJsonObject json = TweetEntity::toJSON();

	json.insert(TEXT_PN, QJsonValue(this->hashText));

	return json;
}


////////////////////////
// Getter and setters //
////////////////////////

// text
QString Hashtag::TEXT_PN = "text";

QString Hashtag::getText() {
	return hashText;
}

void Hashtag::setText(QString newText) {
	hashText = newText;
}

// #hashText
QString Hashtag::getHashtag() {
	QString s = "";
	QTextStream t(&s);
	t << '#' << hashText;
	return t.readAll();
}


//////////
// Misc //
//////////

// Building the rich text for the entity
QString Hashtag::getDisplayedText(QColor linkColor) {
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
