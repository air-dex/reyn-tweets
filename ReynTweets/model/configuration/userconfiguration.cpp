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

#include <QFile>
#include <QtQml>
#include <QTextStream>
#include "userconfiguration.hpp"
#include "../../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
UserConfiguration::UserConfiguration() :
	JsonObject(),
	userAccount(),
	errorLoading("")
{}

// Destructor
UserConfiguration::~UserConfiguration() {}

// Copy constructor
UserConfiguration::UserConfiguration(const UserConfiguration & configuration) :
	JsonObject(),
	userAccount(),
	errorLoading("")
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

// Getter on the error message after loading the settings
QString UserConfiguration::getErrorLoading() {
	return errorLoading;
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

QVariantMap UserConfiguration::getUserAccountProperty() {
	return userAccount.toVariant().toVariantMap();
}

UserAccount UserConfiguration::getUserAccount() {
	return userAccount;
}

UserAccount & UserConfiguration::getUserAccountRef() {
	return userAccount;
}

void UserConfiguration::setUserAccount(QVariantMap accountMap) {
	userAccount.fillWithVariant(QJsonObject::fromVariantMap(accountMap));
	emit currentAccountChanged();
}

void UserConfiguration::setUserAccount(UserAccount account) {
	userAccount = account;
	emit currentAccountChanged();
}

// current_account
QString UserConfiguration::CURRENT_ACCOUNT_PN = "current_account";

UserAccount * UserConfiguration::getCurrentAccount() {
	return &userAccount;
}

void UserConfiguration::setCurrentAccount(UserAccount * account) {
	if (account) {
		userAccount = *account;
	} else {
		userAccount.reset();
	}

	emit currentAccountChanged();
}


////////////////////
// Static members //
////////////////////

// Configuration namefile
QString UserConfiguration::CONFIGURATION_NAMEFILE = "./conf/ReynTweets.conf";


//////////////////////////////
// Configuration management //
//////////////////////////////

// Loading the configuration
CoreResult UserConfiguration::load() {
	// Opening the configuration file
	QFile confFile(CONFIGURATION_NAMEFILE);

	if (!confFile.exists()) {
		return CONFIGURATION_FILE_UNKNOWN;
	}

	bool openOK = confFile.open(QFile::ReadOnly);
	if (!openOK) {
		return CONFIGURATION_FILE_NOT_OPEN;
	}

	// Launching the configuration
	bool parseOK = false;
	JSONParser parser;
	QJsonValue jsonSettings = parser.parse(confFile.readAll(),
										   &parseOK,
										   &errorLoading);

	confFile.close();

	if (!jsonSettings.isObject()) {
		// Parse error : JSON Object expected
		static QString wrongJSONType = UserConfiguration::trUtf8("Parse error : JSON object expected.");
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

// Saving the configuration
CoreResult UserConfiguration::save() {
	// Opening the configuration file
	QFile confFile(CONFIGURATION_NAMEFILE);

	if (!confFile.exists()) {
		return CONFIGURATION_FILE_UNKNOWN;
	}

	bool openOK = confFile.open(QFile::WriteOnly);
	if (!openOK) {
		return CONFIGURATION_FILE_NOT_OPEN;
	}


	// Saving the configuration
	QTextStream readStream(&confFile);
	QByteArray json = QJsonDocument(this->toVariant()).toJson();
	readStream << json;
	confFile.close();

	return SAVE_SUCCESSFUL;
}
