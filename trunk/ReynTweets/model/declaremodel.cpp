/// @file declaremodel.cpp
/// @brief Implementation of functions to init model objects for QVariant and
/// to declare them to the QML system.
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2013 Romain Ducher
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

#include "declaremodel.hpp"

#include "configuration/useraccount.hpp"
#include "configuration/userconfiguration.hpp"

#include "geo/coordinates.hpp"
#include "geo/geoboundingbox.hpp"
#include "geo/geocoord.hpp"
#include "geo/geocoordlist.hpp"
#include "geo/geocoordpolygon.hpp"
#include "geo/twitterplace.hpp"

#include "timelines/timeline.hpp"

#include "tweets/hashtag.hpp"
#include "tweets/hashtaglist.hpp"
#include "tweets/indexbounds.hpp"
#include "tweets/media.hpp"
#include "tweets/medialist.hpp"
#include "tweets/mediasize.hpp"
#include "tweets/mediasizes.hpp"
#include "tweets/retweetinfos.hpp"
#include "tweets/tweet.hpp"
#include "tweets/tweetentities.hpp"
#include "tweets/urlentity.hpp"
#include "tweets/urlentitylist.hpp"
#include "tweets/usermention.hpp"
#include "tweets/usermentionlist.hpp"

#include "users/contributor.hpp"
#include "users/contributorlist.hpp"
#include "users/user.hpp"
#include "users/userentities.hpp"
#include "users/userinfos.hpp"

// Init for QVariant
void initModelSystem() {
	// Configuration
	UserAccount::initSystem();
	UserConfiguration::initSystem();

	// Geolocation
	Coordinates::initSystem();
	GeoBoundingBox::initSystem();
	GeoCoord::initSystem();
	GeoCoordList::initSystem();
	GeoCoordPolygon::initSystem();
	TwitterPlace::initSystem();

	// Timelines
	Timeline::initSystem();

	// Tweets
	Hashtag::initSystem();
	HashtagList::initSystem();
	IndexBounds::initSystem();
	Media::initSystem();
	MediaList::initSystem();
	MediaSize::initSystem();
	MediaSizes::initSystem();
	RetweetInfos::initSystem();
	Tweet::initSystem();
	TweetEntities::initSystem();
	URLEntity::initSystem();
	URLEntityList::initSystem();
	UserMention::initSystem();
	UserMentionList::initSystem();

	// Users
	Contributor::initSystem();
	ContributorList::initSystem();
	User::initSystem();
	UserEntities::initSystem();
	UserInfos::initSystem();
}

// Declaring to the QML system
void declareQMLModel() {
	// Geolocation
	UserAccount::declareQML();
	UserConfiguration::declareQML();
	TwitterPlace::declareQML();

	// Timelines
	Timeline::declareQML();

	// Tweets
	Tweet::declareQML();

	// Users
	Contributor::declareQML();
	User::declareQML();
	UserEntities::declareQML();
	UserInfos::declareQML();
}
