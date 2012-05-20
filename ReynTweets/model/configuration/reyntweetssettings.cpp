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
#include <QObject>
#include "reyntweetssettings.hpp"
#include "../../tools/parsers/jsonparser.hpp"

////////////////////
// Static members //
////////////////////

// Unique instance
ReynTweetsSettings * ReynTweetsSettings::instance = 0;

// Name of the file containing the settings
QString ReynTweetsSettings::SETTINGS_NAMEFILE = "./conf/ReynTweetsSettings.conf";


/////////////////////
// Core management //
/////////////////////

// Private constructor
ReynTweetsSettings::ReynTweetsSettings() :
	loadResult(INVALID_ISSUE),
	errorLoading("")
{
	loadSettings();
}

// Getting a reference on the unique instance.
ReynTweetsSettings & ReynTweetsSettings::getInstance() {
	if (!instance) {
		instance = new ReynTweetsSettings;
	}

	return *instance;
}

// Loading the settings from the settings file.
void ReynTweetsSettings::loadSettings() {
	// Opening the settings file
	QFile confFile(ReynTweetsSettings::SETTINGS_NAMEFILE);

	if (!confFile.exists()) {
		errorLoading = QObject::trUtf8("Settings file unknown.");
		loadResult = CONFIGURATION_FILE_UNKNOWN;
		return;
	}

	bool openOK = confFile.open(QFile::ReadOnly);
	if (!openOK) {
		errorLoading = QObject::trUtf8("Cannot open the settings file.");
		loadResult = CONFIGURATION_FILE_NOT_OPEN;
		return;
	}


	// Parsing datas
	bool parseOK = false;
	JSONParser parser;
	QVariant jsonSettings = parser.parse(confFile.readAll(),
										 parseOK,
										 errorLoading);

	if (!parseOK) {
		loadResult = PARSE_ERROR;
		return;
	}


	// Filling the settings

	QString errorFilling = QObject::trUtf8("The following setting(s) are missing: ");
	bool allSettingsOK = true;
	bool settingOK;
	QStringList missingKeys;
	QVariantMap map = jsonSettings.toMap();

	// Twitter OAuth consumer key
	settingOK = detectSetting(map, "consumer_key", missingKeys);
	if (settingOK) {
		CONSUMER_KEY = QByteArray::fromBase64(map.value("consumer_key").toByteArray());
	}
	allSettingsOK = allSettingsOK && settingOK;

	// Twitter OAuth consumer secret
	settingOK = detectSetting(map, "consumer_secret", missingKeys);
	if (settingOK) {
		CONSUMER_SECRET = QByteArray::fromBase64(map.value("consumer_secret").toByteArray());
	}
	allSettingsOK = allSettingsOK && settingOK;

	// Twitter callback URL
	settingOK = detectSetting(map, "callback_url", missingKeys);
	if (settingOK) {
		CALLBACK_URL = QString::fromUtf8(map.value("callback_url").toByteArray());
	}
	allSettingsOK = allSettingsOK && settingOK;

	// TwitLonger application name
	settingOK = detectSetting(map, "twitlonger_application_name", missingKeys);
	if (settingOK) {
		TWITLONGER_APP_NAME = QString::fromUtf8(map.value("twitlonger_application_name").toByteArray());
	}
	allSettingsOK = allSettingsOK && settingOK;

	// TwitLonger API Key
	settingOK = detectSetting(map, "twitlonger_api_key", missingKeys);
	if (settingOK) {
		TWITLONGER_API_KEY = QByteArray::fromBase64(map.value("twitlonger_api_key").toByteArray());
	}
	allSettingsOK = allSettingsOK && settingOK;

	// Pocket API Key
	settingOK = detectSetting(map, "pocket_api_key", missingKeys);
	if (settingOK) {
		POCKET_API_KEY = QByteArray::fromBase64(map.value("pocket_api_key").toByteArray());
	}
	allSettingsOK = allSettingsOK && settingOK;

	if (allSettingsOK) {
		loadResult = LOAD_CONFIGURATION_SUCCESSFUL;
	} else {
		if (missingKeys.size() > 0) {
			errorFilling.append(missingKeys.join(", "));
		} else {
			errorFilling.append(QObject::trUtf8("no one"));
		}

		errorFilling.append('.');
		errorLoading.append(errorFilling);
		loadResult = EXPECTED_KEY;
	}
}

// Detecting if an application setting is here or not
bool ReynTweetsSettings::detectSetting(QVariantMap settingsMap,
									   const char * settingKey,
									   QStringList & missingKeys)
{
	bool containsKey = settingsMap.contains(settingKey);

	if (!containsKey) {
		missingKeys.append(settingKey);
	}

	return containsKey;
}


////////////////////////
// Getter on settings //
////////////////////////

// Getter on the loading result
CoreResult ReynTweetsSettings::getLoadResult() {
	return loadResult;
}

// Getter on the error message after loading the settings
QString ReynTweetsSettings::getErrorLoading() {
	return errorLoading;
}

// Getter on the Twitter OAuth consumer key.
QByteArray ReynTweetsSettings::getConsumerKey() {
	return CONSUMER_KEY;
}

// Getter on the Twitter OAuth consumer secret.
QByteArray ReynTweetsSettings::getConsumerSecret() {
	return CONSUMER_SECRET;
}

// Getter on the Twitter callback URL.
QString ReynTweetsSettings::getCallbackURL() {
	return CALLBACK_URL;
}

// Getter on the TwitLonger application name.
QString ReynTweetsSettings::getTwitLongerAppName() {
	return TWITLONGER_APP_NAME;
}

// Getter on the TwitLonger API key.
QByteArray ReynTweetsSettings::getTwitLongerAPIKey() {
	return TWITLONGER_API_KEY;
}

// Getter on the Pocket API key.
QByteArray ReynTweetsSettings::getPocketAPIKey() {
	return POCKET_API_KEY;
}
