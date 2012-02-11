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

// Constructor
LaunchingProcess::LaunchingProcess(ReynTweetsConfiguration & conf) :
	GenericProcess(),
	twitter(this),
	configuration(conf)
{}

// Starting the process
void LaunchingProcess::startProcess() {
	loadConfiguration();
}


////////////////////////////////////////
// Step 1 : loading the configuration //
////////////////////////////////////////

// Loading the configuartion from the configuration file
void LaunchingProcess::loadConfiguration() {
	CoreResult loadIssue = configuration.load();

	QString errorMsg = "";

	switch (loadIssue) {
		case LOAD_CONFIGURATION_SUCCESSFUL:
			// The configuration was loaded correctly. Let's check the credentials
			fillOAuthManager();
			return checkTokens();

		case CONFIGURATION_FILE_UNKNOWN:
			errorMsg = LaunchingProcess::trUtf8("Configuration file does not exist.");
			break;

		case CONFIGURATION_FILE_NOT_OPEN:
			errorMsg = LaunchingProcess::trUtf8("Configuration file cannot be opened.");
			break;

		case LOADING_CONFIGURATION_ERROR:
			errorMsg = LaunchingProcess::trUtf8("Configuration cannot be loaded.");
			break;

		default:
			// Unknown problem.
			errorMsg = LaunchingProcess::trUtf8("Unknown problem");
			loadIssue = UNKNOWN_PROBLEM;
			break;
	}

	// Telling the component that the launching process has ended fatally.
	buildResult(false, loadIssue, errorMsg, true);
	endProcess();
}


////////////////////////////////////////
// Step 2 : verifying the credentials //
////////////////////////////////////////

// Checks if the access tokens seem legit.
void LaunchingProcess::checkTokens() {
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(verifyCredentialsEnded(ResultWrapper)));
	twitter.verifyCredentials(true, false);
}

// Slot executed after verifying credentials.
void LaunchingProcess::verifyCredentialsEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == INVALID_RESULT) {
		return;
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(verifyCredentialsEnded(ResultWrapper)));

	ErrorType errorType = result.resultType;

	// For a potenitial anticipated end
	int httpCode = result.httpResponse.code;
	QString verifyMsg = "";
	CoreResult verifyIssue;
	bool isFatal;

	// Analysing the Twitter response
	switch (errorType) {
		case NO_ERROR: {
			// Credentials were right a priori. Ensures that the user is the right one.
			QVariantMap userMap = result.parsedResult.toMap();
			User userOfCredentials;
			userOfCredentials.fillWithVariant(userMap);
			UserAccount account = configuration.getUserAccount();
			User confUser = account.getUser();
			bool rightUser = confUser.getID() == userOfCredentials.getID();
			verifyIssue = rightUser ? TOKENS_OK : WRONG_USER;
			if (rightUser) {
				account.setUser(userOfCredentials);
			}
		}break;

		case TWITTER_ERRORS:
			// Building error message
			verifyMsg = LaunchingProcess::trUtf8("Twitter errors:");

			for (QList<ResponseInfos>::Iterator it = result.twitterErrors.begin();
				 it < result.twitterErrors.end();
				 ++it)
			{
				verifyMsg.append(LaunchingProcess::trUtf8("Error "))
						.append(QString::number(it->code))
						.append(" : ")
						.append(it->message)
						.append(".\n");
			}

			// Erasing the last '\n'
			verifyMsg.chop(1);

			// Looking for specific value of the return code
			if (httpCode / 100 == 5) {
				verifyIssue = TWITTER_DOWN;
			} else if (httpCode == 401) {
				verifyIssue = TOKENS_NOT_AUTHORIZED;
			} else if (httpCode == 420) {
				verifyIssue = RATE_LIMITED;
			} else {
				verifyIssue = UNKNOWN_PROBLEM;
			}
			break;

		case API_CALL:
			// Building error message
			verifyMsg = LaunchingProcess::trUtf8("Network error ");
			verifyMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(result.httpResponse.message)
					.append(" :\n")
					.append(result.errorMessage)
					.append('.');

			// Looking for specific value of the return code
			verifyIssue = NETWORK_CALL;
			break;

		case QJSON_PARSING:
			// Building error message
			verifyMsg = LaunchingProcess::trUtf8("Parsing error:");
			verifyMsg.append('\n')
					.append(LaunchingProcess::trUtf8("Line "))
					.append(QString::number(result.parsingErrors.code))
					.append(" : ")
					.append(result.parsingErrors.message);
			verifyIssue = PARSE_ERROR;
			break;

		default:
			// Unexpected problem. Abort.
			verifyMsg = LaunchingProcess::trUtf8("Unexpected problem:");
			verifyMsg.append('\n').append(result.errorMessage).append('.');
			isFatal = true;
			verifyIssue = UNKNOWN_PROBLEM;
			break;
	}


	// Keeping on launching Reyn Tweets depending on what happened in the request
	bool processOK;
	QString errorMsg = "";

	switch (verifyIssue) {
		case TOKENS_OK:
			// Credentials were right. You can save configuration now.
			return saveConfiguration();

		case WRONG_USER:
			// User of the configuration and user of credentials do not match.
			// Getting tokens for the user of the configuration
			processOK = true;
			verifyIssue = AUTHENTICATION_REQUIRED;
			errorMsg = LaunchingProcess::trUtf8("The user was not the right one.");
			isFatal = false;
			emit authenticationRequired();
			break;

		case TOKENS_NOT_AUTHORIZED:
			// Credentials were wrong for the user.
			// Getting tokens for the user of the configuration.
			processOK = true;
			verifyIssue = AUTHENTICATION_REQUIRED;
			errorMsg = LaunchingProcess::trUtf8("Tokens for authentication to Twitter were wrong.");
			isFatal = false;
			emit authenticationRequired();
			break;

		case RATE_LIMITED:
			// Rate limited. Asking the user to try later.
			processOK = false;
			errorMsg = LaunchingProcess::trUtf8("You reach the authentication rate:");
			errorMsg.append('\n').append(verifyMsg);
			isFatal = false;
			break;

		case TWITTER_DOWN:
			// Twitter problem. Asking the user to try later.
			processOK = false;
			errorMsg = LaunchingProcess::trUtf8("Twitter is down:");
			errorMsg.append('\n').append(verifyMsg);
			isFatal = false;
			break;

		case NETWORK_CALL:
			// Probably problem. Asking the user to try later.
			processOK = false;
			errorMsg = LaunchingProcess::trUtf8("Problem while connecting to Twitter:");
			errorMsg.append('\n').append(verifyMsg);
			isFatal = false;
			break;

		case PARSE_ERROR:
			// Unknown problem. Abort ?
			processOK = false;
			errorMsg = verifyMsg;
			isFatal = true;
			break;

		case UNKNOWN_PROBLEM:
			// Unknown problem. Abort ?
			processOK = false;
			errorMsg = LaunchingProcess::trUtf8("Unknown prolem:");
			errorMsg.append('\n').append(verifyMsg);
			isFatal = true;
			break;

		default:
			// Unexpected result. Abort.
			processOK = false;
			errorMsg = LaunchingProcess::trUtf8("Unexpected result:");
			errorMsg.append('\n').append(verifyMsg);
			isFatal = true;
			break;
	}

	// Telling the component wat happens
	buildResult(processOK, verifyIssue, errorMsg, isFatal);
	endProcess();
}


////////////////////////////////////////////////////
// Step 3 : updating and saving the configuration //
////////////////////////////////////////////////////

// Saving the configuartion in the configuration file
void LaunchingProcess::saveConfiguration() {
	CoreResult saveIssue = configuration.save();
	bool processOK = false;
	QString errorMsg = "";
	bool isFatal = true;

	switch (saveIssue) {
		case SAVE_SUCCESSFUL:
			// The application was saved correctly.
			processOK = true;
			saveIssue = LAUNCH_SUCCESSFUL;
			isFatal = false;
			break;

		case CONFIGURATION_FILE_UNKNOWN:
			errorMsg = LaunchingProcess::trUtf8("Configuration file does not exist.");
			break;

		case CONFIGURATION_FILE_NOT_OPEN:
			errorMsg = LaunchingProcess::trUtf8("Configuration file cannot be opened.");
			break;

		default:
			saveIssue = UNKNOWN_PROBLEM;
			errorMsg = LaunchingProcess::trUtf8("Unknown problem");
			break;
	}

	// Ending the process
	buildResult(processOK, saveIssue, errorMsg, isFatal);
	endProcess();
}


//////////
// Misc //
//////////

// Filling the OAuth manager of the ReynTwitterCalls with right credentials
void LaunchingProcess::fillOAuthManager() {
	ReynTwitterCalls::setNewTokens(configuration.getUserAccount().getAccessToken(),
								   configuration.getUserAccount().getTokenSecret(),
								   ReynTweetsConfiguration::getConsumerKey(),
								   ReynTweetsConfiguration::getConsumerSecret());
}

// Building the process results
void LaunchingProcess::buildResult(bool processOK,
								   CoreResult issue,
								   QString errMsg,
								   bool isFatal)
{
	processResult.processOK = processOK;
	processResult.processIssue = issue;
	processResult.errorMsg = errMsg;
	processResult.fatalError = isFatal;
	processResult.results = QVariantMap();
}
