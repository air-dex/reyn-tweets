/// @file twittercommunicator.cpp
/// @brief Code of the TwitterCommunicator class
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

#include "twittercommunicator.hpp"
#include <QNetworkRequest>

/////////////
// Coplien //
/////////////

// Constructor
TwitterCommunicator::TwitterCommunicator(QString url,
					ArgsMap getArgs,
					ArgsMap postArgs,
					QObject * parent) :
	QObject(parent),
	networkManager(),
	serviceURL(url),
	getParameters(getArgs),
	postParameters(postArgs),
	responseBuffer(""),
	httpReturnCode(0),
	httpReturnReason("Request not done")
{}

// Destructor
TwitterCommunicator::~TwitterCommunicator() {}


///////////////////////////
// Executing the request //
///////////////////////////

void TwitterCommunicator::executeRequest() {
	// GET arguments
	QString getArgs = buildGetDatas();

	// Adding the potential GET arguments at the end of the URL
	if ("" != getArgs) {
		getArgs.prepend('?');
		serviceURL.append(getArgs);
	}

	QNetworkRequest request(serviceURL);

	// POST arguments
	QByteArray postArgs = buildPostDatas();

	// Executing the request
	if ("" == postArgs) {
		// There is not any POST arguments -> networkManager.get()
		reply = networkManager.get(request);
	} else {
		// There is some POST arguments -> networkManager.post()
		reply = networkManager.post(request, postArgs);
	}

	// Connecting the reply
	connect(reply, SIGNAL(finished()), this, SLOT(endRequest()));
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
			this, SLOT(errorRequest(QNetworkReply::NetworkError)));
}


///////////
// Slots //
///////////
#include <QFile>
// Treatments that have to be done at the end of the request
void TwitterCommunicator::endRequest() {
	// Getting the reply
	QNetworkReply * twitterReply = qobject_cast<QNetworkReply*>(sender());

	responseBuffer = twitterReply->readAll();

	QFile f("xenoblade.txt"); //On ouvre le fichier

	if ( f.open(QIODevice::WriteOnly) )
	{
			f.write(responseBuffer); ////On lit la réponse du serveur que l'on met dans un fichier
			f.close(); //On ferme le fichier
	}


	errorReply = twitterReply->error();
	extractHttpStatuses(twitterReply);
	twitterReply->deleteLater();

	// Telling that the Twitter Communicator has ended its work successfully
	emit requestDone(true);
}

// Treatments to do if there is an error
void TwitterCommunicator::errorRequest(QNetworkReply::NetworkError errorCode) {
	// Getting the reply
	QNetworkReply * twitterReply = qobject_cast<QNetworkReply*>(sender());

	errorReply = errorCode;
	extractHttpStatuses(twitterReply);
	twitterReply->deleteLater();

	// Telling that the Twitter Communicator has ended its work unsuccessfully
	emit requestDone(false);
}


/////////////
// Getters //
/////////////

// Getting the raw response
QByteArray TwitterCommunicator::getResponseBuffer() {
	return responseBuffer;
}

// Getting a code indicating whether the request is successful.
QNetworkReply::NetworkError TwitterCommunicator::getNetworkError() {
	return errorReply;
}

// Getting the HTTP return code.
int TwitterCommunicator::getHttpCode() {
	return httpReturnCode;
}

// Getting the HTTP return reason.
QString TwitterCommunicator::getHttpReason() {
	return httpReturnReason;
}


/////////////////////
// Buiding ArgMaps //
/////////////////////

// Building a string that will contain all the GET arguments
QString TwitterCommunicator::buildGetDatas() {
	return buildDatas(getParameters);
}

// Building a QByteArray that will contain all the POST arguments
QByteArray TwitterCommunicator::buildPostDatas() {
	QString postString = buildDatas(postParameters);
	return QByteArray().append(postString);
}

// Building the string that will contain all the arguments
// of the given ArgsMap just like in an URL.
QString TwitterCommunicator::buildDatas(ArgsMap argsMap) {
	QString res = "";

	// Writing the arguments
	for (ArgsMap::iterator argsIterator = argsMap.begin();
		 argsIterator != argsMap.end();
		 ++argsIterator) {
		// Getting the name of the argument and its value
		QString argValue = argsIterator.value();

		if (argValue.isEmpty()) {
			continue;
		}

		QString argName = argsIterator.key();
		// URL encoding of the value
		QByteArray urlizedValue = QUrl::toPercentEncoding(argValue);

		res.append(argName);
		res.append('=');
		res.append(QString(urlizedValue));
		res.append('&');
	}

	// Erasing the last '&'
	res.chop(1);

	return res;
}


////////////////////////////////////////////
// Extracting http results from the reply //
////////////////////////////////////////////

void TwitterCommunicator::extractHttpStatuses(QNetworkReply * reply) {
	if (reply == 0) {
		return;
	}

	QVariant httpStatus;

	// Extract return code
	httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
	httpReturnCode = httpStatus.toInt();

	// Extract return reason
	httpStatus = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute);
	httpReturnReason = QString(httpStatus.toByteArray());
}
