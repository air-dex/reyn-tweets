/// @file mentionshandler.cpp
/// @brief Implementation of MentionsHandler
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

#include "mentionshandler.hpp"
#include <QtQml>
#include "../../reyntweetsutils.hpp"

// Constructor
MentionsHandler::MentionsHandler() :
	ObjectListHandler<UserMentionList, UserMention>()
{}

// Destructor
MentionsHandler::~MentionsHandler() {}

// Copy constructor
MentionsHandler::MentionsHandler(const MentionsHandler & handler) :
	ObjectListHandler<UserMentionList, UserMention>()
{
	recopie(handler);
}

// Affrection operator
const MentionsHandler & MentionsHandler::operator=(const MentionsHandler & handler) {
	recopie(handler);
	return *this;
}

// Copy of a TimelineHandler
void MentionsHandler::recopie(const MentionsHandler &handler) {
	ObjectListHandler<UserMentionList, UserMention>::recopie(handler);
}

// Serialization initialization
void MentionsHandler::initSystem() {
	qRegisterMetaTypeStreamOperators<MentionsHandler>("MentionsHandler");
	qMetaTypeId<MentionsHandler>();
}

// Declaring to the QML components
void MentionsHandler::declareQML() {
	// @uri ReynTweetsComponents
	qmlRegisterType<MentionsHandler>(ReynTweets::QML_LIBRARY_NAME.toLatin1().constData(),
									 ReynTweets::MAJOR_VERSION, ReynTweets::MINOR_VERSION,
									 "MentionsHandler");
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const MentionsHandler & handler) {
	return handler.handledList.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, MentionsHandler & handler) {
	return handler.handledList.fillWithStream(in);
}


///////////////////
// List Handling //
///////////////////

UserMention * MentionsHandler::get(int index) {
	return ObjectListHandler<UserMentionList, UserMention>::get(index);
}

// Filling an element with a QVariant
void MentionsHandler::fillElement(UserMention & realElt,
								  QVariant varelt,
								  bool resetValue)
{
	if (resetValue) {
		realElt.reset();
	}

	realElt.fillWithVariant(QJsonObject::fromVariantMap(varelt.toMap()));
}
