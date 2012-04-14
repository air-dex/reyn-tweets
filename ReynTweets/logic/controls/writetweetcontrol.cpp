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
	QObject(),
	reyn(this)
{}

// Declaring WriteTweetControl to the QML system
void WriteTweetControl::declareQML() {
	qmlRegisterType<WriteTweetControl>("ReynTweetsControls",
									   0, 1,
									   "WriteTweetControl");
}


// Posting a tweet without medias
void WriteTweetControl::postTweet(QString tweet, qlonglong inReplyToTweetID) {
	connect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			this, SLOT(postTweetEnded(ProcessWrapper)));

	reyn.postTweet(tweet, inReplyToTweetID);
}


// After posting a tweet
void WriteTweetControl::postTweetEnded(ProcessWrapper res) {
	ProcessResult result = res.accessResult(this);

	// The result was not for the object. Stop the treatment.
	if (INVALID_ISSUE == result.processIssue) {
		return;
	}

	// Disconnect
	disconnect(&reyn, SIGNAL(sendResult(ProcessWrapper)),
			   this, SLOT(postTweetEnded(ProcessWrapper)));

	CoreResult issue = result.processIssue;

	switch (issue) {
		case TWEET_POSTED:
			// Process successful
			emit tweetPosted();
			emit postEnded(true, QString(), false);
			break;

		case AUTHENTICATION_REQUIRED:
			// An authentication is needed. So let's do it!
			emit authenticationNeeded();
			break;

		// Problems that can be solved trying later
		case RATE_LIMITED:	// The user reached rates.
		case TWITTER_DOWN:	// Twitter does not respond.
			emit postEnded(false, result.errorMsg, false);
			break;

		// Problems with configuration file
		case CONFIGURATION_FILE_UNKNOWN:
		case CONFIGURATION_FILE_NOT_OPEN:
		case LOADING_CONFIGURATION_ERROR:

		// Unknown ends
		case UNKNOWN_PROBLEM:

		default:
			emit postEnded(false, result.errorMsg, true);
			break;
	}
}

//void WriteTweetControl::detectURLs(QString text) {
//	// Regex with one of the following characters : space \n \r \t < > [ \ ] ^ { } | `
//	QString regex = "[\\s\\n\\r\\t\\0074\\0076\\0133\\0134\\0135\\0136\\0140\\0173\\0174\\0175\\0176]";
//	QStringList splittedText = text.split(QRegExp(regex), QString::SkipEmptyParts);

//	urls.clear();
//	qDebug("les urls");
//	for (QStringList::Iterator it = splittedText.begin();
//		 it != splittedText.end();
//		 ++it)
//	{
////		QString R_PROTOCOL = "(http(s)?|ftp)";
////		QString R_HOSTNAMEANDPORT = "[\\w-]+(\\.[\\w-]+)*(:(\\d+))?";
////		QString R_RELATIVEPATH = "(/\\w+)*(/\\w+\\.\\w+)?";
////		QString R_QUERY = "(\\?\\w+=\\w+(&(\\w+=\\w+))*)?";
////		QString URL_REGEX = "^" + R_PROTOCOL + "://" + R_HOSTNAMEANDPORT + R_RELATIVEPATH + R_QUERY;

////		QString candidateURL = *it;
////		candidateURL
////		if (u.isValid()) {
////			urls.append(candidateURL);
////			qDebug(u.toString().toUtf8().data());
////			qDebug(u.errorString().toUtf8().append("£££").data());
////		}
//	}


//}
