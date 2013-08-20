/// @file coreresult.hpp
/// @brief Source file to initialize httpResults.
///
/// Revisions of the file older than r204 are in /trunk/ReynTweets/controls
/// r204 is in /trunk/ReynTweets/logic
/// The file was called launchresult.hpp until r205.
/// @author Romain DUCHER
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

#include "coreresult.hpp"

QMap<int, CoreResult> httpResults = buildHttpResults();

// Initialize httpResults
QMap<int, CoreResult> buildHttpResults() {
	QMap<int, CoreResult> res;

	res.insert(304, NO_MORE_DATA);
	res.insert(400, BAD_REQUEST);
	res.insert(401, AUTHENTICATION_REQUIRED);
	res.insert(403, REFUSED_REQUEST);
	res.insert(404, BAD_REQUEST);
	res.insert(406, INVALID_SEARCH);
	res.insert(410, GONE);
	res.insert(420, RATE_LIMITED);
	res.insert(422, UNPROCESSABLE);
	res.insert(429, RATE_LIMITED);
	res.insert(500, TWITTER_DOWN);
	res.insert(502, TWITTER_DOWN);
	res.insert(503, TWITTER_DOWN);
	res.insert(504, TWITTER_DOWN);

	return res;
}
