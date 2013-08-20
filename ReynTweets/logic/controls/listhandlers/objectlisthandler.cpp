/// @file objectlisthandler.cpp
/// @brief Implementation of ObjectListHandler
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

#include "objectlisthandler.hpp"

#include <QJsonObject>

/////////////
// Coplien //
/////////////

// Constructor
template<typename HL, typename U>
ObjectListHandler<HL,U>::ObjectListHandler() :
	ListHandler<HL, U>()
{}

// Destructor
template<typename HL, typename U>
ObjectListHandler<HL,U>::~ObjectListHandler() {}

// Copy constructor
template<typename HL, typename U>
ObjectListHandler<HL,U>::ObjectListHandler(const ObjectListHandler<HL,U> & listhandler) :
	ListHandler<HL, U>()
{
	recopie(listhandler);
}

// Affectation
template<typename HL, typename U>
const ObjectListHandler<HL,U> & ObjectListHandler<HL,U>::operator=(const ObjectListHandler<HL,U> & listhandler) {
	recopie(listhandler);
	return *this;
}

///////////////////
// List handling //
///////////////////

// Filling an element with a QVariant
template<typename HL, typename U>
void ObjectListHandler<HL,U>::fillElement(U & realElt,
										  QVariant varelt,
										  bool resetValue)
{
	if (resetValue) {
		realElt.reset();
	}

	realElt.fillWithVariant(QJsonObject::fromVariantMap(varelt.toMap()));
}
