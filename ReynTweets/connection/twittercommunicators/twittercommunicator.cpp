/// @file twittercommunicator.cpp
/// @brief Implementation of TwitterCommunicator.
///
/// SVN revisions of this file that are older than r80 are in the folder
/// /trunk/ReynTweets/connection.
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011, 2012 Romain Ducher
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
                                 HeadersMap headersParam) :
    QObject(),
    serviceURL(url),
    requestType(type),
    getParameters(getArgs),
    postParameters(postArgs),
    headers(headersParam),
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
    // Unwiring
    disconnect(&REYN_TWEETS_NETWORK_MANAGER, SIGNAL(finished(QNetworkReply*)),
               this, SLOT(endRequest(QNetworkReply*)));
}


///////////////////////////
// Executing the request //
///////////////////////////

// Preparing the request
QNetworkRequest * TwitterCommunicator::prepareRequest() {
    // GET arguments
    QString getArgs = buildGetDatas();

    // Adding the potential GET arguments at the end of the URL
    if ("" != getArgs) {
        serviceURL.append('?').append(getArgs);
    }

    QNetworkRequest * requestToTwitter = new QNetworkRequest(serviceURL);

    for (HeadersMap::Iterator it = headers.begin();
         it != headers.end();
         ++it)
    {
       requestToTwitter->setRawHeader(it.key(), it.value());
    }

    return requestToTwitter;
}

// Executing the request
void TwitterCommunicator::executeRequest() {
    // Preparing the request
    QNetworkRequest * request = prepareRequest();

    // Executing the request
    if (POST == requestType) {
        // POST arguments
        QByteArray postArgs = buildPostDatas();

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
