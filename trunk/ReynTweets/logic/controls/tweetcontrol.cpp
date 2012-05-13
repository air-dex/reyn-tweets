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
	processing(false),
	status(new Tweet)
{
	connect(this, SIGNAL(tweetEnded(bool,QString,bool)),
			this, SLOT(processAgain(bool,QString,bool)));
}

TweetControl::~TweetControl() {
	//delete status;
}

void TweetControl::processAgain(bool, QString, bool) {
	processing = false;
}

// Declaring TweetControl to the QML system
void TweetControl::declareQML() {
	qmlRegisterType<TweetControl>("ReynTweetsControls", 0, 1, "TweetControl");
}

// Method indicating if the tweet mentions the user.
bool TweetControl::isMention() {
	if (!status) {
		return false;
	}

	qlonglong userID = reyn.getConfiguration().getUserAccount().getUser().getID();

	Tweet & shownTweet = status->isRetweet() ?
				*(status->getRetweetedStatus())
			  : *status;

	UserMentionList mentions = shownTweet.getEntities().getUserMentions();

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


/////////////////////////
// Property management //
/////////////////////////

// Reading the shown_tweet property
Tweet * TweetControl::getShownTweet() {
	return status->isRetweet() ? status->getRetweetedStatus() : status;
}

// Reading the tweet property
Tweet * TweetControl::getTweet() {
	return status;
}

// Writing the tweet property
void TweetControl::setTweet(Tweet * newStatus) {
	if (newStatus) {
		status = newStatus;
		emit tweetChanged();
	}
}


/////////////
// Actions //
/////////////

/////////////
// Retweet //
/////////////

void TweetControl::retweet() {
	// No new process if the control has not finished the last one
	if (processing) {
		return;
	}

	// Protection to not attempt to retweet its own tweets.
	if (status->getAuthor()->getID() ==
			reyn.getConfiguration().getUserAccount().getUser().getID())
	{
		return;
	}

	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(retweetEnd(ProcessWrapper)));

	processing = true;
	reyn.retweet(getShownTweet()->getID());
}

void TweetControl::retweetEnd(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		processing = false;
		return;
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(retweetEnd(ProcessWrapper)));

	CoreResult issue = result.processIssue;
	QVariantMap parsedResults;
	Tweet resultTweet;

	switch (issue) {
		case TWEET_RETWEETED:
			parsedResults = result.results.toMap();
			resultTweet.fillWithVariant(parsedResults);
			if (!resultTweet.isRetweet()) {
				// The retweet is not in the timeline and cannot be updated
				emit tweetEnded(false,
								TweetControl::trUtf8("No retweet in the retweeted status"),
								false);
				break;
			}
			getShownTweet()->reset();
			getShownTweet()->fillWithVariant(resultTweet.getRetweetedStatusVariant());
			status->setRetweeted(true);
			emit tweetChanged();
			emit updateTimeline(QVariant(status->toVariant()));
            emit tweetEnded(true, TweetControl::trUtf8("Tweet retweeted"), false);
			break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;

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

/////////////////////////////
// Favorite and unfavorite //
/////////////////////////////

void TweetControl::favorite() {
	// No new process if the control has not finished the last one
	if (processing) {
		return;
	}

	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(favoriteEnd(ProcessWrapper)));

	processing = true;
	reyn.favoriteTweet(getShownTweet()->getID());
}

void TweetControl::favoriteEnd(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		processing = false;
		return;
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(favoriteEnd(ProcessWrapper)));

	CoreResult issue = result.processIssue;
	QVariantMap parsedResults;

	switch (issue) {
		case FAVORITE_SUCCESSFUL:
			// Don't forget to update the tweet
			parsedResults = result.results.toMap();
			getShownTweet()->reset();
			getShownTweet()->fillWithVariant(parsedResults);
			getShownTweet()->setFavorited(true);
			status->setFavorited(true);
			emit tweetChanged();
            emit updateTimeline(QVariant(status->toVariant()));
            emit tweetEnded(true, TweetControl::trUtf8("Tweet favorited"), false);
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

void TweetControl::unfavorite() {
	// No new process if the control has not finished the last one
	if (processing) {
		return;
	}

	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(unfavoriteEnd(ProcessWrapper)));

	processing = true;
	reyn.unfavoriteTweet(getShownTweet()->getID());
}

void TweetControl::unfavoriteEnd(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		processing = false;
		return;
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(unfavoriteEnd(ProcessWrapper)));

	CoreResult issue = result.processIssue;
	QVariantMap parsedResults;
	TweetEntities entities;

	switch (issue) {
		case FAVORITE_SUCCESSFUL:
			// Don't forget to update the tweet
			parsedResults = result.results.toMap();

			// Saving tweet entities because Twitter API doesn't return them here !
			entities = getShownTweet()->getEntities();

			getShownTweet()->reset();
			getShownTweet()->fillWithVariant(parsedResults);
			getShownTweet()->setEntities(entities);
			getShownTweet()->setFavorited(false);
			status->setFavorited(false);
			emit tweetChanged();
			emit updateTimeline(QVariant(status->toVariant()));
            emit tweetEnded(true, TweetControl::trUtf8("Tweet unfavorited"), false);
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

//////////////////////
// Deleting a tweet //
//////////////////////

void TweetControl::deleteTweet() {
	// No new process if the control has not finished the last one
	if (processing) {
		return;
	}

	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(deleteEnd(ProcessWrapper)));

	processing = true;
	reyn.deleteTweet(*status);
}

void TweetControl::deleteEnd(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		processing = false;
		return;
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(deleteEnd(ProcessWrapper)));

	CoreResult issue = result.processIssue;
	QVariantMap parsedResults;

	switch (issue) {
		case TWEET_DELETED:
			parsedResults = result.results.toMap();

			// Delete the tweet in the timeline ?
			if (parsedResults.value("keep_in_timeline").toBool()) {
				Tweet resultTweet;
				resultTweet.fillWithVariant(parsedResults.value("twitter_result").toMap());

				if (!resultTweet.isRetweet()) {
					// It's a tweet written by the user and should not be kept
					// in the timeline. This is an error.
					emit tweetEnded(false,
                                    TweetControl::trUtf8("Retweet expected in Twitter reply."),
									false);
					return;
				}

				getShownTweet()->reset();
				getShownTweet()->fillWithVariant(resultTweet.getRetweetedStatusVariant());
				status->setRetweeted(false);
				emit tweetChanged();
				emit updateTimeline(QVariant(status->toVariant()));
			} else {
				emit destroyTweet();
			}

            emit tweetEnded(true, TweetControl::trUtf8("Tweet deleted"), false);
			break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;


		// Problems that can be solved trying later
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
		case NETWORK_CALL:
		case TWEET_UNDESTROYABLE: // Tweet not deleted
			emit tweetEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case UNKNOWN_PROBLEM:
		default:
			emit tweetEnded(false, result.errorMsg, true);
			break;
	}

	processing = false;
}
