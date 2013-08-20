/// @file mediashandler.cpp
/// @brief Implementation of MediasHandler
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

#include "mediashandler.hpp"
#include <QtQml>
#include "../../reyntweetsutils.hpp"

// Constructor
MediasHandler::MediasHandler() :
	ObjectListHandler<MediaList, Media>()
{}

// Destructor
MediasHandler::~MediasHandler() {}

// Copy constructor
MediasHandler::MediasHandler(const MediasHandler & handler) :
	ObjectListHandler<MediaList, Media>()
{
	recopie(handler);
}

// Affrection operator
const MediasHandler & MediasHandler::operator=(const MediasHandler & handler) {
	recopie(handler);
	return *this;
}

// Copy of a TimelineHandler
void MediasHandler::recopie(const MediasHandler &handler) {
	ObjectListHandler<MediaList, Media>::recopie(handler);
}

// Serialization initialization
void MediasHandler::initSystem() {
	qRegisterMetaTypeStreamOperators<MediasHandler>("MediasHandler");
	qMetaTypeId<MediasHandler>();
}

// Declaring to the QML components
void MediasHandler::declareQML() {
	// @uri ReynTweetsComponents
	qmlRegisterType<MediasHandler>(ReynTweets::QML_LIBRARY_NAME.toLatin1().constData(),
								   ReynTweets::MAJOR_VERSION, ReynTweets::MINOR_VERSION,
								   "MediasHandler");
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const MediasHandler & handler) {
	return handler.handledList.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, MediasHandler & handler) {
	return handler.handledList.fillWithStream(in);
}


///////////////////
// List Handling //
///////////////////

Media * MediasHandler::get(int index) {
	return ObjectListHandler<MediaList, Media>::get(index);
}

// Filling an element with a QVariant
void MediasHandler::fillElement(Media & realElt,
								QVariant varelt,
								bool resetValue)
{
	if (resetValue) {
		realElt.reset();
	}

	realElt.fillWithVariant(QJsonObject::fromVariantMap(varelt.toMap()));
}
