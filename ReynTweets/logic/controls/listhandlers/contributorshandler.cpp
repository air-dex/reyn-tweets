/// @file contributorshandler.cpp
/// @brief Implementation of ContributorsHandler
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

#include "contributorshandler.hpp"
#include <QtQml>

// Constructor
ContributorsHandler::ContributorsHandler() :
	ObjectListHandler<ContributorList, Contributor>()
{}

// Destructor
ContributorsHandler::~ContributorsHandler() {}

// Copy constructor
ContributorsHandler::ContributorsHandler(const ContributorsHandler & handler) :
	ObjectListHandler<ContributorList, Contributor>()
{
	recopie(handler);
}

// Affrection operator
const ContributorsHandler & ContributorsHandler::operator=(const ContributorsHandler & handler) {
	recopie(handler);
	return *this;
}

// Copy of a TimelineHandler
void ContributorsHandler::recopie(const ContributorsHandler &handler) {
	ObjectListHandler<ContributorList, Contributor>::recopie(handler);
}

// Serialization initialization
void ContributorsHandler::initSystem() {
	qRegisterMetaTypeStreamOperators<ContributorsHandler>("ContributorsHandler");
	qMetaTypeId<ContributorsHandler>();
}

// Declaring to the QML components
void ContributorsHandler::declareQML() {
	qmlRegisterType<ContributorsHandler>("ReynTweetsEntities",
										 0, 2,
										 "ContributorsHandler");
}

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const ContributorsHandler & handler) {
	return handler.handledList.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, ContributorsHandler & handler) {
	return handler.handledList.fillWithStream(in);
}


///////////////////
// List Handling //
///////////////////

Contributor * ContributorsHandler::get(int index) {
	return ObjectListHandler<ContributorList, Contributor>::get(index);
}

// Filling an element with a QVariant
void ContributorsHandler::fillElement(Contributor & realElt,
									  QVariant varelt,
									  bool resetValue)
{
	if (resetValue) {
		realElt.reset();
	}

	realElt.fillWithVariant(QJsonObject::fromVariantMap(varelt.toMap()));
}
