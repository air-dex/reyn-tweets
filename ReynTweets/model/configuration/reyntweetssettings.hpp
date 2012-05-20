/// @file reyntweetssettings.hpp
/// @brief Declaration of the ReynTweetsSettings namespace
///
/// Revisions older than r242 were in /trunk/ReynTweets/connection
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011 Romain Ducher
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

#ifndef REYNTWEETSSETTINGS_HPP
#define REYNTWEETSSETTINGS_HPP

#include <QDataStream>
#include <QString>
#include <QVariant>
#include "../../logic/coreresult.hpp"
#include "../reyntweetsmappable.hpp"

///// @namespace ReynTweetsSettings
///// @brief Namespace with Reyn Tweets settings.
/////
///// The settings are keys, constants and passwords for the following APIs or
///// services :<ul>
///// <li><a href="https://dev.twitter.com/">Twitter API</a></li>
///// <li><a href="http://www.twitlonger.com">TwitLonger</a></li>
///// <li><a href="http://getpocket.com">Pocket</a></li>
///// <li>More to come...</li>
///// <ul>
//namespace ReynTweetsSettings {
//	/////////////////////////
//	// Settings management //
//	/////////////////////////

//	/// @fn CoreResult loadSettings();
//	/// @brief Loading the settings from the settings file.
//	QVariantMap loadSettings();

//	/// @brief Name of the file containing the settings
//	extern QString SETTINGS_NAMEFILE;

//	extern QVariantMap settingsMap;


//	//////////////////////////////
//	// Twitter Settings (OAuth) //
//	//////////////////////////////

//	/// @brief Twitter OAuth consumer key.
//	extern QByteArray CONSUMER_KEY;

//	/// @brief Twitter OAuth consumer secret.
//	extern QByteArray CONSUMER_SECRET;

//	/// @brief Twitter callback URL
//	extern QString CALLBACK_URL;


//	////////////////
//	// TwitLonger //
//	////////////////

//	/// @brief Name of Reyn Tweets in the TwitLonger API
//	extern QString TWITLONGER_APP_NAME;

//	/// @brief TwitLonger API key.
//	extern QByteArray TWITLONGER_API_KEY;


//	////////////////////////////////////////////////
//	// Pocket (formerly known as "Read It Later") //
//	////////////////////////////////////////////////

//	/// @brief Pocket API key.
//	extern QByteArray POCKET_API_KEY;
//}

/// @class ReynTweetsSettings
/// @brief Namespace with Reyn Tweets settings.
///
/// The settings are keys, constants and passwords for the following APIs or
/// services :<ul>
/// <li><a href="https://dev.twitter.com/">Twitter API</a></li>
/// <li><a href="http://www.twitlonger.com">TwitLonger</a></li>
/// <li><a href="http://getpocket.com">Pocket</a></li>
/// <li>More to come...</li>
/// <ul>
class ReynTweetsSettings {

	public:
		static ReynTweetsSettings & getInstance() {
			if (!instance) {
				instance = new ReynTweetsSettings;
			}

			return *instance;
		}

		static ReynTweetsSettings * instance;

		ReynTweetsSettings() {
			loadSettings();
		}

	/////////////////////////
	// Settings management //
	/////////////////////////

	/// @fn CoreResult loadSettings();
	/// @brief Loading the settings from the settings file.
	CoreResult loadSettings();

	/// @brief Name of the file containing the settings
	static QString SETTINGS_NAMEFILE;

	QVariantMap settingsMap;


	//////////////////////////////
	// Twitter Settings (OAuth) //
	//////////////////////////////

	/// @brief Twitter OAuth consumer key.
	QByteArray CONSUMER_KEY;

	/// @brief Twitter OAuth consumer secret.
	QByteArray CONSUMER_SECRET;

	/// @brief Twitter callback URL
	QString CALLBACK_URL;


	////////////////
	// TwitLonger //
	////////////////

	/// @brief Name of Reyn Tweets in the TwitLonger API
	QString TWITLONGER_APP_NAME;

	/// @brief TwitLonger API key.
	QByteArray TWITLONGER_API_KEY;


	////////////////////////////////////////////////
	// Pocket (formerly known as "Read It Later") //
	////////////////////////////////////////////////

	/// @brief Pocket API key.
	QByteArray POCKET_API_KEY;
};

#endif // REYNTWEETSSETTINGS_HPP
