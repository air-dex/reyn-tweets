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
// Siggleton management //
//////////////////////////

// Protected constructor
ReynTwitterCalls::ReynTwitterCalls() :
	requesterManager()
{}

// Init the unique instance
ReynTwitterCalls ReynTwitterCalls::instance = ReynTwitterCalls();

// Getter on the unique instance
ReynTwitterCalls & ReynTwitterCalls::getInstance() {
	return instance;
}


///////////////////////
// Request launchers //
///////////////////////

void ReynTwitterCalls::search(QString q) {
	qDebug("Début de la recherche");
	SearchRequester * requester = new SearchRequester(q);
	requesterManager.append(requester);
	requester->executeRequest();
	connect(requester, SIGNAL(requestDone(bool)), this, SLOT(endSearch(bool)));
	qDebug("fin du call");
}

///////////
// Slots //
///////////
void ReynTwitterCalls::endSearch(bool ok) {
	SearchRequester * requester = qobject_cast<SearchRequester *>(sender());
	int i = requesters.indexOf(requester);
	qDebug(QString::number(i).toUtf8().data());
	requesters.removeAt(i);
	// Recup du Qvariant
	QVariant var = requester->getParsedResult();
	qDebug("Fin de la recherche");

	emit searchResult(var);
}
//*/
