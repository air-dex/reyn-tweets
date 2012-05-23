/// @file twitlongercalls.cpp
/// @brief Implementation of TwitLongerCalls
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

#include "twitlongercalls.hpp"
#include "../requests/twitlongerrequests.hpp"

// Static member
TwitLongerManager TwitLongerCalls::twitlongerManager = TwitLongerManager();

// Constructor
TwitLongerCalls::TwitLongerCalls(QObject * requester) :
	GenericCalls(requester)
{}

// Posting the long message on TwitLonger
void TwitLongerCalls::postOnTwitLonger(QString username,
									   QString message,
									   qlonglong replyToTweetID,
									   QString replyToUser)
{
	PostToTwitLongerRequester * requester = new PostToTwitLongerRequester(twitlongerManager,
																		  message,
																		  username,
																		  replyToTweetID,
																		  replyToUser);
	executeRequest(requester);
}

// Updating the informations on TwitLonger
void TwitLongerCalls::updateLongTweet(QString messageID, qlonglong tweetID) {
	SendIDToTwitLongerRequester * requester = new SendIDToTwitLongerRequester(twitlongerManager,
																			  messageID,
																			  tweetID);
	executeRequest(requester);
}
