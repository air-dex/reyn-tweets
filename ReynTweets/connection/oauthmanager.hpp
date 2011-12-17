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
#include "reyntweetssettings.hpp"

/// @class OAuthManager
/// @brief Class managing OAuth authentication to Twitter.
class OAuthManager : public QObject
{
		Q_OBJECT
	public:
		/// @fn OAuthManager(QString clientKey = ReynTweetsConfiguration::CONSUMER_KEY,
		///			QString clientSecret = ReynTweetsConfiguration::CONSUMER_SECRET,
		///			QString clientUrl = ReynTweetsConfiguration::CALLBACK_URL,
		///			QString signatureAlgorithm = "SHA-1",
		///			QString version = "1.0",
		///			QObject *parent = 0);
		/// @brief Constructor
		/// @param clientKey Consumer key of the application. Reyn Tweets'
		/// consumer key is its default value.
		/// @param clientSecret Consumer secret of the application.
		/// Reyn Tweets' consumer secret is its default value.
		/// @param clientUrl Callback URL of the application Reyn Tweets'
		/// callback URL is its default value.
		/// @param signatureAlgorithm Algorithm used for signing requests.
		/// @param version Version of the OAuth protocol used for
		/// authentication. Reyn Tweets uses OAuth 1.0.
		/// @param parent Parent object
		OAuthManager(QString clientKey = ReynTweetsConfiguration::CONSUMER_KEY,
					 QString clientSecret = ReynTweetsConfiguration::CONSUMER_SECRET,
					 QString clientUrl = ReynTweetsConfiguration::CALLBACK_URL,
					 QString signatureAlgorithm = "SHA-1",
					 QString version = "1.0",
					 QObject *parent = 0);

		/////////////////////////////
		// 3-legged authentication //
		/////////////////////////////

		/// @fn bool getRequestToken();
		/// @brief Getting temporary credentials
		/// @return true if the callback URL is confirmed or if the HTTP return
		/// code is 200 ("OK"), false otherwise.
		bool getRequestToken();

		/// @fn void authorize();
		/// @brief Enabling the application to use the Twitter account
		/// of the user.
		void authorize();

		/// @fn void getRequestToken();
		/// @brief Getting Token credentials
		void getAccessToken();

		////////////////////////////
		// Utilities for requests //
		////////////////////////////

		/// @fn QString signDatas(QByteArray datas);
		/// @brief Method for signing datas
		/// @param datas Datas to sign
		/// @return The signature of the given datas
		QString signDatas(QByteArray datas);

		/// @fn QString getAuthorizationHeader();
		/// @brief Getting that will be written in the "Authorization" field
		/// of requests
		QString getAuthorizationHeader();

	signals:

	public slots:

	protected:
		/// @brief Consumer key
		QString consumerKey;

		/// @brief Consumer secret
		QString consumerSecret;

		/// @brief Callback URL of the application
		QString callbackUrl;

		/// @brief requestToken
		QString requestToken;

		/// @brief requestSecret
		QString requestSecret;

		/// @brief accessToken
		QString accessToken;

		/// @brief tokenSecret
		QString tokenSecret;

		/// @brief Algorithm used for signing requests
		QString oauthSignatureMethod;

		/// @brief Version of the OAuth protocol used for the authentication.
		QString oauthVersion;

		/// @brief Token used for requests
		QString & oauthToken;

		/// @brief Secret used for signatures
		QString & oauthSecret;

		/// @brief Verifier for authentication
		QString oauthVerifier;


	private:
		/// @fn QString generateNonce();
		/// @brief Generates a nonce for a request
		/// @return A nonce for a request.
		QString generateNonce();

		/// @fn QString generateTimestamp();
		/// @brief Generates a timestamp for a request
		/// @return A timestamp corresponding to the current date.
		QString generateTimestamp();

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
};

#endif // OAUTHMANAGER_HPP
