/// @file showtweetrequester.cpp
/// @brief Implementation of ShowTweetRequester
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

#include "showtweetrequester.hpp"
#include "../../../tools/utils.hpp"

// Constructor
ShowTweetRequester::ShowTweetRequester(OAuthManager & authManager,
									   qlonglong id,
									   bool entities,
									   bool userIdsOnly,
									   bool withRTid) :
	AuthenticationRequester(GET, TwitterURL::SHOW_TWEET_URL, authManager),
	tweetID(id),
	includeEntities(entities),
	trimUser(userIdsOnly),
	includeMyRetweet(withRTid)
{}

// Virtual method building getParameters
void ShowTweetRequester::buildGETParameters() {
	getParameters.insert("id", QString::number(tweetID));
	getParameters.insert("include_entities", boolInString(includeEntities));
	getParameters.insert("trim_user", boolInString(trimUser));
	getParameters.insert("include_my_retweet", boolInString(includeMyRetweet));
}
