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
	finalIssue(INVALID_ISSUE)
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

	if (result.resultType == Network::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, &ReynTwitterCalls::sendResult,
			   this, &RefreshTimelineProcess::loadFirstTweetsEnded);

	Network::NetworkResultType errorType = result.resultType;

	// For a potenitial anticipated end
	QString errorMsg = "";
	bool gap = true;

	// Analysing the Twitter response
	switch (errorType) {
		case Network::NO_REQUEST_ERROR: {
			// Getting the most recent tweets timeline
			QJsonArray parsedResults = QJsonValue::fromVariant(result.parsedResult).toArray();
			Timeline retrievedTweets;

			retrievedTweets.fillWithVariant(parsedResults);
			newerTweets.append(retrievedTweets);

			// Are all the newer tweets retrieved ?

			if (retrievedTweets.isEmpty()) {
				finalIssue = NO_MORE_TWEETS;
				errorMsg = RefreshTimelineProcess::trUtf8("Unexpected empty timeline retrieved");
			} else {
				finalIssue = TIMELINE_RETRIEVED;

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

		case Network::SERVICE_ERRORS:
			ProcessUtils::treatTwitterErrorResult(result, errorMsg, finalIssue);
			break;

		case Network::API_CALL:
			ProcessUtils::treatApiCallResult(result, errorMsg, finalIssue);
			break;

		case Network::JSON_PARSING:
			ProcessUtils::treatQjsonParsingResult(result.parsingErrors, errorMsg, finalIssue);
			break;

		default:
			ProcessUtils::treatUnknownResult(result.errorMessage, errorMsg, finalIssue);
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

	if (result.resultType == Network::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, &ReynTwitterCalls::sendResult,
			   this, &RefreshTimelineProcess::loadFirstTweetsEnded);

	Network::NetworkResultType errorType = result.resultType;

	// For a potenitial anticipated end
	QString errorMsg = "";
	CoreResult issue;
	bool gap = true;

	// Analysing the Twitter response
	switch (errorType) {
		case Network::NO_REQUEST_ERROR: {
			// Getting the most recent tweets timeline
			QJsonArray parsedResults = QJsonValue::fromVariant(result.parsedResult).toArray();
			Timeline retrievedTweets;

			retrievedTweets.fillWithVariant(parsedResults);

			// Are all the newer tweets retrieved ?

			if (retrievedTweets.isEmpty()) {
				errorMsg = RefreshTimelineProcess::trUtf8("Twitter should retrieve at least one tweet");
				issue = NO_MORE_TWEETS;
			} else {
				// The first tweet of retrievedTweets should be the last ot newerTweets

				Tweet firstTweet = retrievedTweets.first();

				if (firstTweet != oldestNewTweet) {
					errorMsg = RefreshTimelineProcess::trUtf8("Unexpected first tweet");
					issue = WRONG_TIMELINE;
				}

				retrievedTweets.removeFirst();
				newerTweets.append(retrievedTweets);

				// Need more intermediate tweets ?
				oldestNewTweet = newerTweets.last();

				if (oldestNewTweet == latestTweet) {
					// All the newer tweets are retrieved. End the process
					newerTweets.removeLast();
					gap = false;
					issue = TIMELINE_RETRIEVED;
				} else {
					// Some tweets are missing. Load them.
					return loadIntermediateTweets();
				}
			}
		} break;

		case Network::SERVICE_ERRORS:
			ProcessUtils::treatTwitterErrorResult(result, errorMsg, issue);
			break;

		case Network::API_CALL:
			ProcessUtils::treatApiCallResult(result, errorMsg, issue);
			break;

		case Network::JSON_PARSING:
			ProcessUtils::treatQjsonParsingResult(result.parsingErrors, errorMsg, issue);
			break;

		default:
			ProcessUtils::treatUnknownResult(result.errorMessage, errorMsg, issue);
			break;
	}

	// Process end (may be successful
	this->endProcess(errorMsg, gap, issue);
}

// Building the result
void RefreshTimelineProcess::endProcess(QString errorMessage,
										bool gap,
										CoreResult intermediateIssue)
{
	QVariantMap resMap;

	resMap.insert("newer_tweets", QVariant::fromValue(newerTweets));
	resMap.insert("gap", QVariant::fromValue(gap));
	resMap.insert("intermediate_issue", QVariant::fromValue(int(intermediateIssue)));

	GenericProcess::endProcess(finalIssue,
							   QVariant::fromValue(resMap),
							   errorMessage);
}
