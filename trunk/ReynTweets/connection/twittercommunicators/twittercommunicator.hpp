/// @file twittercommunicator.hpp
/// @brief Header of TwitterCommunicator.<br/>
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
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TWITTERCOMMUNICATOR_HPP
#define TWITTERCOMMUNICATOR_HPP

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArray>
#include <QUrl>
#include <QMap>
#include "../oauthmanager.hpp"

/// @typedef QMap<QString, QString> ArgsMap
/// @brief Convinience to designate QMaps that contains arguments
typedef QMap<QString, QString> ArgsMap;

/// @class TwitterCommunicator
/// @brief Class managing communication with the Twitter API.<br/>
/// A Twitter Communicator needs the URL of the service, GET and POST arguments.
/// It will doing the request and storing it in a QByteArray containing the
/// response. <strong>The content of the QByteArray is not parsed.</strong>
class TwitterCommunicator : public QObject
{
	Q_OBJECT

	public:
		/// @fn TwitterCommunicator(QString url,
		///							RequestType type,
		///							bool authRequired,
		///							OAuthManager * authManager,
		///							ArgsMap getArgs = ArgsMap(),
		///							ArgsMap postArgs = ArgsMap(),
		///							QObject * requester = 0);
		/// @brief Constructor
		/// @param url String representation of the URL
		/// @param type Type of the request (GET ou POST).
		/// @param authRequired Boolean indicating whether an authentication
		/// is required for the request
		/// @param authManager The authentication manager. A pointer is kept
		/// for cases where an authentication is not required
		/// @param getArgs GET arguments
		/// @param postArgs POST arguments
		/// @param requester Requester using the communicator. It corresponds to
		/// the parent QObject.
		TwitterCommunicator(QString url,
							RequestType type,
							bool authRequired,
							OAuthManager * authManager,
							ArgsMap getArgs = ArgsMap(),
							ArgsMap postArgs = ArgsMap(),
							QObject * requester = 0);

		/// @fn ~TwitterCommunicator();
		/// @brief Destructor
		~TwitterCommunicator();

		/// @fn QNetworkRequest * prepareRequest(QByteArray & postArgs = "");
		/// @brief Preparing the request. It builds the parameters for GET
		/// and POST and the Authorization header if needed.
		/// @param postArgs QByteArrray for storing the POST argument under
		/// the form arg1=val1&arg2=val2&...&argN=valN if needed.
		/// @return A pointer on the request
		QNetworkRequest * prepareRequest(QByteArray & postArgs = QByteArray());

		/// @fn virtual void executeRequest();
		/// @brief Executing the request
		virtual void executeRequest();

		/// @fn QByteArray getResponseBuffer();
		/// @brief Getting the content of the response
		/// @return The buffer containing the response
		QByteArray getResponseBuffer();

		/// @fn QNetworkReply::NetworkError getNetworkError();
		/// @brief Getting a code indicating whether the request is successful.
		/// @return The network error
		QNetworkReply::NetworkError getNetworkError();

		/// @fn int getHttpCode();
		/// @brief Getting the HTTP return code.
		/// @return The HTTP code of the request.
		int getHttpCode();

		/// @fn QString getHttpReason();
		/// @brief Getting the HTTP return reason.
		/// @return The description of the HTTP return code.
		QString getHttpReason();


	signals:
		/// @fn void requestDone(bool ok);
		/// @brief Signal indicating the end of a request
		/// @param ok Boolean indicating if the request is ok (true) of if there
		/// was an error (false).
		void requestDone(bool ok);


	protected slots:
		/// @fn void endRequest(QNetworkReply::NetworkError errorCode = QNetworkReply::NoError);
		/// @brief Slot called during the network request if an error occurs or
		/// when the request is finished.
		/// @param errorCode The potential error code. It is unused.
		void endRequest(QNetworkReply::NetworkError = QNetworkReply::NoError);

	protected:
		// Entities for request

		/// @brief Network manager
		QNetworkAccessManager networkManager;

		/// @brief URL of the service
		QString serviceURL;

		/// @brief Request type
		RequestType requestType;

		/// @brief GET datas
		ArgsMap getParameters;

		/// @brief POST datas
		ArgsMap postParameters;

		/// @brief Boolean indicating if authentication is required for the request
		bool authenticationRequired;

		/// @brief Entity with authentication information
		OAuthManager * oauthManager;

		/// @brief The request
		QNetworkRequest * request;


		// Entities for response

		/// @brief Boolean indicating if the request has ended
		bool reqBasta;

		/// @brief Reply
		QNetworkReply * reply;

		/// @brief Content of the response
		QByteArray responseBuffer;

		/// @brief Flag indicating a potential error
		QNetworkReply::NetworkError errorReply;

		/// @brief HTTP return code
		int httpReturnCode;

		/// @brief HHTP return reason
		QString httpReturnReason;

		/// @fn bool treatReply(QNetworkReply * response);
		/// @brief Treating a response.
		/// @param response The Reply to treat
		/// @return A boolean indicating if the request was successful
		bool treatReply(QNetworkReply * response);


	private:
		/// @fn QString buildGetDatas();
		/// @brief Building the string that will contain all the GET arguments
		/// and go through the Internet
		/// @return A QString containing all the GET arguments or an empty
		/// string if there is no GET arguments. This string will be appended
		/// at the end of the URL with a '?' between the URL and the string.
		QString buildGetDatas();

		/// @fn QByteArray buildPostDatas();
		/// @brief Building the array that will contain all the POST arguments
		/// and go through the Internet
		/// @return A QByteArray containing all the POST arguments or an empty
		/// string if there is no POST arguments. If the string is not empty,
		/// it will be passed to the post method of the QNetworkAccessManager
		QByteArray buildPostDatas();

		/// @fn QString buildDatas(ArgsMap argsMap);
		/// @brief Building the string that will contain all the arguments
		/// of the given ArgsMap just like in an URL.
		/// @param argsMap The argument map
		/// @return A QString representation looks like val1=arg1&val2=arg2...
		QString buildDatas(ArgsMap argsMap);

		/// @fn void extractHttpStatuses();
		/// @brief Extract the HTTP return code and reason of the request
		void extractHttpStatuses(QNetworkReply * reply);
};

#endif // TWITTERCOMMUNICATOR_HPP
