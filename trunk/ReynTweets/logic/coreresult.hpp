/// @file coreresults.hpp
/// @brief Header with enums indicating how ReynCore treatments have ended.
/// @author Romain DUCHER

/*
Copyright 2012 Romain Ducher

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

#ifndef CORERESULT_HPP
#define CORERESULT_HPP

/// @enum CoreResult
/// @brief Unified error for all the possible ends of all treatments
enum CoreResult {
	//////////////////////////////////////////////////
	// Results while manipulating the configuration //
	//////////////////////////////////////////////////

	/// @brief The launching was successful
	LOAD_CONFIGURATION_SUCCESSFUL,

	/// @brief The configuration file does not exist
	CONFIGURATION_FILE_UNKNOWN,

	/// @brief The configuration file cannot be opened
	CONFIGURATION_FILE_NOT_OPEN,

	/// @brief The configuration cannot be launched
	LOADING_CONFIGURATION_ERROR,

	/// @brief The launching was successful
	SAVE_SUCCESSFUL,


	////////////////////////////
	// Ends with token issues //
	////////////////////////////

	/// @brief Credentials were right
	TOKENS_OK,

	/// @brief Credentials were wrong
	TOKENS_NOT_AUTHORIZED,

	/// @brief Not obtained tokens (OAuth Authentication Flow)
	NO_TOKENS,


	////////////////
	// OAuth ends //
	////////////////

	/// @brief The application is authorized
	AUTHORIZED,

	/// @brief The application is denied
	DENIED,

	/// @brief Unexpected redirection during POST authorizing
	POST_AUTHORIZING_FAIL,


	/////////////////////////////////////////////////
	// Problems linked to Twitter requests problem //
	/////////////////////////////////////////////////

	/// @brief Rate limit was hit
	RATE_LIMITED,

	/// @brief Twitter got problems (Twitter return code looking like 5xx)
	TWITTER_DOWN,

	/// @brief The request ends with an unknown problem
	UNKNOWN_PROBLEM,

	/// @brief There were an error while parsing results
	PARSE_ERROR,


	//////////
	// Misc //
	//////////

	/// @brief Process ended successfully
	PROCESS_OK,

	/// @brief The user was wrong
	WRONG_USER
};

#endif // CORERESULT_HPP
