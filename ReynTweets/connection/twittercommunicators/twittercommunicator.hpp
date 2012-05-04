/// @file twittercommunicator.hpp
/// @brief Header of TwitterCommunicator.
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
#include "../responseinfos.hpp"

/////////////////////
// Network Manager //
/////////////////////

/// @brief Network manager used by all the requesters for all the request.
/// <strong>Including him in the TwitterCommunicator
/// <a href="https://code.google.com/p/reyn-tweets/issues/detail?id=36">
/// could cause crashes</a></strong>.
extern QNetworkAccessManager REYN_TWEETS_NETWORK_MANAGER;


/// @class TwitterCommunicator
/// @brief Class managing communication with the Twitter API.
///
/// A Twitter Communicator needs the URL of the service, GET and POST arguments.
/// It will doing the request and storing it in a QByteArray containing the
/// response. <strong>The content of the QByteArray is not parsed.</strong>
class TwitterCommunicator : public QObject
{
	Q_OBJECT

	public:
		/// @fn TwitterCommunicator(QString url,
		///							RequestType type,
		///							ArgsMap getArgs,
		///							ArgsMap postArgs,
		///							bool authRequired,
		///							OAuthManager * authManager = 0,
		///							bool tokenNeeded = true,
		///							bool callbackURLNeeded = false,
		///							bool verifierNeeded = false);
		/// @brief Constructor
		/// @param url String representation of the URL
		/// @param type Type of the request (GET ou POST).
		/// @param authRequired Boolean indicating whether an authentication
		/// is required for the request
		/// @param authManager The authentication manager. A pointer is kept
		/// for cases where an authentication is not required
		/// @param getArgs GET arguments
		/// @param postArgs POST arguments
		/// @param tokenNeeded Boolean indicating if the oauth_token parameter
		/// is required for authentication.
		/// @param callbackURLNeeded Boolean indicating if the oauth_callback
		/// parameter is required for authentication.
		/// @param verifierNeeded Boolean indicating if the oauth_verifier
		/// parameter is required for authentication.
		TwitterCommunicator(QString url,
							RequestType type,
							ArgsMap getArgs,
							ArgsMap postArgs,
							bool authRequired,
							OAuthManager * authManager = 0,
							bool tokenNeeded = 0,
							bool callbackURLNeeded = true,
							bool verifierNeeded = false);

		/// @fn ~TwitterCommunicator();
		/// @brief Destructor
		~TwitterCommunicator();

        /// @fn QNetworkRequest * prepareRequest(QByteArray & postArgs);
		/// @brief Preparing the request. It builds the parameters for GET
		/// and POST and the Authorization header if needed.
		/// @param postArgs QByteArrray for storing the POST argument under
		/// the form arg1=val1&arg2=val2&...&argN=valN if needed.
		/// @return A pointer on the request
        QNetworkRequest * prepareRequest(QByteArray & postArgs);

		/// @fn virtual void executeRequest();
		/// @brief Executing the request
		virtual void executeRequest();

		/// @fn QByteArray getResponseBuffer();
		/// @brief Getting the content of the response
		/// @return The buffer containing the response
		QByteArray getResponseBuffer();

		/// @fn ResponseInfos getHttpResponse();
		/// @brief Getting the HTTP response (code and reason).
		/// @return The description of the HTTP return code.
		ResponseInfos getHttpResponse();

		/// @fn QString getReplyURL();
		/// @brief Getting the URL of the reply.
		/// @return replyURL
		QString getReplyURL();

		/// @fn QString getErrorMessage();
		/// @brief Getter on the error massage
		/// @return The error message
		QString getErrorMessage();


	signals:
		/// @fn void requestDone();
		/// @brief Signal indicating the end of a request
		void requestDone();


	protected slots:
		/// @fn void endRequest(QNetworkReply * response);
		/// @brief Slot called at the end of the request.
		/// @param response The network reply.
		void endRequest(QNetworkReply * response);

	protected:
		// Entities for request

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

		/// @brief Boolean indicating if the oauth_token parameter is required
		/// for authentication.
		bool oauthTokenNeeded;

		/// @brief Boolean indicating if the oauth_callback parameter
		/// is required for authentication.
		bool callbackUrlNeeded;

		/// @brief Boolean indicating if the oauth_verifier parameter
		/// is required for authentication.
		bool oauthVerifierlNeeded;

		/// @brief The request
		QNetworkRequest * request;


		// Entities for response

		/// @brief Content of the response
		QByteArray responseBuffer;

		/// @brief HTTP response code and reason
		ResponseInfos httpResponse;

		/// @brief Error message
		QString errorMessage;

		/// @brief URL of the reply
		QString replyURL;


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

		/// @fn void extractHttpStatuses(QNetworkReply * reply);
		/// @brief Extract the HTTP return code and reason of the request
		/// @param reply Network reply containing the statuses.
		void extractHttpStatuses(QNetworkReply * reply);
};

#endif // TWITTERCOMMUNICATOR_HPP
