/// @file oauthmanager.hpp
/// @brief Header of OAuthManager
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
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OAUTHMANAGER_HPP
#define OAUTHMANAGER_HPP

#include <QObject>
#include "twittercommunicator.hpp"

/// @class OAuthManager
/// @brief Class managing OAuth authentication to Twitter.
class OAuthManager : public QObject
{
		Q_OBJECT
	public:
		OAuthManager(QObject *parent = 0);
		QString signDatas(QByteArray datas);
		QString getAuthorizationHeader();

	signals:

	public slots:

	protected:
		QString consumerKey;
		QString consumerSecret;
		QString requestToken;
		QString requestSecret;
		QString accessToken;
		QString tokenSecret;
		QString oauthVersion;
		QString oauthCallback;
		QString oauthSignatureMethod;


	private:
		/// @fn QString OAuthManager::hmacSha1(QByteArray key, QByteArray baseString);
		/// @brief HMAC-SHA1 algorithm for signatures. Its implementation for
		/// Reyn Tweets was found on the <a href="http://developer.qt.nokia.com/">
		/// Qt Developer Network</a> here :
		/// <a href="http://developer.qt.nokia.com/wiki/HMAC-SHA1">
		/// http://developer.qt.nokia.com/wiki/HMAC-SHA1</a>.
		/// @param key Key for signature
		/// @param baseString String that we want to sign
		/// @return The signature
		QString OAuthManager::hmacSha1(QByteArray key, QByteArray baseString);

		/// @fn QString generateNonce();
		/// @brief Generates a nonce for a request
		/// @return A .
		QString generateNonce();

		/// @fn QString generateTimestamp();
		/// @brief Generates a timestamp for a request
		/// @return A .
		QString generateTimestamp();
};

#endif // OAUTHMANAGER_HPP
