/// @file coreresult.hpp
/// @brief Header with enums indicating how ReynCore treatments have ended.
///
/// Revisions of the file older than r204 are in /trunk/ReynTweets/controls
/// r204 is in /trunk/ReynTweets/logic
/// The file was called launchresult.hpp until r205.
/// @author Romain DUCHER
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
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

#ifndef CORERESULT_HPP
#define CORERESULT_HPP

/// @enum CoreResult
/// @brief Unified error for all the possible ends of all treatments
enum CoreResult {
	///////////////////////////////////////////////
	// Rresults independant from Twitter actions //
	///////////////////////////////////////////////

	/// @brief Issue for fake process results
	INVALID_ISSUE,

	/// @brief The request ends with an unknown problem
	UNKNOWN_PROBLEM,

	/// @brief There were an error while parsing results
	PARSE_ERROR,

	/// @brief There were an error while calling the network
	NETWORK_CALL,


	/////////////////////////////////////////////////
	// Problems linked to Twitter requests problem //
	/////////////////////////////////////////////////

	/// @brief There was no more data to return.
	///
	/// Corresponding Twitter return code is 304.
	NO_MORE_DATA,

	/// @brief The request was invalid.
	///
	/// Corresponding Twitter return code is 400.
	BAD_REQUEST,

	/// @brief Twitter did not treat the request.
	///
	/// Corresponding Twitter return code is 403.
	REFUSED_REQUEST,

	/// @brief The URI of the request or the requested resource is invalid.
	///
	/// Corresponding Twitter return code is 404.
	RESOURCE_NOT_FOUND,

	/// @brief The search format is invalid.
	///
	/// Corresponding Twitter return code is 406.
	INVALID_SEARCH,

	/// @brief Rate limit was hit.
	///
	/// Corresponding Twitter return code is 420.
	RATE_LIMITED,

	/// @brief Twitter got problems.
	///
	/// Corresponding Twitter return code looks like 5xx.
	TWITTER_DOWN,


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

	/// @brief Credentials were wrong.
	///
	/// Corresponds to the Twitter return code 401 too.
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
	POST_AUTHORIZING_FAILED,


	//////////
	// Misc //
	//////////

	/// @brief LaunchingProcess ended successfully
	LAUNCH_SUCCESSFUL,

	/// @brief An authentication to Twitter is required
	AUTHENTICATION_REQUIRED,

	/// @brief AllowProcess ended successfully
	ALLOW_SUCCESSFUL,

	/// @brief FavoriteProcess ended successfully
	FAVORITE_SUCCESSFUL,

	/// @brief After retrieving a timeline
	TIMELINE_RETRIEVED,

	/// @brief After deleting a tweet
	TWEET_DELETED,

	/// @brief After updating a tweet
	TWEET_POSTED,

	/// @brief After retweeting a tweet
	TWEET_RETWEETED,

	/// @brief The user was wrong
	WRONG_USER,

	/// @brief If a tweet cannot be deleted
	TWEET_UNDESTROYABLE
};

#endif // CORERESULT_HPP
