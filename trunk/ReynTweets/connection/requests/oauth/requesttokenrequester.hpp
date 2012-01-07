/// @file requesttokenrequester.hpp
/// @brief Header of RequestTokenRequester
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

#ifndef REQUESTTOKENREQUESTER_HPP
#define REQUESTTOKENREQUESTER_HPP

#include "oauthrequester.hpp"

/// @class RequestTokenRequester
/// @brief Class managing requests with the Twitter API about OAuth
class RequestTokenRequester : public OAuthRequester
{
	Q_OBJECT

	public:
		/// @fn RequestTokenRequester(OAuthManager & authManager);
		/// @brief Constructor
		/// @param authManager Information for OAuth.
		RequestTokenRequester(OAuthManager & authManager);

	protected:
		/// @fn QVariant parseResult(bool & parseOK, QVariantMap & parsingErrors);
		/// @brief Method that will parse the raw results of the request. For
		/// this kind of request, results look like :<br/>
		/// oauth_token=value of the request token&
		/// oauth_token_secret=value of the request secret&
		/// oauth_callback_confirmed=true or false
		/// @param parseOK Boolean whose value will be set to true if there was
		/// no problem while parsing, false otherwise.
		/// @param parsingErrors QVariantMap that may contain information about
		/// errors that may occur while parsing.
		/// @return Parsed results
		QVariant parseResult(bool & parseOK, QVariantMap & parsingErrors);
};

#endif // REQUESTTOKENREQUESTER_HPP
