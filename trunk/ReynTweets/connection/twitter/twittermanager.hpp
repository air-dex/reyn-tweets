/// @file twittermanager.hpp
/// @brief Header of TwitterManager
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011, 2013 Romain Ducher
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

#ifndef TWITTERMANAGER_HPP
#define TWITTERMANAGER_HPP

#include "../common/authmanagers/oauth10aauthenticator.hpp"
#include "../common/authmanagers/oauth2authenticator.hpp"

/// @class TwitterManager
/// @brief Class managing OAuth authentication to Twitter.
///
/// Twitter (and so Reyn Tweets) uses both OAuth 1.0a and OAuth 2.
class TwitterManager :
		public OAuth10aAuthenticator,
		public virtual OAuth2Authenticator
{
	public:
		/// @fn OAuthManager();
		/// @brief Constructor.
		///
		/// Application settings (callback URL, consumer credentials) will be
		/// filled later.
		TwitterManager();

		/// @fn virtual ~OAuthManager();
		/// @brief Destructor
		virtual ~TwitterManager();


		/////////////////////
		// Getters on data //
		/////////////////////

		/// @fn void resetTokens();
		/// @brief Resetting the tokens. A full new OAuth authentication process
		/// has to be launch to get tokens and for authentication in requests
		void resetTokens();
/*
		/// @fn void setBearerToken(QByteArray newBearer);
		/// @brief Setter for bearerToken
		/// @param newBearer New value for bearerToken
		void setBearerToken(QByteArray newBearer);

		/// @fn QString getCallbackUrl();
		/// @brief Getter for callbackUrl
		/// @return The callback URL
		QString getCallbackUrl();

		/// @fn void setCallbackUrl(QString newURL);
		/// @brief Setter for callbackUrl
		/// @param newURL New value for the callback URL
		void setCallbackUrl(QString newURL);

		/// @fn void setConsumerKey(QByteArray clientKey);
		/// @brief Setter on the consumer key
		/// @param clientKey New consumer key
		void setConsumerKey(QByteArray clientKey);

		/// @fn void setConsumerSecret(QByteArray clientSecret);
		/// @brief Setter on the consumer secret
		/// @param clientSecret New consumer secret
		void setConsumerSecret(QByteArray clientSecret);

		/// @fn QByteArray getOAuthToken();
		/// @brief Getting the OAuth Token
		/// @return The OAuth Token
		QByteArray getOAuthToken();

		/// @fn void setOAuthToken(QByteArray authToken);
		/// @brief Setter on the OAuth token
		/// @param authToken The new value of the OAuth token
		void setOAuthToken(QByteArray authToken);

		/// @fn void setOAuthSecret(QByteArray oauthSecret);
		/// @brief Setter on the OAuth secret
		/// @param oauthSecret The new value of the OAuth secret
		void setOAuthSecret(QByteArray authSecret);

		/// @fn QByteArray getVerifier();
		/// @brief Getter on the verifier
		/// @return The verifier
		QByteArray getVerifier();

		/// @fn void setVerifier(QByteArray verifier);
		/// @brief Setter on the verifier
		/// @param verifier The new verifier
		void setVerifier(QByteArray verifier);

		////////////////////////////
		// Utilities for requests //
		////////////////////////////

		/// @fn QByteArray getAuthorizationHeader(Network::HTTPRequestType type,
		///										  QString baseURL,
		///										  ArgsMap getDatas,
		///										  ArgsMap postDatas,
		///										  bool oauthTokenNeeded = true,
		///										  bool callbackUrlNeeded = false,
		///										  bool oauthVerifierNeeded = false);
		/// @brief Getting that will be written in the "Authorization" field
		/// of requests
		/// @param type Request type (GET or POST)
		/// @param baseURL URL for the request
		/// @param getDatas GET arguments of the request
		/// @param postDatas POST arguments of the request
		/// @param oauthTokenNeeded Boolean indicating whether
		/// the oauth_token is required for the header.
		/// @param callbackUrlNeeded Boolean indicating whether
		/// the oauth_callback is required for the header.
		/// @param oauthVerifierNeeded Boolean indicating whether
		/// the oauth_verifier is required for the header.
		/// @return Value of the "Authorization" header.
		QByteArray getAuthorizationHeader(Network::HTTPRequestType type,
										  QString baseURL,
										  ArgsMap getDatas,
										  ArgsMap postDatas,
										  bool oauthTokenNeeded = true,
										  bool callbackUrlNeeded = false,
										  bool oauthVerifierNeeded = false);

		/// @fn QByteArray getBasicHeader();
		/// @brief Building the header used to retrieve or to invalidate
		/// a Bearer Token.
		/// @return The corresponding header
		QByteArray getBasicHeader();

		/// @fn QByteArray getBearerHeader();
		/// @brief Building the header used to authenticate requests.
		/// @return The corresponding header
		QByteArray getBearerHeader();

	protected:
		/// @brief Entity for authentications with OAuth 1.0a.
		OAuth10aAuthenticator oauth10a;

		/// @brief Entity for authentications with OAuth 2.
		OAuth2Authenticator oauth2;//*/
};

#endif // TWITTERMANAGER_HPP
