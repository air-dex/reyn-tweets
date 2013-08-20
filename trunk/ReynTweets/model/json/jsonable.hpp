/// @file jsonable.hpp
/// @brief Header of Jsonable
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

#ifndef JSONABLE_HPP
#define JSONABLE_HPP

#include <QDataStream>

/// @class Jsonable
/// @brief Interface for objects that can be serialized under a JSON form.
/// @param J Name of a Qt JSON class which can handle JSON for the Jsonable.
///
/// Most of the time J is a QJsonObject or a QJsonArray.
template <typename J>
class Jsonable
{
	public:
		/// @fn virtual J toJSON() const = 0;
		/// @brief Converting the object into its "JSON handler" equivalent.
		/// @return The corresponding equivalent.
		virtual J toJSON() const = 0;

		/// @fn virtual void fillWithJSON(J json) = 0;
		/// @brief Filling a Jsonable object with a "JSON handler" equivalent.
		/// contained in the map.
		/// @param json The equivalent
		virtual void fillWithJSON(J json) = 0;

		/// @fn virtual QDataStream & fillWithStream(QDataStream & in) = 0;
		/// @brief Filling the Jsonable with the content of a QDataStream
		/// @param in The stream
		/// @return The stream after being read.
		virtual QDataStream & fillWithStream(QDataStream & in) = 0;

		/// @fn virtual QDataStream & writeInStream(QDataStream & out) const = 0;
		/// @brief Writing a QDataStream with the content of the Jsonable
		/// @param out The stream
		/// @return The stream after being written.
		virtual QDataStream & writeInStream(QDataStream & out) const = 0;

};

#endif // JSONABLE_HPP
