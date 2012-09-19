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

#include <QtDeclarative>
#include <QRegExp>
#include <QUrl>
#include "writetweetcontrol.hpp"

// Constructor
WriteTweetControl::WriteTweetControl() :
	GenericControl()
{}

// Declaring WriteTweetControl to the QML system
void WriteTweetControl::declareQML() {
	qmlRegisterType<WriteTweetControl>("ReynTweetsControls",
									   0, 1,
									   "WriteTweetControl");
}


////////////////////////////
// Posting without medias //
////////////////////////////

// Posting a tweet without medias
void WriteTweetControl::postTweet(QString tweet, QString inReplyToTweetID) {
	if (processing) {
		return;
	}

	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(postTweetEnded(ProcessWrapper)));

	processing = true;
	emit showInfoMessage(WriteTweetControl::trUtf8("Posting tweet..."));
	reyn.postTweet(tweet, inReplyToTweetID);
}


// After posting a tweet
void WriteTweetControl::postTweetEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(postTweetEnded(ProcessWrapper)));

	CoreResult issue = result.processIssue;

	switch (issue) {
		case TWEET_POSTED:
			// Process successful
			emit tweetPosted(result.results);
			emit actionEnded(true,
							 WriteTweetControl::trUtf8("Tweet sent successfully"),
							 false);
			break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;

		// Problems that can be solved trying later
		case NO_MORE_DATA:
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


////////////////////////////
// Posting via TwitLonger //
////////////////////////////

// Posting a tweet via TwitLonger
void WriteTweetControl::postViaTwitLonger(QString tweet,
										  QString inReplyToTweetID,
										  QString inReplyToUser)
{
	if (processing) {
		return;
	}

	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(postViaTwitLongerEnded(ProcessWrapper)));

	processing = true;
	emit showInfoMessage(WriteTweetControl::trUtf8("Posting tweet..."));
	reyn.postTweetViaTwitLonger(tweet, inReplyToTweetID, inReplyToUser);
}


// After posting a tweet
void WriteTweetControl::postViaTwitLongerEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return invalidEnd();
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(postViaTwitLongerEnded(ProcessWrapper)));

	CoreResult issue = result.processIssue;
	QString successMessage = WriteTweetControl::trUtf8("Tweet sent successfully");

	switch (issue) {
		// Process successful
		case MESSAGE_NOT_UPDATED:
			// One more thing specific to MESSAGE_NOT_UPDATED before the successful end.
			successMessage.append(WriteTweetControl::trUtf8(" but the message is not updated on TwitLonger."));

		case TWEET_POSTED:
			emit tweetPosted(result.results);
			emit actionEnded(true,
							 successMessage,
							 false);
			break;

		case TOKENS_NOT_AUTHORIZED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;

		// Problems that can be solved trying later
		case NO_MORE_DATA:
		case UNSHORTENABLE_MESSAGE:		// Problems with TwitLonger
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
