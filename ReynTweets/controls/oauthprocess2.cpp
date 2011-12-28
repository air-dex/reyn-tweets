/// @file loginwidget.hpp
/// @brief Header of LoginWidget
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
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "oauthprocess2.hpp"

// Constructor
OAuthProcess2::OAuthProcess2(QObject * parent) :
	QObject(parent),
	twitter(this)
{}

// Resetting the tokens.
void OAuthProcess2::resetTokens() {
	twitter.resetTokens();
}


///////////////////////////////
// OAuth Authentication flow //
///////////////////////////////

// Starting the OAuth authentication flow
void OAuthProcess2::startAuthentication() {
	requestToken();
}

// Demanding a Request Token
void OAuthProcess2::requestToken() {
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(requestTokenDemanded(ResultWrapper)));
	twitter.requestToken();
}

// Treatments after the request for Request Tokens
void OAuthProcess2::requestTokenDemanded(ResultWrapper res) {
	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(requestTokenDemanded(ResultWrapper)));

	RequestResult result = res.accessResult(this);
	ErrorType errorType = result.getErrorType();

	switch (errorType) {
		case NO_ERROR: {
			QVariantMap parsedResults = result.getParsedResult().toMap();
			// The request was successful. Was the callback URL confirmed ?
			if (parsedResults.value("oauth_callback_confirmed").toBool()) {
				// Let's authorize the request tokens !
				authorize();
			} else {
				// Cannot keep on if the URL is not confirmed
				emit errorProcess(true, "Callback URL not confirmed.");
			}
		}break;

		case API_CALL: {
			// Retrieving network informations
			QVariantMap httpMap = result.getHttpInfos();
			int httpCode = httpMap.value("httpCode");
			QString httpReason = httpMap.value("httpReason");

			// Building error message
			QString errorMsg = "Network error ";
			errorMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(httpReason)
					.append('.');
			emit errorProcess(false, errorMsg);
		}break;

		case OAUTH_PARSING: {
			// Building error message
			QString errorMsg = "Parsing error :\n";
			errorMsg.append(result.getErrorMessage());
			emit errorProcess(false, errorMsg);
		}break;

		default: {
			// Unexpected problem. Abort.
			QString errorMessage = "Unexpected problem :\n";
			errorMessage.append(result.getErrorMessage());
			emit errorProcess(true, errorMessage);
		}break;
	}
}

// Authorize the request tokens
void OAuthProcess2::authorize() {
	// Show the browser
	emit loginPanelVisible(true);

	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(authorizeDemanded(ResultWrapper)));
	twitter.authorize(embeddedBrowser);
}

// Treatments after the request for authorizing Request Tokens
void OAuthProcess2::authorizeDemanded(ResultWrapper res) {
	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(authorizeDemanded(ResultWrapper)));
}

// Allowing Reyn Tweets :)
void OAuthProcess2::authorizeReynTweets(QString login, QString password) {
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(authorizeDemanded(ResultWrapper)));
	twitter.postAuthorize(login, password);
}

// Denying Reyn Tweets :(
void OAuthProcess2::denyReynTweets(QString login, QString password, QString denyString) {
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(authorizeDemanded(ResultWrapper)));
	twitter.postAuthorize(login, password, denyString);
}

// The POST authorizing request
void OAuthProcess2::postAuthorizeDemanded(ResultWrapper res) {
	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(postAuthorizeDemanded(ResultWrapper)));
}

// Demanding an Access Token
void OAuthProcess2::accessToken() {
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(accessTokenDemanded(ResultWrapper)));
	twitter.accessToken();
}

// Treatments after the request for Access Tokens
void OAuthProcess2::accessTokenDemanded(ResultWrapper res) {
	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(accessTokenDemanded(ResultWrapper)));

	RequestResult result = res.accessResult(this);
	ErrorType errorType = result.getErrorType();

	switch (errorType) {
		case NO_ERROR: {
			// The authentication process is ended.
			emit authenticationProcessFinished(true);
		}break;

		case API_CALL: {
			// Retrieving network informations
			QVariantMap httpMap = result.getHttpInfos();
			int httpCode = httpMap.value("httpCode");
			QString httpReason = httpMap.value("httpReason");

			// Building error message
			QString errorMsg = "Network error ";
			errorMsg.append(QString::number(httpCode))
					.append(" : ")
					.append(httpReason)
					.append('.');
			emit errorProcess(false, errorMsg);
		}break;

		case OAUTH_PARSING: {
			// Building error message
			QString errorMsg = "Parsing error :\n";
			errorMsg.append(result.getErrorMessage());
			emit errorProcess(false, errorMsg);
		}break;

		default: {
			// Unexpected problem. Abort.
			QString errorMessage = "Unexpected problem :\n";
			errorMessage.append(result.getErrorMessage());
			emit errorProcess(true, errorMessage);
		}break;
	}
}
