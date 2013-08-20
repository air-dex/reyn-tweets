/// @file writetweetcontrol.cpp
/// @brief Implementation of WriteTweetControl
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

#include <QtQml>
#include <QUrl>
#include "writetweetcontrol.hpp"

// Constructor
WriteTweetControl::WriteTweetControl() :
	GenericControl(),
	futureStatus()
{}

// Declaring WriteTweetControl to the QML system
void WriteTweetControl::declareQML() {
	qmlRegisterType<WriteTweetControl>("ReynTweetsControls",
									   0, 2,
									   "WriteTweetControl");
}

// Tweet to update (future_tweet)
Tweet * WriteTweetControl::getFutureTweet() {
	return &futureStatus;
}


////////////////////////////
// Posting without medias //
////////////////////////////

// Posting a tweet without medias
void WriteTweetControl::postTweet() {
	if (processing) {
		return;
	}

	connect(&reyn, &ReynCore::sendResult,
			this, &WriteTweetControl::postTweetEnded);

	processing = true;
	emit showInfoMessage(WriteTweetControl::trUtf8("Posting tweet..."));
	reyn.postTweet(futureStatus);
}


// After posting a tweet
void WriteTweetControl::postTweetEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (ReynTweets::INVALID_END == result.processEnd) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, &ReynCore::sendResult,
			   this, &WriteTweetControl::postTweetEnded);

	switch (result.processEnd) {
		case ReynTweets::TWEET_POSTED:
			// Process successful
			emit tweetPosted(result.results);
			emit actionEnded(true,
							 WriteTweetControl::trUtf8("Tweet sent successfully."),
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


////////////////////////////
// Posting via TwitLonger //
////////////////////////////

// Posting a tweet via TwitLonger
void WriteTweetControl::postViaTwitLonger() {
	if (processing) {
		return;
	}

	connect(&reyn, &ReynCore::sendResult,
			this, &WriteTweetControl::postViaTwitLongerEnded);

	processing = true;
	emit showInfoMessage(WriteTweetControl::trUtf8("Posting tweet..."));
	reyn.postTweetViaTwitLonger(futureStatus);
}


// After posting a tweet
void WriteTweetControl::postViaTwitLongerEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (ReynTweets::INVALID_END == result.processEnd) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, &ReynCore::sendResult,
			   this, &WriteTweetControl::postViaTwitLongerEnded);

	QString successMessage = WriteTweetControl::trUtf8("Tweet sent successfully");

	switch (result.processEnd) {
		// Process successful
		case ReynTweets::MESSAGE_NOT_UPDATED:
			// One more thing specific to ReynTweets::MESSAGE_NOT_UPDATED before the successful end.
			successMessage.append(' ')
					.append(WriteTweetControl::trUtf8("but the message is not updated on TwitLonger."));

		case ReynTweets::TWEET_POSTED:
			emit tweetPosted(result.results);
			emit actionEnded(true,
							 successMessage,
							 false);
			break;

		case ReynTweets::TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;

		// Problems that can be solved trying later
		case ReynTweets::NO_MORE_DATA:
		case ReynTweets::UNSHORTENABLE_MESSAGE:		// Problems with TwitLonger
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
