/// @file authorizetwittercommunicator.cpp
/// @brief Implementation of AuthorizeTwitterCommunicator
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

#include <QWebElement>
#include <QWebFrame>
#include "authorizetwittercommunicator.hpp"
#include "../twitterurls.hpp"

/// @brief Constructor
/// @param embeddedBrowser QWebView to track.
/// @param authManager OAuth manager
/// @param getArgs GET argument
/// @param requester The AuthorizeRequester
AuthorizeTwitterCommunicator::AuthorizeTwitterCommunicator(QWebView & embeddedBrowser,
														   OAuthManager & authManager,
														   ArgsMap getArgs,
														   QObject * requester) :
	TwitterCommunicator(requester,
						TwitterURL::AUTHORIZE_URL,
						GET,
						getArgs,
						ArgsMap(),
						true,
						&authManager),
	browser(embeddedBrowser)
{
	// Sets the tracker for URL
	connect(&browser, SIGNAL(urlChanged(QUrl)),
			this, SLOT(urlAnalyser(QUrl)));

	// Sets the tracker for the browser
	browser.page()->setNetworkAccessManager(&networkManager);
	connect(&networkManager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(repliesCatcher(QNetworkReply*)));
}

// Executing the request
void AuthorizeTwitterCommunicator::executeRequest() {
	request = prepareRequest();
	networkManager.get(*request);
}


// Analysing URLs
void AuthorizeTwitterCommunicator::urlAnalyser(const QUrl & url) {
	QString urlString = url.toString();

	// If it starts with the callback URL, extract the GET parameters and treat results
	if (urlString.startsWith(oauthManager->getCallbackUrl())) {
		// Writing the result
		QString datas = urlString.split("?").at(1);
		responseBuffer = datas.toUtf8();
		responseBuffer.append("denied=false");
		errorMessage = "";
		httpReturnCode = 200;
		httpReturnReason = "OK";

		browser.stop();
		emit requestDone(true);
	}
}

// Slot catching all the network replies of all the requests of the browser.
void AuthorizeTwitterCommunicator::repliesCatcher(QNetworkReply * response) {
	// Fill the communicator with the informations
	bool responseOK = treatReply(response);

	if (responseOK) {
		if (isReynTweetsDenied()) {
			responseBuffer = "denied=true";
			errorMessage = "The user denies Reyn Tweets to use its Twitter Account ! :(";
			emit requestDone(true);
		}
	} else {
		// Error ! The communicator has been already filled.
		emit requestDone(false);
	}
}

// Analysing web pages
bool AuthorizeTwitterCommunicator::isReynTweetsDenied() {
	// Checks the URL
	if (QUrl(TwitterURL::AUTHORIZE_URL) != browser.url()) {
		return false;
	}

	// Checks the class of the body
	QWebElement body = browser.page()->mainFrame()->findFirstElement("body");
	QString bodyClass = body.classes().at(0);
	return bodyClass.startsWith("oauth denied");
}
