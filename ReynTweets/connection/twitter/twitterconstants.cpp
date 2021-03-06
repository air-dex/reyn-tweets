/// @file twitterconstants.cpp
/// @brief Implementation for Reyn Tweets constants related to Twitter.
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

#include "twitterconstants.hpp"

#include "../common/utils/librtconstants.hpp"

// Fake tweet ID
const qlonglong Twitter::FAKE_TWEET_ID = LibRT::FAKE_ID;

// Fake user ID
const qlonglong Twitter::FAKE_USER_ID = LibRT::FAKE_ID;

// Default number of tweets retrieved per call (20).
const int Twitter::DEFAULT_TWEETS_COUNT = 20;

// Maximum number of tweets that can be retrieved per call (200).
const int Twitter::MAX_TWEETS_COUNT = 200;

// Fake Twitter screen name (empty string)
const QString Twitter::FAKE_SCREEN_NAME = LibRT::FAKE_STRING_ID;

// Fake Twitter place ID
const QString Twitter::FAKE_PLACE_ID = LibRT::FAKE_STRING_ID;

// Twitter API error codes
const QList<LibRT::HTTPCode> Twitter::TWITTER_ERROR_CODES;

// Inits TWITTER_ERROR_CODES
const QList<LibRT::HTTPCode> initTwitterErrorCodes() {
	QList<LibRT::HTTPCode> res;

	res.append(LibRT::NOT_MODIFIED);
	res.append(LibRT::BAD_REQUEST);
	res.append(LibRT::UNAUTHORIZED);
	res.append(LibRT::FORBIDDEN);
	res.append(LibRT::NOT_FOUND);
	res.append(LibRT::NOT_ACCEPTABLE);
	res.append(LibRT::GONE);
	res.append(LibRT::ENHANCE_YOUR_CALM);
	res.append(LibRT::UNPROCESSABLLE_ENTITY);
	res.append(LibRT::TOO_MANY_REQUESTS);
	res.append(LibRT::INTERNAL_SERVER_ERROR);
	res.append(LibRT::BAD_GATEWAY);
	res.append(LibRT::SERVICE_UNAVAILABLE);
	res.append(LibRT::GATEWAY_TIMEOUT);

	return res;
}
