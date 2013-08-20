/// @file posttotwitlongerrequester.cpp
/// @brief Implementation of PostToTwitLongerRequester
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

#include "posttotwitlongerrequester.hpp"

// Constructor
PostToTwitLongerRequester::PostToTwitLongerRequester(TwitLongerManager &tlmanager,
													 QString longTweet,
													 QString userScreenName,
													 qlonglong replyToStatusID,
													 QString replyToUserScreenName) :
	TwitLongerRequester(Network::POST, TwitLongerURL::POST_LONG_TWEET_URL, tlmanager),
	message(longTweet),
	username(userScreenName),
	replyToTweetID(replyToStatusID),
	replyToUser(replyToUserScreenName)
{}

// Building POST parameters
void PostToTwitLongerRequester::buildPOSTParameters() {
	// Application IDs on TwitLonger
	postParameters.insert("application", twitlongerManager.getApplicationName());
	postParameters.insert("api_key", twitlongerManager.getAPIKey());

	// User and its long message
	postParameters.insert("username", username);

	if (message.length() > 140) {
		postParameters.insert("message", message);
	} else {
		// End the request to TwitLonger to send the post classicly.
		requestResult.resultType = Network::NO_REQUEST_ERROR;
		requestResult.parsedResult = QVariant("too_short");
		emit requestDone();
	}

	// Optional reply
	if (replyToTweetID != -1) {
		postParameters.insert("in_reply", QString::number(replyToTweetID));
	}

	if (!replyToUser.isEmpty()) {
		postParameters.insert("in_reply_user", replyToUser);
	}
}

// Getting "post" node which is the unique child of the root node.
QDomElement PostToTwitLongerRequester::getInfoElement(QDomElement xmlRoot) {
	// Ensures that it is the root node with its name
	if (xmlRoot.tagName() != "twitlonger") {
		return QDomElement();
	}

	QDomElement theChild = xmlRoot.firstChildElement();
	QDomElement res;

	if (theChild.tagName() == "post") {
		res = theChild;
	} else if (theChild.tagName() == "error") {
		res = xmlRoot;
	}

	return res;
}
