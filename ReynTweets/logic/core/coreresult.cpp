/// @file coreresult.cpp
/// @brief Implementation of utilities around ReynTweets::CoreResult.
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

QMap<LibRT::HTTPCode, ReynTweets::CoreResult> ReynTweets::httpResults = ReynTweets::buildHttpResults();

// Initialize httpResults
QMap<LibRT::HTTPCode, ReynTweets::CoreResult> ReynTweets::buildHttpResults() {
	QMap<LibRT::HTTPCode, ReynTweets::CoreResult> res;

	res.insert(LibRT::NOT_MODIFIED, ReynTweets::NO_MORE_DATA);
	res.insert(LibRT::BAD_REQUEST, ReynTweets::BAD_REQUEST);
	res.insert(LibRT::UNAUTHORIZED, ReynTweets::AUTHENTICATION_REQUIRED);
	res.insert(LibRT::FORBIDDEN, ReynTweets::REFUSED_REQUEST);
	res.insert(LibRT::NOT_FOUND, ReynTweets::BAD_REQUEST);
	res.insert(LibRT::NOT_ACCEPTABLE, ReynTweets::INVALID_SEARCH);
	res.insert(LibRT::GONE, ReynTweets::GONE);
	res.insert(LibRT::ENHANCE_YOUR_CALM, ReynTweets::RATE_LIMITED);
	res.insert(LibRT::UNPROCESSABLLE_ENTITY, ReynTweets::UNPROCESSABLE);
	res.insert(LibRT::TOO_MANY_REQUESTS, ReynTweets::RATE_LIMITED);
	res.insert(LibRT::INTERNAL_SERVER_ERROR, ReynTweets::TWITTER_DOWN);
	res.insert(LibRT::BAD_GATEWAY, ReynTweets::TWITTER_DOWN);
	res.insert(LibRT::SERVICE_UNAVAILABLE, ReynTweets::TWITTER_DOWN);
	res.insert(LibRT::GATEWAY_TIMEOUT, ReynTweets::TWITTER_DOWN);

	return res;
}

// CoreResult corresponding to a given HTTP code
ReynTweets::CoreResult ReynTweets::getCoreResultFromCode(LibRT::HTTPCode code,
														 ReynTweets::CoreResult okEnd)
{
	if (ReynTweets::httpResults.keys().contains(code)) {
		// The code is well known. Give it.
		return ReynTweets::httpResults.value(code);
	} else if (code == LibRT::OK) {
		// httpResults hasn't got a dedicate value for 200. Give it one !
		return okEnd;
	} else {
		// Unknown code => unknown problem
		return ReynTweets::UNKNOWN_PROBLEM;
	}
}
