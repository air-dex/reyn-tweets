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

QMap<int, ReynTweets::CoreResult> httpResults = buildHttpResults();

// Initialize httpResults
QMap<int, ReynTweets::CoreResult> buildHttpResults() {
	QMap<int, ReynTweets::CoreResult> res;

	res.insert(304, ReynTweets::NO_MORE_DATA);
	res.insert(400, ReynTweets::BAD_REQUEST);
	res.insert(401, ReynTweets::AUTHENTICATION_REQUIRED);
	res.insert(403, ReynTweets::REFUSED_REQUEST);
	res.insert(404, ReynTweets::BAD_REQUEST);
	res.insert(406, ReynTweets::INVALID_SEARCH);
	res.insert(410, ReynTweets::GONE);
	res.insert(420, ReynTweets::RATE_LIMITED);
	res.insert(422, ReynTweets::UNPROCESSABLE);
	res.insert(429, ReynTweets::RATE_LIMITED);
	res.insert(500, ReynTweets::TWITTER_DOWN);
	res.insert(502, ReynTweets::TWITTER_DOWN);
	res.insert(503, ReynTweets::TWITTER_DOWN);
	res.insert(504, ReynTweets::TWITTER_DOWN);

	return res;
}
