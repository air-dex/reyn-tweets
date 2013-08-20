/// @file accesstokensprocess.cpp
/// @brief Implementation of AccessTokensProcess
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2013 Romain Ducher
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

#include "accesstokensprocess.hpp"
#include "../../../tools/processutils.hpp"

// Constructor
AccessTokensProcess::AccessTokensProcess(QByteArray verifier) :
	GenericProcess(),
	twitter(this),
	oauthVerifier(verifier),
	configuration(0),
	updateUserConfiguration(false)
{}

// Constructor
AccessTokensProcess::AccessTokensProcess(QByteArray verifier, UserConfiguration &conf) :
	GenericProcess(),
	twitter(this),
	oauthVerifier(verifier),
	configuration(&conf),
	updateUserConfiguration(true)
{}

// Destructor
AccessTokensProcess::~AccessTokensProcess() {
	configuration = 0;
}

// Ask for final tokens
void AccessTokensProcess::startProcess() {
	accessToken();
}

// Building the result of the process
void AccessTokensProcess::buildResult(QByteArray accessToken,
									  QByteArray tokenSecret,
									  qlonglong userID,
									  QString screenName)
{
	QVariantMap resultMap;
	resultMap.insert("access_token", QVariant::fromValue(accessToken));
	resultMap.insert("token_secret", QVariant::fromValue(tokenSecret));
	resultMap.insert("user_id", QVariant::fromValue(userID));
	resultMap.insert("screen_name", QVariant::fromValue(screenName));

	processResult = ProcessUtils::buildProcessResult(AUTHORIZED,
													 QVariant(resultMap));
}

////////////////////////////
// Step 3 : Access tokens //
////////////////////////////

// Demanding an Access Token
void AccessTokensProcess::accessToken() {
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(accessTokenDemanded(ResultWrapper)));
	twitter.accessToken(oauthVerifier);
}

// Treatments after the request for Access Tokens
void AccessTokensProcess::accessTokenDemanded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == Network::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(accessTokenDemanded(ResultWrapper)));

	NetworkResultType errorType = result.resultType;

	// For a potenitial anticipated end
	int httpCode = result.httpResponse.code;
	QString errorMsg = "";
	bool isFatal = false;
	CoreResult issue;

	switch (errorType) {
		case Network::NO_REQUEST_ERROR: {
			// The authentication process is ended.

			// Extract the different values
			QVariantMap resultMap = result.parsedResult.toMap();
			QByteArray accessToken = resultMap.value("oauth_token").toByteArray();
			QByteArray tokenSecret = resultMap.value("oauth_token_secret").toByteArray();
			qlonglong userID = resultMap.value("user_id").toLongLong();
			QString screenName = resultMap.value("screen_name").toString();

			// Successful end
			buildResult(accessToken, tokenSecret, userID, screenName);

			if (updateUserConfiguration) {
				// Now update the configuration
				updateConfiguration(accessToken, tokenSecret, userID, screenName);
			} else {
				// Don't update the configuration. Stop the process here.
				endProcess();
			}
		}return;

		case Network::SERVICE_ERRORS:
			// Building error message
			errorMsg = ProcessUtils::writeTwitterErrors(result);

			// Looking for specific value of the return code
			issue = (httpCode / 100 == 5
					 || httpCode == 401
					 || httpCode == 420
					 || httpCode == 429
					 ) ?
						httpResults.value(httpCode)
					  : NO_TOKENS;
			break;

		case Network::API_CALL:
			ProcessUtils::treatApiCallResult(result, errorMsg, issue);
			break;

		case Network::OAUTH_PARSING:
			ProcessUtils::treatOAuthParsingResult(result.parsingErrors.message,
												  errorMsg,
												  issue);
			break;

		default:
			ProcessUtils::treatUnknownResult(result.errorMessage,
											 errorMsg,
											 issue,
											 isFatal);
			break;
	}

	// Failed end
	GenericProcess::buildResult(false, issue, errorMsg, isFatal);
	endProcess();
}

// Uploading the configuration with the authentified user after an authentication process
void AccessTokensProcess::updateConfiguration(QByteArray accessToken,
											  QByteArray tokenSecret,
											  qlonglong id, QString)
{
	// Updating the tokens
	UserAccount & account = configuration->getUserAccountRef();
	account.setAccessToken(accessToken);
	account.setTokenSecret(tokenSecret);

	// Getting informations about the user behind the account
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(retrieveUserEnded(ResultWrapper)));
	twitter.showUser(id);
}

// Updating a user after requesting it to Twitter
void AccessTokensProcess::retrieveUserEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == Network::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(retrieveUserEnded(ResultWrapper)));

	NetworkResultType errorType = result.resultType;

	// For a potenitial anticipated end
	int httpCode = result.httpResponse.code;
	QString errorMsg = "";
	bool isFatal = false;
	CoreResult issue;

	switch (errorType) {
		case Network::NO_REQUEST_ERROR: {
			// Get user, put it in the conf and save
			QVariantMap parsedResults = result.parsedResult.toMap();
			UserInfos u;
			u.fillWithVariant(QJsonObject::fromVariantMap(parsedResults));
			UserAccount & account = configuration->getUserAccountRef();
			account.setUser(u);
			saveConfiguration();
		}return;

		case Network::SERVICE_ERRORS:
			// Looking for specific value of the return code
			issue = (httpCode / 100 == 5
					 || httpCode == 420
					 || httpCode == 429
					 ) ?
						httpResults.value(httpCode)
					  : NO_TOKENS;

			//ProcessUtils::treatTwitterErrorResult(result, errorMsg, issue);

			// Building error message
			errorMsg = ProcessUtils::writeTwitterErrors(result);
			break;

		case Network::API_CALL:
			ProcessUtils::treatApiCallResult(result, errorMsg, issue);
			break;

		case Network::JSON_PARSING:
			ProcessUtils::treatQjsonParsingResult(result.parsingErrors,
												  errorMsg,
												  issue);
			break;

		default:
			ProcessUtils::treatUnknownResult(result.errorMessage,
											 errorMsg,
											 issue,
											 isFatal);
			break;
	}

	// Failed end
	GenericProcess::buildResult(false, issue, errorMsg, isFatal);
	endProcess();
}

// Saves the configuration
void AccessTokensProcess::saveConfiguration() {
	CoreResult saveIssue = configuration->save();
	bool processOK = false;
	QString errorMsg = "";
	bool isFatal = true;

	switch (saveIssue) {
		case SAVE_SUCCESSFUL:
			// The application was saved correctly.
			processOK = true;
			processResult.processIssue = ALLOW_SUCCESSFUL;
			isFatal = false;
			endProcess();
			return;

		case CONFIGURATION_FILE_UNKNOWN:
			errorMsg = AccessTokensProcess::trUtf8("Configuration file does not exist.");
			break;

		case CONFIGURATION_FILE_NOT_OPEN:
			errorMsg = AccessTokensProcess::trUtf8("Configuration file cannot be opened.");
			break;

		default:
			errorMsg = AccessTokensProcess::trUtf8("Unknown problem");
			break;
	}

	// Ending the process
	GenericProcess::buildResult(processOK, saveIssue, errorMsg, isFatal);
	endProcess();
}
