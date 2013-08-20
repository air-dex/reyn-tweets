/// @file reyntweetsconfiguration.cpp
/// @brief Implementation of ReynTweetsConfiguration
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011, 2012, 2013 Romain Ducher
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


#include <QApplication>
#include <QFile>
#include <QObject>
#include "reyntweetsconfiguration.hpp"
#include "../../tools/parsers/jsonparser.hpp"

////////////////////
// Static members //
////////////////////

// Name of the file containing the settings.
QString ReynTweetsConfiguration::SETTINGS_NAMEFILE = "./conf/ReynTweetsSettings.conf";


/////////////////////
// Core management //
/////////////////////

// Private constructor
ReynTweetsConfiguration::ReynTweetsConfiguration() :
	errorLoading("")
{}

// Loading the settings from the settings file.
CoreResult ReynTweetsConfiguration::load() {
	// Opening the settings file
	QFile confFile(SETTINGS_NAMEFILE);

	if (!confFile.exists()) {
		errorLoading = ReynTweetsConfiguration::trUtf8("Settings file unknown.");
		return  CONFIGURATION_FILE_UNKNOWN;
	}

	bool openOK = confFile.open(QFile::ReadOnly);
	if (!openOK) {
		errorLoading = ReynTweetsConfiguration::trUtf8("Cannot open the settings file.");
		return CONFIGURATION_FILE_NOT_OPEN;
	}


	// Parsing datas
	bool parseOK = false;
	JSONParser parser;
	QJsonValue jsonSettings = parser.parse(confFile.readAll(),
										   parseOK,
										   errorLoading);

	confFile.close();

	if (!jsonSettings.isObject()) {
		// Parse error : JSON Object expected
		static QString wrongJSONType = ReynTweetsConfiguration::trUtf8("Parse error : JSON object expected.");
		errorLoading.append(' ').append(wrongJSONType);
		parseOK = false;
	}

	if (!parseOK) {
		return PARSE_ERROR;
	}


	// Filling the settings

	QJsonObject jsonConf = jsonSettings.toObject();
	QString oldErr = errorLoading;

	this->fillWithJSON(jsonConf);

	bool fillOK = oldErr == errorLoading;	// More errors if it fails.

	return fillOK ? LOAD_CONFIGURATION_SUCCESSFUL : EXPECTED_KEY;
}

// Getter on the error message after loading the settings
QString ReynTweetsConfiguration::getErrorLoading() {
	return errorLoading;
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void ReynTweetsConfiguration::fillWithJSON(QJsonObject json) {
	QJsonValue confValue;
	QByteArray base64Buffer;
	QStringList missingSettings;

	// consumer_key
	confValue = json.value(CONSUMER_KEY_PN);

	if (!confValue.isUndefined() && confValue.isString()) {
		// Right value : fill the setting
		base64Buffer = confValue.toString().toLatin1();
		this->consumerKey = QByteArray::fromBase64(base64Buffer);
	} else {
		// Wrong value : error
		missingSettings.append(CONSUMER_KEY_PN);
	}

	// consumer_secret
	confValue = json.value(CONSUMER_SECRET_PN);

	if (!confValue.isUndefined() && confValue.isString()) {
		// Right value : fill the setting
		base64Buffer = confValue.toString().toLatin1();
		this->consumerSecret = QByteArray::fromBase64(base64Buffer);
	} else {
		// Wrong value : error
		missingSettings.append(CONSUMER_SECRET_PN);
	}

	// callback_url
	confValue = json.value(CALLBACK_URL_PN);

	if (!confValue.isUndefined() && confValue.isString()) {
		// Right value : fill the setting
		this->callbackURL = confValue.toString();
	} else {
		// Wrong value : error
		missingSettings.append(CALLBACK_URL_PN);
	}

	// twitLonger_app_name
	confValue = json.value(TWITLONGER_APP_NAME_PN);

	if (!confValue.isUndefined() && confValue.isString()) {
		// Right value : fill the setting
		this->twitlongerAppName = confValue.toString();
	} else {
		// Wrong value : error
		missingSettings.append(TWITLONGER_APP_NAME_PN);
	}

	// twitlonger_api_key
	confValue = json.value(TWITLONGER_API_KEY_PN);

	if (!confValue.isUndefined() && confValue.isString()) {
		// Wrong value : error
		missingSettings.append(TWITLONGER_API_KEY_PN);
	} else {
		// Right value : fill the setting
		base64Buffer = confValue.toString().toLatin1();
		this->twitlongerAPIKey = QByteArray::fromBase64(base64Buffer);
	}

	// pocket_api_key
	confValue = json.value(POCKET_API_KEY_PN);

	if (!confValue.isUndefined() && confValue.isString()) {
		// Right value : fill the setting
		base64Buffer = confValue.toString().toLatin1();
		this->pocketAPIKey = QByteArray::fromBase64(base64Buffer);
	} else {
		// Wrong value : error
		missingSettings.append(POCKET_API_KEY_PN);
	}

	// Post treatment (missing settings)
	QString errorFilling = ReynTweetsConfiguration::trUtf8("The following setting(s) are missing: ");

	if (!missingSettings.isEmpty()) {
		errorFilling.append(missingSettings.join(", ")).append('.');
		errorLoading.append(' ').append(errorFilling);
	}
}

// QJsonObject representation of the object
QJsonObject ReynTweetsConfiguration::toJSON() const {
	return QJsonObject();
}


///////////////////////////
// Properties management //
///////////////////////////

// consumer_key
QString ReynTweetsConfiguration::CONSUMER_KEY_PN = "consumer_key";

QByteArray ReynTweetsConfiguration::getConsumerKey() {
	return consumerKey;
}

// consumer_secret
QString ReynTweetsConfiguration::CONSUMER_SECRET_PN = "consumer_secret";

QByteArray ReynTweetsConfiguration::getConsumerSecret() {
	return consumerSecret;
}

// callback_url
QString ReynTweetsConfiguration::CALLBACK_URL_PN = "callback_url";

QString ReynTweetsConfiguration::getCallbackURL() {
	return callbackURL;
}

// twitLonger_app_name
QString ReynTweetsConfiguration::TWITLONGER_APP_NAME_PN = "twitLonger_app_name";

QString ReynTweetsConfiguration::getTwitLongerAppName() {
	return twitlongerAppName;
}

// twitlonger_api_key
QString ReynTweetsConfiguration::TWITLONGER_API_KEY_PN = "twitlonger_api_key";

QByteArray ReynTweetsConfiguration::getTwitLongerAPIKey() {
	return twitlongerAPIKey;
}

// pocket_api_key
QString ReynTweetsConfiguration::POCKET_API_KEY_PN = "pocket_api_key";

QByteArray ReynTweetsConfiguration::getPocketAPIKey() {
	return pocketAPIKey;
}
