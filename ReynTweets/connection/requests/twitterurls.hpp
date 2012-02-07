/// @file twitterurls.hpp
/// @brief Declaration of the TwitterURL namespace.
///
/// Revisions older than r242 were in /trunk/ReynTweets/connection
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
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TWITTERURLS_HPP
#define TWITTERURLS_HPP

#include <QString>

/// @namespace TwitterURL
/// @brief Namespace containing all the Twitter API URLs.
namespace TwitterURL
{
	/////////////
	// Account //
	/////////////

	/// @brief URL to verify if credentials are right
	extern QString VERIFY_CREDENTIALS_URL;


	///////////
	// OAuth //
	///////////

	/// @brief URL to get request tokens
	extern QString REQUEST_TOKEN_URL;

	/// @brief URL to authorize the application
	extern QString AUTHORIZE_URL;

	/// @brief URL for authentication
	extern QString AUTHENTICATE_URL;

	/// @brief URL to get access tokens
	extern QString ACCESS_TOKEN_URL;


	//////////////
	// Searches //
	//////////////

	/// @brief URL for search requests
	extern QString SEARCH_URL;


	////////////
	// Tweets //
	////////////

	/// @brief URL to get informations about a given tweet
	extern QString SHOW_TWEET_URL;


	///////////
	// Users //
	///////////

	/// @brief URL to get informations about a given user
	extern QString SHOW_USER_URL;
}

#endif // TWITTERURLS_HPP
