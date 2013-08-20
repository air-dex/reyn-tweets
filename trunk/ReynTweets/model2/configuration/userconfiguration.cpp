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
#include "userconfiguration.hpp"
#include "../../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
UserConfiguration::UserConfiguration() :
	JsonObject(),
	userAccount()
{
	blacklistProperties();
}

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
void UserConfiguration::fillWithJSON(QJsonObject json) {
	this->userAccount.fillWithJSON(json.value(USER_ACCOUNT_PN).toObject());
}

// QJsonObject representation of the object
QJsonObject UserConfiguration::toJSON() const {
	QJsonObject json;

	json.insert(USER_ACCOUNT_PN, QJsonValue(this->userAccount.toJSON()));

	return json;
}


///////////////////////////
// Properties management //
///////////////////////////

// Blacklisting the "current_account"
void UserConfiguration::blacklistProperties() {
	transientProperties.append(QString(QLatin1String(CURRENT_ACCOUNT_PN)));
}

// user_account
QString UserConfiguration::USER_ACCOUNT_PN = "user_account";

QVariantMap UserConfiguration::getUserAccountProperty() {
	return userAccount.toVariant();
}

UserAccount2 UserConfiguration::getUserAccount() {
	return userAccount;
}

UserAccount2 & UserConfiguration::getUserAccountRef() {
	return userAccount;
}

void UserConfiguration::setUserAccount(QVariantMap accountMap) {
	userAccount.fillWithVariant(accountMap);
	emit currentAccountChanged();
}

void UserConfiguration::setUserAccount(UserAccount2 account) {
	userAccount = account;
	emit currentAccountChanged();
}

// current_account
QString UserConfiguration::CURRENT_ACCOUNT_PN = "current_account";

UserAccount2 * UserConfiguration::getCurrentAccount() {
	return &userAccount;
}

void UserConfiguration::setCurrentAccount(UserAccount2 * account) {
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
	QDataStream readStream(&confFile);
	QVariant confVariant;

	readStream >> confVariant;
	confFile.close();

	if (!confVariant.canConvert<UserConfiguration>()) {
		// The content of the file cannot be converted into a configuration.
		return LOADING_CONFIGURATION_ERROR;
	}

	*this = confVariant.value<UserConfiguration>();

	return LOAD_CONFIGURATION_SUCCESSFUL;
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
	QDataStream readStream(&confFile);
	QByteArray json = QJsonDocument(this->toJSON()).toJson();
	readStream << json;
	confFile.close();

	return SAVE_SUCCESSFUL;
}
