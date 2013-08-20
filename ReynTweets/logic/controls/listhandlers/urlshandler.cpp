/// @file urlshandler.cpp
/// @brief Implementation of UrlsHandler
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

#include "urlshandler.hpp"
#include <QtQml>

// Constructor
UrlsHandler::UrlsHandler() :
	ListHandler<URLEntityList, URLEntity>()
{}

// Destructor
UrlsHandler::~UrlsHandler() {}

// Copy constructor
UrlsHandler::UrlsHandler(const UrlsHandler & handler) :
	ListHandler<URLEntityList, URLEntity>()
{
	recopie(handler);
}

// Affrection operator
const UrlsHandler & UrlsHandler::operator=(const UrlsHandler & handler) {
	recopie(handler);
	return *this;
}

// Copy of a TimelineHandler
void UrlsHandler::recopie(const UrlsHandler &handler) {
	ListHandler<URLEntityList, URLEntity>::recopie(handler);
}

// Serialization initialization
void UrlsHandler::initSystem() {
	qRegisterMetaTypeStreamOperators<UrlsHandler>("UrlsHandler");
	qMetaTypeId<UrlsHandler>();
}

// Declaring to the QML components
void UrlsHandler::declareQML() {
	qmlRegisterType<UrlsHandler>("ReynTweetsEntities",
								 0, 2,
								 "UrlsHandler");
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const UrlsHandler & handler) {
	return handler.handledList.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, UrlsHandler & handler) {
	return handler.handledList.fillWithStream(in);
}


///////////////////
// List Handling //
///////////////////

URLEntity * UrlsHandler::get(int index) {
	return ListHandler<URLEntityList, URLEntity>::get(index);
}

// Filling an element with a QVariant
void UrlsHandler::fillElement(URLEntity & realElt,
								QVariant varelt,
								bool resetValue)
{
	if (resetValue) {
		realElt.reset();
	}

	realElt.fillWithVariant(QJsonObject::fromVariantMap(varelt.toMap()));
}
