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
	status(0)
{}

// Declaring TweetControl to the QML system
void TweetControl::declareQML() {
	qmlRegisterType<TweetControl>("ReynTweetsControls", 0, 1, "TweetControl");
}


/////////////////////////
// Property management //
/////////////////////////

// Reading the tweet property
Tweet * TweetControl::getTweet() {
	return status;
}

// Writing the tweet property
void TweetControl::setTweet(Tweet * newStatus) {
	status = newStatus;
	emit tweetChanged();
}


/////////////
// Actions //
/////////////

// Reply

void TweetControl::reply() {
	// TODO
}

void TweetControl::replyEnd(ProcessWrapper res) {
	// TODO
}


// Retweet

void TweetControl::retweet() {
	// TODO
}

void TweetControl::retweetEnd(ProcessWrapper res) {
	// TODO
}


// Quote

void TweetControl::quote() {
	// TODO
}

void TweetControl::quoteEnd(ProcessWrapper res) {
	// TODO
}

// Method indicating if the tweet mentions the user.
bool TweetControl::isMention() {
	if (!status) {
		return false;
	}

	qlonglong userID = reyn.getConfiguration().getUserAccount().getUser().getID();

	Tweet * shownTweet = status->isRetweet() ?
				status->getRetweetedStatus()
			  : status;

	UserMentionList mentions = shownTweet->getEntities().getUserMentions();

	for(UserMentionList::Iterator it = mentions.begin();
		it != mentions.end();
		++it)
	{
		if (it->getID() == userID) {
			return true;
		}
	}

	return false;
}



// Favorite

void TweetControl::favorite() {
	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(favoriteEnd(ProcessWrapper)));
	reyn.favoriteTweet(status->getID());
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

	switch (issue) {
		case FAVORITE_SUCCESSFUL:
			status->setFavorited(true);
			emit tweetChanged();
			break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			return;

		// Problems that can be solved trying later
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
		case NETWORK_CALL:
			emit tweetEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case UNKNOWN_PROBLEM:

		default:
			emit tweetEnded(false, result.errorMsg, true);
			break;
	}
}


// Unfavorite

void TweetControl::unfavorite() {
	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(unfavoriteEnd(ProcessWrapper)));
	reyn.unfavoriteTweet(status->getID());
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

	switch (issue) {
		case FAVORITE_SUCCESSFUL:
			status->setFavorited(false);
			emit tweetChanged();
			break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			return;

		// Problems that can be solved trying later
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
		case NETWORK_CALL:
			emit tweetEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case UNKNOWN_PROBLEM:

		default:
			emit tweetEnded(false, result.errorMsg, true);
			break;
	}
}
