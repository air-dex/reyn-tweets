/// @file reyntweetsutils.cpp
/// @brief Implementation of utilities for the logic part
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

#include "reyntweetsutils.hpp"
#include "../connection/common/utils/librtconstants.hpp"
#include "../connection/twitter/twitterconstants.hpp"

// Converting a bool into a QString
QString ReynTweets::boolInString(bool b) {
	return b ? "true" : "false";
}

// Converting a String into a QColor.
QColor ReynTweets::string2color(QString coloredString) {
	// Add a '#' at the beginning if not present
	static QChar sharp('#');
	if (!coloredString.startsWith(sharp)) {
		coloredString.prepend(sharp);
	}

	return QColor(coloredString);
}


///////////////
// Constants //
///////////////

// Constant for a fake Tweet ID
const qlonglong ReynTweets::FAKE_TWEET_ID = Twitter::FAKE_TWEET_ID;

// Constant for a fake Tweet ID (QString version)
const QString ReynTweets::FAKE_TWEET_ID_STR = QString::number(Twitter::FAKE_TWEET_ID);

// Constant for a fake Tweet ID
const qlonglong ReynTweets::FAKE_USER_ID = Twitter::FAKE_USER_ID;

// Constant for a fake Tweet ID (QString version)
const QString ReynTweets::FAKE_USER_ID_STR = QString::number(Twitter::FAKE_USER_ID);

// Constant for a fake Media ID
const qlonglong ReynTweets::FAKE_MEDIA_ID = LibRT::FAKE_ID;

// Constant for a fake Media ID (QString version)
const QString ReynTweets::FAKE_MEDIA_ID_STR = QString::number(LibRT::FAKE_ID);

// Fake longitude
const int ReynTweets::FAKE_LONGITUDE = LibRT::FAKE_LONGITUDE;

// Fake latitude
const int ReynTweets::FAKE_LATITUDE = LibRT::FAKE_LATITUDE;

// Fake index in an array
const int ReynTweets::FAKE_BOUND = -1;

// Default number of tweets retrieved per call (20).
const int ReynTweets::DEFAULT_TWEETS_COUNT = Twitter::DEFAULT_TWEETS_COUNT;

// Maximum number of tweets that can be retrieved per call (200).
const int ReynTweets::MAX_TWEETS_COUNT = Twitter::MAX_TWEETS_COUNT;
