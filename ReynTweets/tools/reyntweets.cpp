/// @file reyntweets.cpp
/// @brief Implementation of the ReynTweets namespace
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

#include "reyntweets.hpp"

#include <QApplication>
#include <QLocale>
#include "../model/reyntweetsentities.hpp"
#include "../logic/controls/controls.hpp"

////////////////////////////
// Translation management //
////////////////////////////

// Translation manager
QTranslator ReynTweets::TRANSLATION_HANDLER;

// loading the translation
void ReynTweets::loadTranslation() {
	// Defalult idiom : local idiom
	QString locale = QLocale::system().name().section('_', 0, 0);

	// Program in French
//	QString locale = "fr";

	// Loading translation files
	ReynTweets::TRANSLATION_HANDLER.load(QString("reyntweets_") + locale);

	qApp->installTranslator(&ReynTweets::TRANSLATION_HANDLER);
}


/////////////////////
// main() handling //
/////////////////////

// Init for QVariant
void ReynTweets::initSystem() {
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

	// No controls for the moment
}

// Declaring to the QML system
void ReynTweets::declareQML() {
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

	// Controls
	AllowControl::declareQML();
	LaunchingControl::declareQML();
	LoginControl::declareQML();
	ReynControl::declareQML();
	SettingsControl::declareQML();
	TimelineControl::declareQML();
	TweetControl::declareQML();
	WriteTweetControl::declareQML();
}

// Treatments after the execution
void ReynTweets::afterReynTime() {
	// Frees AppConfiguration::REYN_TWEETS_CONFIGURATION pointer
	AppConfiguration::unleashReyn();
}
