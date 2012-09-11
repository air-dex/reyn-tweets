/// @file twitterrequests.hpp
/// @brief Header including all the request classes which call the Twitter API.
///
/// This file was known as requests.hpp until r410.
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

#ifndef TWITTERREQUESTS_HPP
#define TWITTERREQUESTS_HPP

#include "accounts/verifycredentialsrequester.hpp"
#include "favorites/favoriterequester.hpp"
#include "favorites/favoritestimelinerequester.hpp"
#include "favorites/unfavoriterequester.hpp"
#include "oauth/accesstokenrequester.hpp"
#include "oauth/authorizerequester.hpp"
#include "oauth/postauthorizerequester.hpp"
#include "oauth/requesttokenrequester.hpp"
#include "searches/searchrequester.hpp"
#include "timelines/hometimelinerequester.hpp"
#include "timelines/mentionstimelinerequester.hpp"
#include "tweets/destroytweetrequester.hpp"
#include "tweets/posttweetrequester.hpp"
#include "tweets/retweetrequester.hpp"
#include "tweets/showtweetrequester.hpp"
#include "users/showuserrequester.hpp"

#endif // TWITTERREQUESTS_HPP
