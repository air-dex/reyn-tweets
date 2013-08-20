/// @file destroytweetrequester.cpp
/// @brief Implementation of DestroyTweetRequester
/// @author Romain Ducher
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

#include "destroytweetrequester.hpp"
#include "../../../../tools/utils.hpp"

// Constructor
DestroyTweetRequester::DestroyTweetRequester(OAuthManager &authManager,
											 qlonglong statusID,
											 bool userIDonly) :
	TwitterRequester(POST, TwitterURL::DELETE_TWEET_URL, authManager),
	tweetID(statusID),
	trimUser(userIDonly)
{
	// Replacing ":id" in the URL with the tweet ID
	requestURL.replace(":id", QString::number(tweetID));
}

// Building postParameters
void DestroyTweetRequester::buildPOSTParameters() {
	postParameters.insert("id", QString::number(tweetID));
	postParameters.insert("trim_user", boolInString(trimUser));
}
