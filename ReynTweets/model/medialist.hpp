/// @file medialist.hpp
/// @brief Header of Medialist
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

#ifndef MEDIALIST_HPP
#define MEDIALIST_HPP

#include <QVariant>
#include "media.hpp"
#include "reyntweetsserializablelist.hpp"


/// @typedef ReynTweetsListable<Media> MediaList;
/// @brief Shortcut for lists of Media objects
typedef ReynTweetsListable<Media> MediaList;

Q_DECLARE_METATYPE(MediaList)

void MediaList::initSystem();

#endif // MEDIALIST_HPP
