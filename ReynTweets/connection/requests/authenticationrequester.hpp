/// @file authenticationrequester.hpp
/// @brief Header of AuthenticationRequester
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

#ifndef AUTHENTICATIONREQUESTER_HPP
#define AUTHENTICATIONREQUESTER_HPP

#include "genericrequester.hpp"

/// @class AuthenticationRequester
/// @brief Requester specialized for requests which needs authentication.
class AuthenticationRequester : public GenericRequester
{
		Q_OBJECT
	public:
		/// @fn AuthenticationRequester(RequestType type,
		///								QString url,
		///								OAuthManager & authManager,
		///								ErrorType parseError = QJSON_PARSING,
		///								bool tokenNeeded = true,
		///								bool callbackURLNeeded = false,
		///								bool verifierNeeded = false);
		/// @brief Constructor
		/// @param type Type of the request (GET ou POST).
		/// @param url URL called by the requester
		/// @param authManager Entity with information for OAuth
		/// @param parseError Error type if an error occurs while parsing. Most
		/// of the time, this value is set to QJSON_PARSING because results are
		/// QJson stream parsed with QJson. However, OAuth requesters use their
		/// own parsing process so they need a special value called OAUTH_PARSING.
		/// @param tokenNeeded Boolean indicating if the oauth_token parameter
		/// is required for authentication.
		/// @param callbackURLNeeded Boolean indicating if the oauth_callback
		/// parameter is required for authentication.
		/// @param verifierNeeded Boolean indicating if the oauth_verifier
		/// parameter is required for authentication.
		AuthenticationRequester(RequestType type,
								QString url,
								OAuthManager & authManager,
								ErrorType parseError = QJSON_PARSING,
								bool tokenNeeded = true,
								bool callbackURLNeeded = false,
								bool verifierNeeded = false);


	protected:
		/// @brief Entity with authentication information
		OAuthManager & oauthManager;

		/// @brief Boolean indicating if the oauth_token parameter is required
		/// for authentication.
		bool oauthTokenNeeded;

		/// @brief Boolean indicating if the oauth_callback parameter
		/// is required for authentication.
		bool oauthCallbackUrlNeeded;

		/// @brief Boolean indicating if the oauth_token parameter is required
		/// for authentication.
		bool oauthVerifierNeeded;

	private:
		/// @fn virtual void initCommunicator();
		/// @brief Initialize the communicator. This a template method because
		/// of the authorize() request and its special Twitter Communicator.
		virtual void initCommunicator();
};

#endif // AUTHENTICATIONREQUESTER_HPP
