/// @file reyntweetssettings.cpp
/// @brief Values of ReynTweetsSettings namespace.
/// @author Romain Ducher

/*
Copyright 2011 Romain Ducher

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
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "reyntweetssettings.hpp"

// Consumer key
QByteArray ReynTweetsSettings::CONSUMER_KEY = "WUlUMzFFNGE4N29CVFdqeURlUnc=";

// Reyn Tweets' consumer secret
QByteArray ReynTweetsSettings::CONSUMER_SECRET = "dzk3enV0UEpnNkZ6dFZleTNXNkVicG52N0x2MWZtNEVUWGpsbzZFeVQw";

// Reyn Tweets' callback URL. QString::fromUtf8(); is used to avoid problem with character conversion.
QString ReynTweetsSettings::CALLBACK_URL = QString::fromUtf8("http://twitter.com");
