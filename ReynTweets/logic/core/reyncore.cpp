/// @file reyncore.cpp
/// @brief Implementation of ReynCore
///
/// Revisions of the file older than r204 are in /trunk/ReynTweets/controls
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

#include "reyncore.hpp"
#include "../processes/processes.hpp"

// Constructor
ReynCore::ReynCore(QObject * actionRequester) :
	QObject(),
	requestDemander(actionRequester)
{}

// Destructor
ReynCore::~ReynCore() {
	requestDemander = 0;
}

// Copy constructor
ReynCore::ReynCore(const ReynCore & heart) :
	QObject()
{
	recopie(heart);
}

// Affectation
const ReynCore & ReynCore::operator=(const ReynCore & heart) {
	recopie(heart);
	return *this;
}

// Recopy
void ReynCore::recopie(const ReynCore & heart) {
	requestDemander = heart.requestDemander;
}


////////////////////
// Static members //
////////////////////

// Configuration
UserConfiguration ReynCore::userConfiguration = UserConfiguration();

// Configuration
AppConfiguration & ReynCore::appConfiguration = AppConfiguration::getReynTweetsConfiguration();

// Process manager
ProcessManager ReynCore::processManager = ProcessManager();


/////////////////////
// Core management //
/////////////////////

// Adding a requester to the requester manager
void ReynCore::addProcess(GenericProcess * process) {
	if (process) {
		connect(process, SIGNAL(processEnded(ProcessResult)),
				this, SLOT(endProcess(ProcessResult)));
		processManager.addProcess(requestDemander, process);
	}
}

// Removing a requester of the requester manager
void ReynCore::removeProcess(GenericProcess * process) {
	if (process) {
		disconnect(process, SIGNAL(processEnded(ProcessResult)),
				   this, SLOT(endProcess(ProcessResult)));
		processManager.removeProcess(process);
	}
}

// Slot executed when a requester has finished its work
void ReynCore::endProcess(ProcessResult processResult) {
	// Getting the process
	GenericProcess * process = qobject_cast<GenericProcess *>(sender());
	ProcessWrapper result(processManager.getAsker(process), processResult);
	removeProcess(process);
	emit sendResult(result);
}

// Inline method for executing processes
void ReynCore::executeProcess(GenericProcess * process) {
	if (process) {
		addProcess(process);
		process->startProcess();
	}
}


////////////////////////
// Actions to realize //
////////////////////////

// Getting a reference on the user configuration
UserConfiguration & ReynCore::getUserConfiguration() {
	return userConfiguration;
}

// Setting the user configuration
void ReynCore::setUserConfiguration(UserConfiguration userConf) {
	userConfiguration = userConf;
}


//////////////////////////////////
// Launching and authentication //
//////////////////////////////////

// Launching the app
void ReynCore::launchReynTweets() {
	LaunchingProcess * process = new LaunchingProcess(userConfiguration);
	executeProcess(process);
}

// Getting OAuth Request tokens for Reyn Tweets
void ReynCore::requestOAuthTokens() {
	RequestTokensProcess * process = new RequestTokensProcess();
	executeProcess(process);
}

// Getting OAuth Access tokens for Reyn Tweets
void ReynCore::accessOAuthTokens(QByteArray verifier, bool updateConfiguration) {
	AccessTokensProcess * process = updateConfiguration ?
				new AccessTokensProcess(verifier, userConfiguration)
			  : new AccessTokensProcess(verifier);

	executeProcess(process);
}


///////////////
// Timelines //
///////////////

// Loading the Home Timeline
void ReynCore::loadHomeTimeline(qlonglong sinceID,
								qlonglong maxID,
								int count,
								bool trimUser,
								bool includeEntities,
								bool excludeReplies,
								bool contributorsDetails)
{
	LoadingHomeTimelineProcess * process = new LoadingHomeTimelineProcess(sinceID,
																		  maxID,
																		  trimUser,
																		  includeEntities,
																		  excludeReplies,
																		  count,
																		  contributorsDetails);
	executeProcess(process);
}

// Refreshing the Home Timeline
void ReynCore::refreshHomeTimeline(qlonglong sinceID,
								   bool trimUser,
								   bool includeEntities,
								   bool excludeReplies,
								   bool contributorsDetails)
{
	RefreshHomeTimelineProcess * process = new RefreshHomeTimelineProcess(sinceID,
																		  trimUser,
																		  includeEntities,
																		  excludeReplies,
																		  contributorsDetails);
	executeProcess(process);
}

// Loading mentions
void ReynCore::loadMentionsTimeline(qlonglong sinceID,
									qlonglong maxID,
									int count,
									bool trimUser,
									bool includeEntities,
									bool contributorsDetails)
{
	LoadMentionsTimelineProcess * process = new LoadMentionsTimelineProcess(sinceID,
																			maxID,
																			trimUser,
																			includeEntities,
																			count,
																			contributorsDetails);
	executeProcess(process);
}

// Refreshing the Mentions Timeline
void ReynCore::refreshMentionsTimeline(qlonglong sinceID,
									   bool trimUser,
									   bool includeEntities,
									   bool contributorsDetails)
{
	RefreshMentionsTimelineProcess * process = new RefreshMentionsTimelineProcess(sinceID,
																				  trimUser,
																				  includeEntities,
																				  contributorsDetails);
	executeProcess(process);
}


////////////
// Tweets //
////////////

// Favoriting a tweet
void ReynCore::favoriteTweet(qlonglong id, bool includeEntities) {
	FavoriteProcess * process = new FavoriteProcess(id, true, includeEntities);
	executeProcess(process);
}

// Unfavoriting a tweet
void ReynCore::unfavoriteTweet(qlonglong id, bool includeEntities) {
	FavoriteProcess * process = new FavoriteProcess(id, false, includeEntities);
	executeProcess(process);
}

// Posting a tweet without media
void ReynCore::postTweet(QString tweet,
						 qlonglong replyToTweetID,
						 bool trimUser,
						 float latitude,
						 float longitude,
						 QString reversePlace,
						 bool displayCoord)
{
	PostTweetProcess * process = new PostTweetProcess(tweet,
													  replyToTweetID,
													  trimUser,
													  latitude,
													  longitude,
													  reversePlace,
													  displayCoord);

	executeProcess(process);
}

// Posting a tweet without media
void ReynCore::postTweet(QString tweet,
						 QString replyToTweetID,
						 bool trimUser,
						 float latitude,
						 float longitude,
						 QString reversePlace,
						 bool displayCoord)
{
	PostTweetProcess * process = new PostTweetProcess(tweet,
													  replyToTweetID,
													  trimUser,
													  latitude,
													  longitude,
													  reversePlace,
													  displayCoord);

	executeProcess(process);
}

// Posting a long tweet without media
void ReynCore::postTweetViaTwitLonger(QString tweet,
									  qlonglong replyToTweetID,
									  QString replyToUser,
									  bool trimUser,
									  float latitude,
									  float longitude,
									  QString reversePlace,
									  bool displayCoord)
{
	PostViaTwitLongerProcess * process = new PostViaTwitLongerProcess(tweet,
																	  userConfiguration.getUserAccount().getUser().getScreenName(),
																	  replyToTweetID,
																	  replyToUser,
																	  trimUser,
																	  latitude,
																	  longitude,
																	  reversePlace,
																	  displayCoord);

	executeProcess(process);
}

// Posting a long tweet without media
void ReynCore::postTweetViaTwitLonger(QString tweet,
									  QString replyToTweetID,
									  QString replyToUser,
									  bool trimUser,
									  float latitude,
									  float longitude,
									  QString reversePlace,
									  bool displayCoord)
{
	PostViaTwitLongerProcess * process = new PostViaTwitLongerProcess(tweet,
																	  userConfiguration.getUserAccount().getUser().getScreenName(),
																	  replyToTweetID,
																	  replyToUser,
																	  trimUser,
																	  latitude,
																	  longitude,
																	  reversePlace,
																	  displayCoord);

	executeProcess(process);
}

// Reweeting a tweet
void ReynCore::retweet(qlonglong tweetID, bool trimUser) {
	RetweetProcess * process = new RetweetProcess(tweetID, trimUser);
	executeProcess(process);
}

// Deleting a tweet
void ReynCore::deleteTweet(Tweet tweetToDelete, bool trimUser) {
	DeleteTweetProcess * process = new DeleteTweetProcess(userConfiguration.getUserAccount().getUserRef(),
														  tweetToDelete,
														  trimUser);

	executeProcess(process);
}

// Getting a tweet with a given ID.
void ReynCore::getTweet(qlonglong tweetID,
						bool trimUser,
						bool includeEntities,
						bool includeMyRetweet)
{
	GetTweetProcess * process = new GetTweetProcess(tweetID,
													trimUser,
													includeEntities,
													includeMyRetweet);
	executeProcess(process);
}
