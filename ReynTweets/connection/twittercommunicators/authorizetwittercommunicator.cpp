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
	TwitterCommunicator(TwitterURL::AUTHORIZE_URL,
						GET,
						true,
						&authManager,
						getArgs,
						ArgsMap(),
						requester),
	browser(embeddedBrowser)
{
	// Sets the tracker for URL
	connect(&browser, SIGNAL(urlChanged(QUrl)),
			this, SLOT(urlAnalyser(QUrl)));

	// Sets the tracker for Web pages
	connect(&browser, SIGNAL(loadFinished(bool)),
			this, SLOT(isReynTweetsDenied(bool)));

	// Sets the tracker for the browser
	browser.page()->setNetworkAccessManager(&networkManager);
	connect(&networkManager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(repliesCatcher(QNetworkReply*)));
}

// Executing the request
void AuthorizeTwitterCommunicator::executeRequest() {
	request = prepareRequest();

	reply = networkManager.get(*request);
}


// Analysing URLs
void AuthorizeTwitterCommunicator::urlAnalyser(const QUrl & url) {
	QString urlString = url.toString();

	// If it starts with the callback URL, extract the GET parameters and treat results
	if (urlString.startsWith(oauthManager->getCallbackUrl())) {
		// Writing the result
		QString datas = urlString.split("?").at(1);
		responseBuffer = datas.toUtf8();

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
			emit requestDone(true);
		}
	} else {
		// Error !
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
