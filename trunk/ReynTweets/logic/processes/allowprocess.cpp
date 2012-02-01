#include "allowprocess.hpp"

AllowProcess::AllowProcess(ReynTweetsConfiguration & conf) :
	OAuthProcess(),
	authEnded(false),
	configuration(conf)
{}

void AllowProcess::endProcess() {
	// Is the configuration saved ?
	if (authEnded) {
		emit processEnded();
	} else {
		authEnded = true;

		// Is it an anticipated end (auth does not end successfully) ?
		bool anticipatedEnd = !processResult.processOK
				|| processResult.processOK && processResult.processIssue == DENIED;

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
	UserAccount & account = configuration.getUserAccount();
	account.setAccessToken(accessToken.toBase64());
	account.setTokenSecret(tokenSecret.toBase64());

	// Getting informations about the user behind the account
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(retrieveUserEnded(ResultWrapper)));
	twitter.showUser(id);
}

// Updating a user after requesting it to Twitter
void AllowProcess::retrieveUserEnded(ResultWrapper res) {
	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(retrieveUserEnded(ResultWrapper)));

	RequestResult result = res.accessResult(this);
	ErrorType errorType = result.getErrorType();

	CoreResult issue;
	QString errorMsg = "";
	bool isFatal = true;

	switch (errorType) {
		case NO_ERROR: {
			// Get user, put it in the conf and save
			QVariantMap parsedResults = result.getParsedResult().toMap();
			User u;
			u.fillWithVariant(parsedResults);
			UserAccount & account = configuration.getUserAccount();
			account.setUser(u);
			saveConfiguration();
		}return;

		case API_CALL: {
			// Retrieving network informations
			int httpCode = result.getHttpCode();
			QString httpReason = result.getHttpReason();

			// Building error message
			errorMsg = LaunchingProcess::trUtf8("Network error ");
			errorMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(httpReason)
					.append(" :\n")
					.append(result.getErrorMessage())
					.append(".\n");

			// Looking for specific value of the return code
			if (httpCode / 100 == 5) {
				issue = TWITTER_DOWN;
			} else if (httpCode == 420) {
				issue = RATE_LIMITED;
			} else {
				issue = NO_TOKENS;
			}

			isFatal = false;
		}break;

		case OAUTH_PARSING:
			// Building error message
			errorMsg = LaunchingProcess::trUtf8("Parsing error :\n");
			errorMsg.append(result.getParsingErrorMessage());
			issue = PARSE_ERROR;
			break;

		default:
			// Unexpected problem. Abort.
			errorMsg = LaunchingProcess::trUtf8("Unexpected problem :\n");
			errorMsg.append(result.getErrorMessage()).append(".\n");
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
