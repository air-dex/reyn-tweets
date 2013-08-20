/// @file hashtagshandler.cpp
/// @brief Implementation of HashtagsHandler
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

#include "hashtagshandler.hpp"
#include <QtQml>

// Constructor
HashtagsHandler::HashtagsHandler() :
	ListHandler<HashtagList, Hashtag>()
{}

// Destructor
HashtagsHandler::~HashtagsHandler() {}

// Copy constructor
HashtagsHandler::HashtagsHandler(const HashtagsHandler & handler) :
	ListHandler<HashtagList, Hashtag>()
{
	recopie(handler);
}

// Affrection operator
const HashtagsHandler & HashtagsHandler::operator=(const HashtagsHandler & handler) {
	recopie(handler);
	return *this;
}

// Copy of a HashtagsHandler
void HashtagsHandler::recopie(const HashtagsHandler &handler) {
	ListHandler<HashtagList, Hashtag>::recopie(handler);
}

// Serialization initialization
void HashtagsHandler::initSystem() {
	qRegisterMetaTypeStreamOperators<HashtagsHandler>("HashtagsHandler");
	qMetaTypeId<HashtagsHandler>();
}

// Declaring to the QML components
void HashtagsHandler::declareQML() {
	qmlRegisterType<HashtagsHandler>("ReynTweetsEntities",
									 0, 2,
									 "HashtagsHandler");
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const HashtagsHandler & handler) {
	return handler.handledList.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, HashtagsHandler & handler) {
	return handler.handledList.fillWithStream(in);
}


///////////////////
// List Handling //
///////////////////

Hashtag * HashtagsHandler::get(int index) {
	return ListHandler<HashtagList, Hashtag>::get(index);
}

// Filling an element with a QVariant
void HashtagsHandler::fillElement(Hashtag & realElt,
								  QVariant varelt,
								  bool resetValue)
{
	if (resetValue) {
		realElt.reset();
	}

	realElt.fillWithVariant(QJsonObject::fromVariantMap(varelt.toMap()));
}
