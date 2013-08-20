/// @file mappablelist.cpp
/// @brief Implementation of MappableList
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

#include "mappablelist.hpp"

/////////////
// Coplien //
/////////////

// Constructor
MappableList::MappableList() :
	Listable<Mappable>()
{}

// Destructor
MappableList::~MappableList() {}

// Copy constructor
template <class M>
MappableList<M>::MappableList(const MappableList & list) :
	Listable<Mappable>(list)
{}

// Affrection operator
const MappableList & MappableList::operator=(const MappableList & list) {
	this->Listable<Mappable>::recopie(list);
	return *this;
}

/*
// Copy of a MappableList
void MappableList::recopie(const MappableList & list) {
	this->Listable<Mappable>::recopie(list);
}
//*/

////////////////////////
// Variant conversion //
////////////////////////

// Filling the MappableList with a QVariantList.
void MappableList::fillWithVariant(QVariantList entities) {
	this->clear();

	for (QVariantList::Iterator it = entities.begin();
		 it != entities.end();
		 ++it)
	{
		QVariant v = *it;
		Mappable mappable;
		mappable.fillWithVariant(v.toMap());
		this->append(mappable);
	}
}

// Converting a MappableList into a QVariantList
QVariantList MappableList<M>::toVariant() const {
	QVariantList res;

	for (MappableList::const_iterator it = this->begin();
		 it != this->end();
		 ++it)
	{
		Mappable mappable = *it;
		res.append(mappable.toVariant());
	}

	return res;
}


///////////////////////////
// Serialization streams //
///////////////////////////

template <class M>
QDataStream & jsonStreamingOut(QDataStream & out, const MappableList<M> & list) {
	// Serialize the QVariantList form of the MappableList and putting it in the stream.
	return streamVariantOut(out, list.toVariant());
}

// Input stream operator for serialization
template <class M>
QDataStream & jsonStreamingIn(QDataStream & in, MappableList<M> & list) {
	QVariant MappableListVariant;
	streamVariantIn(in, MappableListVariant);
	list.fillWithVariant(MappableListVariant.toList());
	return in;
}
/*
#include "mappable.hpp"

/// @fn QDataStream & jsonStreamingOut(QDataStream & out, const MappableList<Mappable> & list);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param list Object to put in the stream
/// @return The stream with the object
template <>
QDataStream & jsonStreamingOut(QDataStream & out, const MappableList<Mappable> & list);

/// @fn QDataStream & jsonStreamingIn(QDataStream & in, MappableList<M> & list);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param list Object to put in the stream
/// @return The stream with the object
template <>
QDataStream & jsonStreamingIn(QDataStream & in, MappableList<Mappable> & list);
//*/
