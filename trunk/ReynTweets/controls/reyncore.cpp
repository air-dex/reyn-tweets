/// @file reyncore.cpp
/// @brief Implementation of ReynCore
/// @author Romain Ducher

/*
Copyright 2012 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#include <QFile>
#include "reyncore.hpp"

// Constructor
ReynCore::ReynCore() :
	QObject(),
	twitter(this),
	configuration()
{}

//////////////////////////////
// Configuration management //
//////////////////////////////

// Loading the configuartion from the configuration file
void ReynCore::loadConfiguration() {
	emit launchEnded(loadConfigurationPrivate());
}

// Loading the configuartion from the configuration file
LaunchResult ReynCore::loadConfigurationPrivate() {
	// Opening the configuration file
	QFile confFile("conf/ReynTweets.conf");

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

	if (!qVariantCanConvert<ReynTweetsConfiguration>(confVariant)) {
		// The content of the file cannot be converted into a configuration.
		return LOADING_CONFIGURATION_ERROR;
	}

	configuration = qVariantValue<ReynTweetsConfiguration>(confVariant);
	fillOAuthManager();
	return LAUNCH_SUCCESSFUL;
}

// Saving the configuartion in the configuration file
void ReynCore::saveConfiguration() {
	emit saveConfEnded(saveConfigurationPrivate());
}

// Saving the configuartion in the configuration file
SaveConfResult ReynCore::saveConfigurationPrivate() {
	// Opening the configuration file
	QFile confFile("conf/ReynTweets.conf");

	if (!confFile.exists()) {
		return CONFIGURATION_BACKUP_FILE_UNKNOWN;
	}

	bool openOK = confFile.open(QFile::WriteOnly);
	if (!openOK) {
		return CONFIGURATION_BACKUP_FILE_NOT_OPEN;
	}

	// Launching the configuration
	QDataStream readStream(&confFile);
	QVariant confVariant = qVariantFromValue(configuration);

	readStream << confVariant;
	confFile.close();

	return SAVE_SUCCESSFUL;
}

// Filling the OAuth manager of the ReynTwitterCalls with right credentials
void ReynCore::fillOAuthManager() {
	ReynTwitterCalls::setNewTokens(configuration.getUserAccount().getAccessToken(),
								   configuration.getUserAccount().getTokenSecret(),
								   ReynTweetsConfiguration::getConsumerKey(),
								   ReynTweetsConfiguration::getConsumerSecret());
}

// Uploading the configuration after an authentication process
void ReynCore::updateConfAfterAuth(QByteArray accessToken, QByteArray tokenSecret, long id, QString) {
	// Updating the tokens
	UserAccount account = configuration.getUserAccount();
	account.setAccessToken(accessToken);
	account.setTokenSecret(tokenSecret);
	configuration.setUserAccount(account);

	// Getting informations about the user behind the account
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(getUser(ResultWrapper)));
	twitter.showUser(id);
}

// Getting a user after requesting it to Twitter
void ReynCore::getUser(ResultWrapper res) {
	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(getUser(ResultWrapper)));

	RequestResult result = res.accessResult(this);
	ErrorType errorType = result.getErrorType();

	switch (errorType) {
		case NO_ERROR: {
				// Get user, put it in the conf and save
			QVariantMap parsedResults = result.getParsedResult().toMap();
			User u;
			u.fillWithVariant(parsedResults);
			UserAccount account = configuration.getUserAccount();
			account.setUser(u);
			configuration.setUserAccount(account);
			saveConfiguration();
		}break;

		case API_CALL: {
			// Retrieving network informations
			int httpCode = result.getHttpCode();
			QString httpReason = result.getHttpReason();

			// Building error message
			QString errorMsg = "Network error ";
			errorMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(httpReason)
					.append(" :\n")
					.append(result.getErrorMessage())
					.append(".\n");
//			emit errorProcess(false, errorMsg);
		}break;

		case OAUTH_PARSING: {
			// Building error message
			QString errorMsg = "Parsing error :\n";
			errorMsg.append(result.getParsingErrorMessage());
//			emit errorProcess(false, errorMsg);
		}break;

		default: {
			// Unexpected problem. Abort.
			QString errorMessage = "Unexpected problem :\n";
			errorMessage.append(result.getErrorMessage()).append(".\n");
//			emit errorProcess(true, errorMessage);
		}break;
	}
}


///////////////////////////////
// Authentication management //
///////////////////////////////

// Checks if the access tokens seem legit.
void ReynCore::checkTokens() {
	if (!(isValidToken(configuration.getUserAccount().getAccessToken())
		  && isValidToken(configuration.getUserAccount().getTokenSecret())))
	{
		emit authenticationRequired();
	}
}

// Determining if a token seems legit
bool ReynCore::isValidToken(QByteArray token) {
	// Right tokens == Tokens not empty

	// Step 1 : Base 64 form not null or empty
	if (token.isNull() || token.isEmpty()) {
		return false;
	}

	// Step 2 : Clear form not null or empty
	QByteArray clearToken = QByteArray::fromBase64(token);

	return !(clearToken.isNull() || clearToken.isEmpty());
}
