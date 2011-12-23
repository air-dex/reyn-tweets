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

// Protected constructor
ReynTwitterCalls::ReynTwitterCalls() :
	QObject(),
	requesterManager(),
	oauthManager()
{}

// Destructor
ReynTwitterCalls::~ReynTwitterCalls() {
	if (instance) {
		delete instance;
	}
	instance = 0;
}

// Init the unique instance
ReynTwitterCalls * ReynTwitterCalls::instance = 0;

// Getter on the unique instance
ReynTwitterCalls & ReynTwitterCalls::getInstance() {
	if (!instance) {
		instance = new ReynTwitterCalls;
	}
	return *instance;
}


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
void ReynTwitterCalls::search(QObject * requestDemander, QString q) {
	SearchRequester * requester = new SearchRequester(requestDemander, q);
	executeRequest(requester);
}


// OAuth

// Method for getting a request token
void ReynTwitterCalls::requestToken(QObject * requestDemander) {
	RequestTokenRequester * requester = new RequestTokenRequester(oauthManager,
																  requestDemander);
	executeRequest(requester);
}

// Method for authentication
void ReynTwitterCalls::authorize(QObject * requestDemander) {
	AuthorizeRequester * requester = new AuthorizeRequester(oauthManager,
															requestDemander);
	executeRequest(requester);
}

// Method for getting a request token
void ReynTwitterCalls::authenticate(QObject * requestDemander) {
	AuthenticateRequester * requester = new AuthenticateRequester(oauthManager,
																  requestDemander);
	executeRequest(requester);
}

// Method for getting a request token
void ReynTwitterCalls::accessToken(QObject * requestDemander) {
	AccessTokenRequester * requester = new AccessTokenRequester(oauthManager,
																requestDemander);
	executeRequest(requester);
}
