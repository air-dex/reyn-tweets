/// @file variantable.hpp
/// @brief Header of Variantable
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

/// @class Variantable
/// @brief Base class for objects that needs to be easily initialized with
/// objects whose type is V (template parameter) and needs to be easily
/// converted into objects whose type is the template parameter.
///
/// In Reyn Tweets, lots of classes needs a given type of object to be
/// intialized. For example, the Twitter API gives its results in JSON format so
/// the corresponding core objects (tweets, timelines, users...) needs to be
/// initialized with JSON objects or arrays (QJsonObject and QJsonArray Qt JSON
/// classes). Core objects which needs JSON objects will inherit for
/// Variantable<QJsonObject> and Variantable<QJsonArray> will be inherited by
/// core objects which needs JSON Arrays to be initialized.
///
/// Moreover, these same objects initialized by an object whose type is V often
/// needs to be convertible into this kind of "V object". Let's keep on the
/// example with core objects initialized by JSON entities. They may be part of
/// other core objects which needs to be convertible into JSON objects (or
/// arrays). QML might need a JSON version of these core objects too. That's why
/// Variantables need to be easily converted in the same type of the entities
/// they use to be initialized (QJsonObject and QJsonArray in the example).
/// @param V Type of "corresponding object" (QJsonObject or QJsonArray in the
/// description example with core objects and JSON entities).
template <typename V>
class Variantable {
	public:
		/// @fn virtual V toVariant() const = 0;
		/// @brief Converting the Variantable into its V equivalent.
		/// @return The corresponding equivalent.
		virtual V toVariant() const = 0;

		/// @fn virtual void fillWithVariant(V map) = 0;
		/// @brief Filling a Variantable object with a "V" equivalent.
		/// contained in the map.
		/// @param map The equivalent
		virtual void fillWithVariant(V map) = 0;

		//operator V () const { return this->toVariant(); }
};

#endif // VARIANTABLE_HPP
