/// @file posttweetprocess.cpp
/// @brief Implementation of PostTweetProcess
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

#include "posttweetprocess.hpp"

// Constructor
PostTweetProcess::PostTweetProcess(QString status,
								   QString replyTostatusID,
								   bool userIDonly,
								   bool withEntities,
								   float lat,
								   float lon,
								   QString place,
								   bool showCoord) :
	SingleTwitterCallProcess(TWEET_POSTED),
	tweet(status),
	trimUser(userIDonly),
	includeEntities(withEntities),
	latitude(lat),
	longitude(lon),
	reversePlace(place),
	displayCoord(showCoord)
{
	// Converting replyTostatusID QString into a qlonglong
	bool convOK = false;

	replyToTweetID = replyTostatusID.toLongLong(&convOK);
	if (!convOK) {
		replyToTweetID = -1;
	}
}

PostTweetProcess::PostTweetProcess(QString status,
								   qlonglong replyTostatusID,
								   bool userIDonly,
								   bool withEntities,
								   float lat,
								   float lon,
								   QString place,
								   bool showCoord) :
	SingleTwitterCallProcess(TWEET_POSTED),
	tweet(status),
	replyToTweetID(replyTostatusID),
	trimUser(userIDonly),
	includeEntities(withEntities),
	latitude(lat),
	longitude(lon),
	reversePlace(place),
	displayCoord(showCoord)
{}

// Calling Twitter
void PostTweetProcess::callTwitter() {
	twitter.updateTweet(tweet,
						replyToTweetID,
						latitude,
						longitude,
						reversePlace,
						displayCoord,
						trimUser,
						includeEntities);
}
