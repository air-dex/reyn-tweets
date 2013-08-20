/// @file requesttokensprocess.cpp
/// @brief Implementation of RequestTokensProcess
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

#include "requesttokensprocess.hpp"
#include "../processutils.hpp"

RequestTokensProcess::RequestTokensProcess() :
	GenericProcess(),
	twitter(this),
	tokensMap()
{}

// Destructor
RequestTokensProcess::~RequestTokensProcess() {}

// Resetting the tokens.
void RequestTokensProcess::resetTokens() {
	ReynTwitterCalls::resetTokens();
}


///////////////////////////////
// OAuth Authentication flow //
///////////////////////////////

// Starting the OAuth authentication flow
void RequestTokensProcess::startProcess() {
	resetTokens();		// Doing it from scratch by erasing the old tokens
	requestToken();
}

/////////////////////////////
// Step 1 : Request tokens //
/////////////////////////////

// Demanding a Request Token
void RequestTokensProcess::requestToken() {
	connect(&twitter, &ReynTwitterCalls::sendResult,
			this, &RequestTokensProcess::requestTokenDemanded);
	twitter.requestToken();
}

// Treatments after the request for Request Tokens
void RequestTokensProcess::requestTokenDemanded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == LibRT::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, &ReynTwitterCalls::sendResult,
			   this, &RequestTokensProcess::requestTokenDemanded);

	// For a potenitial anticipated end
	QString errorMsg = "";
	ReynTweets::CoreResult procEnd;

	switch (result.resultType) {
		case LibRT::NO_REQUEST_ERROR: {
			// The request was successful. Was the callback URL confirmed ?
			QVariantMap parsedResults = result.parsedResult.toMap();

			// Fill tokens map
			tokensMap.insert("oauth_token",
							 parsedResults.value("oauth_token"));
			tokensMap.insert("oauth_secret",
							 parsedResults.value("oauth_secret"));

			// Continue the process
			if (parsedResults.value("oauth_callback_confirmed").toBool()) {
				// Let's authorize the request tokens !
				return authorize();
			} else {
				// Cannot keep on if the URL is not confirmed
				errorMsg = RequestTokensProcess::trUtf8("Callback URL not confirmed.");
				procEnd = ReynTweets::NO_TOKENS;
			}
		}break;

		case LibRT::SERVICE_ERRORS:
			// Building error message
			errorMsg = ProcessUtils::writeTwitterErrors(result);

			// Looking for specific value of the return code
			procEnd = ReynTweets::getCoreResultFromCode(result.getHTTPCode());

			if (procEnd != ReynTweets::TWITTER_DOWN
					&& procEnd != ReynTweets::RATE_LIMITED)
			{
				procEnd = ReynTweets::NO_TOKENS;
			}
			break;

		case LibRT::API_CALL:
			ProcessUtils::treatApiCallResult(result, errorMsg, procEnd);
			break;

		case LibRT::OAUTH_PARSING:
			ProcessUtils::treatOAuthParsingResult(result.parsingErrors.message,
												  errorMsg,
												  procEnd);
			break;

		default:
			ProcessUtils::treatUnknownResult(result.errorMessage,
											 errorMsg,
											 procEnd);
			break;
	}

	// Failed end
	endProcess(procEnd, errorMsg);
}

//////////////////////////////////////
// Step 2 : Authorizing Reyn Tweets //
//////////////////////////////////////

// Authorize the request tokens
void RequestTokensProcess::authorize() {
	connect(&twitter, &ReynTwitterCalls::sendResult,
			this, &RequestTokensProcess::authorizeDemanded);
	twitter.authorize();
}

// Treatments after the request for authorizing Request Tokens
void RequestTokensProcess::authorizeDemanded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == LibRT::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, &ReynTwitterCalls::sendResult,
			   this, &RequestTokensProcess::authorizeDemanded);

	// For a potenitial anticipated end
	QString errorMsg = "";
	ReynTweets::CoreResult procEnd;

	switch (result.resultType) {
		case LibRT::NO_REQUEST_ERROR:
			tokensMap.unite(result.parsedResult.toMap());
			endProcess(ReynTweets::REQUEST_TOKENS_OK,
					   QVariant::fromValue(tokensMap));
			return;

		case LibRT::SERVICE_ERRORS:
			// Building error message
			errorMsg = ProcessUtils::writeTwitterErrors(result);

			// Looking for specific value of the return code
			procEnd = ReynTweets::getCoreResultFromCode(result.getHTTPCode());

			if (procEnd != ReynTweets::TWITTER_DOWN
					&& procEnd != ReynTweets::RATE_LIMITED
					&& procEnd != ReynTweets::AUTHENTICATION_REQUIRED)
			{
				procEnd = ReynTweets::NO_TOKENS;
			}
			break;

		case LibRT::API_CALL:
			ProcessUtils::treatApiCallResult(result, errorMsg, procEnd);
			break;

		case LibRT::NO_PARSING:
			ProcessUtils::treatOAuthParsingResult(result.parsingErrors.message,
												  errorMsg,
												  procEnd);
			break;

		case LibRT::XML_PARSING:
			ProcessUtils::treatXMLParsingResult(result.parsingErrors,
												errorMsg,
												procEnd);
			break;

		default:
			ProcessUtils::treatUnknownResult(result.errorMessage,
											 errorMsg,
											 procEnd);
			break;
	}

	// Failed end
	endProcess(procEnd, errorMsg);
}
