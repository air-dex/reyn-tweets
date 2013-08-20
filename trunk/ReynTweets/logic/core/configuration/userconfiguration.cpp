/// @file userconfiguration.cpp
/// @brief Implementation of UserConfiguration
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012, 2013 Romain Ducher
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

#include "userconfiguration.hpp"

#include <QtQml>
#include <QDir>
#include <QFile>
#include <QTextStream>

#include "appconfiguration.hpp"
#include "../../../connection/common/utils/parsers/jsonparser.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
UserConfiguration::UserConfiguration() :
	JsonObject(),
	userAccount()
{}

// Destructor
UserConfiguration::~UserConfiguration() {}

// Copy constructor
UserConfiguration::UserConfiguration(const UserConfiguration & configuration) :
	JsonObject(),
	userAccount()
{
	recopie(configuration);
}

// Affectation
const UserConfiguration & UserConfiguration::operator=(const UserConfiguration & configuration) {
	recopie(configuration);
	return *this;
}

// Copy of a ReynTweetsConfiguration
void UserConfiguration::recopie(const UserConfiguration & configuration) {
	JsonObject::recopie(configuration);
	userAccount = configuration.userAccount;
}

// Serialization declaration
void UserConfiguration::initSystem() {
	qRegisterMetaTypeStreamOperators<UserConfiguration>("UserConfiguration");
	qMetaTypeId<UserConfiguration>();
}

// Declaring ReynTweetsConfiguration to the QML system
void UserConfiguration::declareQML() {
	qmlRegisterType<UserConfiguration>("ReynTweetsEntities",
									   0, 2,
									   "UserConfiguration");
}

// Resets the mappable to a default value
void UserConfiguration::reset() {
	*this = UserConfiguration();
}


////////////////////
// JSON Streaming //
////////////////////

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out,
						 const UserConfiguration & configuration)
{
	return configuration.writeInStream(out);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in,
						 UserConfiguration & configuration)
{
	return configuration.fillWithStream(in);
}


/////////////////////
// JSON conversion //
/////////////////////

// Filling the object with a QJsonObject.
void UserConfiguration::fillWithVariant(QJsonObject json) {
	this->userAccount.fillWithVariant(json.value(USER_ACCOUNT_PN).toObject());
}

// QJsonObject representation of the object
QJsonObject UserConfiguration::toVariant() const {
	QJsonObject json;

	json.insert(USER_ACCOUNT_PN, QJsonValue(this->userAccount.toVariant()));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// user_account
QString UserConfiguration::USER_ACCOUNT_PN = "user_account";

UserAccount UserConfiguration::getUserAccount() {
	return userAccount;
}

UserAccount * UserConfiguration::getUserAccountPtr() {
	return &userAccount;
}

UserAccount & UserConfiguration::getUserAccountRef() {
	return userAccount;
}

void UserConfiguration::setUserAccount(UserAccount account) {
	userAccount = account;
	emit currentAccountChanged();
}

void UserConfiguration::setUserAccount(UserAccount * account) {
	if (account) {
		userAccount = *account;
	} else {
		userAccount.reset();
	}

	emit currentAccountChanged();
}


//////////////////////////////
// Configuration management //
//////////////////////////////

// Loading the configuration
ReynTweets::CoreResult UserConfiguration::load(QString & errorMsg) {
	// Ensures that the file can be used correctly. If not, reinit the conf.
	if (!this->checkConfigurationFile()) {
		ReynTweets::CoreResult reinitRes = this->reinit(errorMsg);
		return reinitRes;
	}

	// Opening the configuration file
	QFile confFile(this->getConfigurationFilePath());

	if (!confFile.exists()) {
		errorMsg = UserConfiguration::trUtf8("Cannot load the user configuration file : unknown configuration file. Try to create it manually");
		return ReynTweets::CONFIGURATION_FILE_UNKNOWN;
	}

	if (!confFile.open(QFile::ReadOnly)) {
		errorMsg = UserConfiguration::trUtf8("Cannot load the user configuration file : configuration file cannot be opened. Check if you can read it.");
		return ReynTweets::CONFIGURATION_FILE_NOT_OPEN;
	}

	// Launching the configuration
	JSONParser parser;
	bool parseOK = false;
	QString parseErrMsg = "";
	QJsonValue jsonSettings = parser.parse(confFile.readAll(),
										   &parseOK,
										   &parseErrMsg);

	confFile.close();

	if (!parseOK || !jsonSettings.isObject()) {
		// Parse error : JSON Object expected (and why it's not that).
		errorMsg.append(UserConfiguration::trUtf8("Parse error (JSON object expected):"))
				.append(' ')
				.append(parseErrMsg)
				.append('.');
		return ReynTweets::PARSE_ERROR;
	}


	// Filling the settings
	QJsonObject jsonConf = jsonSettings.toObject();
	QString oldErr = errorMsg;

	this->fillWithVariant(jsonConf);

	bool fillOK = oldErr == errorMsg;	// More errors if it fails.

	return fillOK ?
				ReynTweets::LOAD_CONFIGURATION_SUCCESSFUL
			  : ReynTweets::EXPECTED_KEY;
}

// Saving the configuration
ReynTweets::CoreResult UserConfiguration::save(QString & errorMsg) {
	// Ensures that the file can be used correctly. If not, reinit the conf.
	if (this->checkConfigurationFile()) {
		// Writing the configuration
		ReynTweets::CoreResult writeConf = this->writeConfigurationInFile(errorMsg);

		return writeConf == ReynTweets::WRITE_SUCCESSFUL ?
					ReynTweets::SAVE_SUCCESSFUL
				  : writeConf;
	} else {
		return this->reinit(errorMsg);
	}
}

// Reinit the configuration file
ReynTweets::CoreResult UserConfiguration::reinit(QString & errorMsg) {
	// Default user configuration
	this->reset();

	// Directory where the configuration file is supposed to be
	QDir confdir = AppConfiguration::getReynTweetsConfiguration().getAppDataDir();

	// If fhe App data directory does not exist, create it.
	if (!confdir.exists() && !confdir.mkpath(confdir.path())) {
		errorMsg = UserConfiguration::trUtf8("Cannot create the user configuration file because its directory cannot be created. Try to create it manually");
		return ReynTweets::APP_DATA_DIR_UNKNOWN;
	}

	// Writing the configuration
	// Forces RW in order to be sure that the file file is readable.
	ReynTweets::CoreResult writeConf = this->writeConfigurationInFile(errorMsg, QIODevice::ReadWrite);

	return writeConf == ReynTweets::WRITE_SUCCESSFUL ?
				ReynTweets::REINIT_SUCCESSFUL
			  : writeConf;
}


////////////////////////////////////////
// User configuration file management //
////////////////////////////////////////

// Configuration namefile
QString UserConfiguration::CONFIGURATION_NAMEFILE = "ReynTweets.conf";

// Configuration file path
QString UserConfiguration::getConfigurationFilePath() {
	QDir appDataDir = AppConfiguration::getReynTweetsConfiguration().getAppDataDir();

	return appDataDir.filePath(CONFIGURATION_NAMEFILE);
}

// Checks if the user configuration file exists and is both readable & writable
bool UserConfiguration::checkConfigurationFile() {
	QFileInfo confFileInfo(this->getConfigurationFilePath());

	return confFileInfo.exists()
			&& confFileInfo.isReadable()
			&& confFileInfo.isWritable();
}

// Writing the configuration
ReynTweets::CoreResult UserConfiguration::writeConfigurationInFile(QString & errorMsg,
																   QIODevice::OpenMode openMode)
{
	// Opening the configuration file
	QFile confFile(this->getConfigurationFilePath());

	if (!confFile.open(openMode)) {
		errorMsg = UserConfiguration::trUtf8("Cannot load the user configuration file : configuration file cannot be opened.");
		return ReynTweets::CONFIGURATION_FILE_NOT_OPEN;
	}

	if (!confFile.isWritable()) {
		errorMsg = UserConfiguration::trUtf8("Cannot write the user configuration file.");
		return ReynTweets::CONFIGURATION_FILE_NOT_OPEN;
	}

	if (!confFile.exists()) {
		errorMsg = UserConfiguration::trUtf8("Cannot create the user configuration file. Try to create it manually");
		return ReynTweets::CONFIGURATION_FILE_UNKNOWN;
	}

	// Saving the configuration
	QTextStream readStream(&confFile);
	QByteArray json = QJsonDocument(this->toVariant()).toJson();
	readStream << json;
	confFile.close();

	errorMsg = "";
	return ReynTweets::WRITE_SUCCESSFUL;
}
