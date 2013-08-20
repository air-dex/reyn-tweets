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

// Constructor
AllowControl::AllowControl() :
	GenericControl(),
	control(0)
{}

// Declaring to the QML components
void AllowControl::declareQML() {
	qmlRegisterType<AllowControl>("ReynTweetsControls",
								  0, 2,
								  "AllowControl");
}


/////////////////////////
// Property management //
/////////////////////////

LoginControl * AllowControl::getLoginControl() {
	return control;
}

void AllowControl::setLoginControl(LoginControl * ctrl) {
	control = ctrl;
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
			emit needVerifier(authorizePage);
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

/*
	switch (issue) {
		case ALLOW_SUCCESSFUL:
			// Process successful
			emit actionEnded(true,
							AllowControl::trUtf8("Reyn Tweets was authorized"),
							false);
			break;

		case DENIED:
			// Process successful but Reyn Tweets was denied :(
			displayMessage = AllowControl::trUtf8("Reyn Tweets was denied.");

		// Problems that can be solved trying later
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
			emit actionEnded(false, displayMessage, false);
			break;

		// Problems during process
		case NO_MORE_DATA:
		case TOKENS_NOT_AUTHORIZED:
		case PARSE_ERROR:
		case POST_AUTHORIZING_FAILED:
		case NO_TOKENS:

		// Problems with configuration file
		case CONFIGURATION_FILE_UNKNOWN:
		case CONFIGURATION_FILE_NOT_OPEN:

		// Unknown ends
		case UNKNOWN_PROBLEM:

		default:
			emit actionEnded(false, displayMessage, false);
			break;
	}
	//*/
}

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

	// TODO : new treatments
	switch (issue) {
		case AUTHORIZED:
			// End it !
			endOK = true;
			displayMessage = AllowControl::trUtf8("Reyn Tweets was authorized");
			// TODO : màj la conf'
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
		case UNKNOWN_PROBLEM:
			fatal = true;
			break;

		default:
			fatal = true;
			break;
	}

	emit actionEnded(endOK, displayMessage, fatal);
/*
	switch (issue) {
		case ALLOW_SUCCESSFUL:
			// Process successful
			emit actionEnded(true,
							AllowControl::trUtf8("Reyn Tweets was authorized"),
							false);
			break;

		case DENIED:
			// Process successful but Reyn Tweets was denied :(
			displayMessage = AllowControl::trUtf8("Reyn Tweets was denied.");

		// Problems that can be solved trying later
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
			emit actionEnded(false, displayMessage, false);
			break;

		// Problems during process
		case NO_MORE_DATA:
		case TOKENS_NOT_AUTHORIZED:
		case PARSE_ERROR:
		case POST_AUTHORIZING_FAILED:
		case NO_TOKENS:

		// Problems with configuration file
		case CONFIGURATION_FILE_UNKNOWN:
		case CONFIGURATION_FILE_NOT_OPEN:

		// Unknown ends
		case UNKNOWN_PROBLEM:

		default:
			emit actionEnded(false, displayMessage, false);
			break;
	}
	//*/
}


///////////////////////////////
// Wiring for authentication //
///////////////////////////////

// Wiring
void AllowControl::allowWiring() {
	if (!control) {
		emit actionEnded(false, AllowControl::trUtf8("No control"), true);
		processing = false;
		return;
	}

	// Telling the user that its credentials are required
	connect(&reyn, SIGNAL(userCredentialsNeeded()),
			this, SLOT(credentialsNeeded()));

	// Authorizing (or denying) Reyn Tweets
	connect(control, SIGNAL(authorize(QString,QString)),
			&reyn, SLOT(authorizeReynTweets(QString,QString)));
	connect(control, SIGNAL(deny(QString,QString)),
			&reyn, SLOT(denyReynTweets(QString,QString)));

	// When credentials given by the user are right or wrong
	connect(&reyn, SIGNAL(credentialsValid(bool)),
			this, SLOT(validCredentials(bool)));
}

// Unwiring
void AllowControl::allowUnwiring() {
	if (!control) {
		emit actionEnded(false, AllowControl::trUtf8("No control"), true);
		processing = false;
		return;
	}

	// Telling the user that its credentials are required
	disconnect(&reyn, SIGNAL(userCredentialsNeeded()),
			   this, SLOT(credentialsNeeded()));

	// Authorizing (or denying) Reyn Tweets
	disconnect(control, SIGNAL(authorize(QString,QString)),
			   &reyn, SLOT(authorizeReynTweets(QString,QString)));
	disconnect(control, SIGNAL(deny(QString,QString)),
			   &reyn, SLOT(denyReynTweets(QString,QString)));

	// When credentials given by the user are right or wrong
	disconnect(&reyn, SIGNAL(credentialsValid(bool)),
			   this, SLOT(validCredentials(bool)));
}


//////////////////////////////////////////
// Methods to communicate with the View //
//////////////////////////////////////////

// Credentials OK ?
void AllowControl::validCredentials(bool valid) {
	if (!control) {
		emit actionEnded(false, AllowControl::trUtf8("No control"), true);
		processing = false;
		return;
	}

	if (valid) {
		// Hiding the login popup
		emit showLoginPopup(false);
	} else {
		// Informing the user that the credentials are wrong
		control->wrongCredentials();
	}
}

// Reyn needs credentials
void AllowControl::credentialsNeeded() {
	// Displaying the popup to enter credentials
	emit showLoginPopup(true);
}
