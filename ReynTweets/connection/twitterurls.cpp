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
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "twitterurls.hpp"

// NB : QString::fromUtf8(); is used to avoid problem with character conversion.

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
