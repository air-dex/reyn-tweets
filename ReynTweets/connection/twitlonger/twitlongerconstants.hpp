/// @file twitlongerconstants.hpp
/// @brief Implementation for Reyn Tweets constants related to TwitLonger.
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

#ifndef TWITLONGERCONSTANTS_HPP
#define TWITLONGERCONSTANTS_HPP

#include <QString>

namespace TwitLonger {
	/// @brief Constant for a fake Tweet ID
	extern const qlonglong FAKE_TWEET_ID;

	/// @brief Fake TwitLonger message ID
	extern const QString FAKE_MESSAGE_ID;

	/// @brief Constant for a fake Twitter screen name (empty string)
	extern const QString FAKE_SCREEN_NAME;
}

#endif // TWITLONGERCONSTANTS_HPP
