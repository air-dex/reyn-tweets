/// @file retweetsbymerequester.cpp
/// @brief Implementation of RetweetsByMeRequester
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

#include "retweetsbymerequester.hpp"
#include "../../../tools/utils.hpp"

// Constructor
RetweetsByMeRequester::RetweetsByMeRequester(OAuthManager &authManager,
											 qlonglong oldestID,
											 qlonglong youngestID,
											 int nbRetweets,
											 bool userIDonly,
											 bool withEntities) :
	TwitterRequester(GET,
					 TwitterURL::RETWEETED_BY_ME_TIMELINE_URL,
					 authManager),
	sinceID(oldestID),
	maxID(youngestID),
	count(nbRetweets),
	trimUser(userIDonly),
	includeEntities(withEntities)
{}

// Building getParameters
void RetweetsByMeRequester::buildGETParameters() {
	if (sinceID > -1) {
		getParameters.insert("since_id", QString::number(sinceID));
	}

	if (maxID > -1) {
		getParameters.insert("max_id", QString::number(maxID));
	}

	if (count != 20) {
		getParameters.insert("count", QString::number(count));
	}

	getParameters.insert("trim_user", boolInString(trimUser));
	getParameters.insert("include_entities", boolInString(includeEntities));
}
