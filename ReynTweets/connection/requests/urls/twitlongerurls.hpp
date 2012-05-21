/// @file twitlongerurls.hpp
/// @brief Declaration of the TwitLongerURL namespace.
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

#ifndef TWITLONGERURLS_HPP
#define TWITLONGERURLS_HPP

#include <QString>

/// @namespace TwitLongerURL
/// @brief Namespace containing all the TwitLonger API URLs.
namespace TwitLongerURL
{
	/// @brief URL for posting the long messages to TwitLonger
	extern QString POST_LONG_TWEET_URL;

	/// @brief URL for updating informations about the long message
	extern QString UPDATE_LONG_TWEET_URL;

	/// @brief URL for reading the long message
	extern QString READ_TWEET_URL;
}

#endif // TWITLONGERURLS_HPP
