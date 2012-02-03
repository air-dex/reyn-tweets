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
GNU Lesser General Public License for more details.

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
/// @brief Class managing OAuth authentication to Twitter. For the security,
/// tokens are kept secret. They are encoded for that.
class OAuthManager
{
	public:
		/// @fn OAuthManager(QByteArray clientKey = ReynTweetsConfiguration::CONSUMER_KEY,
		///					 QByteArray clientSecret = ReynTweetsConfiguration::CONSUMER_SECRET,
		///					 QString clientUrl = ReynTweetsConfiguration::CALLBACK_URL,
		///					 QString signatureAlgorithm = "SHA-1",
		///					 QString version = "1.0");
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
		OAuthManager(QByteArray clientKey = ReynTweetsSettings::CONSUMER_KEY,
					 QByteArray clientSecret = ReynTweetsSettings::CONSUMER_SECRET,
					 QString clientUrl = ReynTweetsSettings::CALLBACK_URL,
					 QString signatureAlgorithm = "HMAC-SHA1",
					 QString version = "1.0");

		/// @fn virtual ~OAuthManager();
		/// @brief Destructor
		virtual ~OAuthManager();


		/////////////////////
		// Getters on data //
		/////////////////////

		/// @fn QString getCallbackUrl();
		/// @brief Getter for callbackUrl
		/// @return The callback URL
		QString getCallbackUrl();

		/// @fn void setConsumerKey(QByteArray clientKey);
		/// @brief Setter on the consumer key
		/// @param clientKey New consumer key
		void setConsumerKey(QByteArray clientKey);

		/// @fn void setConsumerSecret(QByteArray clientSecret);
		/// @brief Setter on the consumer secret
		/// @param clientSecret New consumer secret
		void setConsumerSecret(QByteArray clientSecret);

		/// @fn QByteArray getOAuthToken(bool isClear = true);
		/// @brief Getting the OAuth Token
		/// @param isClear Boolean indicating if the clear value is asked
		/// @return The OAuth Token
		QByteArray getOAuthToken(bool isClear = true);

		/// @fn void setOAuthToken(QByteArray authToken, bool isClear = true);
		/// @brief Setter on the OAuth token
		/// @param authToken The new value of the OAuth token
		/// @param isClear Boolean indicating if the token passed to the method
		/// is clear or encrypted.
		void setOAuthToken(QByteArray authToken, bool isClear = true);

		/// @fn void setOAuthSecret(QByteArray oauthSecret, bool isClear = true);
		/// @brief Setter on the OAuth secret
		/// @param oauthSecret The new value of the OAuth secret
		/// @param isClear Boolean indicating if the token passed to the method
		/// is clear or encrypted.
		void setOAuthSecret(QByteArray authSecret, bool isClear = true);

		/// @fn QByteArray getVerifier(bool isClear = true);
		/// @brief Getter on the verifier
		/// @param isClear Boolean indicating if the clear value is asked
		/// @return The verifier
		QByteArray getVerifier(bool isClear = true);

		/// @fn void setVerifier(QByteArray verifier);
		/// @brief Setter on the verifier
		/// @param verifier The new verifier (clear value)
		void setVerifier(QByteArray verifier);

		/// @fn QByteArray getAuthenticityToken(bool isClear = true);
		/// @brief Getter on the Authenticity Token
		/// @param isClear Boolean indicating if the clear value is asked
		/// @return The Authenticity Token
		QByteArray getAuthenticityToken(bool isClear = true);

		/// @fn void setAuthenticityToken(QByteArray authToken);
		/// @brief Setter on the Authenticity Token
		/// @param authToken The new value of the Authenticity Token (clear value)
		void setAuthenticityToken(QByteArray authToken);

		/// @fn QString getDeny();
		/// @brief Getter on the deny tag
		/// @return The verifier
		QString getDeny();

		/// @fn void setDeny(QString denyString);
		/// @brief Setter on the deny tag
		/// @param denyString The new value for the deny tag
		void setDeny(QString denyString);


		////////////////////////////
		// Utilities for requests //
		////////////////////////////

		/// @fn QByteArray getAuthorizationHeader(RequestType type,
		///										  QString baseURL,
		///										  QString getDatas,
		///										  QString postDatas,
		///										  bool oauthTokenNeeded,
		///										  bool callbackUrlNeeded,
		///										  bool oauthVerifierNeeded);
		/// @brief Getting that will be written in the "Authorization" field
		/// of requests
		/// @param type Request type (GET or POST)
		/// @param baseURL URL for the request
		/// @param getDatas GET arguments of the request
		/// @param postDatas POST arguments of the request
		/// @param oauthTokenNeeded Boolean indicationg that the oauth_token
		/// is requested for the header.
		/// @param callbackUrlNeeded Boolean indicationg that the oauth_callback
		/// is requested for the header.
		/// @param oauthVerifierNeeded Boolean indicationg that the oauth_verifier
		/// is requested for the header.
		/// @return Value of the "Authorization" header.
		QByteArray getAuthorizationHeader(RequestType type,
										  QString baseURL,
										  QString getDatas,
										  QString postDatas,
										  bool oauthTokenNeeded,
										  bool callbackUrlNeeded,
										  bool oauthVerifierNeeded);

		/// @fn void resetTokens();
		/// @brief Resetting the tokens. A full new OAuth authentication process
		/// has to be launch to get tokens and for authentication in requests
		void resetTokens();


	protected:
		/// @brief Consumer key
		QByteArray consumerKey;

		/// @brief Consumer secret
		QByteArray consumerSecret;

		/// @brief Callback URL of the application
		QString callbackUrl;

		/// @brief Algorithm used for signing requests
		QString oauthSignatureMethod;

		/// @brief Version of the OAuth protocol used for the authentication.
		QString oauthVersion;

		/// @brief Token used for requests
		QByteArray oauthToken;

		/// @brief Secret used for signatures
		QByteArray oauthSecret;

		/// @brief Verifier for authentication
		QByteArray oauthVerifier;

		/// @brief Authenticity token for POST authorizing()
		QByteArray authenticityToken;

		/// @brief Value used to tell Twitter that an application is denied
		QString denyTag;


	private:
		/// @fn QString generateNonce();
		/// @brief Generates a nonce for a request. To generate a nonce,
		/// a random string is generated by taking 32 times one letter in the
		/// alphabet. The letter could be in upper case or lower case. The final
		/// nonce is the 64 base-encoding of the random string.
		/// @return A nonce for a request.
		QString generateNonce();

		/// @fn QString generateTimestamp();
		/// @brief Generates a timestamp for a request. The timestamp is the
		/// number of seconds since the Unix Epoch (1/1/1970 at midnight).
		/// @return A timestamp corresponding to the current date.
		QString generateTimestamp();

		/// @fn QString signDatas(RequestType type,
		///						  QString baseURL,
		///						  QString getDatas,
		///						  QString postDatas,
		///						  QString nonce,
		///						  QString timestamp,
		///						  bool oauthTokenNeeded,
		///						  bool callbackUrlNeeded,
		///						  bool oauthVerifierNeeded);
		/// @brief Method for signing datas. It is described
		/// <a href="https://dev.twitter.com/docs/auth/creating-signature">here
		/// </a>.
		/// @param type Request type (GET or POST)
		/// @param baseURL URL of the service
		/// @param getDatas GET datas to sign
		/// @param postDatas POST datas to sign
		/// @param nonce Nonce of the request
		/// @param timestamp Timestamp of the request
		/// @param oauthTokenNeeded Boolean indicationg that the oauth_token
		/// is requested for the header.
		/// @param callbackUrlNeeded Boolean indicationg that the oauth_callback
		/// is requested for the header.
		/// @param oauthVerifierNeeded Boolean indicationg that the oauth_verifier
		/// is requested for the header.
		/// @return The signature of the given datas
		QString signDatas(RequestType type,
						  QString baseURL,
						  QString getDatas,
						  QString postDatas,
						  QString nonce,
						  QString timestamp,
						  bool oauthTokenNeeded,
						  bool callbackUrlNeeded,
						  bool oauthVerifierNeeded);

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