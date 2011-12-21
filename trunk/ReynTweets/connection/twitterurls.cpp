/// @file twitterurls.cpp
/// @brief Implementation of the TwitterURL namespace.
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
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "twitterurls.hpp"

///////////
// OAuth //
///////////

/// @brief URL for getting a request token
QString TwitterURL::REQUEST_TOKEN_URL = "https://api.twitter.com/oauth/request_token";

/// @brief URL for authorizing the application
QString TwitterURL::AUTHORIZE_URL = "https://api.twitter.com/oauth/authorize";

/// @brief URL for authentication
QString TwitterURL::AUTHENTICATE_URL = "https://api.twitter.com/oauth/authenticate";

/// @brief URL for getting an access token
QString TwitterURL::ACCESS_TOKEN_URL = "https://api.twitter.com/oauth/access_token";


//////////////
// Searches //
//////////////

/// @brief URL for a search request
QString TwitterURL::SEARCH_URL = "http://search.twitter.com/search.json";
