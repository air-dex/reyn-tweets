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
#include "../processutils.hpp"

// Constructor
AccessTokensProcess::AccessTokensProcess(QByteArray verifier) :
	GenericProcess(),
	twitter(this),
	oauthVerifier(verifier),
	configuration(0),
	updateUserConfiguration(false),
	oauthRes()
{}

// Constructor
AccessTokensProcess::AccessTokensProcess(QByteArray verifier, UserConfiguration &conf) :
	GenericProcess(),
	twitter(this),
	oauthVerifier(verifier),
	configuration(&conf),
	updateUserConfiguration(true),
	oauthRes()
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
void AccessTokensProcess::buildOAuthResults(QByteArray accessToken,
									  QByteArray tokenSecret,
									  qlonglong userID,
									  QString screenName)
{
	oauthRes.insert("access_token", QVariant::fromValue(accessToken));
	oauthRes.insert("token_secret", QVariant::fromValue(tokenSecret));
	oauthRes.insert("user_id", QVariant::fromValue(userID));
	oauthRes.insert("screen_name", QVariant::fromValue(screenName));
}

////////////////////////////
// Step 3 : Access tokens //
////////////////////////////

// Demanding an Access Token
void AccessTokensProcess::accessToken() {
	connect(&twitter, &ReynTwitterCalls::sendResult,
			this, &AccessTokensProcess::accessTokenDemanded);
	twitter.accessToken(oauthVerifier);
}

// Treatments after the request for Access Tokens
void AccessTokensProcess::accessTokenDemanded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == Network::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, &ReynTwitterCalls::sendResult,
			   this, &AccessTokensProcess::accessTokenDemanded);

	NetworkResultType errorType = result.resultType;

	// For a potenitial anticipated end
	int httpCode = result.httpResponse.code;
	QString errorMsg = "";
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
			buildOAuthResults(accessToken, tokenSecret, userID, screenName);

			if (updateUserConfiguration) {
				// Now update the configuration
				// TODO : if fail, knowing that it was authorized
				updateConfiguration(accessToken, tokenSecret, userID, screenName);
			} else {
				// Don't update the configuration. Stop the process here.
				endProcess(AUTHORIZED, oauthRes);
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
											 issue);
			break;
	}

	// Failed end
	endProcess(issue, errorMsg);
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
	connect(&twitter, &ReynTwitterCalls::sendResult,
			this, &AccessTokensProcess::retrieveUserEnded);
	twitter.showUser(id);
}

// Updating a user after requesting it to Twitter
void AccessTokensProcess::retrieveUserEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == Network::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, &ReynTwitterCalls::sendResult,
			   this, &AccessTokensProcess::retrieveUserEnded);

	NetworkResultType errorType = result.resultType;

	// For a potenitial anticipated end
	int httpCode = result.httpResponse.code;
	QString errorMsg = "";
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
											 issue);
			break;
	}

	// Failed end
	endProcess(issue, errorMsg);
}

// Saves the configuration
void AccessTokensProcess::saveConfiguration() {
	QString errorMsg = "";
	CoreResult saveIssue = configuration->save(errorMsg);

	// NOTE : verify the reinit case

	switch (saveIssue) {
		case SAVE_SUCCESSFUL:
			// The application was saved correctly.
			return endProcess(ALLOW_SUCCESSFUL, oauthRes);

		case REINIT_SUCCESSFUL:
			errorMsg = AccessTokensProcess::trUtf8("User configuration was reset.");
			break;

		case CONFIGURATION_FILE_UNKNOWN:
		case CONFIGURATION_FILE_NOT_OPEN:
			break;

		default:
			saveIssue = UNKNOWN_PROBLEM;
			errorMsg = AccessTokensProcess::trUtf8("Unknown problem").append(" : ")
					   .append(errorMsg);;
			break;
	}

	// Ending the process
	endProcess(saveIssue, errorMsg);
}
