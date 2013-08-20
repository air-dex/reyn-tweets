/// @file launchingprocess.cpp
/// @brief Implementation of LaunchingProcess
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
#include "launchingprocess.hpp"
#include "processutils.hpp"
#include "../../connection/twitlonger/twitlongercalls.hpp"

// Constructor
LaunchingProcess::LaunchingProcess(UserConfiguration & userConf) :
	GenericProcess(),
	twitter(this),
	userConfiguration(userConf),
	appConfiguration(AppConfiguration::getReynTweetsConfiguration())
{}

// Starting the process
void LaunchingProcess::startProcess() {
	checkSettingsLoad();
}


////////////////////////////////////////////////////
// Step 1 : loading the application configuration //
////////////////////////////////////////////////////

// Starting the process
void LaunchingProcess::checkSettingsLoad() {
	// Check if the application settings were loaded correctly
	CoreResult loadIssue = appConfiguration.load();

	switch(loadIssue) {
		case LOAD_CONFIGURATION_SUCCESSFUL:
			fillTwitterOAuthAppSettings();
			fillTwitLongerAppSettings();
			return loadConfiguration();

		// Expected errors
		case CONFIGURATION_FILE_NOT_OPEN:
		case PARSE_ERROR:
		case CONFIGURATION_FILE_UNKNOWN:
		case EXPECTED_KEY:
			break;

		default:
			loadIssue = UNKNOWN_PROBLEM;
			break;
	}

	// Failed end
	QString errMsg = appConfiguration.getErrorLoading();
	endProcess(loadIssue, errMsg);
}


/////////////////////////////////////////////
// Step 2 : loading the user configuration //
/////////////////////////////////////////////

// Loading the configuartion from the configuration file
void LaunchingProcess::loadConfiguration() {
	QString errorMsg = "";
	CoreResult loadIssue = userConfiguration.load(errorMsg);

	// TODO : warn if the conf is reset.

	switch (loadIssue) {
		case REINIT_SUCCESSFUL:
			errorMsg = LaunchingProcess::trUtf8("User configuration was reset.");

		case LOAD_CONFIGURATION_SUCCESSFUL:
			// The configuration was loaded correctly. Let's check the credentials
			fillTwitterOAuthUserSettings();
			return checkTokens();

		case PARSE_ERROR:
		case EXPECTED_KEY:
			loadIssue = LOADING_CONFIGURATION_ERROR;
			break;

		case LOADING_CONFIGURATION_ERROR:
		case CONFIGURATION_FILE_UNKNOWN:
		case CONFIGURATION_FILE_NOT_OPEN:
			break;

		default:
			// Unknown problem.
			loadIssue = UNKNOWN_PROBLEM;
			errorMsg = LaunchingProcess::trUtf8("Unknown problem").append(" : ")
					   .append(errorMsg);
			break;
	}

	// Failed end
	endProcess(loadIssue, errorMsg);
}


////////////////////////////////////////
// Step 3 : verifying the credentials //
////////////////////////////////////////

// Checks if the access tokens seem legit.
void LaunchingProcess::checkTokens() {
	// Looking at the user tokens
	UserAccount ua = userConfiguration.getUserAccount();

	if (ua.getAccessToken().isEmpty() || ua.getTokenSecret().isEmpty()) {
		// There's no OAuth tokens for Twitter -> Let's authenticate !
		CoreResult issue = AUTHENTICATION_REQUIRED;
		QString errMsg = LaunchingProcess::trUtf8("Unexpected empty Twitter tokens.");

		emit authenticationRequired();
		endProcess(issue, errMsg);
	} else {
		// Tokens seems legit. Let's ensure that's really the case
		connect(&twitter, &ReynTwitterCalls::sendResult,
				this, &LaunchingProcess::verifyCredentialsEnded);
		twitter.verifyCredentials(true, false);
	}
}

// Slot executed after verifying credentials.
void LaunchingProcess::verifyCredentialsEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == Network::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, &ReynTwitterCalls::sendResult,
			   this, &LaunchingProcess::verifyCredentialsEnded);

	NetworkResultType errorType = result.resultType;

	// For a potenitial anticipated end
	int httpCode = result.httpResponse.code;
	QString verifyMsg = "";
	CoreResult verifyIssue;

	// Analysing the Twitter response
	switch (errorType) {
		case Network::NO_REQUEST_ERROR: {
			// Credentials were right a priori. Ensures that the user is the right one.
			QVariantMap userMap = result.parsedResult.toMap();
			UserInfos userOfCredentials;
			userOfCredentials.fillWithVariant(QJsonObject::fromVariantMap(userMap));
			UserAccount & account = userConfiguration.getUserAccountRef();
			UserInfos confUser = account.getUser();
			bool rightUser = confUser == userOfCredentials;
			verifyIssue = rightUser ? TOKENS_OK : WRONG_USER;
			if (rightUser) {
				account.setUser(userOfCredentials);
			}
		}break;

		case Network::SERVICE_ERRORS:
			// Building error message
			verifyMsg = ProcessUtils::writeTwitterErrors(result);

			// Looking for specific value of the return code
			verifyIssue = (httpCode / 100 == 5
						   || httpCode == 401
						   || httpCode == 420
						   || httpCode == 429
						   ) ?
						httpResults.value(httpCode)
					  : UNKNOWN_PROBLEM;
			break;

		case Network::API_CALL:
			ProcessUtils::treatApiCallResult(result, verifyMsg, verifyIssue);
			break;

		case Network::JSON_PARSING:
			ProcessUtils::treatQjsonParsingResult(result.parsingErrors,
												  verifyMsg,
												  verifyIssue);
			break;

		default:
			ProcessUtils::treatUnknownResult(result.errorMessage,
											 verifyMsg,
											 verifyIssue);
			break;
	}


	// Keeping on launching Reyn Tweets depending on what happened in the request
	QString errorMsg = "";

	switch (verifyIssue) {
		case TOKENS_OK:
			// Credentials were right. You can save configuration now.
			return saveConfiguration();

		case WRONG_USER:
			// User of the configuration and user of credentials do not match.
			// Getting tokens for the user of the configuration
			verifyIssue = AUTHENTICATION_REQUIRED;
			errorMsg = LaunchingProcess::trUtf8("The user was not the right one.");
			emit authenticationRequired();
			break;

		case TOKENS_NOT_AUTHORIZED:
			// Credentials were wrong for the user.
			// Getting tokens for the user of the configuration.
			verifyIssue = AUTHENTICATION_REQUIRED;
			errorMsg = LaunchingProcess::trUtf8("Tokens for authentication to Twitter were wrong.");
			emit authenticationRequired();
			break;

		case RATE_LIMITED:
			// Rate limited. Asking the user to try later.
			errorMsg = LaunchingProcess::trUtf8("You reach the authentication rate:");
			errorMsg.append(' ').append(verifyMsg);
			break;

		case TWITTER_DOWN:
			// Twitter problem. Asking the user to try later.
			errorMsg = LaunchingProcess::trUtf8("Twitter is down:");
			errorMsg.append(' ').append(verifyMsg);
			break;

		case NETWORK_CALL:
			// Probably problem. Asking the user to try later.
			errorMsg = LaunchingProcess::trUtf8("Problem while connecting to Twitter:");
			errorMsg.append(' ').append(verifyMsg);
			break;

		case PARSE_ERROR:		// Parsing problem. Abort
		case UNKNOWN_PROBLEM:	// Unknown problem. Abort
			errorMsg = verifyMsg;
			break;

		default:
			// Unexpected result. Abort.
			errorMsg = LaunchingProcess::trUtf8("Unexpected result:");
			errorMsg.append(' ').append(verifyMsg);
			break;
	}

	// Telling the control wat happened
	endProcess(verifyIssue, errorMsg);
}


////////////////////////////////////////////////////
// Step 4 : updating and saving the configuration //
////////////////////////////////////////////////////

// Saving the configuartion in the configuration file
void LaunchingProcess::saveConfiguration() {
	QString errorMsg = "";
	CoreResult saveIssue = userConfiguration.save(errorMsg);

	// NOTE : verify the reinit case

	switch (saveIssue) {
		case SAVE_SUCCESSFUL:
			// The application was saved correctly.
			saveIssue = LAUNCH_SUCCESSFUL;
			break;

		case REINIT_SUCCESSFUL:
			errorMsg = LaunchingProcess::trUtf8("User configuration was reset.");
			break;

		case CONFIGURATION_FILE_UNKNOWN:
		case CONFIGURATION_FILE_NOT_OPEN:
			break;

		default:
			saveIssue = UNKNOWN_PROBLEM;
			errorMsg = LaunchingProcess::trUtf8("Unknown problem").append(" : ")
					   .append(errorMsg);
			break;
	}

	// Ending the process
	endProcess(saveIssue, errorMsg);
}


///////////////////////////
// Filling configuration //
///////////////////////////

// Filling the TwitterAuthenticator of Twitter with consumer tokens
void LaunchingProcess::fillTwitterOAuthAppSettings() {
	ReynTwitterCalls::setAppTokens(appConfiguration.getConsumerKey(),
								   appConfiguration.getConsumerSecret(),
								   appConfiguration.getCallbackURL());
}

// Filling the TwitterAuthenticator of Twitter with access tokens
void LaunchingProcess::fillTwitterOAuthUserSettings() {
	ReynTwitterCalls::setUserTokens(userConfiguration.getUserAccount().getAccessToken(),
									userConfiguration.getUserAccount().getTokenSecret());
}

// Filling the TwitLongerAuthenticator with the TwitLonger IDs of the application.
void LaunchingProcess::fillTwitLongerAppSettings() {
	TwitLongerCalls::setAppTokens(appConfiguration.getTwitLongerAppName(),
								  appConfiguration.getTwitLongerAPIKey());
}
