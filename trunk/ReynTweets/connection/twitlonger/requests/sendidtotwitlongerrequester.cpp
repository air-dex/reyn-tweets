/// @file sendidtotwitlongerrequester.cpp
/// @brief Implementation of SendIDToTwitLongerRequester
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

#include "sendidtotwitlongerrequester.hpp"

// Constructor
SendIDToTwitLongerRequester::SendIDToTwitLongerRequester(TwitLongerAuthenticator &manager,
														 QString tlMessageID,
														 qlonglong statusID) :
	TwitLongerRequester(LibRT::POST, TwitLongerURL::UPDATE_LONG_TWEET_URL, manager),
	messageID(tlMessageID),
	tweetID(statusID)
{}

// Building parameters map
void SendIDToTwitLongerRequester::buildPOSTParameters() {
	// Application IDs on TwitLonger
	postParameters.insert("application", twitlongerManager.getApplicationName());
	postParameters.insert("api_key", twitlongerManager.getAPIKey());

	// Parameters
	postParameters.insert("message_id", messageID);
	postParameters.insert("twitter_id", QString::number(tweetID));
}

// Getting "post" node which is the unique child of the root node.
QDomElement SendIDToTwitLongerRequester::getInfoElement(QDomElement xmlRoot) {
	// Ensures that it is the root node with its name
	if (xmlRoot.tagName() != "twitlonger") {
		return QDomElement();
	}

	return xmlRoot;
}
