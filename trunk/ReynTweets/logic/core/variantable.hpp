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

// TODO : rewrite the @brief with new Variantables features
/// @class Variantable
/// @brief Class for objects that needs to be converted into QVariant Objects
/// (such as QVariantMap or QVariantList).
///
/// In practice, some network replies can be parsed in QVariantMaps whose keys
/// are the name of the different fields of the replies. The values corresponding
/// to the fields are stocked in QVariant objects. Complex field values are
/// stored in QVariantLists or QVariantMaps too.
///
/// But ReynTweets do not manipulate QVariantMaps with fields but complex model
/// objects with values which get a meaning, just like a tweet with a text
/// (string), an ID (number), an author. Not a QVariantMap with fields named
/// "text", "id" or "user". Informations needed by these objects are stored
/// in QVariantMaps. As a consequence, the QVariantMaps replies have to
/// be converted in these model objects.<br/>
/// Moreover, the complex model objects might need to be converted into
/// QVariant objects. It is the case when they are manipulated by QML. For this,
/// Mappables ar first converted into QVariantMaps which are then put in a
/// QVariant object.
///
/// In the complex objects, the fields of QVariantMaps are stocked in QObject
/// properties which are represented by class members. Types of the class
/// members are the type of the QVariant value of the field.
///
/// However, some properties are complex objects (ex. author of a tweet) too
/// and they are not easily handled by Qt. These fields get an equivalent
/// member (often a ReynTweetsSerializable - the class was made for them) that
/// corresponds to a QVariantList or a QVariantMap property.
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

		//operator V () const { return this->toVariant(); }
};

#endif // VARIANTABLE_HPP
