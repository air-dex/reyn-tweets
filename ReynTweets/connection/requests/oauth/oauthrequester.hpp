/// @file oauthrequester.hpp
/// @brief Header of OAuthRequester
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

#ifndef OAUTHREQUESTER_HPP
#define OAUTHREQUESTER_HPP

#include "../authenticationrequester.hpp"

/// @class OAuthRequester
/// @brief Generic requester for requests dealing with OAuth
class OAuthRequester : public AuthenticationRequester
{
	Q_OBJECT

	public:
		/// @fn OAuthRequester(RequestType type,
		///					   QString url,
		///					   OAuthManager &authManager,
		///					   ErrorType parseErrorType,
		///					   bool tokenNeeded = true,
		///					   bool callbackURLNeeded = false,
		///					   bool verifierNeeded = false);
		/// @brief Constructor
		/// @param type Type of the request (GET ou POST).
		/// @param url URL of the request
		/// @param authManager Information for OAuth. The requester takes its
		/// memory address.
		/// @param parseErrorType Error type while parsing. It is not JSON.
		/// @param tokenNeeded Boolean indicating if the oauth_token parameter
		/// is required for authentication.
		/// @param callbackURLNeeded Boolean indicating if the oauth_callback
		/// parameter is required for authentication.
		/// @param verifierNeeded Boolean indicating if the oauth_verifier
		/// parameter is required for authentication.
		OAuthRequester(RequestType type,
					   QString url,
					   OAuthManager &authManager,
					   ErrorType parseErrorType,
					   bool tokenNeeded = true,
					   bool callbackURLNeeded = false,
					   bool verifierNeeded = false);
};

#endif // OAUTHREQUESTER_HPP
