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

#include <QByteArray>
#include <QString>
#include "reyntweetssettings.hpp"
#include "requesttype.hpp"

/// @class OAuthManager
/// @brief Class managing OAuth authentication to Twitter.
class OAuthManager
{
	public:
		/// @fn OAuthManager(QString clientKey = ReynTweetsConfiguration::CONSUMER_KEY,
		///			QString clientSecret = ReynTweetsConfiguration::CONSUMER_SECRET,
		///			QString clientUrl = ReynTweetsConfiguration::CALLBACK_URL,
		///			QString signatureAlgorithm = "SHA-1",
		///			QString version = "1.0);
		/// @brief Constructor
		/// @param clientKey Consumer key of the application. Reyn Tweets'
		/// consumer key is its default value.
		/// @param clientSecret Consumer secret of the application.
		/// Reyn Tweets' consumer secret is its default value.
		/// @param clientUrl Callback URL of the application Reyn Tweets'
		/// callback URL is its default value.
		/// @param signatureAlgorithm Algorithm used for signing requests.
		/// @param version Version of the OAuth protocol used for the
		/// authentication. Reyn Tweets uses OAuth 1.0.
		OAuthManager(QString clientKey = ReynTweetsConfiguration::CONSUMER_KEY,
					 QString clientSecret = ReynTweetsConfiguration::CONSUMER_SECRET,
					 QString clientUrl = ReynTweetsConfiguration::CALLBACK_URL,
					 QString signatureAlgorithm = "HMAC-SHA1",
					 QString version = "1.0");


		/////////////////////
		// Getters on data //
		/////////////////////

		/// @fn QString getCallbackUrl();
		/// @brief Getter for callbackUrl
		/// @return The callback URL
		QString getCallbackUrl();

		/// @fn void setOAuthToken(QString oauthToken);
		/// @brief Setter on the OAuth token
		/// @param oauthToken The new value of the OAuth token
		void setOAuthToken(QString oauthToken);

		/// @fn void setOAuthSecret(QString oauthSecret);
		/// @brief Setter on the OAuth secret
		/// @param oauthSecret The new value of the OAuth secret
		void setOAuthSecret(QString oauthSecret);

		/// @fn void setVerifier(QString verifier);
		/// @brief Setter on the verifier
		/// @param verifier The new verifier
		void setVerifier(QString verifier);


		////////////////////////////
		// Utilities for requests //
		////////////////////////////

		/// @fn QByteArray getAuthorizationHeader(RequestType type,
		///										  QString baseURL,
		///										  QString getDatas,
		///										  QString postDatas,
		///										  bool isRequestTokenRequest);
		/// @brief Getting that will be written in the "Authorization" field
		/// of requests
		/// @param type Request type (GET or POST)
		/// @param dataToSign Datas that will be signed
		/// @param isRequestTokenRequest Boolean indicationg whether the request
		/// is for a request token. In this case, the "oauth_token" parameter is
		/// replaced by "oauth_callback_url".
		/// @return That will be written in the "Authorization" header.
		QByteArray getAuthorizationHeader(RequestType type,
										  QString baseURL,
										  QString getDatas,
										  QString postDatas,
										  bool isRequestTokenRequest);


	protected:
		/// @brief Consumer key
		QString consumerKey;

		/// @brief Consumer secret
		QString consumerSecret;

		/// @brief Callback URL of the application
		QString callbackUrl;

		/// @brief Algorithm used for signing requests
		QString oauthSignatureMethod;

		/// @brief Version of the OAuth protocol used for the authentication.
		QString oauthVersion;

		/// @brief Token used for requests
		QString oauthToken;

		/// @brief Secret used for signatures
		QString oauthSecret;

		/// @brief Verifier for authentication
		QString oauthVerifier;


	private:
		/// @fn QString generateNonce();
		/// @brief Generates a nonce for a request. To generate a nonce,
		/// a random string is generated by taking 32 times one letter in the
		/// alphabet. The letter could be in upper case or lower case. The final
		/// nonce is the 64 base-encoding of the random string.
		/// @return A nonce for a request.
		QString generateNonce();

		/// @fn QString generateTimestamp();
		/// @brief Generates a timestamp for a request
		/// @return A timestamp corresponding to the current date.
		QString generateTimestamp();

		/// @fn QString signDatas(RequestType type,
		///						  QString baseURL,
		///						  QString getDatas,
		///						  QString postDatas,
		///						  QString nonce,
		///						  QString timestamp,
		///						  bool isRequestTokenRequest);
		/// @brief Method for signing datas. It is described
		/// <a href="https://dev.twitter.com/docs/auth/creating-signature">here
		/// </a>.
		/// @param type Request type (GET or POST)
		/// @param baseURL URL of the service
		/// @param getDatas GET datas to sign
		/// @param postDatas POST datas to sign
		/// @param nonce Nonce of the request
		/// @param timestamp Timestamp of the request
		/// @return The signature of the given datas
		QString signDatas(RequestType type,
						  QString baseURL,
						  QString getDatas,
						  QString postDatas,
						  QString nonce,
						  QString timestamp,
						  bool isRequestTokenRequest);

		/// @fn QString hmacSha1(QByteArray key, QByteArray baseString);
		/// @brief HMAC-SHA1 algorithm for signatures. Its implementation for
		/// Reyn Tweets was found on the <a href="http://developer.qt.nokia.com/">
		/// Qt Developer Network</a> here :
		/// <a href="http://developer.qt.nokia.com/wiki/HMAC-SHA1">
		/// http://developer.qt.nokia.com/wiki/HMAC-SHA1</a>.
		/// @param key Key for signature
		/// @param baseString String that we want to sign
		/// @return The signature
		QString hmacSha1(QByteArray key, QByteArray baseString);

		/// @fn QString formatOAuthParam(QString name,
		///								 QString value,
		///								 bool putDoubleQuotes);
		/// @brief Method for formatting parameters in the Authorization header
		/// and in the signature.
		/// The process of how formatting parameters is described
		/// <a href="https://dev.twitter.com/docs/auth/authorizing-request">here
		/// </a> for the Authorization header and
		/// <a href="https://dev.twitter.com/docs/auth/creating-signature">here
		/// </a> for the signature. The difference between these two algorithm
		/// is that double quotes '"' surrounds the percent encoded value for
		/// the Authorization Header and not for the signature.
		/// @param name Name of the parameter
		/// @param value Value of the parameter
		/// @param putDoubleQuotes Boolean indicating if double quotes have to
		/// surround the percent encoded value.
		/// @return The formatted parameters
		QString formatOAuthParam(QString name,
								 QString value,
								 bool putDoubleQuotes);
};

#endif // OAUTHMANAGER_HPP
