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
#include <QDesktopServices>

// Constructor
TweetControl::TweetControl() :
	GenericControl(),
	status(new Tweet)
{
	connect(this, SIGNAL(tweetChanged()),
			this, SLOT(commitTweet()));
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

	qlonglong userID = reyn.getUserConfiguration().getUserAccount().getUser().getID();

	UserMentionList mentions = status->getShownTweet()->getEntities().getUserMentions();

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

// Updating the timeline
void TweetControl::commitTweet() {
	emit updateTimeline(status->toVariant());
}

/////////////////////////
// Property management //
/////////////////////////

// Reading the property timeline_type
Timeline::TimelineType TweetControl::getTimelineType() {
	return timelineType;
}

// Writing the property timeline_type
void TweetControl::setTimelineType(Timeline::TimelineType newType) {
	timelineType = newType;
	emit timelineTypeChanged();
}

// Reading the shown_tweet property
Tweet * TweetControl::getShownTweet() {
	return status->getShownTweet();
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
// Refresh //
/////////////

void TweetControl::refresh() {
	// No new process if the control has not finished the last one
	if (processing) {
		return;
	}

	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(refreshEnd(ProcessWrapper)));

	processing = true;
	emit showInfoMessage(TweetControl::trUtf8("Refreshing tweet..."));
	reyn.getTweet(status->getID());
}

void TweetControl::refreshEnd(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(refreshEnd(ProcessWrapper)));

	CoreResult issue = result.processIssue;
	QVariantMap parsedResults;

	switch (issue) {
		case TWEET_RETRIEVED:
			parsedResults = result.results.toMap();
			status->reset();
			status->fillWithVariant(parsedResults);
			emit tweetChanged();
			emit actionEnded(true, TweetControl::trUtf8("Tweet refreshed"), false);
			break;

		case RESOURCE_NOT_FOUND:
			// Twitter didn't find the tweet so it doesn't exist anymore. Erase it.
			emit destroyTweet();
			emit actionEnded(false,
							 TweetControl::trUtf8("Twitter did not find the tweet."),
							 false);
			break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;

		// Problems that can be solved trying later
		case BAD_REQUEST:
		case REFUSED_REQUEST:
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
		case NETWORK_CALL:
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case UNKNOWN_PROBLEM:

		default:
			emit actionEnded(false, result.errorMsg, true);
			break;
	}
}


/////////////
// Sharing //
/////////////

void TweetControl::shareByMail() {
	// Writing what to send by mail

	QString mailURL = "mailto:?";

	// Writing the subject
	QString subject = TweetControl::trUtf8("Tweet by ");
	subject.append(getShownTweet()->getAuthor()->getName());

	// Need to encode it on Windows
	#ifdef Q_OS_WIN32
		subject = QUrl::toPercentEncoding(subject);
	#endif

	mailURL.append("subject=").append(subject).append('&');

	// Writing the body
	QString body = getShownTweet()->getTweetURL().toString();
	body.append(" \n\n");
	body.append(TweetControl::trUtf8("If you cannot open this url by clicking on it, copy the link and paste it in the address bar of your web browser."));
	body.append(" \n\n");
	body.append(TweetControl::trUtf8("Sent via Reyn Tweets"));
	body.append(" ( http://code.google.com/p/reyn-tweets/ ).");

	// Need to encode it on Windows
	#ifdef Q_OS_WIN32
		body = QUrl::toPercentEncoding(body);
	#endif

	mailURL.append("body=").append(body);

	// Send it
	QDesktopServices::openUrl(mailURL);
}


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
			reyn.getUserConfiguration().getUserAccount().getUser().getID())
	{
		return;
	}

	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(retweetEnd(ProcessWrapper)));

	processing = true;

	switch (timelineType) {
		case Timeline::HOME:
			emit showInfoMessage(TweetControl::trUtf8("Retweeting..."));
			reyn.retweet(getShownTweet()->getID());
			break;

		case Timeline::MENTIONS:
			// Do not retweet if the user was retweeted
			if (getShownTweet()->getID() ==
					reyn.getUserConfiguration().getUserAccount().getUser().getID())
			{
				processing = false;
				disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
						   this, SLOT(retweetEnd(ProcessWrapper)));
				emit actionEnded(false,
								 TweetControl::trUtf8("Cannot retweet this tweet"),
								 false);
			} else {
				emit showInfoMessage(TweetControl::trUtf8("Retweeting..."));
				reyn.retweet(getShownTweet()->getID());
			}
			break;

		default:
			processing = false;
			disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
					   this, SLOT(retweetEnd(ProcessWrapper)));
			emit actionEnded(false,
							 TweetControl::trUtf8("Cannot retweet this tweet"),
							 false);
			break;
	}
}

void TweetControl::retweetEnd(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return invalidEnd();
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
				emit actionEnded(false,
								 TweetControl::trUtf8("No retweet in the retweeted status"),
								 false);
				break;
			}
			getShownTweet()->reset();
			getShownTweet()->fillWithVariant(resultTweet.getRetweetedStatusVariant());
			getShownTweet()->setRetweeted(true);
			status->setRetweeted(true);
			// NB : status.id do not change.
			emit tweetChanged();
			emit actionEnded(true, TweetControl::trUtf8("Tweet retweeted"), false);
			break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;

		// Problems that can be solved trying later
		case TWEET_UNDESTROYABLE:
		case BAD_REQUEST:
		case REFUSED_REQUEST:
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
		case NETWORK_CALL:
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case UNKNOWN_PROBLEM:

		default:
			emit actionEnded(false, result.errorMsg, true);
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

	switch (timelineType) {
		case Timeline::HOME:
		case Timeline::MENTIONS:
			emit showInfoMessage(TweetControl::trUtf8("Favoriting..."));
			reyn.favoriteTweet(getShownTweet()->getID());
			break;

		default:
			processing = false;
			disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
					   this, SLOT(favoriteEnd(ProcessWrapper)));
			emit actionEnded(false,
							 TweetControl::trUtf8("Cannot favorite this tweet"),
							 false);
			break;
	}
}

void TweetControl::favoriteEnd(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return invalidEnd();
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
			emit tweetChanged();
			emit actionEnded(true, TweetControl::trUtf8("Tweet favorited"), false);
			break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;

		// Problems that can be solved trying later
		case BAD_REQUEST:
			if (result.errorMsg.contains("You have already favorited this status")) {
				getShownTweet()->setFavorited(true);
			}
			emit actionEnded(false, result.errorMsg, false);
			break;

		case REFUSED_REQUEST:
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
		case NETWORK_CALL:
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case UNKNOWN_PROBLEM:

		default:
			emit actionEnded(false, result.errorMsg, true);
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

	switch (timelineType) {
		case Timeline::HOME:
		case Timeline::MENTIONS:
			emit showInfoMessage(TweetControl::trUtf8("Unfavoriting..."));
			reyn.unfavoriteTweet(getShownTweet()->getID());
			break;

		default:
			processing = false;
			disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
					   this, SLOT(unfavoriteEnd(ProcessWrapper)));
			emit actionEnded(false,
							 TweetControl::trUtf8("Cannot unfavorite this tweet"),
							 false);
			break;
	}
}

void TweetControl::unfavoriteEnd(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return invalidEnd();
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
			emit tweetChanged();
			emit actionEnded(true, TweetControl::trUtf8("Tweet unfavorited"), false);
			break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;

		// Problems that can be solved trying later
		case BAD_REQUEST:
		case REFUSED_REQUEST:
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
		case NETWORK_CALL:
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case UNKNOWN_PROBLEM:

		default:
			emit actionEnded(false, result.errorMsg, true);
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

	switch (timelineType) {
		case Timeline::HOME:
		case Timeline::MENTIONS:
			emit showInfoMessage(TweetControl::trUtf8("Deleting the tweet..."));
			reyn.deleteTweet(*status);
			break;

		default:
			processing = false;
			disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
					   this, SLOT(deleteEnd(ProcessWrapper)));
			emit actionEnded(false,
							 TweetControl::trUtf8("Cannot delete this tweet"),
							 false);
			break;
	}
}

void TweetControl::deleteEnd(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return invalidEnd();
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
					emit actionEnded(false,
									TweetControl::trUtf8("Retweet expected in Twitter reply."),
									false);
					return;
				}

				getShownTweet()->reset();
				getShownTweet()->fillWithVariant(resultTweet.getRetweetedStatusVariant());
				status->setRetweeted(false);
				emit tweetChanged();
			} else {
				emit destroyTweet();
			}

			emit actionEnded(true, TweetControl::trUtf8("Tweet deleted"), false);
			break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;


		// Problems that can be solved trying later
		case BAD_REQUEST:
		case REFUSED_REQUEST:
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
		case NETWORK_CALL:
		case TWEET_UNDESTROYABLE: // Tweet not deleted
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case UNKNOWN_PROBLEM:
		default:
			emit actionEnded(false, result.errorMsg, true);
			break;
	}
}
