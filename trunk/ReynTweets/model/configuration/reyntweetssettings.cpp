/// @file reyntweetssettings.cpp
/// @brief Values of ReynTweetsSettings namespace.
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


#include <QFile>
#include <QJson/Parser>
#include <QJson/Serializer>
#include "reyntweetssettings.hpp"


////////////////////////////////
//// Twitter Settings (OAuth) //
////////////////////////////////

//// Consumer key
//QByteArray ReynTweetsSettings::CONSUMER_KEY = "";

//// Reyn Tweets' consumer secret
//QByteArray ReynTweetsSettings::CONSUMER_SECRET = "";

//// Reyn Tweets' callback URL. QString::fromUtf8(); is used to avoid problem with character conversion.
//QString ReynTweetsSettings::CALLBACK_URL = "";


//////////////////
//// TwitLonger //
//////////////////

///// @brief Name of Reyn Tweets in the TwitLonger API
//QString ReynTweetsSettings::TWITLONGER_APP_NAME = "";

///// @brief TwitLonger API key.
//QByteArray ReynTweetsSettings::TWITLONGER_API_KEY = "";


//////////////////////////////////////////////////
//// Pocket (formerly known as "Read It Later") //
//////////////////////////////////////////////////

///// @brief Pocket API key.
//QByteArray ReynTweetsSettings::POCKET_API_KEY = "";


////////////////////////
// Loading management //
////////////////////////
ReynTweetsSettings * ReynTweetsSettings::instance = 0;
// Name of the file containing the settings
QString ReynTweetsSettings::SETTINGS_NAMEFILE = "./conf/ReynTweetsSettings.conf";

// Loading the settings from the settings file.
CoreResult ReynTweetsSettings::loadSettings() {
	// Opening the settings file
	QFile confFile(ReynTweetsSettings::SETTINGS_NAMEFILE);

	if (!confFile.exists()) {
		return CONFIGURATION_FILE_UNKNOWN;
	}

	bool openOK = confFile.open(QFile::ReadOnly);
	if (!openOK) {
		return CONFIGURATION_FILE_NOT_OPEN;
	}

	QJson::Parser parser;
	QVariant jsonSettings = parser.parse(&confFile);

	QByteArray * b;
	QString * s;

	QVariantMap map = jsonSettings.toMap();

	CONSUMER_KEY = QByteArray::fromBase64(map.value("consumer_key").toByteArray());

	CONSUMER_SECRET = QByteArray::fromBase64(map.value("consumer_secret").toByteArray());

	CALLBACK_URL = QString::fromUtf8(map.value("callback_url").toByteArray());

	TWITLONGER_APP_NAME = QString::fromUtf8(map.value("twitlonger_application_name").toByteArray());

	TWITLONGER_API_KEY = QByteArray::fromBase64(map.value("twitlonger_api_key").toByteArray());

	POCKET_API_KEY = QByteArray::fromBase64(map.value("pocket_api_key").toByteArray());

	qDebug("Settings ok");

	return LOAD_CONFIGURATION_SUCCESSFUL;
}
