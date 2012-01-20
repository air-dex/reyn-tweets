/// @file timeline.hpp
/// @brief Header of Timeline
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

#ifndef TIMELINE_HPP
#define TIMELINE_HPP

#include <QVariant>
#include "tweet.hpp"
#include "reyntweetsserializablelist.tpp"


/// @typedef ReynTweetsSerializableList<Tweet> Timeline;
/// @brief Definition of a timeline : a list of tweets.
typedef ReynTweetsListable<Tweet> Timeline;

Q_DECLARE_METATYPE(Timeline)

template <>
void systemDeclaration<Tweet>();

#endif // TIMELINE_HPP
