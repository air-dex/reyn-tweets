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
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QByteArray>
#include <QUrl>
#include <QMap>

/// @class TwitterCommunicator
/// @brief Class managing communication with the Twitter API.<br/>
/// A Twitter Communicator needs the URL of the service, GET and POST arguments.
/// It will doing the request and storing it in a QByteArray containing the
/// response. <strong>The content of the QByteArray is not parsed.</strong>
class TwitterCommunicator : public QObject
{
Q_OBJECT

public:
TwitterCommunicator(QObject *parent = 0);
~TwitterCommunicator();
QByteArray getresponseBuffer();

signals:

public slots:

protected:
/// @brief Network manager
QNetworkAccessManager * networkManager;

/// @brief URL of the service
QUrl serviceURL;

/// @brief GET datas
QMap getDatas;

/// @brief POST datas
QMap postDatas;

/// @brief Resquest to send
QNetworkRequest request;

/// @brief Entity managing Twitter reply
QNetworkReply * twitterReply;

/// @brief Content of the response
QByteArray responseBuffer;

};

#endif // TWITTERCOMMUNICATOR_HPP
