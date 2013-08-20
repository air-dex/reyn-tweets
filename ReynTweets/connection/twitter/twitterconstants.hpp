/// @file twitterconstants.hpp
/// @brief Header for Reyn Tweets constants related to Twitter.
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

#ifndef TWITTERCONSTANTS_HPP
#define TWITTERCONSTANTS_HPP

#include <QString>

namespace Twitter {
	/// @brief Constant for a fake Tweet ID (-1)
	extern const qlonglong FAKE_TWEET_ID;

	/// @brief Constant for a fake Tweet ID (-1)
	extern const qlonglong FAKE_USER_ID;

	/// @brief Default number of tweets retrieved per call (20).
	extern const int DEFAULT_TWEETS_COUNT;

	/// @brief Maximum number of tweets that can be retrieved per call (200).
	extern const int MAX_TWEETS_COUNT;

	/// @brief Constant for a fake Twitter screen name (empty string)
	extern const QString FAKE_SCREEN_NAME;

	/// @brief Fake Twitter place ID
	extern const QString FAKE_PLACE_ID;
}

#endif // TWITTERCONSTANTS_HPP
