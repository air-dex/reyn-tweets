/// @file refreshtimelineprocess.cpp
/// @brief Implementation of RefreshTimelineProcess
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2013 Romain Ducher
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

#include "refreshtimelineprocess.hpp"
#include "processutils.hpp"

// Constructor
RefreshTimelineProcess::RefreshTimelineProcess(Tweet oldestTweet) :
	GenericProcess(),
	twitter(this),
	latestTweet(oldestTweet),
	newerTweets(),
	oldestNewTweet(),
	finalEnd(ReynTweets::INVALID_END)
{}

// Starting the process
void RefreshTimelineProcess::startProcess() {
	loadFirstTweets();
}


/////////////////
// The process //
/////////////////

/////////////////////////////////////////////
// Step 1 : loading the most recent tweets //
/////////////////////////////////////////////

// Loading
void RefreshTimelineProcess::loadFirstTweets() {
	connect(&twitter, &ReynTwitterCalls::sendResult,
			this, &RefreshTimelineProcess::loadFirstTweetsEnded);

	this->retrievingFirstTweets();
}

// After loading
void RefreshTimelineProcess::loadFirstTweetsEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);

	if (result.resultType == LibRT::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, &ReynTwitterCalls::sendResult,
			   this, &RefreshTimelineProcess::loadFirstTweetsEnded);

	// For a potenitial anticipated end
	QString errorMsg = "";
	bool gap = true;

	// Analysing the Twitter response
	switch (result.resultType) {
		case LibRT::NO_REQUEST_ERROR: {
			// Getting the most recent tweets timeline
			QJsonArray parsedResults = QJsonValue::fromVariant(result.parsedResult).toArray();
			Timeline retrievedTweets;

			retrievedTweets.fillWithVariant(parsedResults);
			newerTweets.append(retrievedTweets);

			// Are all the newer tweets retrieved ?

			if (retrievedTweets.isEmpty()) {
				finalEnd = ReynTweets::NO_MORE_TWEETS;
				errorMsg = RefreshTimelineProcess::trUtf8("Unexpected empty timeline retrieved");
			} else {
				finalEnd = ReynTweets::TIMELINE_RETRIEVED;

				// Need more intermediate tweets ?
				oldestNewTweet = newerTweets.last();

				if (oldestNewTweet == latestTweet) {
					// All the newer tweets are retrieved. End the process
					newerTweets.removeLast();
					gap = false;
				} else {
					// Some tweets are missing. Load them.
					return loadIntermediateTweets();
				}
			}
		} break;

		case LibRT::SERVICE_ERRORS:
			ProcessUtils::treatTwitterErrorResult(result, errorMsg, finalEnd);
			break;

		case LibRT::API_CALL:
			ProcessUtils::treatApiCallResult(result, errorMsg, finalEnd);
			break;

		case LibRT::JSON_PARSING:
			ProcessUtils::treatQjsonParsingResult(result.parsingErrors, errorMsg, finalEnd);
			break;

		default:
			ProcessUtils::treatUnknownResult(result.errorMessage, errorMsg, finalEnd);
			break;
	}

	// Process end (may be successful)
	this->endProcess(errorMsg, gap);
}


//////////////////////////////////////////
// Step 2 : loading intermediate tweets //
//////////////////////////////////////////

// Loading
void RefreshTimelineProcess::loadIntermediateTweets() {
	connect(&twitter, &ReynTwitterCalls::sendResult,
			this, &RefreshTimelineProcess::loadIntermediateTweetsEnded);

	this->retrievingIntermediateTweets();
}

// After loading
void RefreshTimelineProcess::loadIntermediateTweetsEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);

	if (result.resultType == LibRT::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, &ReynTwitterCalls::sendResult,
			   this, &RefreshTimelineProcess::loadFirstTweetsEnded);

	// For a potenitial anticipated end
	QString errorMsg = "";
	ReynTweets::CoreResult procEnd;
	bool gap = true;

	// Analysing the Twitter response
	switch (result.resultType) {
		case LibRT::NO_REQUEST_ERROR: {
			// Getting the most recent tweets timeline
			QJsonArray parsedResults = QJsonValue::fromVariant(result.parsedResult).toArray();
			Timeline retrievedTweets;

			retrievedTweets.fillWithVariant(parsedResults);

			// Are all the newer tweets retrieved ?

			if (retrievedTweets.isEmpty()) {
				errorMsg = RefreshTimelineProcess::trUtf8("Twitter should retrieve at least one tweet");
				procEnd = ReynTweets::NO_MORE_TWEETS;
			} else {
				// The first tweet of retrievedTweets should be the last ot newerTweets

				Tweet firstTweet = retrievedTweets.first();

				if (firstTweet != oldestNewTweet) {
					errorMsg = RefreshTimelineProcess::trUtf8("Unexpected first tweet");
					procEnd = ReynTweets::WRONG_TIMELINE;
				}

				retrievedTweets.removeFirst();
				newerTweets.append(retrievedTweets);

				// Need more intermediate tweets ?
				oldestNewTweet = newerTweets.last();

				if (oldestNewTweet == latestTweet) {
					// All the newer tweets are retrieved. End the process
					newerTweets.removeLast();
					gap = false;
					procEnd = ReynTweets::TIMELINE_RETRIEVED;
				} else {
					// Some tweets are missing. Load them.
					return loadIntermediateTweets();
				}
			}
		} break;

		case LibRT::SERVICE_ERRORS:
			ProcessUtils::treatTwitterErrorResult(result, errorMsg, procEnd);
			break;

		case LibRT::API_CALL:
			ProcessUtils::treatApiCallResult(result, errorMsg, procEnd);
			break;

		case LibRT::JSON_PARSING:
			ProcessUtils::treatQjsonParsingResult(result.parsingErrors, errorMsg, procEnd);
			break;

		default:
			ProcessUtils::treatUnknownResult(result.errorMessage, errorMsg, procEnd);
			break;
	}

	// Process end (may be successful)
	this->endProcess(errorMsg, gap, procEnd);
}

// Building the result
void RefreshTimelineProcess::endProcess(QString errorMessage,
										bool gap,
										ReynTweets::CoreResult intermediateEnd)
{
	QVariantMap resMap;

	resMap.insert("newer_tweets", QVariant::fromValue(newerTweets));
	resMap.insert("gap", QVariant::fromValue(gap));
	resMap.insert("intermediate_end", QVariant::fromValue(int(intermediateEnd)));

	GenericProcess::endProcess(finalEnd,
							   QVariant::fromValue(resMap),
							   errorMessage);
}
