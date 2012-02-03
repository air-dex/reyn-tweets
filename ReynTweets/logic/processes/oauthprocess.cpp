/// @file oauthprocess.cpp
/// @brief Implementation of OAuthProcess
/// @author Romain Ducher

/*
Copyright 2011 Romain Ducher

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
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

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
	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(requestTokenDemanded(ResultWrapper)));

	RequestResult result = res.accessResult(this);
	ErrorType errorType = result.getErrorType();

	// For a potenitial anticipated end
	QString errorMsg = "";
	bool isFatal = false;
	CoreResult issue;


	switch (errorType) {
		case NO_ERROR: {
			QVariantMap parsedResults = result.getParsedResult().toMap();
			// The request was successful. Was the callback URL confirmed ?
			if (parsedResults.value("oauth_callback_confirmed").toBool()) {
				// Let's authorize the request tokens !
				return authorize();
			} else {
				// Cannot keep on if the URL is not confirmed
				errorMsg = OAuthProcess::trUtf8("Callback URL not confirmed.");
				isFatal = true;
				issue = NO_TOKENS;
				emit errorProcess(true, "Callback URL not confirmed.");
			}
		}break;

		case API_CALL: {
			// Retrieving network informations
			int httpCode = result.getHttpCode();
			QString httpReason = result.getHttpReason();

			// Building error message
			errorMsg = OAuthProcess::trUtf8("Network error ");
			errorMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(httpReason)
					.append(" :\n")
					.append(result.getErrorMessage())
					.append('.');
			emit errorProcess(false, errorMsg);

			// Looking for specific value of the return code
			if (httpCode / 100 == 5) {
				issue = TWITTER_DOWN;
			} else if (httpCode == 420) {
				issue = RATE_LIMITED;
			} else {
				issue = NO_TOKENS;
			}
		}break;

		case OAUTH_PARSING:
			// Building error message
			errorMsg = OAuthProcess::trUtf8("Parsing error:\n");
			errorMsg.append(result.getParsingErrorMessage());
			issue = PARSE_ERROR;
			emit errorProcess(false, errorMsg);
			break;

		default:
			// Unexpected problem. Abort.
			errorMsg = OAuthProcess::trUtf8("Unexpected problem:\n");
			errorMsg.append(result.getErrorMessage()).append('.');
			isFatal = true;
			issue = UNKNOWN_PROBLEM;
			emit errorProcess(true, errorMsg);
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
	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(authorizeDemanded(ResultWrapper)));

	RequestResult result = res.accessResult(this);
	ErrorType errorType = result.getErrorType();

	// For a potenitial anticipated end
	QString errorMsg = "";
	bool isFatal = false;
	CoreResult issue;

	switch (errorType) {
		case NO_ERROR:
			// The user can give its credentials now
			emit userCredentialsRequired();
			emit loginPanelVisible(true);	// DEPRECATED
			return;

		case API_CALL: {
			// Retrieving network informations
			int httpCode = result.getHttpCode();
			QString httpReason = result.getHttpReason();

			// Building error message
			errorMsg = OAuthProcess::trUtf8("Network error ");
			errorMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(httpReason)
					.append(" :\n")
					.append(result.getErrorMessage())
					.append('.');
			emit errorProcess(false, errorMsg);

			// Looking for specific values of the return code
			if (httpCode / 100 == 5) {
				issue = TWITTER_DOWN;
			} else if (httpCode == 401) {
				issue = TOKENS_NOT_AUTHORIZED;
			} else if (httpCode == 420) {
				issue = RATE_LIMITED;
			} else {
				issue = NO_TOKENS;
			}
		}break;

		case HTML_PARSING:
			// Building error message
			errorMsg = OAuthProcess::trUtf8("Parsing error:\n");
			errorMsg.append(result.getParsingErrorMessage());
			issue = PARSE_ERROR;
			emit errorProcess(false, errorMsg);
			break;

		default:
			// Unexpected problem. Abort.
			errorMsg = OAuthProcess::trUtf8("Unexpected problem:\n");
			errorMsg.append(result.getErrorMessage()).append('.');
			isFatal = true;
			issue = UNKNOWN_PROBLEM;
			emit errorProcess(true, errorMsg);
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
	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(postAuthorizeDemanded(ResultWrapper)));

	RequestResult result = res.accessResult(this);
	ErrorType errorType = result.getErrorType();

	// For a potenitial anticipated end
	QString errorMsg = "";
	bool isFatal = false;
	CoreResult issue;

	switch (errorType) {
		case NO_ERROR: {
			QVariantMap resultMap = result.getParsedResult().toMap();
			bool urlOK = resultMap.value("urlOK").toBool();

			if (urlOK) {
				bool rightCrdentials = resultMap.value("rightCredentials").toBool();
				emit credentialsOK(rightCrdentials);

				if (rightCrdentials) {
					emit loginPanelVisible(false);	// DEPRECATED

					if (resultMap.value("denied").toBool()) {
						// Reyn Tweets is denied. The process ends.
						emit authenticationProcessFinished(RT_DENIED);	// Deprecated
						buildResult(true, DENIED);
						emit processEnded();
					} else {
						// Request tokens are authorized. Let's get access tokens.
						accessToken();
					}
				}

				return;		// The process does not fail for the moment
			} else {
				errorMsg = OAuthProcess::trUtf8("Unexpected redirection. Process aborted.\n");
				isFatal = true;
				issue = POST_AUTHORIZING_FAILED;
				emit errorProcess(true, errorMsg);
			}
		}break;

		case API_CALL: {
			// Retrieving network informations
			int httpCode = result.getHttpCode();
			QString httpReason = result.getHttpReason();

			// Building error message
			errorMsg = OAuthProcess::trUtf8("Network error ");
			errorMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(httpReason)
					.append(" :\n")
					.append(result.getErrorMessage())
					.append('.');
			emit errorProcess(false, errorMsg);

			// Looking for specific values of the return code
			if (httpCode / 100 == 5) {
				issue = TWITTER_DOWN;
			} else if (httpCode == 401) {
				issue = TOKENS_NOT_AUTHORIZED;
			} else if (httpCode == 420) {
				issue = RATE_LIMITED;
			} else {
				issue = NO_TOKENS;
			}
		}break;

		case HTML_PARSING:
		case OAUTH_PARSING:
			// Building error message
			errorMsg = OAuthProcess::trUtf8("Parsing error:\n");
			errorMsg.append(result.getParsingErrorMessage());
			issue = PARSE_ERROR;
			emit errorProcess(false, errorMsg);
			break;

		default:
			// Unexpected problem. Abort.
			errorMsg = OAuthProcess::trUtf8("Unexpected problem:\n");
			errorMsg.append(result.getErrorMessage()).append('.');
			isFatal = true;
			issue = UNKNOWN_PROBLEM;
			emit errorProcess(true, errorMsg);
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
	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(accessTokenDemanded(ResultWrapper)));

	RequestResult result = res.accessResult(this);
	ErrorType errorType = result.getErrorType();

	// For a potenitial anticipated end
	QString errorMsg = "";
	bool isFatal = false;
	CoreResult issue;

	switch (errorType) {
		case NO_ERROR: {
			// The authentication process is ended.

			// Extract the different values
			QVariantMap resultMap = result.getParsedResult().toMap();
			QByteArray accessToken = resultMap.value("oauth_token").toByteArray();
			QByteArray tokenSecret = resultMap.value("oauth_token_secret").toByteArray();
			qlonglong userID = resultMap.value("user_id").toLongLong();
			QString screenName = resultMap.value("screen_name").toString();

			emit authenticationProcessFinished(RT_AUTHORIZED,
											   accessToken,
											   tokenSecret,
											   userID,
											   screenName);
			// Successful end
			buildResult(true,
						AUTHORIZED,
						"", false,
						accessToken, tokenSecret,
						userID, screenName);
			endProcess();
		}return;

		case API_CALL: {
			// Retrieving network informations
			int httpCode = result.getHttpCode();
			QString httpReason = result.getHttpReason();

			// Building error message
			errorMsg = OAuthProcess::trUtf8("Network error ");
			errorMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(httpReason)
					.append(" :\n")
					.append(result.getErrorMessage())
					.append('.');
			emit errorProcess(false, errorMsg);

			// Looking for specific values of the return code
			if (httpCode / 100 == 5) {
				issue = TWITTER_DOWN;
			} else if (httpCode == 401) {
				issue = TOKENS_NOT_AUTHORIZED;
			} else if (httpCode == 420) {
				issue = RATE_LIMITED;
			} else {
				issue = NO_TOKENS;
			}
		}break;

		case OAUTH_PARSING:
			// Building error message
			errorMsg = OAuthProcess::trUtf8("Parsing error:\n");
			errorMsg.append(result.getParsingErrorMessage());
			emit errorProcess(false, errorMsg);
			break;

		default:
			// Unexpected problem. Abort.
			errorMsg = OAuthProcess::trUtf8("Unexpected problem:\n");
			errorMsg.append(result.getErrorMessage()).append('.');
			isFatal = true;
			issue = UNKNOWN_PROBLEM;
			emit errorProcess(true, errorMsg);
			break;
	}

	// Failed end
	buildResult(false, issue, errorMsg, isFatal);
	endProcess();
}
