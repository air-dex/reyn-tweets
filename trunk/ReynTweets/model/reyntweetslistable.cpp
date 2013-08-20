/// @file reyntweetslistable.cpp
/// @brief Implementation of ReynTweetsListable
///
/// This file was also known as reyntweetsserializablelist.cpp until r243
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
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

#include "reyntweetslistable.hpp"
#include "../tools/utils.hpp"

/////////////
// Coplien //
/////////////

// Constructor
template <class S>
ReynTweetsListable<S>::ReynTweetsListable() :
	QList<S>()
{}

// Destructor
template <class S>
ReynTweetsListable<S>::~ReynTweetsListable() {}

// Copy constructor
template <class S>
ReynTweetsListable<S>::ReynTweetsListable(const ReynTweetsListable<S> & list) :
	QList<S>()
{
	recopie(list);
}

// Affrection operator
template <class S>
const ReynTweetsListable<S> & ReynTweetsListable<S>::operator=(const ReynTweetsListable<S> & list) {
	recopie(list);
	return *this;
}

// Copy of a ReynTweetsListable
template <class S>
void ReynTweetsListable<S>::recopie(const ReynTweetsListable<S> & list) {
	this->clear();

	for (typename ReynTweetsListable<S>::const_iterator it = list.begin();
		 it != list.end();
		 ++it)
	{
		S serializable = *it;
		this->append(serializable);
	}
}

////////////////////////
// Variant conversion //
////////////////////////

// Converting a QVariantList into a list of entities.
template <class S>
void ReynTweetsListable<S>::fillWithVariant(QVariantList entities) {
	this->clear();

	for (QVariantList::Iterator it = entities.begin();
		 it != entities.end();
		 ++it)
	{
		QVariant v = *it;
		S entity;
		entity.fillWithVariant(v.toMap());
		this->append(entity);
	}
}

// Converting a list of serializables into a QVariantList
template <class S>
QVariantList ReynTweetsListable<S>::toVariant() const {
	QVariantList res;

	for (typename ReynTweetsListable<S>::const_iterator it = this->begin();
		 it != this->end();
		 ++it)
	{
		S serializable = *it;
		res.append(serializable.toVariant());
	}

	return res;
}


///////////////////////////
// Serialization streams //
///////////////////////////

template <class S>
QDataStream & jsonStreamingOut(QDataStream & out, const ReynTweetsListable<S> & list) {
	// Serialize the QVariantList form of the listable and putting it in the stream.
	return streamVariantOut(out, list.toVariant());
}

// Input stream operator for serialization
template <class S>
QDataStream & jsonStreamingIn(QDataStream & in, ReynTweetsListable<S> & list) {
	QVariant listableVariant;
	streamVariantIn(in, listableVariant);
	list.fillWithVariant(listableVariant.toList());
	return in;
}
/*
/// @fn QDataStream & jsonStreamingOut(QDataStream & out, const ReynTweetsListable<ReynTweetsMappables> & list);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param list Object to put in the stream
/// @return The stream with the object
template <>
QDataStream & jsonStreamingOut(QDataStream & out, const ReynTweetsListable<ReynTweetsMappable> & list);

/// @fn QDataStream & jsonStreamingIn(QDataStream & in, ReynTweetsListable<S> & list);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param list Object to put in the stream
/// @return The stream with the object
template <>
QDataStream & jsonStreamingIn(QDataStream & in, ReynTweetsListable<ReynTweetsMappable> & list);
//*/
