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
#include <QtQml>
#include <QDesktopServices>

// Constructor
TweetControl::TweetControl() :
	GenericControl(),
	status(new Tweet)
{
	connect(this, &TweetControl::tweetChanged,
			this, &TweetControl::commitTweet);
}

// Declaring TweetControl to the QML system
void TweetControl::declareQML() {
	// @uri ReynTweetsComponents
	qmlRegisterType<TweetControl>(ReynTweets::QML_LIBRARY_NAME.toLatin1().constData(),
								  ReynTweets::MAJOR_VERSION, ReynTweets::MINOR_VERSION,
								  "TweetControl");
}

// Method indicating if the tweet mentions the user.
bool TweetControl::isMention() {
	if (!status) {
		return false;
	}

	QString userID = reyn.getUserConfiguration().getUserAccount().getUser().getIDstr();

	UserMentionList mentions = status->getShownTweet()->getEntities().getUserMentions();

	for(UserMentionList::Iterator it = mentions.begin();
		it != mentions.end();
		++it)
	{
		if (it->getIDstr() == userID) {
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

// timeline_type
TimelineHandler::TimelineType TweetControl::getTimelineType() {
	return timelineType;
}

void TweetControl::setTimelineType(TimelineHandler::TimelineType newType) {
	timelineType = newType;
	emit timelineTypeChanged();
}

// shown_tweet
Tweet * TweetControl::getShownTweet() {
	return status->getShownTweet();
}

// tweet
Tweet * TweetControl::getTweet() {
	return status;
}

// tweet_model
QJsonObject TweetControl::getTweetModel() {
	return status->toVariant();
}

void TweetControl::setTweetModel(QJsonObject newStatus) {
	status->reset();
	status->fillWithVariant(newStatus);
	emit tweetChanged();
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

	connect(&reyn, &ReynCore::sendResult,
			this, &TweetControl::refreshEnd);

	processing = true;
	emit showInfoMessage(TweetControl::trUtf8("Refreshing tweet..."));
	reyn.getTweet(status->getIDstr().toLongLong());
}

void TweetControl::refreshEnd(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (ReynTweets::INVALID_END == result.processEnd) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, &ReynCore::sendResult,
			   this, &TweetControl::refreshEnd);

	QVariantMap parsedResults;

	switch (result.processEnd) {
		case ReynTweets::TWEET_RETRIEVED:
			parsedResults = result.results.toMap();
			status->reset();
			status->fillWithVariant(QJsonObject::fromVariantMap(parsedResults));
			emit tweetChanged();
			emit actionEnded(true,
							 TweetControl::trUtf8("Tweet refreshed."),
							 false);
			break;

		case ReynTweets::RESOURCE_NOT_FOUND:
			// Twitter didn't find the tweet so it doesn't exist anymore. Erase it.
			emit destroyTweet(status->toVariant());
			emit actionEnded(false,
							 TweetControl::trUtf8("Twitter did not find the tweet."),
							 false);
			break;

		case ReynTweets::TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;

		// Problems that can be solved trying later
		case ReynTweets::NO_MORE_DATA:
		case ReynTweets::BAD_REQUEST:
		case ReynTweets::REFUSED_REQUEST:
		case ReynTweets::RATE_LIMITED:	// The user reached rates.
		case ReynTweets::TWITTER_DOWN:	// Twitter does not respond.
		case ReynTweets::NETWORK_CALL:
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case ReynTweets::UNKNOWN_PROBLEM:

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
	QString subject = "";
	subject.append(TweetControl::trUtf8("Tweet by"))
			.append(' ')
			.append(getShownTweet()->getUser().getName());

	// Need to encode it on Windows
	#ifdef Q_OS_WIN
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
	#ifdef Q_OS_WIN
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
	if (status->getUser() ==
			reyn.getUserConfiguration().getUserAccount().getUser())
	{
		return;
	}

	connect(&reyn, &ReynCore::sendResult,
			this, &TweetControl::retweetEnd);

	processing = true;

	switch (timelineType) {
		case TimelineHandler::HOME:
			emit showInfoMessage(TweetControl::trUtf8("Retweeting..."));
			reyn.retweet(getShownTweet()->getIDstr().toLongLong());
			break;

		case TimelineHandler::MENTIONS:
			// Do not retweet if the user was retweeted
			if (getShownTweet()->getUser() ==
					reyn.getUserConfiguration().getUserAccount().getUser())
			{
				processing = false;
				disconnect(&reyn, &ReynCore::sendResult,
						   this, &TweetControl::retweetEnd);
				emit actionEnded(false,
								 TweetControl::trUtf8("Cannot retweet this tweet."),
								 false);
			} else {
				emit showInfoMessage(TweetControl::trUtf8("Retweeting..."));
				reyn.retweet(getShownTweet()->getIDstr().toLongLong());
			}
			break;

		default:
			processing = false;
			disconnect(&reyn, &ReynCore::sendResult,
					   this, &TweetControl::retweetEnd);
			emit actionEnded(false,
							 TweetControl::trUtf8("Cannot retweet this tweet"),
							 false);
			break;
	}
}

void TweetControl::retweetEnd(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (ReynTweets::INVALID_END == result.processEnd) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, &ReynCore::sendResult,
			   this, &TweetControl::retweetEnd);

	QVariantMap parsedResults;
	Tweet resultTweet;

	switch (result.processEnd) {
		case ReynTweets::TWEET_RETWEETED:
			parsedResults = result.results.toMap();
			resultTweet.fillWithVariant(QJsonObject::fromVariantMap(parsedResults));
			if (!resultTweet.isRetweet()) {
				// The retweet is not in the timeline and cannot be updated
				emit actionEnded(false,
								 TweetControl::trUtf8("No retweet in the retweeted status."),
								 false);
				break;
			}
			getShownTweet()->reset();
			getShownTweet()->fillWithVariant(resultTweet.getRetweetedStatus()->toVariant());
			getShownTweet()->setRetweeted(true);
			status->setRetweeted(true);
			// NB : status.id do not change.
			emit tweetChanged();
			emit actionEnded(true,
							 TweetControl::trUtf8("Tweet retweeted."),
							 false);
			break;

		case ReynTweets::TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;

		// Problems that can be solved trying later
		case ReynTweets::NO_MORE_DATA:
		case ReynTweets::TWEET_UNDESTROYABLE:
		case ReynTweets::BAD_REQUEST:
		case ReynTweets::REFUSED_REQUEST:
		case ReynTweets::RATE_LIMITED:	// The user reached rates.
		case ReynTweets::TWITTER_DOWN:	// Twitter does not respond.
		case ReynTweets::NETWORK_CALL:
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case ReynTweets::UNKNOWN_PROBLEM:

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

	connect(&reyn, &ReynCore::sendResult,
			this, &TweetControl::favoriteEnd);

	processing = true;

	switch (timelineType) {
		case TimelineHandler::HOME:
		case TimelineHandler::MENTIONS:
			emit showInfoMessage(TweetControl::trUtf8("Favoriting..."));
			reyn.favoriteTweet(getShownTweet()->getIDstr().toLongLong());
			break;

		default:
			processing = false;
			disconnect(&reyn, &ReynCore::sendResult,
					   this, &TweetControl::favoriteEnd);
			emit actionEnded(false,
							 TweetControl::trUtf8("Cannot favorite this tweet."),
							 false);
			break;
	}
}

void TweetControl::favoriteEnd(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (ReynTweets::INVALID_END == result.processEnd) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, &ReynCore::sendResult,
			   this, &TweetControl::favoriteEnd);

	QVariantMap parsedResults;

	switch (result.processEnd) {
		case ReynTweets::FAVORITE_SUCCESSFUL:
			// Don't forget to update the tweet
			parsedResults = result.results.toMap();
			getShownTweet()->reset();
			getShownTweet()->fillWithVariant(QJsonObject::fromVariantMap(parsedResults));
			getShownTweet()->setFavorited(true);
			emit tweetChanged();
			emit actionEnded(true,
							 TweetControl::trUtf8("Tweet favorited."),
							 false);
			break;

		case ReynTweets::TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;

		// Problems that can be solved trying later
		case ReynTweets::BAD_REQUEST:
			if (result.errorMsg.contains("You have already favorited this status")) {
				getShownTweet()->setFavorited(true);
			}
			emit actionEnded(false, result.errorMsg, false);
			break;

		case ReynTweets::NO_MORE_DATA:
		case ReynTweets::REFUSED_REQUEST:
		case ReynTweets::RATE_LIMITED:	// The user reached rates.
		case ReynTweets::TWITTER_DOWN:	// Twitter does not respond.
		case ReynTweets::NETWORK_CALL:
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case ReynTweets::UNKNOWN_PROBLEM:

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

	connect(&reyn, &ReynCore::sendResult,
			this, &TweetControl::unfavoriteEnd);

	processing = true;

	switch (timelineType) {
		case TimelineHandler::HOME:
		case TimelineHandler::MENTIONS:
			emit showInfoMessage(TweetControl::trUtf8("Unfavoriting..."));
			reyn.unfavoriteTweet(getShownTweet()->getIDstr().toLongLong());
			break;

		default:
			processing = false;
			disconnect(&reyn, &ReynCore::sendResult,
					   this, &TweetControl::unfavoriteEnd);
			emit actionEnded(false,
							 TweetControl::trUtf8("Cannot unfavorite this tweet."),
							 false);
			break;
	}
}

void TweetControl::unfavoriteEnd(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (ReynTweets::INVALID_END == result.processEnd) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, &ReynCore::sendResult,
			   this, &TweetControl::unfavoriteEnd);

	QVariantMap parsedResults;

	switch (result.processEnd) {
		case ReynTweets::FAVORITE_SUCCESSFUL:
			// Don't forget to update the tweet
			parsedResults = result.results.toMap();

			getShownTweet()->reset();
			getShownTweet()->fillWithVariant(QJsonObject::fromVariantMap(parsedResults));
			getShownTweet()->setFavorited(false);
			emit tweetChanged();
			emit actionEnded(true,
							 TweetControl::trUtf8("Tweet unfavorited."),
							 false);
			break;

		case ReynTweets::TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;

		// Problems that can be solved trying later
		case ReynTweets::NO_MORE_DATA:
		case ReynTweets::BAD_REQUEST:
		case ReynTweets::REFUSED_REQUEST:
		case ReynTweets::RATE_LIMITED:	// The user reached rates.
		case ReynTweets::TWITTER_DOWN:	// Twitter does not respond.
		case ReynTweets::NETWORK_CALL:
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case ReynTweets::UNKNOWN_PROBLEM:

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

	connect(&reyn, &ReynCore::sendResult,
			this, &TweetControl::deleteEnd);

	processing = true;

	switch (timelineType) {
		case TimelineHandler::HOME:
		case TimelineHandler::MENTIONS:
			emit showInfoMessage(TweetControl::trUtf8("Deleting the tweet..."));
			reyn.deleteTweet(*status);
			break;

		default:
			processing = false;
			disconnect(&reyn, &ReynCore::sendResult,
					   this, &TweetControl::deleteEnd);
			emit actionEnded(false,
							 TweetControl::trUtf8("Cannot delete this tweet."),
							 false);
			break;
	}
}

void TweetControl::deleteEnd(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (ReynTweets::INVALID_END == result.processEnd) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, &ReynCore::sendResult,
			   this, &TweetControl::deleteEnd);

	QVariantMap parsedResults;

	switch (result.processEnd) {
		case ReynTweets::TWEET_DELETED:
			parsedResults = result.results.toMap();

			// Delete the tweet in the timeline ?
			if (parsedResults.value("keep_in_timeline").toBool()) {
				Tweet resultTweet;
				resultTweet.fillWithVariant(QJsonObject::fromVariantMap(parsedResults.value("twitter_result").toMap()));

				if (!resultTweet.isRetweet()) {
					// It's a tweet written by the user and should not be kept
					// in the timeline. This is an error.
					emit actionEnded(false,
									 TweetControl::trUtf8("Retweet expected in Twitter reply."),
									 false);
					return;
				}

				getShownTweet()->reset();
				getShownTweet()->fillWithVariant(resultTweet.getRetweetedStatus()->toVariant());
				status->setRetweeted(false);
				emit tweetChanged();
			} else {
				emit destroyTweet(status->toVariant());
			}

			emit actionEnded(true,
							 TweetControl::trUtf8("Tweet deleted."),
							 false);
			break;

		case ReynTweets::TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;


		// Problems that can be solved trying later
		case ReynTweets::NO_MORE_DATA:
		case ReynTweets::BAD_REQUEST:
		case ReynTweets::REFUSED_REQUEST:
		case ReynTweets::RATE_LIMITED:	// The user reached rates.
		case ReynTweets::TWITTER_DOWN:	// Twitter does not respond.
		case ReynTweets::NETWORK_CALL:
		case ReynTweets::TWEET_UNDESTROYABLE: // Tweet not deleted
			emit actionEnded(false, result.errorMsg, false);
			break;

		// Unknown ends
		case ReynTweets::UNKNOWN_PROBLEM:
		default:
			emit actionEnded(false, result.errorMsg, true);
			break;
	}
}
