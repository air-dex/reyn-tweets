/// @file twitterurls.cpp
/// @brief Implementation of the "Twitter" namespace part containing
/// Twitter URLs.
///
/// Revisions older than SVN's r242 were in /trunk/ReynTweets/connection
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011 Romain Ducher
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

#include "twitterurls.hpp"

// NB : QString::fromUtf8(); is used to avoid problem with character conversion.

//////////////
// Accounts //
//////////////

// Verify credentials
QString Twitter::VERIFY_CREDENTIALS_URL = QString::fromUtf8("https://api.twitter.com/1.1/account/verify_credentials.json");


///////////////
// Favorites //
///////////////

// Favorite a tweet
QString Twitter::CREATE_FAVORITE_URL = QString::fromUtf8("https://api.twitter.com/1.1/favorites/create.json");

// Unfavorite a tweet
QString Twitter::DELETE_FAVORITE_URL = QString::fromUtf8("https://api.twitter.com/1.1/favorites/destroy.json");

// Getting the timeline of the favorite tweets of a user
QString Twitter::FAVORITE_TIMELINE_URL = QString::fromUtf8("https://api.twitter.com/1.1/favorites/list.json");


///////////
// OAuth //
///////////

// Getting a request token
QString Twitter::REQUEST_TOKEN_URL = QString::fromUtf8("https://api.twitter.com/oauth/request_token");

// Authorizing the application
QString Twitter::AUTHORIZE_URL = QString::fromUtf8("https://api.twitter.com/oauth/authorize");

// Authentication
QString Twitter::AUTHENTICATE_URL = QString::fromUtf8("https://api.twitter.com/oauth/authenticate");

// Getting an access token
QString Twitter::ACCESS_TOKEN_URL = QString::fromUtf8("https://api.twitter.com/oauth/access_token");


//////////////
// Searches //
//////////////

// Search request
QString Twitter::SEARCH_URL = QString::fromUtf8("https://api.twitter.com/1.1/search/tweets.json");


///////////////
// Timelines //
///////////////

// Getting the timeline with friends tweets
QString Twitter::HOME_TIMELINE_URL = QString::fromUtf8("https://api.twitter.com/1.1/statuses/home_timeline.json");

// Getting the timeline containing the user's mentions
QString Twitter::MENTIONS_TIMELINE_URL = QString::fromUtf8("https://api.twitter.com/1.1/statuses/mentions_timeline.json");

// Getting the timeline with retweets retweeted by the user
QString Twitter::RETWEETED_BY_ME_TIMELINE_URL = QString::fromUtf8("http://api.twitter.com/1/statuses/retweeted_by_me.json");


////////////
// Tweets //
////////////

// Deleting a tweet (or a retweet)
QString Twitter::DELETE_TWEET_URL = QString::fromUtf8("https://api.twitter.com/1.1/statuses/destroy/:id.json");

// Retweeting a tweet
QString Twitter::RETWEET_URL = QString::fromUtf8("https://api.twitter.com/1.1/statuses/retweet/:id.json");

// Getting informations about a given tweet
QString Twitter::SHOW_TWEET_URL = QString::fromUtf8("https://api.twitter.com/1.1/statuses/show.json");

// Updating a tweet without medias
QString Twitter::UPDATE_TWEET_URL = QString::fromUtf8("https://api.twitter.com/1.1/statuses/update.json");

// Updating a tweet with medias
QString Twitter::UPDATE_TWEET_WITH_MEDIA_URL = QString::fromUtf8("https://upload.twitter.com/1.1/statuses/update_with_media.json");


///////////
// Users //
///////////

// Getting informations about a given user
QString Twitter::SHOW_USER_URL = QString::fromUtf8("https://api.twitter.com/1.1/users/show.json");
