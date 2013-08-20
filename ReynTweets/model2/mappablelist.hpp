/// @file mappablelist.hpp
/// @brief Header of MappableList
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

#ifndef MAPPABLELIST_HPP
#define MAPPABLELIST_HPP

#include "listable.tpp"
#include "mappable.hpp"

/// @class MappableList
/// @brief Listable which is a list of Mappables.
class MappableList : public Listable<Mappable>
{
	public:
		/// @fn MappableList();
		/// @brief Constructor
		MappableList();

		/// @fn virtual ~MappableList();
		/// @brief Destructor
		virtual ~MappableList();

		/// @fn MappableList(const MappableList & list);
		/// @brief Copy constructor
		/// @param list MappableList to copy
		MappableList(const MappableList & list);

		/// @fn const MappableList & operator=(const MappableList & list);
		/// @brief Affrection operator
		/// @param list MappableList to affect
		const MappableList & operator=(const MappableList & list);

		/// @fn virtual void fillWithVariant(QVariantList entities);
		/// @brief Filling the list with the contentnt of a QVariantList
		/// @param entities The QVariantList
		virtual void fillWithVariant(QVariantList entities);

		/// @fn virtual QVariantList toVariant() const;
		/// @brief Converting the list of serializables into a QVariantList.
		/// @return The corresponding QVariantList.
		virtual QVariantList toVariant() const;
/*
	protected:
		/// @fn virtual void recopie(const MappableList & list);
		/// @brief Copy of a MappableList
		/// @param list MappableList to copy
		virtual void recopie(const MappableList &list);
//*/
};

/////////////
// Streams //
/////////////

/// @fn QDataStream & jsonStreamingOut(QDataStream & out, MappableList & list);
/// @brief Output stream operator for serialization
/// @param out The output stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & jsonStreamingOut(QDataStream & out, const MappableList & list);

/// @fn QDataStream & jsonStreamingIn(QDataStream & in, MappableList & list);
/// @brief Input stream operator for serialization
/// @param in The input stream
/// @param list Object to put in the stream
/// @return The stream with the object
QDataStream & jsonStreamingIn(QDataStream & in, MappableList & list);

#endif // MAPPABLELIST_HPP
