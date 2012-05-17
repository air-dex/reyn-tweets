/// @file twittercommunicator.cpp
/// @brief Implementation of TwitterCommunicator.
///
/// SVN revisions of this file that are older than r80 are in the folder
/// /trunk/ReynTweets/connection.
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011 Romain Ducher
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

#include <QNetworkRequest>
#include "twittercommunicator.hpp"
#include "../../tools/utils.hpp"

// Network manager
#ifdef Q_OS_WIN32
	QNetworkAccessManager REYN_TWEETS_NETWORK_MANAGER = QNetworkAccessManager();
#endif
#ifdef Q_OS_LINUX
	QNetworkAccessManager REYN_TWEETS_NETWORK_MANAGER;
#endif
#ifdef Q_OS_SYMBIAN    // TODO
//    QNetworkAccessManager REYN_TWEETS_NETWORK_MANAGER = QNetworkAccessManager();
#endif

/////////////
// Coplien //
/////////////

// Constructor
TwitterCommunicator::TwitterCommunicator(QString url,
										 RequestType type,
										 ArgsMap getArgs,
										 ArgsMap postArgs,
										 bool authRequired,
										 OAuthManager * authManager,
										 bool tokenNeeded,
										 bool callbackURLNeeded,
										 bool verifierNeeded) :
	QObject(),
	serviceURL(url),
	requestType(type),
	getParameters(getArgs),
	postParameters(postArgs),
	authenticationRequired(authRequired),
	oauthManager(authManager),
	oauthTokenNeeded(tokenNeeded),
	callbackUrlNeeded(callbackURLNeeded),
	oauthVerifierlNeeded(verifierNeeded),
	request(0),
	responseBuffer(""),
	httpResponse(),
	errorMessage("Request not done"),
	replyURL("")
{
	// Connection for receiving the response
	connect(&REYN_TWEETS_NETWORK_MANAGER, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(endRequest(QNetworkReply*)));
}

// Destructor
TwitterCommunicator::~TwitterCommunicator() {
	// Deleting the request
	if (request != 0) {
		delete request;
	}

	// Unwiring
	disconnect(&REYN_TWEETS_NETWORK_MANAGER, SIGNAL(finished(QNetworkReply*)),
			   this, SLOT(endRequest(QNetworkReply*)));
}


///////////////////////////
// Executing the request //
///////////////////////////

// Preparing the request
QNetworkRequest * TwitterCommunicator::prepareRequest(QByteArray & postArgs) {
	// GET arguments
	QString getArgs = buildGetDatas();
	QString baseURL = serviceURL;

	// Adding the potential GET arguments at the end of the URL
	if ("" != getArgs) {
		serviceURL.append('?').append(getArgs);
	}

	QNetworkRequest * requestToTwitter = new QNetworkRequest(serviceURL);

	// POST arguments
	postArgs = buildPostDatas();

	// Building the authentication header if needed
	if (authenticationRequired && oauthManager != 0) {
		// Bulding the Authorization header
		QByteArray authHeader = oauthManager->getAuthorizationHeader(requestType,
																	 baseURL,
																	 getParameters,
																	 postParameters,
																	 oauthTokenNeeded,
																	 callbackUrlNeeded,
																	 oauthVerifierlNeeded);

		// Insert the header
		requestToTwitter->setRawHeader("Authorization", authHeader);
	}

#ifndef Q_OS_SYMBIAN
	// Needed for Qt 4.8.x (Windows and Linux) and Symbian version is 4.7.4.
	requestToTwitter->setRawHeader("Content-Type", "application/x-www-form-urlencoded");
#endif

	return requestToTwitter;
}

// Executing the request
void TwitterCommunicator::executeRequest() {
	QByteArray postArgs;

	// Preparing the request
	request = prepareRequest(postArgs);

	// Executing the request
	if (POST == requestType) {
		// There is some POST arguments -> networkManager.post()
		REYN_TWEETS_NETWORK_MANAGER.post(*request, postArgs);
	} else {
		// There is not any POST arguments -> networkManager.get()
		REYN_TWEETS_NETWORK_MANAGER.get(*request);
	}
}


//////////
// Slot //
//////////

// Treatments that have to be done at the end of the request
void TwitterCommunicator::endRequest(QNetworkReply * response) {
	// Treating the response
	if (!response) {
		return;
	}

	// Analysing the response
	extractHttpStatuses(response);
	errorMessage = response->errorString();
	replyURL = response->url().toString();

	// Extracting informations
	responseBuffer = response->readAll();
	response->deleteLater();

	// responseBuffer (for debug purposes)
	/*
	qDebug("responseBuffer :");
	qDebug(responseBuffer.data());
	qDebug("\n");
	//*/

	// Ending the request
	emit requestDone();
}


/////////////
// Getters //
/////////////

// Getting the raw response
QByteArray TwitterCommunicator::getResponseBuffer() {
	return responseBuffer;
}

// Getting the HTTP response (code and reason)
ResponseInfos TwitterCommunicator::getHttpResponse() {
	return httpResponse;
}

// Getting the URL of the reply
QString TwitterCommunicator::getReplyURL() {
	return replyURL;
}

// Getter on the error massage
QString TwitterCommunicator::getErrorMessage() {
	return errorMessage;
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
		// Getting the value of the argument
		QString argValue = argsIterator.value();

		if (argValue.isEmpty()) {
			continue;
		}

		// Getting the name of the argument
		QString argName = argsIterator.key();

		// Append the argument in the argument string
		res.append(formatParam(argName, argValue));
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
	httpResponse.code = httpStatus.toInt();

	// Extract return reason
	httpStatus = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute);
	httpResponse.message = QString::fromAscii(httpStatus.toByteArray());
}
