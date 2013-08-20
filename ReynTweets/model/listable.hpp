/// @file listable.hpp
/// @brief Header of Listable
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

#ifndef LISTABLE_HPP
#define LISTABLE_HPP

#include <QList>
#include <QVariant>
#include "variantable.hpp"

/// @class Listable
/// @brief Class for objects that needs to be converted into a QVariantList.
///
/// These objects have to be convertible into a QVariant. So most of the time
/// they will be Variantables (and Mappables too).
/// @param V Type of the objects which composed the list.
template <typename V>
class Listable : public Variantable<QVariantList>, public QList<V>
{
	public:
		/// @fn Listable();
		/// @brief Constructor
		Listable();

		/// @fn virtual ~Listable();
		/// @brief Destructor
		virtual ~Listable();

		/// @fn Listable(const Listable<V> & list);
		/// @brief Copy constructor
		/// @param list Listable to copy
		Listable(const Listable<V> & list);

		/// @fn const Listable & operator=(const Listable<V> & list);
		/// @brief Affrection operator
		/// @param list Listable to affect
		const Listable<V> & operator=(const Listable<V> & list);

		////////////////////////
		// Variant conversion //
		////////////////////////

		/// @fn virtual void fillWithVariant(QVariantList entities);
		/// @brief Filling the list with the content of a QVariantList
		/// @param entities The QVariantList
		virtual void fillWithVariant(QVariantList entities);

		/// @fn virtual QVariantList toVariant() const;
		/// @brief Converting the list of serializables into a QVariantList.
		/// @return The corresponding QVariantList.
		virtual QVariantList toVariant() const;

	protected:
		/// @fn virtual void recopie(const Listable<S> & list);
		/// @brief Copy of a Listable
		/// @param list Listable to copy
		virtual void recopie(const Listable<V> &list);
};

#endif // LISTABLE_HPP