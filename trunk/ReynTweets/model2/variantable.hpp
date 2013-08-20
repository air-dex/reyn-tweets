/// @file variantable.hpp
/// @brief Header of ReynTweetsSerializable
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

#ifndef VARIANTABLE_HPP
#define VARIANTABLE_HPP

#include <QVariant>

/// @class Variantable
/// @brief Class for objects that needs to be converted into Variant Objects
/// (such as QVariantMap or QVariantList).
/// @param V Type of Variant class (such as QVariantMap or QVariantList).
template <typename V>
class Variantable
{
	public:
		/// @fn virtual V toVariant() const = 0;
		/// @brief Converting the object into its equivalent.
		/// @return The corresponding equivalent.
		virtual V toVariant() const = 0;

		/// @fn virtual void fillWithVariant(V map) = 0;
		/// @brief Filling a ReynTweetsSerializable object with an equivalent.
		/// contained in the map.
		/// @param map The equivalent
		virtual void fillWithVariant(V map) = 0;
};

#endif // VARIANTABLE_HPP