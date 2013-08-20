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

#include <QFile>
#include <QObject>
#include "appconfiguration.hpp"
#include "../../tools/parsers/jsonparser.hpp"

////////////////////
// Static members //
////////////////////

// Name of the file containing the settings.
QString AppConfiguration::SETTINGS_NAMEFILE = "./conf/ReynTweetsSettings.conf";

AppConfiguration * AppConfiguration::REYN_TWEETS_CONFIGURATION = new AppConfiguration();

/////////////////////
// Core management //
/////////////////////

// Getter on the configuration
AppConfiguration & AppConfiguration::getReynTweetsConfiguration() {
	return *REYN_TWEETS_CONFIGURATION;
}

// Deletes REYN_TWEETS_CONFIGURATION pointer
void AppConfiguration::unleashReyn() {
	delete REYN_TWEETS_CONFIGURATION;
}

// Private constructor
AppConfiguration::AppConfiguration() :
	errorLoading(""),
	consumerKey(""),
	consumerSecret(""),
	callbackURL(""),
	twitlongerAppName(""),
	twitlongerAPIKey(""),
	pocketAPIKey("")
{}

// Reset the app configuration
void AppConfiguration::reset() {
	*this = AppConfiguration();
}

// Loading the settings from the settings file.
CoreResult AppConfiguration::load() {
	// Opening the settings file
	QFile confFile(SETTINGS_NAMEFILE);

	if (!confFile.exists()) {
		errorLoading = AppConfiguration::trUtf8("Settings file unknown.");
		return  CONFIGURATION_FILE_UNKNOWN;
	}

	bool openOK = confFile.open(QFile::ReadOnly);
	if (!openOK) {
		errorLoading = AppConfiguration::trUtf8("Cannot open the settings file.");
		return CONFIGURATION_FILE_NOT_OPEN;
	}


	// Parsing datas
	bool parseOK = false;
	JSONParser parser;
	QJsonValue jsonSettings = parser.parse(confFile.readAll(),
										   &parseOK,
										   &errorLoading);

	confFile.close();

	if (!jsonSettings.isObject()) {
		// Parse error : JSON Object expected
		static QString wrongJSONType = AppConfiguration::trUtf8("Parse error : JSON object expected.");
		errorLoading.append(' ').append(wrongJSONType);
		parseOK = false;
	}

	if (!parseOK) {
		return PARSE_ERROR;
	}


	// Filling the settings

	QJsonObject jsonConf = jsonSettings.toObject();
	QString oldErr = errorLoading;

	this->fillWithVariant(jsonConf);

	bool fillOK = oldErr == errorLoading;	// More errors if it fails.

	return fillOK ? LOAD_CONFIGURATION_SUCCESSFUL : EXPECTED_KEY;
}

// Getter on the error message after loading the settings
QString AppConfiguration::getErrorLoading() {
	return errorLoading;
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void AppConfiguration::fillWithVariant(QJsonObject json) {
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

	// twitlonger_application_name
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
		// Right value : fill the setting
		base64Buffer = confValue.toString().toLatin1();
		this->twitlongerAPIKey = QByteArray::fromBase64(base64Buffer);
	} else {
		// Wrong value : error
		missingSettings.append(TWITLONGER_API_KEY_PN);
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
	QString errorFilling = AppConfiguration::trUtf8("The following setting(s) are missing: ");

	if (!missingSettings.isEmpty()) {
		errorFilling.append(missingSettings.join(", ")).append('.');
		errorLoading.append(' ').append(errorFilling);
	}
}

// QJsonObject representation of the object
QJsonObject AppConfiguration::toVariant() const {
	return QJsonObject();
}


///////////////////////////
// Properties management //
///////////////////////////

// consumer_key
QString AppConfiguration::CONSUMER_KEY_PN = "consumer_key";

QByteArray AppConfiguration::getConsumerKey() {
	return consumerKey;
}

// consumer_secret
QString AppConfiguration::CONSUMER_SECRET_PN = "consumer_secret";

QByteArray AppConfiguration::getConsumerSecret() {
	return consumerSecret;
}

// callback_url
QString AppConfiguration::CALLBACK_URL_PN = "callback_url";

QString AppConfiguration::getCallbackURL() {
	return callbackURL;
}

// twitlonger_application_name
QString AppConfiguration::TWITLONGER_APP_NAME_PN = "twitlonger_application_name";

QString AppConfiguration::getTwitLongerAppName() {
	return twitlongerAppName;
}

// twitlonger_api_key
QString AppConfiguration::TWITLONGER_API_KEY_PN = "twitlonger_api_key";

QByteArray AppConfiguration::getTwitLongerAPIKey() {
	return twitlongerAPIKey;
}

// pocket_api_key
QString AppConfiguration::POCKET_API_KEY_PN = "pocket_api_key";

QByteArray AppConfiguration::getPocketAPIKey() {
	return pocketAPIKey;
}
