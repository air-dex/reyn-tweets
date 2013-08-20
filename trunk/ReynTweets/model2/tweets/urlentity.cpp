/// @file urlentity.cpp
/// @brief Implementation of URLEntity
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

#include "urlentity.hpp"
#include <QTextStream>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
URLEntity2::URLEntity2() :
	TweetEntity2(),
	extractedURL(""),
	displayedURL(""),
	expandedURL("")
{}

// Destructor
URLEntity2::~URLEntity2() {}

// Copy constructor
URLEntity2::URLEntity2(const URLEntity & entity) :
	TweetEntity2(),
	extractedURL(""),
	displayedURL(""),
	expandedURL("")
{
	recopie(entity);
}

// Affectation
const URLEntity2 & URLEntity2::operator=(const URLEntity2 & entity) {
	recopie(entity);
	return *this;
}

// Serialization declaration
void URLEntity2::initSystem() {
	qRegisterMetaTypeStreamOperators<URLEntity2>("URLEntity2");
	qMetaTypeId<URLEntity2>();
}

// Copy of a URLEntity
void URLEntity2::recopie(const URLEntity2 & entity) {
	TweetEntity2::recopie(entity);
	extractedURL = entity.extractedURL;
	displayedURL = entity.displayedURL;
	expandedURL = entity.expandedURL;
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const URLEntity2 & entity) {
	return entity.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, URLEntity2 & entity) {
	return entity.fillWithStream(in);
}

// Resets the mappable to a default value
void URLEntity2::reset() {
	*this = URLEntity2();
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void URLEntity2::fillWithJSON(QJsonObject json) {
	// Base class
	TweetEntity2::fillWithJSON(json);

	// "url" property
	QJsonValue propval = json.value(URL_PN);

	if (!propval.isUndefined() && propval.isString()) {
		QString url = propval.toString();
		this->extractedURL = url;
	}

	// "displayed_url" property
	propval = json.value(DISPLAYED_URL_PN);

	if (!propval.isUndefined() && propval.isString()) {
		QString url = propval.toString();
		this->displayedURL = url;
	}

	// "expanded_url" property
	propval = json.value(EXPANDED_URL_PN);

	if (!propval.isUndefined() && propval.isString()) {
		QString url = propval.toString();
		this->expandedURL = url;
	}
}

// Getting a QJsonObject representation of the object
QJsonObject URLEntity2::toJSON() const {
	QJsonObject json = TweetEntity2::toJSON();

	json.insert(URL_PN, QJsonValue(this->extractedURL));
	json.insert(DISPLAYED_URL_PN, QJsonValue(this->displayedURL));
	json.insert(EXPANDED_URL_PN, QJsonValue(this->expandedURL));

	return json;
}


////////////////////////
// Getter and setters //
////////////////////////

// url
QString URLEntity2::URL_PN = "url";

QString URLEntity2::getURL() {
	return extractedURL;
}

void URLEntity2::setURL(QString newURL) {
	extractedURL = newURL;
}

// displayed_url
QString URLEntity2::DISPLAYED_URL_PN = "displayed_url";

QString URLEntity2::getDisplayedURL() {
	return displayedURL;
}

void URLEntity2::setDisplayedURL(QString newURL) {
	displayedURL = newURL;
}

// expanded_url
QString URLEntity2::EXPANDED_URL_PN = "expanded_url";

QString URLEntity2::getExpandedURL() {
	return expandedURL;
}

void URLEntity2::setExpandedURL(QString newURL) {
	expandedURL = newURL;
}


//////////
// Misc //
//////////

// Building the rich text for the entity
QString URLEntity2::getDisplayedText(QColor linkColor) {
	QWebPage page;
	QWebFrame * frame = page.mainFrame();

	if (frame) {
		frame->setHtml("<a></a>");
		QWebElement link = frame->documentElement().findFirst("a");

		link.setPlainText(expandedURL);
		link.setAttribute("href", extractedURL);
		link.setStyleProperty("color", linkColor.name());
		link.setStyleProperty("text-decoration", "none");

		return link.toOuterXml();
	} else {
		QString s = "";
		QTextStream t(&s);

		t << "<a href=\"" << extractedURL
		  << "style=\"text-decoration: none ; color:\""
		  << linkColor.name() << "\">" << expandedURL << "</a>";

		return t.readAll();
	}
}
