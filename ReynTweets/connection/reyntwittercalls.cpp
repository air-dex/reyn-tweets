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

//////////////////////////
// Singleton management //
//////////////////////////

// Protected constructor
ReynTwitterCalls::ReynTwitterCalls() :
	QObject(),
	requesterManager()
{}

// Init the unique instance
ReynTwitterCalls ReynTwitterCalls::instance = ReynTwitterCalls();

// Getter on the unique instance
ReynTwitterCalls & ReynTwitterCalls::getInstance() {
	return instance;
}


/////////////////////
// Core management //
/////////////////////

// Adding a requester to the requester manager
void ReynTwitterCalls::addRequester(GenericRequester * requester) {
	if (requester != 0) {
		requesterManager.insert(requester->getUuid(), requester);
	}
}

// Slot executed when a requester has finished its work
void ReynTwitterCalls::endRequest() {
	GenericRequester * requester = qobject_cast<GenericRequester *>(sender());
	ResultWrapper res = buildResultSender(requester);
	removeRequester(requester);
	emit sendResult(res);
}

// Removing a requester of the requester manager
void ReynTwitterCalls::removeRequester(GenericRequester * requester) {
	if (requester != 0) {
		requesterManager.remove(requester->getUuid());
	}
}

// Method that builds the wrapper of a result
ResultWrapper ReynTwitterCalls::buildResultSender(GenericRequester * endedRequest) {
	return (endedRequest == 0) ? ResultWrapper::INVALID_RESULTWRAPPER
							   : ResultWrapper(endedRequest->parent(),
											   endedRequest->getParsedResult());
}

// Inline method for executing requests
void ReynTwitterCalls::executeRequest(GenericRequester * requester) {
	if (requester != 0) {
		connect(requester, SIGNAL(requestDone()), this, SLOT(endRequest()));
		addRequester(requester);
		requester->executeRequest();
	}
}


///////////////////////
// Request launchers //
///////////////////////

void ReynTwitterCalls::search(QObject * requestDemander, QString q) {
	SearchRequester * requester = new SearchRequester(requestDemander, q);
	connect(requester, SIGNAL(requestDone()), this, SLOT(endRequest()));
	addRequester(requester);
	requester->executeRequest();
}
