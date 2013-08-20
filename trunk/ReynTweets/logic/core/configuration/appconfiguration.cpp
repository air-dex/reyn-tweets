/// @file appconfiguration.cpp
/// @brief Implementation of AppConfiguration
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
#include <QJsonObject>
#include "appconfiguration.hpp"
#include "../../../connection/common/utils/parsers/jsonparser.hpp"
#include "../../reyntweetsutils.hpp"

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
	QObject(),
	dataDir(""),
	dataDirs(),
	consumerKey(ReynTweets::FAKE_TOKEN),
	consumerSecret(ReynTweets::FAKE_TOKEN),
	callbackURL(ReynTweets::FAKE_URL),
	twitlongerAppName(""),
	twitlongerAPIKey(ReynTweets::FAKE_TOKEN),
	pocketAPIKey(ReynTweets::FAKE_TOKEN)
{}

// Loading the settings from the settings file.
ReynTweets::CoreResult AppConfiguration::load(QString & errorMsg) {
	// Opening the settings file
	QFile confFile(SETTINGS_NAMEFILE);

	if (!confFile.exists()) {
		errorMsg = AppConfiguration::trUtf8("Settings file unknown.");
		return  ReynTweets::CONFIGURATION_FILE_UNKNOWN;
	}

	if (!confFile.open(QFile::ReadOnly)) {
		errorMsg = AppConfiguration::trUtf8("Cannot open the settings file.");
		return ReynTweets::CONFIGURATION_FILE_NOT_OPEN;
	}


	// Parsing datas
	JSONParser parser;
	bool parseOK = false;
	QString parseErrMsg = "";
	QJsonValue jsonSettings = parser.parse(confFile.readAll(),
										   &parseOK,
										   &parseErrMsg);

	confFile.close();

	if (!parseOK || !jsonSettings.isObject()) {
		// Parse error : JSON Object expected (and why it's not that).
		errorMsg.append(AppConfiguration::trUtf8("Parse error (JSON object expected):"))
				.append(' ')
				.append(parseErrMsg)
				.append('.');
		return ReynTweets::PARSE_ERROR;
	}


	// Filling the settings
	QJsonObject jsonConf = jsonSettings.toObject();
	QString fillErr = "";

	this->fillWithVariant(jsonConf, fillErr);

	if (fillErr.isEmpty()) {
		// No error while filling the configuration
		return ReynTweets::LOAD_CONFIGURATION_SUCCESSFUL;
	} else {
		// Error while filling the configuration
		errorMsg.append(' ').append(fillErr);
		return ReynTweets::EXPECTED_KEY;
	}
}

// Getting the directory where application datas are stored.
QDir AppConfiguration::getAppDataDir() {
	QString appDataPath = QDir::homePath().append(dataDir);

	return QDir(appDataPath);
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void AppConfiguration::fillWithVariant(QJsonObject json, QString &fillingError) {
	QJsonValue confValue;
	QByteArray base64Buffer;
	QStringList missingSettings;

	fillingError = "";

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

	// data_dir & data_dirs
	confValue = json.value(DATA_DIRS_PN);

	if (!confValue.isUndefined() && confValue.isObject()) {
		// Right value : fill the setting
		dataDirs = confValue.toObject().toVariantMap();
		setDataDir();

		if (dataDir.isEmpty()) {
			fillingError = AppConfiguration::trUtf8("Unknown Application Data Directory.");
		}
	} else {
		// Wrong value : error
		missingSettings.append(DATA_DIRS_PN);
	}

	// Post treatment (missing settings)

	if (!missingSettings.isEmpty()) {
		fillingError.append(AppConfiguration::trUtf8("The following setting(s) are missing"))
				.append(" : ")
				.append(missingSettings.join(", "))
				.append('.');
	}
}


///////////////////////////
// Properties management //
///////////////////////////

// data_dir
QString AppConfiguration::getDataDir() {
	return dataDir;
}

void AppConfiguration::setDataDir() {
	#ifdef Q_OS_WIN
		QString osName = "windows";
	#elif defined(Q_OS_LINUX)
		QString osName = "linux";
	#else
		QString osName = "";
	#endif

	dataDir = osName.isEmpty() ? "" : dataDirs.value(osName).toString();
}

// data_dirs
QString AppConfiguration::DATA_DIRS_PN = "data_dir";

QVariantMap AppConfiguration::getDataDirs() {
	return dataDirs;
}

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
