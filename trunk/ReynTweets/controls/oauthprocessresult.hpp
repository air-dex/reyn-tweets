/// @file oauthprocessresult.hpp
/// @brief Header of OAuthProcessResult
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

#ifndef OAUTHPROCESSRESULT_HPP
#define OAUTHPROCESSRESULT_HPP

/// @enum OAuthProcessResult
/// @brief Result of the OAuth Process
enum OAuthProcessResult {
	/// @brief The application is authorized
	AUTHORIZED,

	/// @brief The application is denied
	DENIED,

	/// @brief An error occured during the process
	ERROR_PROCESS
};

#endif // OAUTHPROCESSRESULT_HPP
