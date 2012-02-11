/// @file oauthprocess.cpp
/// @brief Implementation of OAuthProcess
///
/// Revisions of the file older than r204 are in /trunk/ReynTweets/controls
/// r204 is in /trunk/ReynTweets/logic
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011 Romain Ducher
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

#include "oauthprocess.hpp"

// Constructor
OAuthProcess::OAuthProcess() :
	GenericProcess(),
	twitter(this)
{}

// Destructor
OAuthProcess::~OAuthProcess() {}

// Resetting the tokens.
void OAuthProcess::resetTokens() {
	ReynTwitterCalls::resetTokens();
}

// Building the result of the process
void OAuthProcess::buildResult(bool processOK,
							   CoreResult issue,
							   QString errMsg, bool isFatal,
							   QByteArray accessToken, QByteArray tokenSecret,
							   qlonglong userID, QString screenName)
{
	processResult.processOK = processOK;
	processResult.processIssue = issue;
	processResult.errorMsg = errMsg;
	processResult.fatalError = isFatal;

	QVariantMap resultMap;
	resultMap.insert("access_token", qVariantFromValue(accessToken));
	resultMap.insert("token_secret", qVariantFromValue(tokenSecret));
	resultMap.insert("user_id", qVariantFromValue(userID));
	resultMap.insert("screen_name", qVariantFromValue(screenName));

	processResult.results = resultMap;
}


///////////////////////////////
// OAuth Authentication flow //
///////////////////////////////

// Starting the OAuth authentication flow
void OAuthProcess::startProcess() {
	resetTokens();		// Doing it from scratch by erasing the old tokens
	requestToken();
}

// Demanding a Request Token
void OAuthProcess::requestToken() {
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(requestTokenDemanded(ResultWrapper)));
	twitter.requestToken();
}

// Treatments after the request for Request Tokens
void OAuthProcess::requestTokenDemanded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == INVALID_RESULT) {
		return;
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(requestTokenDemanded(ResultWrapper)));

	ErrorType errorType = result.resultType;

	// For a potenitial anticipated end
	int httpCode = result.httpResponse.code;
	QString errorMsg = "";
	bool isFatal = false;
	CoreResult issue;


	switch (errorType) {
		case NO_ERROR: {
			// The request was successful. Was the callback URL confirmed ?
			QVariantMap parsedResults = result.parsedResult.toMap();
			if (parsedResults.value("oauth_callback_confirmed").toBool()) {
				// Let's authorize the request tokens !
				return authorize();
			} else {
				// Cannot keep on if the URL is not confirmed
				errorMsg = OAuthProcess::trUtf8("Callback URL not confirmed.");
				isFatal = true;
				issue = NO_TOKENS;
			}
		}break;

		case TWITTER_ERRORS:
			// Building error message
			errorMsg = OAuthProcess::trUtf8("Twitter errors:");

			for (QList<ResponseInfos>::Iterator it = result.twitterErrors.begin();
				 it < result.twitterErrors.end();
				 ++it)
			{
				errorMsg.append(OAuthProcess::trUtf8("Error "))
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
			break;

		case API_CALL:
			// Building error message
			errorMsg = OAuthProcess::trUtf8("Network error ");
			errorMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(result.httpResponse.message)
					.append(" :\n")
					.append(result.errorMessage)
					.append('.');

			// Looking for specific value of the return code
			issue = NETWORK_CALL;
			break;

		case OAUTH_PARSING:
			// Building error message
			errorMsg = OAuthProcess::trUtf8("Parsing error:");
			errorMsg.append('\n')
					.append(result.parsingErrors.message);
			issue = PARSE_ERROR;
			break;

		default:
			// Unexpected problem. Abort.
			errorMsg = OAuthProcess::trUtf8("Unexpected problem:");
			errorMsg.append('\n').append(result.errorMessage).append('.');
			isFatal = true;
			issue = UNKNOWN_PROBLEM;
			break;
	}

	// Failed end
	buildResult(false, issue, errorMsg, isFatal);
	endProcess();
}

// Authorize the request tokens
void OAuthProcess::authorize() {
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(authorizeDemanded(ResultWrapper)));
	twitter.authorize();
}

// Treatments after the request for authorizing Request Tokens
void OAuthProcess::authorizeDemanded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == INVALID_RESULT) {
		return;
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(authorizeDemanded(ResultWrapper)));

	ErrorType errorType = result.resultType;

	// For a potenitial anticipated end
	int httpCode = result.httpResponse.code;
	QString errorMsg = "";
	bool isFatal = false;
	CoreResult issue;

	switch (errorType) {
		case NO_ERROR:
			// The user can give its credentials now
			emit userCredentialsRequired();
			return;

		case TWITTER_ERRORS:
			// Building error message
			errorMsg = OAuthProcess::trUtf8("Twitter errors:");

			for (QList<ResponseInfos>::Iterator it = result.twitterErrors.begin();
				 it < result.twitterErrors.end();
				 ++it)
			{
				errorMsg.append(OAuthProcess::trUtf8("Error "))
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
			} else if (httpCode == 401) {
				issue = TOKENS_NOT_AUTHORIZED;
			} else if (httpCode == 420) {
				issue = RATE_LIMITED;
			} else {
				issue = NO_TOKENS;
			}
			break;

		case API_CALL:
			// Building error message
			errorMsg = OAuthProcess::trUtf8("Network error ");
			errorMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(result.httpResponse.message)
					.append(" :\n")
					.append(result.errorMessage)
					.append('.');

			// Looking for specific value of the return code
			issue = NETWORK_CALL;
			break;

		case HTML_PARSING:
			// Building error message
			errorMsg = OAuthProcess::trUtf8("Parsing error:");
			errorMsg.append('\n')
					.append(result.parsingErrors.message);
			issue = PARSE_ERROR;
			break;

		default:
			// Unexpected problem. Abort.
			errorMsg = OAuthProcess::trUtf8("Unexpected problem:");
			errorMsg.append('\n').append(result.errorMessage).append('.');
			isFatal = true;
			issue = UNKNOWN_PROBLEM;
			break;
	}

	// Failed end
	buildResult(false, issue, errorMsg, isFatal);
	endProcess();
}

// Allowing Reyn Tweets :)
void OAuthProcess::authorizeReynTweets(QString login, QString password) {
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(postAuthorizeDemanded(ResultWrapper)));
	twitter.postAuthorize(login, password, false);
}

// Denying Reyn Tweets :(
void OAuthProcess::denyReynTweets(QString login, QString password) {
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(postAuthorizeDemanded(ResultWrapper)));
	twitter.postAuthorize(login, password, true);
}

// Treatments for the POST authorizing request
void OAuthProcess::postAuthorizeDemanded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == INVALID_RESULT) {
		return;
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(postAuthorizeDemanded(ResultWrapper)));

	ErrorType errorType = result.resultType;

	// For a potenitial anticipated end
	int httpCode = result.httpResponse.code;
	QString errorMsg = "";
	bool isFatal = false;
	CoreResult issue;

	switch (errorType) {
		case NO_ERROR: {
			QVariantMap resultMap = result.parsedResult.toMap();
			bool urlOK = resultMap.value("urlOK").toBool();

			if (urlOK) {
				bool rightCrdentials = resultMap.value("rightCredentials").toBool();
				emit credentialsOK(rightCrdentials);

				if (rightCrdentials) {
					if (resultMap.value("denied").toBool()) {
						// Reyn Tweets is denied. The process ends.
						buildResult(true, DENIED);
						emit processEnded();
					} else {
						// Request tokens are authorized. Let's get access tokens.
						accessToken();
					}
				}

				return;		// The process does not fail for the moment
			} else {
				errorMsg = OAuthProcess::trUtf8("Unexpected redirection. Process aborted.").append('\n');
				isFatal = true;
				issue = POST_AUTHORIZING_FAILED;
			}
		}break;

		case TWITTER_ERRORS:
			// Building error message
			errorMsg = OAuthProcess::trUtf8("Twitter errors:");

			for (QList<ResponseInfos>::Iterator it = result.twitterErrors.begin();
				 it < result.twitterErrors.end();
				 ++it)
			{
				errorMsg.append(OAuthProcess::trUtf8("Error "))
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
			} else if (httpCode == 401) {
				issue = TOKENS_NOT_AUTHORIZED;
			} else if (httpCode == 420) {
				issue = RATE_LIMITED;
			} else {
				issue = NO_TOKENS;
			}
			break;

		case API_CALL:
			// Building error message
			errorMsg = OAuthProcess::trUtf8("Network error ");
			errorMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(result.httpResponse.message)
					.append(" :\n")
					.append(result.errorMessage)
					.append('.');

			// Looking for specific value of the return code
			issue = NETWORK_CALL;
			break;

		case HTML_PARSING:
		case OAUTH_PARSING:
			// Building error message
			errorMsg = OAuthProcess::trUtf8("Parsing error:");
			errorMsg.append('\n')
					.append(result.parsingErrors.message);
			issue = PARSE_ERROR;
			break;

		default:
			// Unexpected problem. Abort.
			errorMsg = OAuthProcess::trUtf8("Unexpected problem:");
			errorMsg.append('\n').append(result.errorMessage).append('.');
			isFatal = true;
			issue = UNKNOWN_PROBLEM;
			break;
	}

	// Failed end
	buildResult(false, issue, errorMsg, isFatal);
	endProcess();
}

// Demanding an Access Token
void OAuthProcess::accessToken() {
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(accessTokenDemanded(ResultWrapper)));
	twitter.accessToken();
}

// Treatments after the request for Access Tokens
void OAuthProcess::accessTokenDemanded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == INVALID_RESULT) {
		return;
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(accessTokenDemanded(ResultWrapper)));

	ErrorType errorType = result.resultType;

	// For a potenitial anticipated end
	int httpCode = result.httpResponse.code;
	QString errorMsg = "";
	bool isFatal = false;
	CoreResult issue;

	switch (errorType) {
		case NO_ERROR: {
			// The authentication process is ended.

			// Extract the different values
			QVariantMap resultMap = result.parsedResult.toMap();
			QByteArray accessToken = resultMap.value("oauth_token").toByteArray();
			QByteArray tokenSecret = resultMap.value("oauth_token_secret").toByteArray();
			qlonglong userID = resultMap.value("user_id").toLongLong();
			QString screenName = resultMap.value("screen_name").toString();

			// Successful end
			buildResult(true,
						AUTHORIZED,
						"", false,
						accessToken, tokenSecret,
						userID, screenName);
			endProcess();
		}return;

		case TWITTER_ERRORS:
			// Building error message
			errorMsg = OAuthProcess::trUtf8("Twitter errors:");

			for (QList<ResponseInfos>::Iterator it = result.twitterErrors.begin();
				 it < result.twitterErrors.end();
				 ++it)
			{
				errorMsg.append(OAuthProcess::trUtf8("Error "))
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
			} else if (httpCode == 401) {
				issue = TOKENS_NOT_AUTHORIZED;
			} else if (httpCode == 420) {
				issue = RATE_LIMITED;
			} else {
				issue = NO_TOKENS;
			}
			break;

		case API_CALL:
			// Building error message
			errorMsg = OAuthProcess::trUtf8("Network error ");
			errorMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(result.httpResponse.message)
					.append(" :\n")
					.append(result.errorMessage)
					.append('.');

			// Looking for specific value of the return code
			issue = NETWORK_CALL;
			break;

		case OAUTH_PARSING:
			// Building error message
			errorMsg = OAuthProcess::trUtf8("Parsing error:");
			errorMsg.append('\n')
					.append(result.parsingErrors.message);
			issue = PARSE_ERROR;
			break;

		default:
			// Unexpected problem. Abort.
			errorMsg = OAuthProcess::trUtf8("Unexpected problem:");
			errorMsg.append('\n').append(result.errorMessage).append('.');
			isFatal = true;
			issue = UNKNOWN_PROBLEM;
			break;
	}

	// Failed end
	buildResult(false, issue, errorMsg, isFatal);
	endProcess();
}
