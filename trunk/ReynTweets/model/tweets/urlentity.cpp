/// @file urlentity.cpp
/// @brief Implementation of URLEntity
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

#include "urlentity.hpp"
#include <QTextStream>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>

//////////////////////////////
// Serialization management //
//////////////////////////////

// Constructor
URLEntity::URLEntity() :
	TweetEntity(),
	extractedURL(""),
	displayedURL(""),
	expandedURL("")
{}

// Destructor
URLEntity::~URLEntity() {}

// Copy constructor
URLEntity::URLEntity(const URLEntity & entity) :
	TweetEntity(),
	extractedURL(""),
	displayedURL(""),
	expandedURL("")
{
	recopie(entity);
}

// Affectation
const URLEntity & URLEntity::operator=(const URLEntity & entity) {
	recopie(entity);
	return *this;
}

// Serialization declaration
void URLEntity::initSystem() {
	qRegisterMetaTypeStreamOperators<URLEntity>("URLEntity");
	qMetaTypeId<URLEntity>();
}

// Copy of a URLEntity
void URLEntity::recopie(const URLEntity & entity) {
	TweetEntity::recopie(entity);
	extractedURL = entity.extractedURL;
	displayedURL = entity.displayedURL;
	expandedURL = entity.expandedURL;
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const URLEntity & entity) {
	return entity.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, URLEntity & entity) {
	return entity.fillWithStream(in);
}

// Resets the mappable to a default value
void URLEntity::reset() {
	*this = URLEntity();
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void URLEntity::fillWithJSON(QJsonObject json) {
	// Base class
	TweetEntity::fillWithJSON(json);

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
QJsonObject URLEntity::toJSON() const {
	QJsonObject json = TweetEntity::toJSON();

	json.insert(URL_PN, QJsonValue(this->extractedURL));
	json.insert(DISPLAYED_URL_PN, QJsonValue(this->displayedURL));
	json.insert(EXPANDED_URL_PN, QJsonValue(this->expandedURL));

	return json;
}


////////////////////////
// Getter and setters //
////////////////////////

// url
QString URLEntity::URL_PN = "url";

QString URLEntity::getURL() {
	return extractedURL;
}

void URLEntity::setURL(QString newURL) {
	extractedURL = newURL;
}

// displayed_url
QString URLEntity::DISPLAYED_URL_PN = "displayed_url";

QString URLEntity::getDisplayedURL() {
	return displayedURL;
}

void URLEntity::setDisplayedURL(QString newURL) {
	displayedURL = newURL;
}

// expanded_url
QString URLEntity::EXPANDED_URL_PN = "expanded_url";

QString URLEntity::getExpandedURL() {
	return expandedURL;
}

void URLEntity::setExpandedURL(QString newURL) {
	expandedURL = newURL;
}


//////////
// Misc //
//////////

// Building the rich text for the entity
QString URLEntity::getDisplayedText(QColor linkColor) {
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
