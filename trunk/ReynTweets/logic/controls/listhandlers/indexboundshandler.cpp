/// @file indexboundshandler.cpp
/// @brief Implementation of IndexBoundsHandler
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

#include "indexboundshandler.hpp"
#include <QtQml>

// Constructor
IndexBoundsHandler::IndexBoundsHandler() :
	ListHandler<IndexBounds, int>()
{}

// Destructor
IndexBoundsHandler::~IndexBoundsHandler() {}

// Copy constructor
IndexBoundsHandler::IndexBoundsHandler(const IndexBoundsHandler & handler) :
	ListHandler<IndexBounds, int>()
{
	recopie(handler);
}

// Affrection operator
const IndexBoundsHandler & IndexBoundsHandler::operator=(const IndexBoundsHandler & handler) {
	recopie(handler);
	return *this;
}

// Copy of a IndexBoundsHandler
void IndexBoundsHandler::recopie(const IndexBoundsHandler &handler) {
	ListHandler<IndexBounds, int>::recopie(handler);
}

// Serialization initialization
void IndexBoundsHandler::initSystem() {
	qRegisterMetaTypeStreamOperators<IndexBoundsHandler>("IndexBoundsHandler");
	qMetaTypeId<IndexBoundsHandler>();
}

// Declaring to the QML components
void IndexBoundsHandler::declareQML() {
	qmlRegisterType<IndexBoundsHandler>("ReynTweetsEntities",
										0, 2,
										"IndexBoundsHandler");
}


/////////////////////////////////////
// Friends serialization operators //
/////////////////////////////////////

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out, const IndexBoundsHandler & handler) {
	return handler.handledList.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in, IndexBoundsHandler & handler) {
	return handler.handledList.fillWithStream(in);
}


////////////////////////////
// Rewriting some methods //
////////////////////////////

// Filling an element with a QVariant
void IndexBoundsHandler::fillElement(int & realElt,
									 QVariant varelt,
									 bool resetValue)
{
	Q_UNUSED(resetValue)
	realElt = varelt.toInt();
}


///////////////////
// List Handling //
///////////////////

int * IndexBoundsHandler::get(int index) {
	return ListHandler<IndexBounds, int>::get(index);
}


//////////////////////////
// Properties on bounds //
//////////////////////////

// lower_bound
int IndexBoundsHandler::getLowerBound() {
	return handledList.getMin();
}

void IndexBoundsHandler::setLowerBound(int newBound) {
	handledList.setMin(newBound);
	emit lowerBoundChanged();
}

// upper_bound
int IndexBoundsHandler::getUpperBound() {
	return handledList.getMax();
}

void IndexBoundsHandler::setUpperBound(int newBound) {
	handledList.setMax(newBound);
	emit upperBoundChanged();
}
