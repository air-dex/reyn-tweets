/// @file twittercommunicator.hpp
/// @brief Header of TwitterCommunicator.
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

#ifndef TWITTERCOMMUNICATOR_HPP
#define TWITTERCOMMUNICATOR_HPP

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QByteArray>
#include <QUrl>
#include <QMap>
#include <QTimer>
#include "../headersmap.hpp"
#include "../httprequesttype.hpp"
#include "../networkresult.hpp"


/////////////////////
// Network Manager //
/////////////////////


namespace Network {
	/// @brief Network manager used by all the requesters for all the request.
	/// <strong>Including him in the TwitterCommunicator
	/// <a href="https://code.google.com/p/reyn-tweets/issues/detail?id=36">
	/// could cause crashes</a></strong>.
	extern QNetworkAccessManager REYN_TWEETS_NETWORK_MANAGER;
}


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
		/// @fn TwitterCommunicator(QString &url,
		///							RequestType type,
		///							ArgsMap &getArgs,
		///							ArgsMap &postArgs,
		///							HeadersMap &headersParam);
		/// @brief Constructor
		/// @param url String representation of the URL
		/// @param type Type of the request (GET ou POST).
		/// @param getArgs GET arguments
		/// @param postArgs POST arguments
		/// @param headersParam HTTP headers
		TwitterCommunicator(QString & url,
							HTTPRequestType type,
							ArgsMap &getArgs,
							ArgsMap &postArgs,
							HeadersMap &headersParam);

		/// @fn ~TwitterCommunicator();
		/// @brief Destructor
		~TwitterCommunicator();

		/// @fn QNetworkRequest * prepareRequest();
		/// @brief Preparing the request. It builds the parameters for GET
		/// and POST and the Authorization header if needed.
		/// @return A pointer on the request
		QNetworkRequest * prepareRequest();

		/// @fn virtual void executeRequest();
		/// @brief Executing the request
		virtual void executeRequest();


	signals:
		/// @fn void requestDone(NetworkResponse result);
		/// @brief Signal indicating the end of a request
		void requestDone(NetworkResponse result);


	protected slots:
		/// @fn void endRequest(QNetworkReply * response);
		/// @brief Slot called at the end of the request.
		/// @param response The network reply.
		void endRequest(QNetworkReply * response);

		/// @fn void timeout();
		/// @brief Slot called it there is a network timeout.
		void timeout();

	protected:
		/// @brief Timer to avoid to wait for responses ad vitam aeternam.
		QTimer timeoutTimer;

		// Entities for request

		/// @brief URL of the service
		QString & serviceURL;

		/// @brief Request type
		HTTPRequestType requestType;

		/// @brief GET datas
		ArgsMap & getParameters;

		/// @brief POST datas
		ArgsMap & postParameters;

		/// @brief HTTP headers
		HeadersMap & headers;


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
};

#endif // TWITTERCOMMUNICATOR_HPP
