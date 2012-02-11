/// @file twitterurls.cpp
/// @brief Implementation of the TwitterURL namespace.
///
/// Revisions older than r242 were in /trunk/ReynTweets/connection
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
QString TwitterURL::VERIFY_CREDENTIALS_URL = QString::fromUtf8("https://api.twitter.com/1/account/verify_credentials.json");


///////////////
// Favorites //
///////////////

// Favorite a tweet
QString TwitterURL::CREATE_FAVORITE_URL = QString::fromUtf8("https://api.twitter.com/1/favorites/create/:id.json");

// Unfavorite a tweet
QString TwitterURL::DELETE_FAVORITE_URL = QString::fromUtf8("https://api.twitter.com/1/favorites/destroy/:id.json");

// Getting the timeline of the favorite tweets of a user
QString TwitterURL::FAVORITE_TIMELINE_URL = QString::fromUtf8("https://api.twitter.com/1/favorites.json");


///////////
// OAuth //
///////////

// Getting a request token
QString TwitterURL::REQUEST_TOKEN_URL = QString::fromUtf8("https://api.twitter.com/oauth/request_token");

// Authorizing the application
QString TwitterURL::AUTHORIZE_URL = QString::fromUtf8("https://api.twitter.com/oauth/authorize");

// Authentication
QString TwitterURL::AUTHENTICATE_URL = QString::fromUtf8("https://api.twitter.com/oauth/authenticate");

// Getting an access token
QString TwitterURL::ACCESS_TOKEN_URL = QString::fromUtf8("https://api.twitter.com/oauth/access_token");


//////////////
// Searches //
//////////////

// Search request
QString TwitterURL::SEARCH_URL = QString::fromUtf8("http://search.twitter.com/search.json");


///////////////
// Timelines //
///////////////

// Getting the timeline with friends tweets
QString TwitterURL::HOME_TIMELINE_URL = QString::fromUtf8("https://api.twitter.com/1/statuses/home_timeline.json");


////////////
// Tweets //
////////////

// Getting informations about a given tweet
QString TwitterURL::SHOW_TWEET_URL = QString::fromUtf8("https://api.twitter.com/1/statuses/show.json");


///////////
// Users //
///////////

// Getting informations about a given user
QString TwitterURL::SHOW_USER_URL = QString::fromUtf8("https://api.twitter.com/1/users/show.json");
