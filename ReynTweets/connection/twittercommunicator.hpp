/// @file twittercommunicator.hpp
/// @brief Class managing communication with the Twitter API
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
#include <QByteArray>
#include <QUrl>
#include <QMap>

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
		///			ArgsMap getArgs = ArgsMap(),
		///			ArgsMap postArgs = ArgsMap(),
		///			QObject * parent = 0);
		/// @brief Constructor
		/// @param url String representation of the URL
		/// @param getArgs GET arguments
		/// @param postArgs POST arguments
		/// @param parent Parent Qobject
		TwitterCommunicator(QString url = "http://api.twitter.com",
							ArgsMap getArgs = ArgsMap(),
							ArgsMap postArgs = ArgsMap(),
							QObject * parent = 0);

		/// @fn ~TwitterCommunicator();
		/// @brief Destructor
		~TwitterCommunicator();

		/// @fn const TwitterCommunicator & operator=(const TwitterCommunicator & communicator);
		/// @brief Affectation
		/// @param communicator Twitter Communicator to copy
		/// @return Copy of the object
		const TwitterCommunicator & operator=(const TwitterCommunicator & communicator);

		/// @fn TwitterCommunicator(const TwitterCommunicator & communicator);
		/// @brief Constructor with recopy
		/// @param communicator Twitter Communicator to copy
		TwitterCommunicator(const TwitterCommunicator & communicator);

		/// @fn void executeRequest();
		/// @brief Executing the request
		void executeRequest();

		/// @fn QByteArray getResponseBuffer();
		/// @brief Getting the content of the response
		QByteArray getResponseBuffer();

		/// @fn QNetworkReply::NetworkError getNetworkError();
		/// @brief Getting a code indicating whether the request is successful.
		QNetworkReply::NetworkError getNetworkError();

		/// @fn int getHttpCode();
		/// @brief Getting the HTTP return code.
		int getHttpCode();

		/// @fn QString getHttpReason();
		/// @brief Getting the HTTP return reason.
		QString getHttpReason();


	signals:
		/// @fn void requestDone(bool ok);
		/// @brief Signal indicating the end of a request
		/// @param ok Boolean indicating if the request is ok (true) of if there
		/// was an error (false).
		void requestDone(bool ok);


	protected slots:
		/// @fn void endRequest();
		/// @brief Treatments that have to be done at the end of the request
		void endRequest();

		/// @fn void errorRequest(QNetworkReply::NetworkError errorCode);
		/// @brief Treatments to do if there is an error
		/// @param errorCode The error code
		void errorRequest(QNetworkReply::NetworkError errorCode);


	protected:
		/// @brief Network manager
		QNetworkAccessManager networkManager;

		/// @brief URL of the service
		QString serviceURL;

		/// @brief GET datas
		ArgsMap getParameters;

		/// @brief POST datas
		ArgsMap postParameters;

		/// @brief Content of the response
		QByteArray responseBuffer;

		/// @brief Flag indicating a potential error
		QNetworkReply::NetworkError errorReply;

		/// @brief HTTP return code
		int httpReturnCode;

		/// @brief HHTP return reason
		QString httpReturnReason;


	private:
		/// @fn void recopie(const TwitterCommunicator & communicator);
		/// @brief Copying a Twitter Communicator
		/// @param communicator Initial communicator
		/// @return Copy of communicator
		void recopie(const TwitterCommunicator & communicator);

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
