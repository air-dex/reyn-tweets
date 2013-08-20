/// @file twitlongerurls.cpp
/// @brief Implementation of the TwitLonger namespace part containing
/// TwitLonger URLs.
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

#include "twitlongerurls.hpp"

// NB : QString::fromUtf8(); is used to avoid problem with character conversion.

// Posting the long messages to TwitLonger
QString TwitLonger::POST_LONG_TWEET_URL = QString::fromUtf8("http://www.twitlonger.com/api_post");

// Updating informations about the long message
QString TwitLonger::UPDATE_LONG_TWEET_URL = QString::fromUtf8("http://www.twitlonger.com/api_set_id");

// Reading the long message
QString TwitLonger::READ_TWEET_URL = QString::fromUtf8("http://www.twitlonger.com/api_read/message_id");
