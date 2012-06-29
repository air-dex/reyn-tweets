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

#include <QTextStream>
#include <QWebPage>
#include <QWebFrame>
#include <QWebElement>
#include "urlentity.hpp"
#include "../tools/utils.hpp"

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
    TweetEntity()
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
	return jsonStreamingOut(out, entity);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, URLEntity & entity) {
	return jsonStreamingIn(in, entity);
}

// Resets the mappable to a default value
void URLEntity::reset() {
	*this = URLEntity();
}


////////////////////////
// Getter and setters //
////////////////////////

// Reading extractedURL
QString URLEntity::getURL() {
	return extractedURL;
}

// Writing extractedURL
void URLEntity::setURL(QString newURL) {
	extractedURL = newURL;
}

// Reading method for displayedURL
QString URLEntity::getDisplayedURL() {
	return displayedURL;
}

// Writing displayedURL
void URLEntity::setDisplayedURL(QString newURL) {
	displayedURL = newURL;
}

// Reading method for expandedURL
QString URLEntity::getExpandedURL() {
	return expandedURL;
}

// Writing method for expandedURL
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
