/// @file reyntweetsuserconfiguration.cpp
/// @brief Implementation of ReynTweetsUserConfiguration
///
/// Revisions older than r242 were in /trunk/ReynTweets/connection
/// Revisions until r431 were known as ReynTweetsConfiguration
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
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
#include <QtDeclarative>
#include "reyntweetsuserconfiguration.hpp"
#include "../../tools/utils.hpp"

//////////////////////////////
// Serialization management //
//////////////////////////////

// Default constructor
ReynTweetsUserConfiguration::ReynTweetsUserConfiguration() :
	ReynTweetsMappable(),
	userAccount()
{
	blacklistProperties();
}

// Destructor
ReynTweetsUserConfiguration::~ReynTweetsUserConfiguration() {}

// Copy constructor
ReynTweetsUserConfiguration::ReynTweetsUserConfiguration(const ReynTweetsUserConfiguration & configuration) :
	ReynTweetsMappable()
{
	recopie(configuration);
}

// Affectation
const ReynTweetsUserConfiguration & ReynTweetsUserConfiguration::operator=(const ReynTweetsUserConfiguration & configuration) {
	recopie(configuration);
	return *this;
}

// Copy of a ReynTweetsConfiguration
void ReynTweetsUserConfiguration::recopie(const ReynTweetsUserConfiguration & configuration) {
	ReynTweetsMappable::recopie(configuration);
	userAccount = configuration.userAccount;
}

// Serialization declaration
void ReynTweetsUserConfiguration::initSystem() {
	qRegisterMetaTypeStreamOperators<ReynTweetsUserConfiguration>("ReynTweetsUserConfiguration");
	qMetaTypeId<ReynTweetsUserConfiguration>();
}

// Declaring ReynTweetsConfiguration to the QML system
void ReynTweetsUserConfiguration::declareQML() {
	qmlRegisterType<ReynTweetsUserConfiguration>("ReynTweetsEntities",
												 0, 1,
												 "ReynTweetsUserConfiguration");
}

// Resets the mappable to a default value
void ReynTweetsUserConfiguration::reset() {
	*this = ReynTweetsUserConfiguration();
}


////////////////////
// JSON Streaming //
////////////////////

// Output stream operator for serialization
QDataStream & operator<<(QDataStream & out,
						 const ReynTweetsUserConfiguration & configuration)
{
	return jsonStreamingOut(out, configuration);
}

// Input stream operator for serialization
QDataStream & operator>>(QDataStream & in,
						 ReynTweetsUserConfiguration & configuration)
{
	return jsonStreamingIn(in, configuration);
}


///////////////////////////
// Properties management //
///////////////////////////

// Blacklisting the "current_account"
void ReynTweetsUserConfiguration::blacklistProperties() {
	transientProperties.append(QString(QLatin1String("current_account")));
}

// Reading the property p_userAccount
QVariantMap ReynTweetsUserConfiguration::getUserAccountProperty() {
	return userAccount.toVariant();
}

// Writing the property p_userAccount
void ReynTweetsUserConfiguration::setUserAccount(QVariantMap accountMap) {
	userAccount.fillWithVariant(accountMap);
	emit currentAccountChanged();
}

// Reading the property current_account
UserAccount * ReynTweetsUserConfiguration::getCurrentAccount() {
	return &userAccount;
}

// Writing the property current_account
void ReynTweetsUserConfiguration::setCurrentAccount(UserAccount * account) {
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
QString ReynTweetsUserConfiguration::CONFIGURATION_NAMEFILE = "./conf/ReynTweets.conf";


//////////////////////////////
// Configuration management //
//////////////////////////////

// Getter on userAccount
UserAccount ReynTweetsUserConfiguration::getUserAccount() {
	return userAccount;
}

// Getter on userAccount
UserAccount & ReynTweetsUserConfiguration::getUserAccountRef() {
	return userAccount;
}

// Setter on userAccount
void ReynTweetsUserConfiguration::setUserAccount(UserAccount account) {
	userAccount = account;
	emit currentAccountChanged();
}

// Loading the configuration
CoreResult ReynTweetsUserConfiguration::load() {
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

	if (!qVariantCanConvert<ReynTweetsUserConfiguration>(confVariant)) {
		// The content of the file cannot be converted into a configuration.
		return LOADING_CONFIGURATION_ERROR;
	}

	*this = qVariantValue<ReynTweetsUserConfiguration>(confVariant);

	return LOAD_CONFIGURATION_SUCCESSFUL;
}

// Saving the configuration
CoreResult ReynTweetsUserConfiguration::save() {
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
	QVariant confVariant = qVariantFromValue(*this);

	readStream << confVariant;
	confFile.close();

	return SAVE_SUCCESSFUL;
}
