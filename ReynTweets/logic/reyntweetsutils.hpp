/// @file reyntweetsutils.cpp
/// @brief Header of utilities for the logic part
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

#ifndef REYNTWEETSUTILS_HPP
#define REYNTWEETSUTILS_HPP

#include <QColor>
#include <QString>

namespace ReynTweets {
	/// @fn QString boolInString(bool b);
	/// @brief Converting a bool into a QString
	/// @param b The boolean
	/// @return The corresponding QString
	QString boolInString(bool b);

	/// @fn QColor string2color(QString coloredString);
	/// @brief Converting a String into a QColor.
	///
	/// This function was written because of Twitter which forgets the '#'
	/// character before the hexadecimal code under the form 'RRGGBB'.
	/// @param coloredString The string with the RRGGBB format.
	/// @return The corresponding color : &#135;RRGGBB
	QColor string2color(QString coloredString);

	///////////////
	// Constants //
	///////////////

	/// @brief Constant for a fake Tweet ID
	extern const qlonglong FAKE_TWEET_ID;

	/// @brief Constant for a fake Tweet ID (QString version)
	extern const QString FAKE_TWEET_ID_STR;

	/// @brief Constant for a fake Tweet ID
	extern const qlonglong FAKE_USER_ID;

	/// @brief Constant for a fake Tweet ID (QString version)
	extern const QString FAKE_USER_ID_STR;

	/// @brief Constant for a fake Media ID
	extern const qlonglong FAKE_MEDIA_ID;

	/// @brief Constant for a fake Media ID (QString version)
	extern const QString FAKE_MEDIA_ID_STR;

	/// @brief Fake longitude
	extern const float FAKE_LONGITUDE;

	/// @brief Fake latitude
	extern const float FAKE_LATITUDE;

	/// @brief Maximum absolute value for a longitude (180 since a valid
	/// longitude is between -180 and +180).
	extern const float MAX_LONGITUDE;

	/// @brief Maximum absolute value for a latitude (180 since a valid
	/// latitude is between -90 and +90).
	extern const float MAX_LATITUDE;

	/// @brief Fake index in an array
	extern const int FAKE_BOUND;

	/// @brief Default number of tweets retrieved per call (20).
	extern const int DEFAULT_TWEETS_COUNT;

	/// @brief Maximum number of tweets that can be retrieved per call (200).
	extern const int MAX_TWEETS_COUNT;

	/// @brief Fake value for a token (empty string)
	extern const QByteArray FAKE_TOKEN;

	/// @brief Fake value for an URL (empty string)
	extern const QString FAKE_URL;

	/// @brief Constant for a fake Twitter screen name (empty string)
	extern const QString FAKE_SCREEN_NAME;

	/// @brief Fake Twitter place ID
	extern const QString FAKE_PLACE_ID;

	/// @brief Name of the QML library containing all the Reyn Tweets C++
	/// classes available for pure QML objects.
	extern const QString QML_LIBRARY_NAME;

	/// @brief Reyn Tweets major version.
	extern const int MAJOR_VERSION;

	/// @brief Reyn Tweets minor version.
	extern const int MINOR_VERSION;
}

#endif // REYNTWEETSUTILS_HPP
