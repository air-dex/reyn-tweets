/// @file twitterurls.hpp
/// @brief Declaration of the TwitterURL namespace.
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

#ifndef TWITTERURLS_HPP
#define TWITTERURLS_HPP

#include <QString>

/// @namespace TwitterURL
/// @brief Namespace containing all the Twitter API URLs.
namespace TwitterURL
{
	///////////
	// OAuth //
	///////////

	/// @brief URL for getting a request token
	extern QString REQUEST_TOKEN_URL;

	/// @brief URL for authorizing the application
	extern QString AUTHORIZE_URL;

	/// @brief URL for authentication
	extern QString AUTHENTICATE_URL;

	/// @brief URL for getting an access token
	extern QString ACCESS_TOKEN_URL;


	//////////////
	// Searches //
	//////////////

	/// @brief URL for a search request
	extern QString SEARCH_URL;
}

#endif // TWITTERURLS_HPP
