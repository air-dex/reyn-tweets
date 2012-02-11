/// @file tweetcontrol.cpp
/// @brief Implementation of TweetControl
///
/// Revisions of the file older than r204 are in /trunk/ReynTweets/controls
/// r204 is in /trunk/ReynTweets/logic
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

#include "tweetcontrol.hpp"
#include <QtDeclarative>

TweetControl::TweetControl() :
	QObject(),
	reyn(this),
	status()
{}

// Declaring TweetControl to the QML system
void TweetControl::declareQML() {
	qmlRegisterType<TweetControl>("ReynTweetsControls", 0, 1, "TweetControl");
}


/////////////////////////
// Property management //
/////////////////////////

// Reading the tweet property
Tweet TweetControl::getTweet() {
	return status;
}

// Writing the tweet property
void TweetControl::setTweet(Tweet newStatus) {
	status = newStatus;
}


/////////////
// Actions //
/////////////

// Reply to the tweet
void TweetControl::reply() {
	// TODO
}

// Retweet the tweet
void TweetControl::retweet() {
	// TODO
}

// Quote the tweet (old retweet method)
void TweetControl::quote() {
	// TODO
}

// Favorite the tweet
void TweetControl::favorite() {
	// TODO
}

// Unfavorite the tweet
void TweetControl::unfavorite() {
	// TODO
}
