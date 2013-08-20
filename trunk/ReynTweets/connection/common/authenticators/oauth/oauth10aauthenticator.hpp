/// @file oauth10aauthenticator.hpp
/// @brief Header of OAuth10aAuthenticator
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2013 Romain Ducher
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

#ifndef OAUTH10AAUTHENTICATOR_HPP
#define OAUTH10AAUTHENTICATOR_HPP

#include <QByteArray>
#include <QMap>
#include <QString>
#include "oauthauthenticator.hpp"
#include "../../httprequesttype.hpp"
#include "../../headersmap.hpp"

/// @class OAuth10aAuthenticator
/// @brief Authenticator for stuff related to OAuth 1.0a.
class OAuth10aAuthenticator : public virtual OAuthAuthenticator
{
	public:
		/// @fn OAuth10aAuthenticator(QString signatureAlgorithm = "SHA-1");
		/// @brief Constructor.
		///
		/// Application settings (callback URL, oauth credentials) will be
		/// filled later.
		/// @param signatureAlgorithm Algorithm used for signing requests.
		OAuth10aAuthenticator(QString signatureAlgorithm = "HMAC-SHA1");

		/// @fn virtual ~OAuth10aAuthenticator();
		/// @brief Destructor
		virtual ~OAuth10aAuthenticator();


		/////////////////////
		// Getters on data //
		/////////////////////

		/// @fn QString getCallbackUrl();
		/// @brief Getter for callbackUrl
		/// @return The callback URL
		QString getCallbackUrl();

		/// @fn void setCallbackUrl(QString newURL);
		/// @brief Setter for callbackUrl
		/// @param newURL New value for the callback URL
		void setCallbackUrl(QString newURL);

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

		/// @fn void resetTokens();
		/// @brief Resetting the tokens. A full new OAuth authentication process
		/// has to be launch to get tokens and for authentication in requests
		void resetTokens();


	protected:
		/// @brief Callback URL of the application
		QString callbackUrl;

		/// @brief Access tokens
		TokenPair oauthTokens;

		/// @brief Algorithm used for signing requests
		QString oauthSignatureMethod;

		/// @brief Verifier for authentication
		QByteArray oauthVerifier;

		/// @fn QByteArray signDatas(Network::RequestType type,
		///							 QString baseURL,
		///							 ArgsMap getDatas,
		///							 ArgsMap postDatas,
		///							 QString nonce,
		///							 QString timestamp,
		///							 bool oauthTokenNeeded = true,
		///							 bool callbackUrlNeeded = false,
		///							 bool oauthVerifierNeeded = false);
		/// @brief Method for signing datas. It is described
		/// <a href="https://dev.twitter.com/docs/auth/creating-signature">here
		/// </a>.
		/// @param type Request type (GET or POST)
		/// @param baseURL URL of the service, without the GET arguments.
		/// @param getDatas GET datas to sign
		/// @param postDatas POST datas to sign
		/// @param nonce Nonce of the request
		/// @param timestamp Timestamp of the request
		/// @param oauthTokenNeeded Boolean indicating whether
		/// the oauth_token is required.
		/// @param callbackUrlNeeded Boolean indicating whether
		/// the oauth_callback is required.
		/// @param oauthVerifierNeeded Boolean indicating whether
		/// the oauth_verifier is required.
		/// @return The signature of the given datas
		QByteArray signDatas(Network::HTTPRequestType type,
							 QString baseURL,
							 ArgsMap getDatas,
							 ArgsMap postDatas,
							 QString nonce,
							 QString timestamp,
							 bool oauthTokenNeeded = true,
							 bool callbackUrlNeeded = false,
							 bool oauthVerifierNeeded = false);

		/// @fn QString buildOAuthParameterString(QString nonce,
		///										  QString timestamp,
		///										  QString separator,
		///										  bool oauthTokenNeeded,
		///										  bool callbackUrlNeeded,
		///										  bool oauthVerifierNeeded,
		///										  bool putDoubleQuotes,
		///										  bool signatureNeeded,
		///										  QByteArray signature = "");
		/// @brief Generic method to build strings with OAuth parameters.
		///
		/// It is used for the signature (string with the OAuth parameters) and
		/// for the Authorization Header
		/// @param nonce Nonce of the request
		/// @param timestamp Timestamp of the request
		/// @param separator Separator between parameters
		/// @param oauthTokenNeeded Boolean indicating whether
		/// the oauth_token is required.
		/// @param callbackUrlNeeded Boolean indicating whether
		/// the oauth_callback is required.
		/// @param oauthVerifierNeeded Boolean indicating whether
		/// the oauth_verifier is required.
		/// @param putDoubleQuotes Boolean indicating if double quotes have to
		/// surround the percent encoded value.
		/// @param signatureNeeded Boolean indicating that the signature of
		/// the request is required.
		/// @param signature Signature of the request, if needed.
		/// @return The string with the parameters.
		QString buildOAuthParameterString(QString nonce,
										  QString timestamp,
										  QString separator,
										  bool oauthTokenNeeded,
										  bool callbackUrlNeeded,
										  bool oauthVerifierNeeded,
										  bool putDoubleQuotes,
										  bool signatureNeeded,
										  QByteArray signature = "");

		/// @fn QString buildSignatureBaseString(ArgsMap getDatas,
		///										 ArgsMap postDatas,
		///										 QString oauthString);
		/// @brief Method builing the base string for the OAuth Signature.
		/// @param getDatas GET datas of the request
		/// @param postDatas POST datas of the request
		/// @param oauthString String with the OAuth parameters.
		///
		/// At a certain point of the algorithm, all the parameters have to be
		/// sorted lexicographically with their name. All the OAuth parameters
		/// are named "&lt;oauth_something&gt;" and likely to be one after
		/// another after sorting the parameters. That's why they are all
		/// put into a "oauthString" parameter which will be inserted
		/// at the right place.
		/// @return The string built just like Twitter describes
		/// <a href="https://dev.twitter.com/docs/auth/creating-signature">
		/// here</a>.
		QString buildSignatureBaseString(ArgsMap getDatas,
										 ArgsMap postDatas,
										 QString oauthString);
};

#endif // OAUTH10AAUTHENTICATOR_HPP
