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
#include "processes/processes.hpp"

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
ReynTweetsUserConfiguration ReynCore::userConfiguration = ReynTweetsUserConfiguration();

// Configuration
ReynTweetsAppConfiguration ReynCore::appConfiguration = ReynTweetsAppConfiguration();

// Process manager
ProcessManager ReynCore::processManager = ProcessManager();


/////////////////////
// Core management //
/////////////////////

// Adding a requester to the requester manager
void ReynCore::addProcess(GenericProcess * process) {
	if (process) {
		connect(process, SIGNAL(processEnded()),
				this, SLOT(endProcess()));
		processManager.addProcess(requestDemander, process);
	}
}

// Removing a requester of the requester manager
void ReynCore::removeProcess(GenericProcess * process) {
	if (process) {
		disconnect(process, SIGNAL(processEnded()),
				   this, SLOT(endProcess()));
		processManager.removeProcess(process->getProcessUUID());
	}
}

// Slot executed when a requester has finished its work
void ReynCore::endProcess() {
	// Getting the process
	GenericProcess * process = qobject_cast<GenericProcess *>(sender());
	ProcessWrapper result = buildResultSender(process);
	removeProcess(process);
	emit sendResult(result);
}

// Method that builds the wrapper of a result
ProcessWrapper ReynCore::buildResultSender(GenericProcess * endedProcess) {
	if (endedProcess) {
		ProcessInfos & procInfos = processManager.getProcessInfos(endedProcess->getProcessUUID());
		return ProcessWrapper(procInfos.asker,
							  procInfos.process->getProcessResult());
	} else {
		return ProcessWrapper();
	}
}

// Inline method for executing processes
void ReynCore::executeProcess(GenericProcess * process) {
	if (process) {
		addProcess(process);
		process->startProcess();
	}
}


////////////////////
// Special wiring //
////////////////////

// OAuth process giving informations about user credentials

// Executed when an OAuthProcess send its userCredentialsRequired() signal.
void ReynCore::userCredentialsRequired() {
	emit userCredentialsNeeded();
}

// Telling the user whether credentials given by it are right.
void ReynCore::credentialsOK(bool credsOK) {
	emit credentialsValid(credsOK);
}


// Authorize or deny

// Allowing Reyn Tweets to use the Twitter account :)
void ReynCore::authorizeReynTweets(QString login, QString password) {
	emit authorize(login, password);
}

// Denying Reyn Tweets :(
void ReynCore::denyReynTweets(QString login, QString password) {
	emit deny(login, password);
}


////////////////////////
// Actions to realize //
////////////////////////

// Getting a reference on the user configuration
ReynTweetsUserConfiguration & ReynCore::getUserConfiguration() {
	return userConfiguration;
}

// Getting a reference on the configuration of Reyn Tweets
ReynTweetsAppConfiguration & ReynCore::getAppConfiguration() {
	return appConfiguration;
}

//////////////////////////////////
// Launching and authentication //
//////////////////////////////////

// Launching the app
void ReynCore::launchReynTweets() {
	LaunchingProcess * process = new LaunchingProcess(userConfiguration,
													  appConfiguration);
	executeProcess(process);
}

// Allowing Reyn Tweets
void ReynCore::authorizeReynTweets() {
	OAuthProcess * process = new OAuthProcess();
	oauthSpecialWiring(process);
	executeProcess(process);
}

// Allowing Reyn Tweets
void ReynCore::allowReynTweets() {
	AllowProcess * process = new AllowProcess(userConfiguration);
	oauthSpecialWiring(process);
	executeProcess(process);
}

// Special wiring of an OAuth process.
void ReynCore::oauthSpecialWiring(OAuthProcess * oauthProcess) {
	// Process giving informations about user credentials
	connect(oauthProcess, SIGNAL(userCredentialsRequired()),
			this, SLOT(userCredentialsRequired()));
	connect(oauthProcess, SIGNAL(credentialsOK(bool)),
			this, SLOT(credentialsOK(bool)));

	// User telling the process if he want to authorize or to deny Reyn Tweets
	connect(this, SIGNAL(authorize(QString,QString)),
			oauthProcess, SLOT(authorizeReynTweets(QString,QString)));
	connect(this, SIGNAL(deny(QString,QString)),
			oauthProcess, SLOT(denyReynTweets(QString,QString)));
}

///////////////
// Timelines //
///////////////

// Unfavoriting a tweet
void ReynCore::loadHomeTimeline(qlonglong sinceID,
								qlonglong maxID,
								int count,
								bool trimUser,
								bool includeRTS,
								bool includeEntities,
								bool excludeReplies,
								int page,
								bool contributorsDetails)
{
	LoadingHomeTimelineProcess * process = new LoadingHomeTimelineProcess(sinceID,
																		  maxID,
																		  trimUser,
																		  includeRTS,
																		  includeEntities,
																		  excludeReplies,
																		  page,
																		  count,
																		  contributorsDetails);
	executeProcess(process);
}

////////////
// Tweets //
////////////

// Favoriting a tweet
void ReynCore::favoriteTweet(qlonglong id) {
	FavoriteProcess * process = new FavoriteProcess(id, true);
	executeProcess(process);
}

// Unfavoriting a tweet
void ReynCore::unfavoriteTweet(qlonglong id) {
	FavoriteProcess * process = new FavoriteProcess(id, false);
	executeProcess(process);
}

// Posting a tweet without media
void ReynCore::postTweet(QString tweet,
						 qlonglong replyToTweetID,
						 bool trimUser,
						 bool includeEntities,
						 float latitude,
						 float longitude,
						 QString reversePlace,
						 bool displayCoord)
{
	PostTweetProcess * process = new PostTweetProcess(tweet,
													  replyToTweetID,
													  trimUser,
													  includeEntities,
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
						 bool includeEntities,
						 float latitude,
						 float longitude,
						 QString reversePlace,
						 bool displayCoord)
{
	PostTweetProcess * process = new PostTweetProcess(tweet,
													  replyToTweetID,
													  trimUser,
													  includeEntities,
													  latitude,
													  longitude,
													  reversePlace,
													  displayCoord);

	executeProcess(process);
}

// Posting a tweet without media
void ReynCore::postTweetViaTwitLonger(QString tweet,
									  qlonglong replyToTweetID,
									  QString replyToUser,
									  bool trimUser,
									  bool includeEntities,
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
																	  includeEntities,
																	  latitude,
																	  longitude,
																	  reversePlace,
																	  displayCoord);

	executeProcess(process);
}

// Posting a tweet without media
void ReynCore::postTweetViaTwitLonger(QString tweet,
									  QString replyToTweetID,
									  QString replyToUser,
									  bool trimUser,
									  bool includeEntities,
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
																	  includeEntities,
																	  latitude,
																	  longitude,
																	  reversePlace,
																	  displayCoord);

	executeProcess(process);
}

// Reweeting a tweet
void ReynCore::retweet(qlonglong tweetID, bool includeEntities, bool trimUser) {
	RetweetProcess * process = new RetweetProcess(tweetID,
												  includeEntities,
												  trimUser);

	executeProcess(process);
}

// Deleting a tweet
void ReynCore::deleteTweet(Tweet tweetToDelete, bool includeEntities, bool trimUser) {
	DeleteTweetProcess * process = new DeleteTweetProcess(userConfiguration.getUserAccount().getUserRef(),
														  tweetToDelete,
														  includeEntities,
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
