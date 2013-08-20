/// @file genericcalls.cpp
/// @brief Implementation of GenericCalls
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
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

#include "genericcalls.hpp"

// Static components
RequesterManager GenericCalls::requesterManager = RequesterManager();

// Protected constructor
GenericCalls::GenericCalls(QObject * requester) :
	QObject(),
	requestDemander(requester)
{}

// Destructor
GenericCalls::~GenericCalls() {
	requestDemander = 0;
}


/////////////////////
// Core management //
/////////////////////

// Adding a requester to the requester manager
void GenericCalls::addRequester(GenericRequester * requester) {
	if (requester != 0) {
		connect(requester, SIGNAL(requestDone(RequesterManager)),
				this, SLOT(endRequest()));
		requesterManager.addRequest(requestDemander, requester);
	}
}

// Removing a requester of the requester manager
void GenericCalls::removeRequester(GenericRequester * requester) {
	if (requester != 0) {
		disconnect(requester, SIGNAL(requestDone(RequesterManager)),
				   this, SLOT(endRequest()));
		requesterManager.removeRequest(requester->getUuid());
	}
}

// Slot executed when a requester has finished its work
void GenericCalls::endRequest(RequestResult requestResult) {
	GenericRequester * requester = qobject_cast<GenericRequester *>(sender());
	ResultWrapper res = buildResultSender(requester, requestResult);
	removeRequester(requester);
	emit sendResult(res);
}

// Method that builds the wrapper of a result
ResultWrapper GenericCalls::buildResultSender(GenericRequester * endedRequest,
											  RequestResult requestResult)
{
	return endedRequest ?
				ResultWrapper(requesterManager.getRequestInfos(endedRequest->getUuid()).getAsker(),
							  requestResult)
			  : ResultWrapper();
}

// Inline method for executing requests
void GenericCalls::executeRequest(GenericRequester * requester) {
	if (requester != 0) {
		addRequester(requester);
		requester->executeRequest();
	}
}
