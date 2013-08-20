/// @file listhandler.cpp
/// @brief Implementation of ListHandler
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

#include "listhandler.hpp"

#include <QJsonObject>

/////////////
// Coplien //
/////////////

// Constructor
template<typename HL, typename U>
ListHandler<HL,U>::ListHandler() :
	HandlerEmitter(),
	handledList()
{}

// Destructor
template<typename HL, typename U>
ListHandler<HL,U>::~ListHandler() {}

// Copy constructor
template<typename HL, typename U>
ListHandler<HL,U>::ListHandler(const ListHandler<HL,U> & listhandler) :
	HandlerEmitter(),
	handledList()
{
	recopie(listhandler);
}

// Affectation
template<typename HL, typename U>
const ListHandler<HL,U> & ListHandler<HL,U>::operator=(const ListHandler<HL,U> & listhandler) {
	recopie(listhandler);
	return *this;
}

// Recopy of a ListHandler
template<typename HL, typename U>
void ListHandler<HL,U>::recopie(const ListHandler<HL,U> & listhandler) {
	this->handledList = listhandler.handledList;
}


///////////////////
// List handling //
///////////////////

// Getter on the handled list
template<typename HL, typename U>
HL ListHandler<HL,U>::getHandledList() {
	return handledList;
}

// Getter on a reference on the handled list
template<typename HL, typename U>
HL & ListHandler<HL,U>::getHandledListRef() {
	return handledList;
}

// Setter on the handled list
template<typename HL, typename U>
void ListHandler<HL,U>::setHandledList(HL newlist) {
	handledList = newlist;
	emit handledListChanged();
}

// Get an element of the handled list
template<typename HL, typename U>
U * ListHandler<HL,U>::get(int index) {
	if (index >= 0 && index < handledList.size()) {
		//return &(handledList[index]);
		return new U(handledList[index]);
	} else {
		return new U;
	}
}

// Getting the size of the handled list.
template<typename HL, typename U>
int ListHandler<HL,U>::getHandledListSize() {
	return handledList.size();
}

// Replacing an element in the list
template<typename HL, typename U>
void ListHandler<HL,U>::replace(QVariant varelt) {
	U realElt;
	realElt.fillWithVariant(QJsonObject::fromVariantMap(varelt.toMap()));

	bool exact;
	int index = getElementIndex(realElt, exact);

	// Replace only if it's really in the list
	if (exact) {
		U & listElt = handledList[index];
		listElt = realElt;
		emit handledListChanged();
	}
}

template<typename HL, typename U>
void ListHandler<HL,U>::replace(QVariant varelt, int index) {
	if (index < 0 || index >= handledList.count()) {
		return;
	}

	U & listElt = handledList[index];
	listElt.reset();
	listElt.fillWithVariant(QJsonObject::fromVariantMap(varelt.toMap()));
	emit handledListChanged();
}

// Removing an element of the list
template<typename HL, typename U>
void ListHandler<HL,U>::remove(int index) {
	if (index >= 0 || index < handledList.count()) {
		handledList.removeAt(index);
		emit handledListChanged();
	}
}

template<typename HL, typename U>
void ListHandler<HL,U>::remove(QVariant varelt) {
	U realElt;
	realElt.fillWithVariant(QJsonObject::fromVariantMap(varelt.toMap()));

	bool exact;
	int index = getElementIndex(realElt, exact);

	// Delete only if it's really in the list
	if (exact) {
		handledList.removeAt(index);
		emit handledListChanged();
	}
}
