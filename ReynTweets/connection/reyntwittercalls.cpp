/// @file searchrequest.cpp
/// @brief Code of the ReynTwitterCalls class
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

#include "reyntwittercalls.hpp"
#include "requests/requests.hpp"

//////////////////////////
// Singleton management //
//////////////////////////

// Static components
QMap<QUuid, GenericRequester *> ReynTwitterCalls::requesterManager = QMap<QUuid, GenericRequester *>();

/// @brief OAuth information
OAuthManager ReynTwitterCalls::oauthManager = OAuthManager();

// Protected constructor
ReynTwitterCalls::ReynTwitterCalls(QObject & requester) :
	QObject(&requester),
	requestDemander(requester)
{}

// Destructor
ReynTwitterCalls::~ReynTwitterCalls() {}


/////////////////////
// Core management //
/////////////////////

// Adding a requester to the requester manager
void ReynTwitterCalls::addRequester(GenericRequester * requester) {
	if (requester != 0) {
		connect(requester, SIGNAL(requestDone()),
				this, SLOT(endRequest()));
		requesterManager.insert(requester->getUuid(), requester);
	}
}

// Removing a requester of the requester manager
void ReynTwitterCalls::removeRequester(GenericRequester * requester) {
	if (requester != 0) {
		disconnect(requester, SIGNAL(requestDone()),
				   this, SLOT(endRequest()));
		requesterManager.remove(requester->getUuid());
	}
}

// Slot executed when a requester has finished its work
void ReynTwitterCalls::endRequest() {
	GenericRequester * requester = qobject_cast<GenericRequester *>(sender());
	ResultWrapper res = buildResultSender(requester);
	removeRequester(requester);
	emit sendResult(res);
}

// Method that builds the wrapper of a result
ResultWrapper ReynTwitterCalls::buildResultSender(GenericRequester * endedRequest) {
	return (endedRequest == 0) ? ResultWrapper()
							   : ResultWrapper(endedRequest->parent(),
											   endedRequest->getRequestResult());
}

// Inline method for executing requests
void ReynTwitterCalls::executeRequest(GenericRequester * requester) {
	if (requester != 0) {
		addRequester(requester);
		requester->executeRequest();
	}
}


///////////////////////
// Request launchers //
///////////////////////

// Method that launch searches
void ReynTwitterCalls::search(QString q) {
	SearchRequester * requester = new SearchRequester(&requestDemander, q);
	executeRequest(requester);
}

///////////
// OAuth //
///////////

// Method for getting a request token
void ReynTwitterCalls::requestToken() {
	RequestTokenRequester * requester = new RequestTokenRequester(&requestDemander,
																  oauthManager);
	executeRequest(requester);
}

// Authorizing request Tokens
void ReynTwitterCalls::authorize(QWebView & browser) {
	AuthorizeRequester * requester = new AuthorizeRequester(browser,
															oauthManager,
															&requestDemander);
	executeRequest(requester);
}

// Authorizing request Tokens
void ReynTwitterCalls::authorize2() {
	AuthorizeRequester2 * requester = new AuthorizeRequester2(&requestDemander,
															oauthManager);
	executeRequest(requester);
}

// POST authorize() requests to allow or to deny the application.
void ReynTwitterCalls::postAuthorize(QString login, QString password, bool deny) {
	PostAuthorizeRequester * requester = new PostAuthorizeRequester(&requestDemander,
																	oauthManager,
																	login,
																	password,
																	deny);
	executeRequest(requester);
}

// Getting the access tokens
void ReynTwitterCalls::accessToken() {
	AccessTokenRequester * requester = new AccessTokenRequester(&requestDemander,
																oauthManager);
	executeRequest(requester);
}

// Resetting the credentials to connect to Twitter
void ReynTwitterCalls::resetTokens() {
	oauthManager.resetTokens();
}
