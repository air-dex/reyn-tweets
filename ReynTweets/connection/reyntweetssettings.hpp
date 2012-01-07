/// @file reyntweetssettings.hpp
/// @brief Declaration of the ReynTweetsSettings namespace
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

#ifndef REYNTWEETSSETTINGS_HPP
#define REYNTWEETSSETTINGS_HPP

#include <QString>

/// @namespace ReynTweetsSettings
/// @brief Namespace with Reyn Tweets settings for OAuth
namespace ReynTweetsSettings {
	/// @brief Reyn Tweets' consumer key
	extern QByteArray CONSUMER_KEY;

	/// @brief Reyn Tweets' consumer secret
	extern QByteArray CONSUMER_SECRET;

	/// @brief Reyn Tweets' callback URL
	extern QString CALLBACK_URL;
}

#endif // REYNTWEETSSETTINGS_HPP
