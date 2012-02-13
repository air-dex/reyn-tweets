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

// Reply

void TweetControl::reply() {
	// TODO
}

void TweetControl::replyEnd(ProcessWrapper res) {
	//
}


// Retweet

void TweetControl::retweet() {
	// TODO
}

void TweetControl::retweetEnd(ProcessWrapper res) {
	//
}


// Quote

void TweetControl::quote() {
	// TODO
}

void TweetControl::quoteEnd(ProcessWrapper res) {
	//
}


// Favorite

void TweetControl::favorite() {
	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(favoriteEnd(ProcessWrapper)));
	reyn.favoriteTweet(status.getID());
}

void TweetControl::favoriteEnd(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return;
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(favoriteEnd(ProcessWrapper)));

	CoreResult issue = result.processIssue;

	// TODO
	switch (issue) {
		case FAVORITE_SUCCESSFUL:
			status.setFavorited(true);
			break;

		case TWITTER_DOWN:
		case RATE_LIMITED:
		case NETWORK_CALL:
		case TOKENS_NOT_AUTHORIZED:
		case PARSE_ERROR:
		case UNKNOWN_PROBLEM:
		default:
			break;
	}
}


// Unfavorite

void TweetControl::unfavorite() {
	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(unfavoriteEnd(ProcessWrapper)));
	reyn.unfavoriteTweet(status.getID());
}

void TweetControl::unfavoriteEnd(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return;
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(unfavoriteEnd(ProcessWrapper)));

	CoreResult issue = result.processIssue;

	// TODO
	switch (issue) {
		case FAVORITE_SUCCESSFUL:
			status.setFavorited(false);
			break;

		case TWITTER_DOWN:
		case RATE_LIMITED:
		case NETWORK_CALL:
		case TOKENS_NOT_AUTHORIZED:
		case PARSE_ERROR:
		case UNKNOWN_PROBLEM:
		default:
			break;
	}
}
