/// @file place.hpp
/// @brief Header of Place
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

#ifndef PLACE_HPP
#define PLACE_HPP

#include "../json/jsonobject.hpp"

/// @class Place
/// @brief Class for representing a random place in the world
class Place : public JsonObject
{
		Q_OBJECT
	public:
		explicit Place(QObject *parent = 0);

	signals:

	public slots:

};

#endif // PLACE_HPP
