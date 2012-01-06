/// @file authorizerequester.hpp
/// @brief Header of AuthorizeRequester
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

#ifndef AUTHORIZEREQUESTER_HPP
#define AUTHORIZEREQUESTER_HPP

#include "oauthrequester.hpp"

/// @class AuthorizeRequester
/// @brief Requester for OAuth authentication
class AuthorizeRequester : public OAuthRequester
{
	Q_OBJECT

	public:
		/// @fn AuthorizeRequester(OAuthManager & authManager);
		/// @brief Constructor
		/// @param authManager Informations for OAuth.
		AuthorizeRequester(OAuthManager & authManager);

	protected:
		/////////////////////////////////
		// Override for this requester //
		/////////////////////////////////

		/// @fn void buildGETParameters();
		/// @brief Method building GET Parameters
		void buildGETParameters();

		/// @fn QVariant parseResult(bool & parseOK, QVariantMap & parsingErrors);
		/// @brief Method that will parse the raw results of the request.
		/// @param parseOK Boolean whose value will be set to true if there was
		/// no problem while parsing, false otherwise.
		/// @param parsingErrors QVariantMap that may contain information about
		/// errors that may occur while parsing.
		/// @return Parsed results
		QVariant parseResult(bool & parseOK, QVariantMap & parsingErrors);
};

#endif // AUTHORIZEREQUESTER_HPP
