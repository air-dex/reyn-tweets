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
#include "../../model/configuration/appconfiguration.hpp"
#include "../../connection/twitter/requests/twitterurls.hpp"
#include "../../tools/parsers/oauthparser.hpp"
#include "../../tools/parsers/htmlparser.hpp"

// Constructor
AllowControl::AllowControl() :
	GenericControl()
{}

// Declaring to the QML components
void AllowControl::declareQML() {
	qmlRegisterType<AllowControl>("ReynTweetsControls",
								  0, 2,
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

	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(requestTokensOK(ProcessWrapper)));

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
	if (INVALID_ISSUE == result.processIssue) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(requestTokensOK(ProcessWrapper)));

	CoreResult issue = result.processIssue;
	bool fatal = false;

	// TODO : new treatments
	switch (issue) {
		case REQUEST_TOKENS_OK: {
			// Send HTML to QML
			QVariantMap parsedResults = result.results.toMap();
			QString authorizePage = parsedResults.value("html").toString();
			QString baseURL = parsedResults.value("reply_url").toString();
			emit needVerifier(authorizePage, baseURL);
			processAgain();
		} return;

		// Problems that can be solved trying later
		case NO_TOKENS:
		case RATE_LIMITED:
		case TWITTER_DOWN:
		case NETWORK_CALL:
		case REFUSED_REQUEST:	// Update limits
			fatal = false;
			break;

		// Problematic ends
		case PARSE_ERROR:
		case NO_MORE_DATA:
		case BAD_REQUEST:
		case AUTHENTICATION_REQUIRED:
		case INVALID_SEARCH:
		case GONE:
		case UNPROCESSABLE:
		case UNKNOWN_PROBLEM:
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
	if (postauthURL.startsWith(TwitterURL::AUTHORIZE_URL)) {
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
			// Denied :( ! TODO
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
	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(accessTokensOK(ProcessWrapper)));
	reyn.accessOAuthTokens(verifier.toLatin1());
}


// After an authentication, if needed.
void AllowControl::accessTokensOK(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(requestTokensOK(ProcessWrapper)));

	QString displayMessage = result.errorMsg;
	CoreResult issue = result.processIssue;
	bool endOK = false;
	bool fatal = false;

	switch (issue) {
		case ALLOW_SUCCESSFUL:
		case AUTHORIZED:
			// End it !
			endOK = true;
			displayMessage = AllowControl::trUtf8("Reyn Tweets was authorized");
			break;

		// Problems that can be solved trying later
		case NO_TOKENS:
		case RATE_LIMITED:
		case TWITTER_DOWN:
		case NETWORK_CALL:
		case REFUSED_REQUEST:	// Update limits
			fatal = false;
			break;

		// Problematic ends
		case PARSE_ERROR:
		case NO_MORE_DATA:
		case BAD_REQUEST:
		case AUTHENTICATION_REQUIRED:
		case INVALID_SEARCH:
		case GONE:
		case UNPROCESSABLE:
		case CONFIGURATION_FILE_UNKNOWN:
		case CONFIGURATION_FILE_NOT_OPEN:
		case UNKNOWN_PROBLEM:
			fatal = true;
			break;

		default:
			fatal = true;
			break;
	}

	emit actionEnded(endOK, displayMessage, fatal);
}
