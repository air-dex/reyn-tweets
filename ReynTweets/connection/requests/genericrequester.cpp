/// @file genericrequester.cpp
/// @brief Code of the GenericRequest class
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

#include "genericrequester.hpp"

// Constructor. It just calls the parent constructor.
GenericRequester::GenericRequester(QString url, QObject * parent) :
	QObject(parent),
	requestURL(url),
	getParameters(),
	postParameters(),
	communicator(0),
	parsedResult()
{
}


// Destructor
GenericRequester::~GenericRequester() {
	// Deleting the communicator
	if (communicator != 0) {
		delete communicator;
	}
}


// Executing the request
void GenericRequester::executeRequest() {
	// Building the ArgsMap
	buildGETParameters();
	buildPOSTParameters();

	// Executing the request
	communicator = new TwitterCommunicator(requestURL,
										   getParameters,
										   postParameters);
	connect(communicator, SIGNAL(requestDone(bool)),
			this, SLOT(treatResults(bool)));
	communicator->executeRequest();
}


// Slot executed when the Twitter Communicator has just finished its work.
void GenericRequester::treatResults(bool ok) {
	if (ok) {
		parseResult();
	} else {
		treatError();
	}

	// Telling the ReynTwitterAPI that the requester has finished
	emit requestDone(ok);
}


// Getting parsed results
QVariant GenericRequester::getParsedResult() {
	return parsedResult;
}


/*
// Parse the raw results of the request.
virtual void GenericRequester::parseResult() = 0;	// Maybe not virtual
//*/
