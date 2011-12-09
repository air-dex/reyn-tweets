/// @file searchrequest.cpp
/// @brief Code of the SearchRequest class
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

#include "searchrequester.hpp"
#include "../twitterurls.hpp"

// Constructor
SearchRequester::SearchRequester(QString q, QObject * parent) :
	GenericRequester(TwitterRequestUrl::SEARCH_URL, parent),
	query(q)
{
	QString s = "Recherche dans Twitter de : " + q;
	qDebug(s.toUtf8().data());
}

// Virtual method building getParameters
void SearchRequester::buildGETParameters() {
	getParameters.insert("q", query);
}

// Virtual method building postParameters
void SearchRequester::buildPOSTParameters() {}

// Method that will parse the raw results of the request.
void SearchRequester::parseResult() {
	QByteArray rawResponse = communicator->getResponseBuffer();
	QVariant var(rawResponse);
	parsedResult = var;
}

// Method that will treat errors of the requests made by the communicator.
void SearchRequester::treatError() {
	// TODO
}
