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
	appConfiguration(AppConfiguration::getReynTweetsConfiguration()),
	userconfReinit(false)
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
	QString errMsg = "";
	ReynTweets::CoreResult loadEnd = appConfiguration.load(errMsg);

	switch(loadEnd) {
		case ReynTweets::LOAD_CONFIGURATION_SUCCESSFUL:
			fillTwitterOAuthAppSettings();
			fillTwitLongerAppSettings();
			return loadConfiguration();

		// Expected errors
		case ReynTweets::CONFIGURATION_FILE_NOT_OPEN:
		case ReynTweets::PARSE_ERROR:
		case ReynTweets::CONFIGURATION_FILE_UNKNOWN:
		case ReynTweets::EXPECTED_KEY:
			break;

		default:
			loadEnd = ReynTweets::UNKNOWN_PROBLEM;
			break;
	}

	// Failed end
	endProcess(loadEnd, errMsg);
}


/////////////////////////////////////////////
// Step 2 : loading the user configuration //
/////////////////////////////////////////////

// Loading the configuartion from the configuration file
void LaunchingProcess::loadConfiguration() {
	QString errorMsg = "";
	ReynTweets::CoreResult loadEnd = userConfiguration.load(errorMsg);

	switch (loadEnd) {
		case ReynTweets::REINIT_SUCCESSFUL:
			userconfReinit = true;

		case ReynTweets::LOAD_CONFIGURATION_SUCCESSFUL:
			// The configuration was loaded correctly. Let's check the credentials
			fillTwitterOAuthUserSettings();
			return checkTokens();

		case ReynTweets::PARSE_ERROR:
		case ReynTweets::EXPECTED_KEY:
			loadEnd = ReynTweets::LOADING_CONFIGURATION_ERROR;
			break;

		case ReynTweets::LOADING_CONFIGURATION_ERROR:
		case ReynTweets::CONFIGURATION_FILE_UNKNOWN:
		case ReynTweets::CONFIGURATION_FILE_NOT_OPEN:
			break;

		default:
			// Unknown problem.
			loadEnd = ReynTweets::UNKNOWN_PROBLEM;
			errorMsg = LaunchingProcess::trUtf8("Unknown problem").append(" : ")
					   .append(errorMsg);
			break;
	}

	// Failed end
	endProcess(loadEnd, errorMsg);
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
		emit authenticationRequired();
		endProcess(ReynTweets::AUTHENTICATION_REQUIRED,
				   LaunchingProcess::trUtf8("Unexpected empty Twitter tokens."));
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
	if (result.resultType == LibRT::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, &ReynTwitterCalls::sendResult,
			   this, &LaunchingProcess::verifyCredentialsEnded);

	// For a potenitial anticipated end
	QString verifyMsg = "";
	ReynTweets::CoreResult verifyEnd;

	// Analysing the Twitter response
	switch (result.resultType) {
		case LibRT::NO_REQUEST_ERROR: {
			// Credentials were right a priori. Ensures that the user is the right one.
			QVariantMap userMap = result.parsedResult.toMap();
			UserInfos userOfCredentials;
			userOfCredentials.fillWithVariant(QJsonObject::fromVariantMap(userMap));
			UserAccount & account = userConfiguration.getUserAccountRef();

			bool rightUser = account.getUser() == userOfCredentials;
			verifyEnd = rightUser ?
							ReynTweets::TOKENS_OK
						  : ReynTweets::WRONG_USER;
			if (rightUser) {
				account.setUser(userOfCredentials);
			}
		}break;

		case LibRT::SERVICE_ERRORS:
			// Building error message
			verifyMsg = ProcessUtils::writeTwitterErrors(result);

			// Looking for specific value of the return code
			verifyEnd = ReynTweets::getCoreResultFromCode(result.getHTTPCode());

			if (verifyEnd != ReynTweets::TWITTER_DOWN
					&& verifyEnd != ReynTweets::RATE_LIMITED
					&& verifyEnd != ReynTweets::AUTHENTICATION_REQUIRED)
			{
				verifyEnd = ReynTweets::UNKNOWN_PROBLEM;
			}
			break;

		case LibRT::API_CALL:
			ProcessUtils::treatApiCallResult(result, verifyMsg, verifyEnd);
			break;

		case LibRT::JSON_PARSING:
			ProcessUtils::treatQjsonParsingResult(result.parsingErrors,
												  verifyMsg,
												  verifyEnd);
			break;

		default:
			ProcessUtils::treatUnknownResult(result.errorMessage,
											 verifyMsg,
											 verifyEnd);
			break;
	}


	// Keeping on launching Reyn Tweets depending on what happened in the request
	QString errorMsg = "";

	switch (verifyEnd) {
		case ReynTweets::TOKENS_OK:
			// Credentials were right. You can save configuration now.
			return saveConfiguration();

		case ReynTweets::WRONG_USER:
			// User of the configuration and user of credentials do not match.
			// Getting tokens for the user of the configuration
			verifyEnd = ReynTweets::AUTHENTICATION_REQUIRED;
			errorMsg = LaunchingProcess::trUtf8("The user was not the right one.");
			emit authenticationRequired();
			break;

		case ReynTweets::TOKENS_NOT_AUTHORIZED:
			// Credentials were wrong for the user.
			// Getting tokens for the user of the configuration.
			verifyEnd = ReynTweets::AUTHENTICATION_REQUIRED;
			errorMsg = LaunchingProcess::trUtf8("Tokens for authentication to Twitter were wrong.");
			emit authenticationRequired();
			break;

		case ReynTweets::RATE_LIMITED:
			// Rate limited. Asking the user to try later.
			errorMsg = LaunchingProcess::trUtf8("You reach the authentication rate:");
			errorMsg.append(' ').append(verifyMsg);
			break;

		case ReynTweets::TWITTER_DOWN:
			// Twitter problem. Asking the user to try later.
			errorMsg = LaunchingProcess::trUtf8("Twitter is down:");
			errorMsg.append(' ').append(verifyMsg);
			break;

		case ReynTweets::NETWORK_CALL:
			// Probably problem. Asking the user to try later.
			errorMsg = LaunchingProcess::trUtf8("Problem while connecting to Twitter:");
			errorMsg.append(' ').append(verifyMsg);
			break;

		case ReynTweets::PARSE_ERROR:		// Parsing problem. Abort
		case ReynTweets::UNKNOWN_PROBLEM:	// Unknown problem. Abort
			errorMsg = verifyMsg;
			break;

		default:
			// Unexpected result. Abort.
			errorMsg = LaunchingProcess::trUtf8("Unexpected result:");
			errorMsg.append(' ').append(verifyMsg);
			break;
	}

	// Telling the control wat happened
	endProcess(verifyEnd, errorMsg);
}


////////////////////////////////////////////////////
// Step 4 : updating and saving the configuration //
////////////////////////////////////////////////////

// Saving the configuartion in the configuration file
void LaunchingProcess::saveConfiguration() {
	QString errorMsg = "";
	ReynTweets::CoreResult saveEnd = userConfiguration.save(errorMsg);

	switch (saveEnd) {
		case ReynTweets::SAVE_SUCCESSFUL:
			// The application was saved correctly.
			saveEnd = ReynTweets::LAUNCH_SUCCESSFUL;
			break;

		case ReynTweets::REINIT_SUCCESSFUL:
			userconfReinit = true;
			break;

		case ReynTweets::CONFIGURATION_FILE_UNKNOWN:
		case ReynTweets::CONFIGURATION_FILE_NOT_OPEN:
			break;

		default:
			saveEnd = ReynTweets::UNKNOWN_PROBLEM;
			errorMsg = LaunchingProcess::trUtf8("Unknown problem").append(" : ")
					   .append(errorMsg);
			break;
	}

	// Ending the process
	endProcess(saveEnd, errorMsg);
}

void LaunchingProcess::endProcess(ReynTweets::CoreResult procEnd,
								  QString errorMessage)
{
	if (userconfReinit) {
		errorMessage.append(' ')
				.append(LaunchingProcess::trUtf8("User configuration was reset."));
	}

	GenericProcess::endProcess(procEnd,
							   QVariant::fromValue<bool>(userconfReinit),
							   errorMessage);
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
