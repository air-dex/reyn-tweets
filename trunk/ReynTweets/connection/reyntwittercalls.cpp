/// @file reyntwittercalls.cpp
/// @brief Implementation of ReynTwitterCalls
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011 Romain Ducher
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

#include "reyntwittercalls.hpp"
#include "requests/requests.hpp"

// Static components
RequesterManager ReynTwitterCalls::requesterManager = RequesterManager();

// OAuth information
OAuthManager ReynTwitterCalls::oauthManager = OAuthManager();

// Protected constructor
ReynTwitterCalls::ReynTwitterCalls(QObject * requester) :
	QObject(),
	requestDemander(requester)
{}

// Destructor
ReynTwitterCalls::~ReynTwitterCalls() {
	requestDemander = 0;
}


/////////////////////
// Core management //
/////////////////////

// Adding a requester to the requester manager
void ReynTwitterCalls::addRequester(GenericRequester * requester) {
	if (requester != 0) {
		connect(requester, SIGNAL(requestDone()),
				this, SLOT(endRequest()));
		requesterManager.addRequest(requestDemander, requester);
	}
}

// Removing a requester of the requester manager
void ReynTwitterCalls::removeRequester(GenericRequester * requester) {
	if (requester != 0) {
		disconnect(requester, SIGNAL(requestDone()),
				   this, SLOT(endRequest()));
		requesterManager.removeRequest(requester->getUuid());
	}
}

// Slot executed when a requester has finished its work
void ReynTwitterCalls::endRequest() {
	GenericRequester * requester = qobject_cast<GenericRequester *>(sender());
	ResultWrapper res = buildResultSender(requester);
	removeRequester(requester);
	emit sendResult(res);
}

// Method that builds the wrapper of a result
ResultWrapper ReynTwitterCalls::buildResultSender(GenericRequester * endedRequest) {
	if (endedRequest) {
		RequestInfos & requestInfos = requesterManager.getRequestInfos(endedRequest->getUuid());
		return ResultWrapper(requestInfos.getAsker(),
							 requestInfos.getRequester()->getRequestResult());
	} else {
		return ResultWrapper();
	}
}

// Inline method for executing requests
void ReynTwitterCalls::executeRequest(GenericRequester * requester) {
	if (requester != 0) {
		addRequester(requester);
		requester->executeRequest();
	}
}


///////////////////////
// Request launchers //
///////////////////////

//////////////
// Accounts //
//////////////

// Verifying credentials
void ReynTwitterCalls::verifyCredentials(bool entities, bool skipStatus) {
	VerifyCredentialsRequester * requester = new VerifyCredentialsRequester(oauthManager,
																			entities,
																			skipStatus);
	executeRequest(requester);
}


///////////////
// Favorites //
///////////////

// Favoriting a tweet
void ReynTwitterCalls::favoriteTweet(qlonglong id, bool entities) {
	FavoriteRequester * requester = new FavoriteRequester(oauthManager,
														  id,
														  entities);
	executeRequest(requester);
}

// Retrieving the timeline with the favorite tweets of the userwhose ID is id.
void ReynTwitterCalls::getFavoriteTimeline(qlonglong id,
										   qlonglong sinceID,
										   bool entities,
										   int page,
										   int count)
{
	FavoritesTimelineRequester * requester = new FavoritesTimelineRequester(oauthManager,
																			id,
																			count,
																			sinceID,
																			page,
																			entities);
	executeRequest(requester);
}

// Retrieving the timeline with the favorite tweets of the user whose screen name is id.
void ReynTwitterCalls::getFavoriteTimeline(QString id,
										   qlonglong sinceID,
										   bool entities,
										   int page,
										   int count)
{
	FavoritesTimelineRequester * requester = new FavoritesTimelineRequester(oauthManager,
																			id,
																			count,
																			sinceID,
																			page,
																			entities);
	executeRequest(requester);
}

// Unavoriting a tweet
void ReynTwitterCalls::unfavoriteTweet(qlonglong id) {
	UnfavoriteRequester * requester = new UnfavoriteRequester(oauthManager, id);
	executeRequest(requester);
}

///////////
// OAuth //
///////////

// Method for getting a request token
void ReynTwitterCalls::requestToken() {
	RequestTokenRequester * requester = new RequestTokenRequester(oauthManager);
	executeRequest(requester);
}

// Authorizing request Tokens
void ReynTwitterCalls::authorize() {
	AuthorizeRequester * requester = new AuthorizeRequester(oauthManager);
	executeRequest(requester);
}

// POST authorize() requests to allow or to deny the application.
void ReynTwitterCalls::postAuthorize(QString login, QString password, bool deny) {
	PostAuthorizeRequester * requester = new PostAuthorizeRequester(oauthManager,
																	login,
																	password,
																	deny);
	executeRequest(requester);
}

// Getting the access tokens
void ReynTwitterCalls::accessToken() {
	AccessTokenRequester * requester = new AccessTokenRequester(oauthManager);
	executeRequest(requester);
}

// Resetting the credentials to connect to Twitter
void ReynTwitterCalls::resetTokens() {
	oauthManager.resetTokens();
}

// Setting new credentials to connect to Twitter
void ReynTwitterCalls::setNewTokens(QByteArray accessToken,
									QByteArray tokenSecret,
									QByteArray consumerKey,
									QByteArray consumerSecret)
{
	oauthManager.setOAuthToken(accessToken, false);
	oauthManager.setOAuthSecret(tokenSecret, false);
	oauthManager.setConsumerKey(consumerKey);
	oauthManager.setConsumerSecret(consumerSecret);
}


//////////////
// Searches //
//////////////

// Method that launch searches
void ReynTwitterCalls::search(QString q) {
	SearchRequester * requester = new SearchRequester(q);
	executeRequest(requester);
}


///////////////
// Timelines //
///////////////

// Retrieving the timeline with the tweets of the user's friends
void ReynTwitterCalls::retrieveHomeTimeline(qlonglong sinceID,
											qlonglong maxID,
											bool trimUser,
											bool includeRTS,
											bool includeEntities,
											bool excludeReplies,
											int page,
											int count,
											bool contributorsDetails)
{
	HomeTimelineRequester * requester = new HomeTimelineRequester(oauthManager,
																  sinceID,
																  maxID,
																  trimUser,
																  includeRTS,
																  includeEntities,
																  excludeReplies,
																  page,
																  count,
																  contributorsDetails);
	executeRequest(requester);
}

// Retrieving the timeline with the tweets of the user's friends
void ReynTwitterCalls::userRetweetsTimeline(qlonglong sinceID,
											qlonglong maxID,
											int count,
											bool trimUser,
											bool includeEntities)
{
	RetweetsByMeRequester * requester = new RetweetsByMeRequester(oauthManager,
																  sinceID,
																  maxID,
																  count,
																  trimUser,
																  includeEntities);
	executeRequest(requester);
}


////////////
// Tweets //
////////////

// Destroying (deleting) a tweet
void ReynTwitterCalls::destroyTweet(qlonglong tweetID,
									bool entities,
									bool trimUser)
{
	DestroyTweetRequester * requester = new DestroyTweetRequester(oauthManager,
																  tweetID,
																  entities,
																  trimUser);
	executeRequest(requester);
}

// Retweeting a tweet
void ReynTwitterCalls::retweet(qlonglong tweetID, bool entities, bool trimUser) {
	RetweetRequester * requester = new RetweetRequester(oauthManager,
														tweetID,
														entities,
														trimUser);
	executeRequest(requester);
}

// Showing a tweet
void ReynTwitterCalls::showTweet(qlonglong tweetID, bool entities, bool trimUser) {
	ShowTweetRequester * requester = new ShowTweetRequester(tweetID,
															entities,
															trimUser);
	executeRequest(requester);
}

// Posting a tweet without media
void ReynTwitterCalls::updateTweet(QString tweet,
								   qlonglong replyToTweetID,
								   float latitude,
								   float longitude,
								   QString reversePlace,
								   bool displayCoord,
								   bool trimUser,
								   bool includeEntities)
{
	PostTweetRequester * requester = new PostTweetRequester(oauthManager,
															tweet,
															replyToTweetID,
															latitude,
															longitude,
															reversePlace,
															displayCoord,
															trimUser,
															includeEntities);
	executeRequest(requester);
}


///////////
// Users //
///////////

// Showing a user identified by its ID
void ReynTwitterCalls::showUser(qlonglong userID, bool entities) {
	ShowUserRequester * requester = new ShowUserRequester(oauthManager,
														  userID,
														  entities);
	executeRequest(requester);
}

// Showing a user identified by its screen name
void ReynTwitterCalls::showUser(QString screenName, bool entities) {
	ShowUserRequester * requester = new ShowUserRequester(oauthManager,
														  screenName,
														  entities);
	executeRequest(requester);
}
