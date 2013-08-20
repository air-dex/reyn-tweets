/// @file reyncore.hpp
/// @brief Header of ReynCore
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

#ifndef REYNCORE_HPP
#define REYNCORE_HPP

#include <QObject>
#include <QByteArray>
#include "coreresult.hpp"
#include "configuration/userconfiguration.hpp"
#include "configuration/appconfiguration.hpp"
#include "tweets/tweet.hpp"
#include "../processes/genericprocess.hpp"
#include "../processes/processmanager.hpp"
#include "../processes/processwrapper.hpp"

/// @class ReynCore
/// @brief Heart of Reyn Tweets.
///
/// It is the main controller of the application. All the Controls rely on it
/// to do everything they have to do.
class ReynCore : public QObject
{
	Q_OBJECT

	//////////////////////////////////
	// Core management of the class //
	//////////////////////////////////

	public:
		/// @fn ReynCore(QObject * actionRequester);
		/// @brief Constructor
		/// @param actionRequester Entity which asks the Core to do something
		ReynCore(QObject * actionRequester);

		/// @fn ~ReynCore();
		/// @brief Destructor
		~ReynCore();

		/// @fn ReynCore(const ReynCore & heart);
		/// @brief Copy constructor
		/// @param heart Core to copy
		ReynCore(const ReynCore & heart);

		/// @fn const ReynCore & operator=(const ReynCore & heart);
		/// @brief Affectation operator
		/// @param heart Core to copy
		const ReynCore & operator=(const ReynCore & heart);

	signals:
		/// @fn void sendResult(ProcessWrapper res);
		/// @brief Signal emitted to the QObject that requests the process
		/// @param res Result of a process
		void sendResult(ProcessWrapper res);

	public slots:
		/// @fn void endProcess(ProcessResult processResult);
		/// @brief Slot executed when a requester has finished its work
		/// @param processResult Result of the process
		void endProcess(ProcessResult processResult);

	protected:
		/// @brief QObject that asks for the request
		QObject * requestDemander;

		/// @brief Process manager
		static ProcessManager processManager;

		/// @brief Configuration of users
		static UserConfiguration userConfiguration;

		/// @brief Configuration of the application
		static AppConfiguration & appConfiguration;

	private:
		/// @fn void recopie(const ReynCore & heart);
		/// @brief Copying a ReynCore
		/// @param heart Core to copy
		void recopie(const ReynCore & heart);

		/// @fn void addProcess(GenericProcess * process);
		/// @brief Adding a process to the process manager
		/// @param process Address of the process
		void addProcess(GenericProcess * process);

		/// @fn void removeProcess(GenericProcess * process);
		/// @brief Removing a process of the process manager
		/// @param process Address of the process
		void removeProcess(GenericProcess * process);

		/// @fn inline void executeProcess(GenericProcess * process);
		/// @brief Inline method for executing processes
		/// @param process The process
		inline void executeProcess(GenericProcess * process);


	////////////////////////
	// Actions to realize //
	////////////////////////

	public:
		/// @fn static ReynTweetsUserConfiguration & getUserConfiguration();
		/// @brief Getting a reference on the user configuration
		/// @return Reference on userConfiguration
		static UserConfiguration & getUserConfiguration();

		/// @fn static void setUserConfiguration(ReynTweetsUserConfiguration userConf);
		/// @brief Setting the user configuration
		/// @param userConf New value for userConfiguration
		static void setUserConfiguration(UserConfiguration userConf);

		//////////////////////////////////
		// Launching and authentication //
		//////////////////////////////////

		/// @fn void launchReynTweets();
		/// @brief Launching the app
		void launchReynTweets();

		/// @fn void requestOAuthTokens();
		/// @brief Getting OAuth Request tokens for Reyn Tweets
		void requestOAuthTokens();

		/// @fn void accessOAuthTokens(QByteArray verifier,
		///							   bool updateConfiguration = true);
		/// @brief Getting OAuth Access tokens for Reyn Tweets
		/// @param verifier OAuth verifier
		/// @param updateConfiguration Boolean indicating if the (user)
		/// configuration has to be updated.
		void accessOAuthTokens(QByteArray verifier,
							   bool updateConfiguration = true);

		///////////////
		// Timelines //
		///////////////

		/// @fn void loadHomeTimeline(qlonglong sinceID = -1,
		///							  qlonglong maxID = -1,
		///							  int count = 20,
		///							  bool trimUser = false,
		///							  bool includeEntities = true,
		///							  bool excludeReplies = false,
		///							  bool contributorsDetails = false);
		/// @brief Loading the home timeline of a user
		/// @param sinceID Minimum tweet ID possible in the timeline
		/// @param maxID Maximum tweet ID possible in the timeline
		/// @param count Number of tweets
		/// @param trimUser In tweets, giving only the ID of the author (true).
		/// @param includeEntities Including Tweet Entities in the tweets (true).
		/// @param excludeReplies Excluding the replies
		/// @param contributorsDetails Including details about contributors
		/// @see https://dev.twitter.com/docs/api/1.1/get/statuses/home_timeline
		void loadHomeTimeline(qlonglong sinceID = -1,
							  qlonglong maxID = -1,
							  int count = 20,
							  bool trimUser = false,
							  bool includeEntities = true,
							  bool excludeReplies = false,
							  bool contributorsDetails = false);

		/// @fn void refreshHomeTimeline(Tweet latestTweet,
		///								 bool trimUser = false,
		///								 bool includeEntities = true,
		///								 bool excludeReplies = false,
		///								 bool contributorsDetails = false);
		/// @brief Refreshing the home timeline of a user
		/// @param latestTweet Most recent tweet already known
		/// @param trimUser In tweets, giving only the ID of the author (true).
		/// @param includeEntities Including Tweet Entities in the tweets (true).
		/// @param excludeReplies Excluding the replies
		/// @param contributorsDetails Including details about contributors
		/// @see https://dev.twitter.com/docs/api/1.1/get/statuses/home_timeline
		void refreshHomeTimeline(Tweet latestTweet,
								 bool trimUser = false,
								 bool includeEntities = true,
								 bool excludeReplies = false,
								 bool contributorsDetails = false);

		/// @fn void loadMentionsTimeline(qlonglong sinceID = -1,
		///								  qlonglong maxID = -1,
		///								  int count = 20,
		///								  bool trimUser = false,
		///								  bool includeEntities = true,
		///								  bool contributorsDetails = false);
		/// @brief Loading the timeline containing the mentions of the user
		/// @param sinceID Minimum tweet ID possible in the timeline
		/// @param maxID Maximum tweet ID possible in the timeline
		/// @param count Number of tweets
		/// @param trimUser In tweets, giving only the ID of the author (true).
		/// @param includeEntities Including Tweet Entities in the tweets (true).
		/// @param contributorsDetails Including details about contributors
		/// @see https://dev.twitter.com/docs/api/1.1/get/statuses/mentions
		void loadMentionsTimeline(qlonglong sinceID = -1,
								  qlonglong maxID = -1,
								  int count = 20,
								  bool trimUser = false,
								  bool includeEntities = true,
								  bool contributorsDetails = false);

		/// @fn void refreshMentionsTimeline(Tweet latestTweet,
		///									 bool trimUser = false,
		///									 bool includeEntities = true,
		///									 bool contributorsDetails = false);
		/// @brief Refreshing the timeline containing the mentions of the user
		/// @param latestTweet Most recent tweet already known
		/// @param trimUser In tweets, giving only the ID of the author (true).
		/// @param includeEntities Including Tweet Entities in the tweets (true).
		/// @param contributorsDetails Including details about contributors
		/// @see https://dev.twitter.com/docs/api/1.1/get/statuses/mentions
		void refreshMentionsTimeline(Tweet latestTweet,
									 bool trimUser = false,
									 bool includeEntities = true,
									 bool contributorsDetails = false);

		////////////
		// Tweets //
		////////////

		/// @fn void favoriteTweet(qlonglong id, bool includeEntities = true);
		/// @brief Favoriting a tweet
		/// @param id ID of the tweet to favorite
		/// @param includeEntities Including Tweet Entities in the favorited
		/// tweet (when set to true).
		void favoriteTweet(qlonglong id, bool includeEntities = true);

		/// @fn void unfavoriteTweet(qlonglong id, bool includeEntities = true);
		/// @brief Unfavoriting a tweet
		/// @param id ID of the tweet to unfavorite
		/// @param includeEntities Including Tweet Entities in the unfavorited
		/// tweet (when set to true).
		void unfavoriteTweet(qlonglong id, bool includeEntities = true);

		/// @fn void postTweet(QString tweet,
		///					   qlonglong replyToTweetID,
		///					   bool trimUser = false,
		///					   float latitude = -361,
		///					   float longitude = -361,
		///					   QString reversePlace = "",
		///					   bool displayCoord = false);
		/// @brief Posting a tweet without media (ID qlonglong)
		/// @param tweet Text of the tweet
		/// @param replyToTweetID If the tweet is a reply, this parameter is
		/// the ID of the tweet that this tweet replies to.
		/// @param trimUser In tweets, giving only the ID of the author (true).
		/// @param longitude For geolocation, your longitude.
		/// @param latitude For geolocation, your latitude.
		/// @param reversePlace For geolocation, ID of the place where the tweet
		/// is supposed to be sent
		/// @param displayCoord Displaying the coordonates of the tweet
		/// with a pin on a map
		/// @see https://dev.twitter.com/docs/api/1.1/post/statuses/update
		void postTweet(QString tweet,
					   qlonglong replyToTweetID = -1,
					   bool trimUser = false,
					   float latitude = -361,
					   float longitude = -361,
					   QString reversePlace = "",
					   bool displayCoord = false);

		/// @fn void postTweet(QString tweet,
		///					   QString replyToTweetID = "-1",
		///					   bool trimUser = false,
		///					   float latitude = -361,
		///					   float longitude = -361,
		///					   QString reversePlace = "",
		///					   bool displayCoord = false);
		/// @brief Posting a tweet without media (ID QString)
		/// @param tweet Text of the tweet
		/// @param replyToTweetID If the tweet is a reply, this parameter is
		/// the ID of the tweet that this tweet replies to.
		/// @param trimUser In tweets, giving only the ID of the author (true).
		/// @param longitude For geolocation, your longitude.
		/// @param latitude For geolocation, your latitude.
		/// @param reversePlace For geolocation, ID of the place where the tweet
		/// is supposed to be sent
		/// @param displayCoord Displaying the coordonates of the tweet
		/// with a pin on a map
		/// @see https://dev.twitter.com/docs/api/1.1/post/statuses/update
		void postTweet(QString tweet,
					   QString replyToTweetID = "-1",
					   bool trimUser = false,
					   float latitude = -361,
					   float longitude = -361,
					   QString reversePlace = "",
					   bool displayCoord = false);

		/// @fn void postTweetViaTwitLonger(QString tweet,
		///									qlonglong replyToTweetID = -1,
		///									QString replyToUser = "",
		///									bool trimUser = false,
		///									float latitude = -361,
		///									float longitude = -361,
		///									QString reversePlace = "",
		///									bool displayCoord = false);
		/// @brief Posting a tweet via TwitLonger
		/// @param tweet Text of the tweet
		/// @param replyToTweetID If the tweet is a reply, this parameter is
		/// the ID of the tweet that this tweet replies to.
		/// @param replyToUser If the tweet is a reply, this parameter is
		/// the screen name of the tweet that this tweet replies to.
		/// @param trimUser In tweets, giving only the ID of the author (true).
		/// @param longitude For geolocation, your longitude.
		/// @param latitude For geolocation, your latitude.
		/// @param reversePlace For geolocation, ID of the place where the tweet
		/// is supposed to be sent
		/// @param displayCoord Displaying the coordonates of the tweet
		/// with a pin on a map
		void postTweetViaTwitLonger(QString tweet,
									qlonglong replyToTweetID = -1,
									QString replyToUser = "",
									bool trimUser = false,
									float latitude = -361,
									float longitude = -361,
									QString reversePlace = "",
									bool displayCoord = false);

		/// @fn void postTweetViaTwitLonger(QString tweet,
		///									QString replyToTweetID = "-1",
		///									QString replyToUser = "",
		///									bool trimUser = false,
		///									float latitude = -361,
		///									float longitude = -361,
		///									QString reversePlace = "",
		///									bool displayCoord = false);
		/// @brief Posting a tweet via TwitLonger
		/// @param tweet Text of the tweet
		/// @param replyToTweetID If the tweet is a reply, this parameter is
		/// the ID of the tweet that this tweet replies to.
		/// @param replyToUser If the tweet is a reply, this parameter is
		/// the screen name of the tweet that this tweet replies to.
		/// @param trimUser In tweets, giving only the ID of the author (true).
		/// @param longitude For geolocation, your longitude.
		/// @param latitude For geolocation, your latitude.
		/// @param reversePlace For geolocation, ID of the place where the tweet
		/// is supposed to be sent
		/// @param displayCoord Displaying the coordonates of the tweet
		/// with a pin on a map
		void postTweetViaTwitLonger(QString tweet,
									QString replyToTweetID = "-1",
									QString replyToUser = "",
									bool trimUser = false,
									float latitude = -361,
									float longitude = -361,
									QString reversePlace = "",
									bool displayCoord = false);

		/// @fn void retweet(qlonglong tweetID, bool trimUser = false);
		/// @brief Reweeting a tweet
		/// @param tweetID ID of the tweet to retweet
		/// @param trimUser In tweets, giving only the ID of the author (true).
		/// @see https://dev.twitter.com/docs/api/1.1/post/statuses/retweet/%3Aid
		void retweet(qlonglong tweetID, bool trimUser = false);

		/// @fn void deleteTweet(Tweet tweetToDelete,
		///						 bool trimUser = false);
		/// @brief Deleting a tweet
		/// @param tweetToDelete The tweet to delete
		/// @param trimUser In tweets, giving only the ID of the author (true).
		/// @see https://dev.twitter.com/docs/api/1.1/post/statuses/destroy/%3Aid
		void deleteTweet(Tweet tweetToDelete,
						 bool trimUser = false);

		/// @fn void getTweet(qlonglong tweetID,
		///					  bool trimUser = false,
		///					  bool includeEntities = true,
		///					  bool includeMyRetweet = true);
		/// @brief Getting a tweet with a given ID.
		/// @param tweetID ID of the tweet to retweet
		/// @param trimUser In tweets, giving only the ID of the author (true).
		/// @param includeEntities Including Tweet Entities in the tweets (true).
		/// @param includeMyRetweet If the user retweeted the tweet and if this
		/// boolean is set to true, this would include the id of the retweet.
		/// @see https://dev.twitter.com/docs/api/1.1/get/statuses/show/%3Aid
		void getTweet(qlonglong tweetID,
					  bool trimUser = false,
					  bool includeEntities = true,
					  bool includeMyRetweet = true);
};

#endif // REYNCORE_HPP
