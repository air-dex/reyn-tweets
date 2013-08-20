/// @file mappable.cpp
/// @brief Implementation of Mappable
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

#include "mappable.hpp"
#include "../tools/utils.hpp"
/*
/////////////
// Coplien //
/////////////

// Default constructor
Mappable::Mappable() :
	QObject(),
	Variantable<QVariantMap>()
{}

// Destructor
Mappable::~Mappable() {}

// Copy constructor
Mappable::Mappable(const Mappable & mappable) :
	QObject(),
	Variantable<QVariantMap>()
{}

// Affecting a Mappable
const Mappable & Mappable::operator=(const Mappable & mappable) {
	return *this;
}

// Affecting a QVariantMap
const Mappable & Mappable::operator=(const QVariantMap & mappable) {
	this->fillWithVariant(mappable);
	return *this;
}//*/
