/// @file reyntweetslistable.hpp
/// @brief Header of ReynTweetsListable
/// @author Romain Ducher

/*
Copyright 2012 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef REYNTWEETSLISTABLE_HPP
#define REYNTWEETSLISTABLE_HPP

#include <QList>
#include <QVariant>
#include "reyntweetsserializable.hpp"
#include "reyntweetsmappable.hpp"

/// @class ReynTweetsListable
/// @brief Class for object that needs to be converted into a QVariantList.
///
/// In practice, these objects will be lists of ReynTweetsSerializable objects
/// whose type is represented by the template type S.
/// @param S Type of a ReynTweetsSerializable object.
template <class S>
class ReynTweetsListable : public ReynTweetsSerializable<QVariantList>, public QList<S>
{
	public:
		/// @fn ReynTweetsListable();
		/// @brief Constructor
		ReynTweetsListable();

		/// @fn virtual ~ReynTweetsListable();
		/// @brief Destructor
		virtual ~ReynTweetsListable();

		/// @fn ReynTweetsListable(const ReynTweetsListable & list);
		/// @brief Copy constructor
		/// @param list ReynTweetsSerializableList to copy
		ReynTweetsListable(const ReynTweetsListable<S> & list);

		/// @fn const ReynTweetsListable & operator=(const ReynTweetsListable & list);
		/// @brief Affrection operator
		/// @param list ReynTweetsListable to affect
		const ReynTweetsListable & operator=(const ReynTweetsListable<S> & list);

		/// @fn virtual void fillWithVariant(QVariantList entities);
		/// @brief Filling the list with the contentnt of a QVariantList
		/// @param entities The QVariantList
		virtual void fillWithVariant(QVariantList entities);

		/// @fn virtual QVariantList toVariant() const;
		/// @brief Converting the list of serializables into a QVariantList.
		/// @return The corresponding QVariantList.
		virtual QVariantList toVariant() const;

	protected:
		/// @fn virtual void recopie(const ReynTweetsListable<S> & list);
		/// @brief Copy of a ReynTweetsListable
		/// @param list ReynTweetsListable to copy
		virtual void recopie(const ReynTweetsListable<S> &list);
};

/////////////
// Streams //
/////////////

/// @fn QDataStream & jsonStreamingOut(QDataStream & out, const ReynTweetsListable<S> & list);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param list Object to put in the stream
/// @return The stream with the object
template <class S>
QDataStream & jsonStreamingOut(QDataStream & out, const ReynTweetsListable<S> & list);

/// @fn QDataStream & jsonStreamingIn(QDataStream & in, ReynTweetsListable<S> & list);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param list Object to put in the stream
/// @return The stream with the object
template <class S>
QDataStream & jsonStreamingIn(QDataStream & in, ReynTweetsListable<S> & list);

#endif // REYNTWEETSLISTABLE_HPP
