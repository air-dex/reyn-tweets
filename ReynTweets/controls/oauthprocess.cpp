#include "oauthprocess.hpp"

// Constructor
OAuthProcess::OAuthProcess(QWebView & browser, QObject * parent) :
	QObject(parent),
	twitterCalls(ReynTwitterCalls::getInstance()),
	embeddedBrowser(browser)
{}

///////////////////////////////
// OAuth Authentication flow //
///////////////////////////////

// Starting the authentication flow
void OAuthProcess::startAuthentication() {
	requestToken();
}

// Demanding a Request Token
void OAuthProcess::requestToken() {
	connect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(browserVisible(ResultWrapper)));
	twitterCalls.requestToken(this);
}

// Treatments after the request for Request Tokens
void OAuthProcess::requestTokenDemanded(ResultWrapper res) {
	disconnect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(browserVisible(ResultWrapper)));

	// Treatments on res for continuing the authentication process

	authorize();	// If that's ok
}

// Authorizing Reyn Tweets by displaying the Twitter
void OAuthProcess::authorize() {
	// Show the browser
	emit browserVisible(true);

	connect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(endAuthentication(ResultWrapper)));
	twitterCalls.requestToken(this);
}

// Treatments after the request for authorizing Request Tokens
void OAuthProcess::authorizeDemanded(ResultWrapper res) {
	disconnect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(endAuthentication(ResultWrapper)));

	// Hide the browser
	emit browserVisible(false);

	// Treatments on res for continuing the authentication process

	accessToken();	// If that's ok
}

// Demanding an Access Token
void OAuthProcess::accessToken() {
	connect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(accessTokenDemanded(ResultWrapper)));
	twitterCalls.accessToken(this);
}

// Treatments after the request for Access Tokens
void OAuthProcess::accessTokenDemanded(ResultWrapper res) {
	disconnect(&twitterCalls, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(accessTokenDemanded(ResultWrapper)));

	bool accessTokenOK;

	// Treatments on res

	emit authenticationFinished(accessTokenOK);
}
