/// @file controls.hpp
/// @brief Header with all the processes
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
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

#ifndef CONTROLS_HPP
#define CONTROLS_HPP

// List handlers
#include "listhandlers/contributorshandler.hpp"
#include "listhandlers/geocoordhandler.hpp"
#include "listhandlers/geocoordpolygonhandler.hpp"
#include "listhandlers/hashtagshandler.hpp"
#include "listhandlers/indexboundshandler.hpp"
#include "listhandlers/mediashandler.hpp"
#include "listhandlers/mentionshandler.hpp"
#include "listhandlers/timelinehandler.hpp"
#include "listhandlers/urlshandler.hpp"

// Other controls
#include "allowcontrol.hpp"
#include "launchingcontrol.hpp"
#include "reyncontrol.hpp"
#include "settingscontrol.hpp"
#include "tweetcontrol.hpp"
#include "timelinecontrol.hpp"
#include "writetweetcontrol.hpp"

#endif // CONTROLS_HPP
