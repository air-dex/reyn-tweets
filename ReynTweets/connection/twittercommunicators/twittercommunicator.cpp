/// @file twittercommunicator.cpp
/// @brief Implementation of TwitterCommunicator.<br/>
/// SVN revisions of this file that are older than r80 are in the folder
/// /trunk/ReynTweets/connection.
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

#include <QNetworkRequest>
#include "twittercommunicator.hpp"

/////////////
// Coplien //
/////////////

// Constructor
TwitterCommunicator::TwitterCommunicator(QString url,
										 RequestType type,
										 bool authRequired,
										 OAuthManager * authManager,
										 ArgsMap getArgs,
										 ArgsMap postArgs,
										 QObject * requester) :
	QObject(requester),
	networkManager(),
	serviceURL(url),
	requestType(type),
	getParameters(getArgs),
	postParameters(postArgs),
	authenticationRequired(authRequired),
	oauthManager(authManager),
	request(0),
	reqBasta(false),
	reply(0),
	responseBuffer(""),
	httpReturnCode(0),
	httpReturnReason(""),
	errorMessage("Request not done")
{}

// Destructor
TwitterCommunicator::~TwitterCommunicator() {
	// Deleting the request
	if (request != 0) {
		delete request;
	}

	// Deleting the reply
	if (reply != 0) {
		delete reply;
	}
}


///////////////////////////
// Executing the request //
///////////////////////////

// Preparing the request
QNetworkRequest * TwitterCommunicator::prepareRequest(QByteArray & postArgs) {
	// GET arguments
	QString getArgs = buildGetDatas();

	// Adding the potential GET arguments at the end of the URL
	if ("" != getArgs) {
		getArgs.prepend('?');
		serviceURL.append(getArgs);
	}

	QNetworkRequest * requestToTwitter = new QNetworkRequest(serviceURL);


	// POST arguments
	postArgs = buildPostDatas();


	// Building the authentication header if needed
	if (authenticationRequired && oauthManager != 0) {
		// Is it a RequestTokenRequest ?
		bool isRequestTokenRequest = oauthManager->getOAuthToken().isEmpty();

		// Is it a AccessTokenRequest ?
		bool isAccessTokenRequest = oauthManager->getVerifier().isEmpty();

		// Bulding the Authorization header
		QByteArray authHeader = oauthManager->getAuthorizationHeader(requestType,
																	 serviceURL,
																	 getArgs,
																	 postArgs,
																	 isRequestTokenRequest,
																	 isAccessTokenRequest);

		// Insert the header
		requestToTwitter->setRawHeader("Authorization", authHeader);
	}

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
		reply = networkManager.post(*request, postArgs);
	} else {
		// There is not any POST arguments -> networkManager.get()
		reply = networkManager.get(*request);
	}


	// Connecting the reply
	connect(reply, SIGNAL(finished()),
			this, SLOT(endRequest()));
	connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
			this, SLOT(endRequest(QNetworkReply::NetworkError)));
}


//////////
// Slot //
//////////

// Treatments that have to be done at the end of the request
void TwitterCommunicator::endRequest(QNetworkReply::NetworkError) {
	// If we have already got a response, no need to continue
	if (reqBasta) {
		return;
	}

	// Treating the response
	bool requestOK = treatReply(reply);

	// Ending the request
	reqBasta = true;
	emit requestDone(requestOK);
}

bool TwitterCommunicator::treatReply(QNetworkReply * response) {
	if (!response) {
		return false;
	}

	// Analysing the response
	extractHttpStatuses(response);
	errorReply = response->error();
	errorMessage = response->errorString();
	bool requestOK = httpReturnCode == 200;

	// Extracting informations
	responseBuffer = response->readAll();
	response->deleteLater();

	// Ending the request
	return requestOK;
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

		// URL encoding of the value
		QByteArray urlizedValue = QUrl::toPercentEncoding(argValue);

		// Getting the name of the argument
		QString argName = argsIterator.key();

		// Append the argument in the argument string
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
