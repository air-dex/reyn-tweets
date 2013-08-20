/// @file allowcontrol.cpp
/// @brief Implementation of AllowControl
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012, 2013 Romain Ducher
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

#include "allowcontrol.hpp"
#include <QtQml>
#include "../core/configuration/appconfiguration.hpp"
#include "../../connection/twitter/requests/twitterurls.hpp"
#include "../../connection/common/utils/parsers/oauthparser.hpp"
#include "../../connection/common/utils/parsers/htmlparser.hpp"

// Constructor
AllowControl::AllowControl() :
	GenericControl()
{}

// Declaring to the QML components
void AllowControl::declareQML() {
	// @uri ReynTweetsComponents
	qmlRegisterType<AllowControl>(ReynTweets::QML_LIBRARY_NAME.toLatin1().constData(),
								  ReynTweets::MAJOR_VERSION, ReynTweets::MINOR_VERSION,
								  "AllowControl");
}


//////////////////////////////
// Execution of the process //
//////////////////////////////

// Allowing Reyn Tweets to use a Twitter Account
void AllowControl::allowReynTweets() {
	if (processing) {
		return;
	}

	connect(&reyn, &ReynCore::sendResult,
			this, &AllowControl::requestTokensOK);

	processing = true;
	emit showInfoMessage(AllowControl::trUtf8("Authorizing Reyn Tweets..."));
	reyn.requestOAuthTokens();
}

/////////////////////////////
// Step 1 : Request tokens //
/////////////////////////////

// After an authentication, if needed.
void AllowControl::requestTokensOK(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (ReynTweets::INVALID_END == result.processEnd) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, &ReynCore::sendResult,
			   this, &AllowControl::requestTokensOK);

	bool fatal = false;

	switch (result.processEnd) {
		case ReynTweets::REQUEST_TOKENS_OK: {
			// Send HTML to QML
			QVariantMap parsedResults = result.results.toMap();
			QString authorizePage = parsedResults.value("html").toString();
			QString baseURL = parsedResults.value("reply_url").toString();
			emit needVerifier(authorizePage, baseURL);
			processAgain();
		} return;

		// Problems that can be solved trying later
		case ReynTweets::NO_TOKENS:
		case ReynTweets::RATE_LIMITED:
		case ReynTweets::TWITTER_DOWN:
		case ReynTweets::NETWORK_CALL:
		case ReynTweets::REFUSED_REQUEST:	// Update limits
			fatal = false;
			break;

		// Problematic ends
		case ReynTweets::PARSE_ERROR:
		case ReynTweets::NO_MORE_DATA:
		case ReynTweets::BAD_REQUEST:
		case ReynTweets::AUTHENTICATION_REQUIRED:
		case ReynTweets::INVALID_SEARCH:
		case ReynTweets::GONE:
		case ReynTweets::UNPROCESSABLE:
		case ReynTweets::UNKNOWN_PROBLEM:
			fatal = true;
			break;

		default:
			fatal = true;
			break;
	}

	emit actionEnded(false, result.errorMsg, fatal);
}


//////////////////////////////////////
// Step 2 : Authorizing Reyn Tweets //
//////////////////////////////////////

// End of authentication
bool AllowControl::endAuth(QString postauthURL) {
	// Do not disturb the Control while working
	if (processing) {
		return false;
	}

	// Have a look at the URL
	if (postauthURL.startsWith(Twitter::AUTHORIZE_URL)) {
		// Still in POST authorizing
		// TODO : passer l'HTML pour être sûr qu'on est encore en POST authorizing
		return false;
	} else if (postauthURL.startsWith(AppConfiguration::getReynTweetsConfiguration().getCallbackURL())) {
		// This is the end (hold your breath & count to 10). Authorized or denied ?
		QUrl endURL(postauthURL);

		OAuthParser parser;
		bool parseOK;
		QString parseErr;

		QVariantMap veryEndArgs = parser.parse(endURL.query().toLatin1(),
											   &parseOK,
											   &parseErr);

		if (parseOK && veryEndArgs.contains("oauth_verifier")) {
			// Authorized :) !
			getAccessTokens(veryEndArgs.value("oauth_verifier").toByteArray());
		} else if (parseOK && veryEndArgs.contains("denied")) {
			// TODO : Denied :( !
			emit actionEnded(false,
							 AllowControl::trUtf8("Reyn Tweets was denied."),
							 false);
		} else {
			// Unable to know the result.
			QString errMsg = AllowControl::trUtf8("Cannot determine if the application was authorized or if she was denied");

			errMsg.append(" :\n");

			if (parseOK) {
				errMsg.append(AllowControl::trUtf8("No clue to know a priori what you decide"));
			} else {
				errMsg.append(AllowControl::trUtf8("Parsing error"))
						.append(" : ")
						.append(parseErr);
			}

			errMsg.append('.');

			emit actionEnded(false, errMsg, true);
		}

		return true;
	} else {
		// Awkward URL. Exit.
		emit actionEnded(false,
						 AllowControl::trUtf8("Callback URL expected."),
						 true);
		return true;
	}

}


////////////////////////////
// Step 3 : Access tokens //
////////////////////////////

// Allowing Reyn Tweets to use a Twitter Account
void AllowControl::getAccessTokens(QString verifier) {
	if (processing) {
		return;
	}

	processing = true;
	connect(&reyn, &ReynCore::sendResult,
			this, &AllowControl::accessTokensOK);
	reyn.accessOAuthTokens(verifier.toLatin1());
}


// After an authentication, if needed.
void AllowControl::accessTokensOK(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (ReynTweets::INVALID_END == result.processEnd) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, &ReynCore::sendResult,
			   this, &AllowControl::accessTokensOK);

	QString displayMessage = result.errorMsg;
	ReynTweets::CoreResult procEnd = result.processEnd;
	bool endOK = false;
	bool fatal = false;

	// Real process end
	if (result.results.toMap().value("authorized").toBool()) {
		if (procEnd != ReynTweets::AUTHORIZED) {
			displayMessage = AllowControl::trUtf8("Reyn Tweets was authorized.");
		} else {
			displayMessage = AllowControl::trUtf8("Reyn Tweets was authorized but")
							 .append(' ')
							 .append(result.errorMsg);
		}

		procEnd = ReynTweets::AUTHORIZED;
	}

	switch (procEnd) {
		case ReynTweets::ALLOW_SUCCESSFUL:
		case ReynTweets::AUTHORIZED:
			// End it !
			endOK = true;
			break;

		// Problems that can be solved trying later
		case ReynTweets::NO_TOKENS:
		case ReynTweets::RATE_LIMITED:
		case ReynTweets::TWITTER_DOWN:
		case ReynTweets::NETWORK_CALL:
		case ReynTweets::REINIT_SUCCESSFUL:
		case ReynTweets::REFUSED_REQUEST:	// Update limits
			fatal = false;
			break;

		// Problematic ends
		case ReynTweets::PARSE_ERROR:
		case ReynTweets::NO_MORE_DATA:
		case ReynTweets::BAD_REQUEST:
		case ReynTweets::AUTHENTICATION_REQUIRED:
		case ReynTweets::INVALID_SEARCH:
		case ReynTweets::GONE:
		case ReynTweets::UNPROCESSABLE:
		case ReynTweets::CONFIGURATION_FILE_UNKNOWN:
		case ReynTweets::CONFIGURATION_FILE_NOT_OPEN:
		case ReynTweets::UNKNOWN_PROBLEM:
			fatal = true;
			break;

		default:
			fatal = true;
			break;
	}

	emit actionEnded(endOK, displayMessage, fatal);
}
