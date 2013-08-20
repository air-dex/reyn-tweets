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
template <class M>
Listable<M>::Listable() :
	Variantable<QVariantList>(),
	QList<M>()
{}

// Destructor
template <class M>
Listable<M>::~Listable() {}

// Copy constructor
template <class M>
Listable<M>::Listable(const Listable<M> & list) :
	Variantable<QVariantList>(),
	QList<M>()
{
	this->recopie(list);
}

// Affrection operator
template <class M>
const Listable<M> & Listable<M>::operator=(const Listable<M> & list) {
	this->recopie(list);
	return *this;
}

// Copy of a Listable
template <class M>
void Listable<M>::recopie(const Listable<M> & list) {
	this->clear();

	for (typename Listable<M>::const_iterator it = list.begin();
		 it != list.end();
		 ++it)
	{
		M serializable = *it;
		this->append(serializable);
	}
}

///////////////////////////
// Serialization streams //
///////////////////////////

template <class M>
QDataStream & jsonStreamingOut(QDataStream & out, const Listable<M> & list) {
	// Serialize the QVariantList form of the listable and putting it in the stream.
	return streamVariantOut(out, list.toVariant());
}

// Input stream operator for serialization
template <class M>
QDataStream & jsonStreamingIn(QDataStream & in, Listable<M> & list) {
	QVariant listableVariant;
	streamVariantIn(in, listableVariant);
	list.fillWithVariant(listableVariant.toList());
	return in;
}
/*
#include "mappable.hpp"

/// @fn QDataStream & jsonStreamingOut(QDataStream & out, const Listable<Mappable> & list);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param list Object to put in the stream
/// @return The stream with the object
template <>
QDataStream & jsonStreamingOut(QDataStream & out, const Listable<Mappable> & list);

/// @fn QDataStream & jsonStreamingIn(QDataStream & in, Listable<M> & list);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param list Object to put in the stream
/// @return The stream with the object
template <>
QDataStream & jsonStreamingIn(QDataStream & in, Listable<Mappable> & list);
//*/
