/// @file listable.cpp
/// @brief Implementation of Listable
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

#include "listable.hpp"
#include "../tools/utils.hpp"

/////////////
// Coplien //
/////////////

// Constructor
template <typename V>
Listable<V>::Listable() :
	Variantable<QVariantList>(),
	QList<V>()
{}

// Destructor
template <typename V>
Listable<V>::~Listable() {}

// Copy constructor
template <typename V>
Listable<V>::Listable(const Listable<V> & list) :
	Variantable<QVariantList>(),
	QList<V>()
{
	this->recopie(list);
}

// Affrection operator
template <typename V>
const Listable<V> & Listable<V>::operator=(const Listable<V> & list) {
	this->recopie(list);
	return *this;
}

// Copy of a Listable
template <typename V>
void Listable<V>::recopie(const Listable<V> & list) {
	this->clear();

	for (typename Listable<V>::const_iterator it = list.begin();
		 it != list.end();
		 ++it)
	{
		V variantable = *it;
		this->append(variantable);
	}
}

////////////////////////
// Variant conversion //
////////////////////////

// Filling the MappableList with a QVariantList.
template <typename V>
void Listable<V>::fillWithVariant(QVariantList entities) {
	this->clear();

	for (QVariantList::Iterator it = entities.begin();
		 it != entities.end();
		 ++it)
	{
		QVariant v = *it;
		this->append(v.value<V>());
	}
}

// Converting a MappableList into a QVariantList
template <typename V>
QVariantList Listable<V>::toVariant() const {
	QVariantList res;

	for (typename Listable<V>::const_iterator it = this->begin();
		 it != this->end();
		 ++it)
	{
		V listableElt = *it;
		res.append(QVariant::fromValue(listableElt));
	}

	return res;
}
