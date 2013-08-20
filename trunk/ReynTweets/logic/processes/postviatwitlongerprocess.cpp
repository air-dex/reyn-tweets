/// @file postviatwitlongerprocess.cpp
/// @brief Implementation of PostViaTwitLongerProcess
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

#include "postviatwitlongerprocess.hpp"
#include "processutils.hpp"

// Constructor with QString ID
PostViaTwitLongerProcess::PostViaTwitLongerProcess(QString status,
												   QString userScreenName,
												   QString replyTostatusID,
												   QString replyToUserScreenName,
												   bool userIDonly,
												   float lat,
												   float lon,
												   QString place,
												   bool showCoord) :
	GenericProcess(),
	twitter(this),
	twitlonger(this),
	tweet(status),
	username(userScreenName),
	replyToUser(replyToUserScreenName),
	trimUser(userIDonly),
	longitude(lon),
	latitude(lat),
	reversePlace(place),
	displayCoord(showCoord),
	shortenedTweet(""),
	messageID(""),
	postedTweet()
{
	// Converting replyTostatusID QString into a qlonglong
	bool convOK = false;

	replyToTweetID = replyTostatusID.toLongLong(&convOK);
	if (!convOK) {
		replyToTweetID = -1;
	}
}

// Constructor with qlonglong ID
PostViaTwitLongerProcess::PostViaTwitLongerProcess(QString status,
												   QString userScreenName,
												   qlonglong replyTostatusID,
												   QString replyToUserScreenName,
												   bool userIDonly,
												   float lat,
												   float lon,
												   QString place,
												   bool showCoord) :
	GenericProcess(),
	twitter(this),
	twitlonger(this),
	tweet(status),
	username(userScreenName),
	replyToTweetID(replyTostatusID),
	replyToUser(replyToUserScreenName),
	trimUser(userIDonly),
	longitude(lon),
	latitude(lat),
	reversePlace(place),
	displayCoord(showCoord),
	enoughShortMessage(false),
	shortenedTweet(""),
	messageID(""),
	postedTweet()
{}


// Starting the process
void PostViaTwitLongerProcess::startProcess() {
	postToTwitLonger();
}

///////////////////////////////////////////////
// Step 1 : shorten the tweet via TwitLonger //
///////////////////////////////////////////////

void PostViaTwitLongerProcess::postToTwitLonger() {
	connect(&twitlonger, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(postToTwitLongerEnded(ResultWrapper)));

	twitlonger.postOnTwitLonger(username, tweet, replyToTweetID, replyToUser);
}

void PostViaTwitLongerProcess::postToTwitLongerEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);

	if (result.resultType == Network::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitlonger, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(postToTwitLongerEnded(ResultWrapper)));

	NetworkResultType errorType = result.resultType;

	// For a potenitial anticipated end
	QString errorMsg = "";
	CoreResult issue;

	// Analysing the Twitter response
	switch (errorType) {
		case Network::NO_REQUEST_ERROR:
			if (result.parsedResult.canConvert<QVariantMap>()) {
				// Request ends successfully
				QVariantMap resMap = result.parsedResult.toMap();
				messageID = resMap.value("id").toString();
				shortenedTweet = resMap.value("content").toString();
				return postTweet();
			} else if (result.parsedResult.canConvert<QString>()
					   && result.parsedResult.toString() == "too_short")
			{
				// The tweet was too short
				shortenedTweet = tweet;
				enoughShortMessage = true;
				return postTweet();
			} else {
				// Unexpected end : abort !
				ProcessUtils::treatUnknownResult(result.errorMessage,
												 errorMsg,
												 issue);
			}
			break;

		case Network::SERVICE_ERRORS:
			issue = UNSHORTENABLE_MESSAGE;
			errorMsg = PostViaTwitLongerProcess::trUtf8("Tweet cannot be shortened");
			break;

		case Network::API_CALL:
			ProcessUtils::treatApiCallResult(result, errorMsg, issue);
			break;

		case Network::XML_PARSING:
			ProcessUtils::treatXMLParsingResult(result.parsingErrors, errorMsg, issue);
			break;

		default:
			ProcessUtils::treatUnknownResult(result.errorMessage, errorMsg, issue);
			break;
	}

	// Failed end
	endProcess(issue, errorMsg);
}

//////////////////////////////////////////////////
// Step 2 : post the shortened tweet on Twitter //
//////////////////////////////////////////////////

void PostViaTwitLongerProcess::postTweet() {
	connect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(postTweetEnded(ResultWrapper)));

	twitter.updateTweet(shortenedTweet,
						replyToTweetID,
						latitude,
						longitude,
						reversePlace,
						displayCoord,
						trimUser);
}

void PostViaTwitLongerProcess::postTweetEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);

	if (result.resultType == Network::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitter, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(postTweetEnded(ResultWrapper)));

	NetworkResultType errorType = result.resultType;

	// For a potenitial anticipated end
	QString errorMsg = "";
	CoreResult issue;

	// Analysing the Twitter response
	switch (errorType) {
		case Network::NO_REQUEST_ERROR:
			if (enoughShortMessage) {
				// Classic post, normal end
				return endProcess(TWEET_POSTED, result.parsedResult);
			} else {
				// Go to the next step !
				postedTweet.fillWithVariant(QJsonObject::fromVariantMap(result.parsedResult.toMap()));
				return updateTweetOnTwitLonger();
			}

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

	// Failed end
	endProcess(issue, errorMsg);
}

///////////////////////////////////////////////////
// Step 3 : update the tweet datas on TwitLonger //
///////////////////////////////////////////////////

void PostViaTwitLongerProcess::updateTweetOnTwitLonger() {
	connect(&twitlonger, SIGNAL(sendResult(ResultWrapper)),
			this, SLOT(updateTweetOnTwitLongerEnded(ResultWrapper)));

	twitlonger.updateLongTweet(messageID, postedTweet.getIDstr().toLongLong());
}

void PostViaTwitLongerProcess::updateTweetOnTwitLongerEnded(ResultWrapper res) {
	// Ensures that res is for the process
	RequestResult result = res.accessResult(this);

	if (result.resultType == Network::INVALID_RESULT) {
		return invalidEnd();
	}

	disconnect(&twitlonger, SIGNAL(sendResult(ResultWrapper)),
			   this, SLOT(updateTweetOnTwitLongerEnded(ResultWrapper)));

	NetworkResultType errorType = result.resultType;

	// For a potenitial anticipated end
	QString errorMsg = "";
	CoreResult issue;

	// Analysing the Twitter response
	switch (errorType) {
		case Network::NO_REQUEST_ERROR:
			// TODO : final treatment : Nothing a priori
			issue = TWEET_POSTED;
			break;

		case Network::SERVICE_ERRORS:
			issue = MESSAGE_NOT_UPDATED;
			errorMsg = PostViaTwitLongerProcess::trUtf8("Message on TwitLonger cannot be updated.");
			break;

		case Network::API_CALL:
			ProcessUtils::treatApiCallResult(result, errorMsg, issue);
			issue = MESSAGE_NOT_UPDATED;
			break;

		case Network::XML_PARSING:
			ProcessUtils::treatXMLParsingResult(result.parsingErrors, errorMsg, issue);
			issue = TWEET_POSTED;
			break;

		default:
			ProcessUtils::treatUnknownResult(result.errorMessage, errorMsg, issue);
			break;
	}

	// End of the process
	/*
	 * This is not a real problem if this step failed for known reasons
	 * (TwitLonger errors, network problems, failed to parse the TwitLonger XML
	 * response). The most important is done (posting the tweet) !
	 */
	endProcess(issue, postedTweet.toVariant(), errorMsg);
}
