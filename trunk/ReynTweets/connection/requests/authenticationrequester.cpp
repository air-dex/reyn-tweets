#include "authenticationrequester.hpp"

AuthenticationRequester::AuthenticationRequester(QObject *parent) :
	GenericRequester(parent)
{
}

// Constructor
AuthenticationRequester::AuthenticationRequester(QObject * requester,
												 RequestType type,
												 QString url,
												 OAuthManager & authManager,
												 ErrorType parseError = QJSON_PARSING,
												 bool tokenNeeded = true,
												 bool callbackURLneeded = false) :
	GenericRequester(requester, type, url, parseError),
	oauthManager(authManager),
	oauthTokenNeeded(tokenNeeded),
	oauthCallbackUrlNeeded(callbackURLneeded)
{}


// Initialize the communicator
virtual void AuthenticationRequester::initCommunicator() {
	communicator = new TwitterCommunicator(this,
										   requestURL,
										   requestType,
										   getParameters,
										   postParameters,
										   true,
										   &oauthManager,
										   oauthTokenNeeded,
										   oauthCallbackUrlNeeded);
	connect(communicator, SIGNAL(requestDone(bool)),
			this, SLOT(treatResults(bool)));
}
