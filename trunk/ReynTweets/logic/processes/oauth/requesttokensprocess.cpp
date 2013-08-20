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
#include "../../../tools/processutils.hpp"

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
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(requestTokenDemanded(ResultWrapper)));
	twitter.requestToken();
}

// Treatments after the request for Request Tokens
void RequestTokensProcess::requestTokenDemanded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == Network::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(requestTokenDemanded(ResultWrapper)));

	NetworkResultType errorType = result.resultType;

	// For a potenitial anticipated end
	int httpCode = result.httpResponse.code;
	QString errorMsg = "";
	CoreResult issue;


	switch (errorType) {
		case Network::NO_REQUEST_ERROR: {
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
				issue = NO_TOKENS;
			}
		}break;

		case Network::SERVICE_ERRORS:
			// Building error message
			errorMsg = ProcessUtils::writeTwitterErrors(result);

			// Looking for specific value of the return code
			issue = (httpCode / 100 == 5
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

//////////////////////////////////////
// Step 2 : Authorizing Reyn Tweets //
//////////////////////////////////////

// Authorize the request tokens
void RequestTokensProcess::authorize() {
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(authorizeDemanded(ResultWrapper)));
	twitter.authorize();
}

// Treatments after the request for authorizing Request Tokens
void RequestTokensProcess::authorizeDemanded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);
	if (result.resultType == Network::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(authorizeDemanded(ResultWrapper)));

	NetworkResultType errorType = result.resultType;

	// For a potenitial anticipated end
	int httpCode = result.httpResponse.code;
	QString errorMsg = "";
	CoreResult issue;

	switch (errorType) {
		case Network::NO_REQUEST_ERROR:
			tokensMap.unite(result.parsedResult.toMap());
			endProcess(REQUEST_TOKENS_OK, QVariant(tokensMap));
			return;

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

		case Network::NO_PARSING:
			ProcessUtils::treatOAuthParsingResult(result.parsingErrors.message,
												  errorMsg,
												  issue);
			break;

		case Network::XML_PARSING:
			ProcessUtils::treatXMLParsingResult(result.parsingErrors,
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
