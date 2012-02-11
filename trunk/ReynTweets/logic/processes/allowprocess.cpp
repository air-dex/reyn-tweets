/// @file allowprocess.cpp
/// @brief Implementation of AllowProcess
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

#include "allowprocess.hpp"

// Constructor
AllowProcess::AllowProcess(ReynTweetsConfiguration & conf) :
	OAuthProcess(),
	authEnded(false),
	configuration(conf)
{}

// End of the process
void AllowProcess::endProcess() {
	// Is the configuration saved ?
	if (authEnded) {
		emit processEnded();
	} else {
		authEnded = true;

		// Is it an anticipated end (auth does not end successfully) ?
		bool anticipatedEnd = !processResult.processOK
				|| processResult.processOK && processResult.processIssue == DENIED;

		processResult.results.value("is_authorized",
									processResult.processIssue == AUTHORIZED);

		if (anticipatedEnd) {
			emit processEnded();
		} else {
			// Retrieve the user and save

			// Extract the different values
			QVariantMap resultMap = processResult.results;
			QByteArray accessToken = resultMap.value("access_token").toByteArray();
			QByteArray tokenSecret = resultMap.value("token_secret").toByteArray();
			qlonglong userID = resultMap.value("user_id").toLongLong();
			QString screenName = resultMap.value("screen_name").toString();

			updateConfiguration(accessToken, tokenSecret, userID, screenName);
		}
	}
}

// Uploading the configuration with the authentified user after an authentication process
void AllowProcess::updateConfiguration(QByteArray accessToken,
									   QByteArray tokenSecret,
									   qlonglong id, QString)
{
	// Updating the tokens
	UserAccount account = configuration.getUserAccount();
	account.setAccessToken(accessToken.toBase64());
	account.setTokenSecret(tokenSecret.toBase64());
	configuration.setUserAccount(account);

	// Getting informations about the user behind the account
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(retrieveUserEnded(ResultWrapper)));
	twitter.showUser(id);
}

// Updating a user after requesting it to Twitter
void AllowProcess::retrieveUserEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result == RequestResult()) {
		return;
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(retrieveUserEnded(ResultWrapper)));

	ErrorType errorType = result.resultType;

	// For a potenitial anticipated end
	int httpCode = result.httpResponse.code;
	QString errorMsg = "";
	bool isFatal = false;
	CoreResult issue;

	switch (errorType) {
		case NO_ERROR: {
			// Get user, put it in the conf and save
			QVariantMap parsedResults = result.parsedResult.toMap();
			User u;
			u.fillWithVariant(parsedResults);
			UserAccount account = configuration.getUserAccount();
			account.setUser(u);
			configuration.setUserAccount(account);
			saveConfiguration();
		}return;

		case TWITTER_ERRORS:
			// Building error message
			errorMsg = AllowProcess::trUtf8("Twitter errors:");

			for (QList<ResponseInfos>::Iterator it = result.twitterErrors.begin();
				 it < result.twitterErrors.end();
				 ++it)
			{
				errorMsg.append(AllowProcess::trUtf8("Error "))
						.append(QString::number(it->code))
						.append(" : ")
						.append(it->message)
						.append(".\n");
			}

			// Erasing the last '\n'
			errorMsg.chop(1);

			// Looking for specific value of the return code
			if (httpCode / 100 == 5) {
				issue = TWITTER_DOWN;
			} else if (httpCode == 420) {
				issue = RATE_LIMITED;
			} else {
				issue = NO_TOKENS;
			}

			isFatal = false;
			break;

		case API_CALL:
			// Retrieving network informations
			int httpCode = result.httpResponse.code;

			// Building error message
			errorMsg = AllowProcess::trUtf8("Network error ");
			errorMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(result.httpResponse.message)
					.append(" :\n")
					.append(result.errorMessage)
					.append('.');

			// Looking for specific value of the return code
			issue = NETWORK_CALL;

			isFatal = false;
			break;

		case QJSON_PARSING:
			// Building error message
			errorMsg = AllowProcess::trUtf8("Parsing error:");
			errorMsg.append('\n')
					.append(AllowProcess::trUtf8("Line "))
					.append(QString::number(result.parsingErrors.code))
					.append(" : ")
					.append(result.parsingErrors.message);
			issue = PARSE_ERROR;
			break;

		default:
			// Unexpected problem. Abort.
			errorMsg = AllowProcess::trUtf8("Unexpected problem :");
			errorMsg.append('\n').append(result.getErrorMessage()).append(".\n");
			issue = UNKNOWN_PROBLEM;
			break;
	}

	// Failed end
	buildResult(false, issue, errorMsg, isFatal);
	endProcess();
}

void AllowProcess::saveConfiguration() {
	CoreResult saveIssue = configuration.save();
	bool processOK = false;
	QString errorMsg = "";
	bool isFatal = true;

	switch (saveIssue) {
		case SAVE_SUCCESSFUL:
			// The application was saved correctly.
			processOK = true;
			saveIssue = ALLOW_SUCCESSFUL;
			isFatal = false;
			break;

		case CONFIGURATION_FILE_UNKNOWN:
			errorMsg = AllowProcess::trUtf8("Configuration file does not exist.");
			break;

		case CONFIGURATION_FILE_NOT_OPEN:
			errorMsg = AllowProcess::trUtf8("Configuration file cannot be opened.");
			break;

		default:
			errorMsg = AllowProcess::trUtf8("Unknown problem");
			break;
	}

	// Ending the process
	buildResult(processOK, saveIssue, errorMsg, isFatal);
	endProcess();
}
