/// @file posttweetrequester.cpp
/// @brief Implementation of PostTweetRequester
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

#include "posttweetrequester.hpp"
#include "../../../common/utils/connectionutils.hpp"

// Constructor
PostTweetRequester::PostTweetRequester(TwitterAuthenticator & authManager,
									   QString status,
									   qlonglong replyTostatusID,
									   float lat,
									   float lon,
									   QString place,
									   bool showCoord,
									   bool userIDonly) :
	TwitterRequester(Network::POST, TwitterURL::UPDATE_TWEET_URL, authManager),
	tweet(status),
	replyToTweetID(replyTostatusID),
	trimUser(userIDonly),
	longitude(lon),
	latitude(lat),
	reversePlace(place),
	displayCoord(showCoord)
{}

// Building getParameters
void PostTweetRequester::buildPOSTParameters() {
	postParameters.insert("status", tweet);

	if (replyToTweetID != -1) {
		postParameters.insert("in_reply_to_status_id", QString::number(replyToTweetID));
	}

	if (latitude >= -90 && latitude <= 90) {
		postParameters.insert("lat", QString::number(latitude));
	}

	if (longitude >= -180 && longitude <= 180) {
		postParameters.insert("long", QString::number(longitude));
	}

	if (!reversePlace.isEmpty()) {
		postParameters.insert("place_id", reversePlace);
	}

	postParameters.insert("display_coordinates", boolInString(displayCoord));
	postParameters.insert("trim_user", boolInString(trimUser));
}
