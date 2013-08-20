/// @file reyntwittercalls.hpp
/// @brief Header of ReynTwitterCalls
///
/// SVN revisions of this file that are older than r412 are in the folder
/// /trunk/ReynTweets/connection.
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

#ifndef REYNTWITTERCALLS_HPP
#define REYNTWITTERCALLS_HPP

#include "../common/calls/genericcalls.hpp"
#include "twitterauthenticator.hpp"
#include "twitterconstants.hpp"

/// @class ReynTwitterCalls
/// @brief ReynTwitterCalls is a class which manages calls to Twitter.
class ReynTwitterCalls : public GenericCalls
{
	Q_OBJECT

	public:
		/// @fn ReynTwitterCalls(QObject * requester);
		/// @brief Constructor
		/// @param requester Entity asking for the request
		ReynTwitterCalls(QObject * requester);

		/// @fn ~ReynTwitterCalls();
		/// @brief Destructor
		~ReynTwitterCalls();

	protected:
		/// @brief OAuth information
		static TwitterAuthenticator oauthManager;


	/////////////////////////////
	// Methods calling Twitter //
	/////////////////////////////

	public:
		//////////////
		// Accounts //
		//////////////

		/// @fn void verifyCredentials(bool entities, bool skipStatus);
		/// @brief Verifying credentials
		/// @param entities Include Tweet Entities in th reply ?
		/// @param skipStatus Include the last tweet written by the user ?
		/// @see https://api.twitter.com/1.1/account/verify_credentials.json
		void verifyCredentials(bool entities, bool skipStatus);


		///////////////
		// Favorites //
		///////////////

		/// @fn void favoriteTweet(qlonglong id, bool entities = true);
		/// @brief Favoriting a tweet
		/// @param id ID of the tweet to favorite
		/// @param entities Boolean whose value is true if the tweet
		/// in the reply has got its entities
		/// @see https://dev.twitter.com/docs/api/1.1/post/favorites/create
		void favoriteTweet(qlonglong id, bool entities = true);

		/// @fn void getFavoriteTimeline(qlonglong id = Twitter::FAKE_USER_ID,
		///								 qlonglong sinceID = Twitter::FAKE_TWEET_ID,
		///								 qlonglong maxID = Twitter::FAKE_TWEET_ID,
		///								 bool entities = false,
		///								 int count = Twitter::DEFAULT_TWEETS_COUNT);
		/// @brief Retrieving the timeline with the favorite tweets of the user
		/// whose ID is id.
		/// @param id ID of the user whose favorites timeline will be
		/// retrieved by the request.
		/// @param count Number of tweets in the timeline
		/// @param sinceID Minimum ID for a tweet possible in the timeline
		/// @param maxID Maximum tweet ID possible in the timeline
		/// @param entities Boolean whose value is true if the tweets have got
		/// their entities
		/// @see https://dev.twitter.com/docs/api/1.1/get/favorites
		void getFavoriteTimeline(qlonglong id = Twitter::FAKE_USER_ID,
								 qlonglong sinceID = Twitter::FAKE_TWEET_ID,
								 qlonglong maxID = Twitter::FAKE_TWEET_ID,
								 bool entities = false,
								 int count = Twitter::DEFAULT_TWEETS_COUNT);

		/// @fn void getFavoriteTimeline(QString username = Twitter::FAKE_SCREEN_NAME,
		///								 qlonglong sinceID = Twitter::FAKE_TWEET_ID,
		///								 qlonglong maxID = Twitter::FAKE_TWEET_ID,
		///								 bool entities = false,
		///								 int count = Twitter::DEFAULT_TWEETS_COUNT);
		/// @brief Retrieving the timeline with the favorite tweets of the user
		/// whose screen name is username.
		/// @param username Screen name of the user whose favorites timeline
		/// will be retrieved by the request.
		/// @param count Number of tweets in the timeline
		/// @param sinceID Minimum ID for a tweet possible in the timeline
		/// @param maxID Maximum tweet ID possible in the timeline
		/// @param entities Boolean whose value is true if the tweets have got
		/// their entities
		/// @see https://dev.twitter.com/docs/api/1.1/get/favorites
		void getFavoriteTimeline(QString username = Twitter::FAKE_SCREEN_NAME,
								 qlonglong sinceID = Twitter::FAKE_TWEET_ID,
								 qlonglong maxID = Twitter::FAKE_TWEET_ID,
								 bool entities = false,
								 int count = Twitter::DEFAULT_TWEETS_COUNT);

		/// @fn void unfavoriteTweet(qlonglong id, bool entities = true);
		/// @brief Unavoriting a tweet
		/// @param id ID of the tweet to unfavorite
		/// @param entities Including Tweet Entities in the favorited (true).
		/// @see https://dev.twitter.com/docs/api/1.1/post/favorites/destroy
		void unfavoriteTweet(qlonglong id, bool entities = true);


		///////////
		// OAuth //
		///////////

		/// @fn static void resetTokens();
		/// @brief Resetting the tokens. A full new OAuth authentication process
		/// has to be launch to get tokens and for authentication in requests
		static void resetTokens();

		/// @fn static void setUserTokens(QByteArray accessToken,
		///								  QByteArray tokenSecret);
		/// @brief Setting new OAuth access tokens in the TwitterAuthenticator
		/// to connect to Twitter
		/// @param accessToken New access token
		/// @param tokenSecret New token secret
		static void setUserTokens(QByteArray accessToken,
								  QByteArray tokenSecret);

		/// @fn static void setAppTokens(QByteArray consumerKey,
		///								 QByteArray consumerSecret,
		///								 QString callbackURL);
		/// @brief Setting new OAuth consumer credentials and callback URL
		/// in the TwitterAuthenticator to connect to Twitter.
		/// @param consumerKey New consumer key
		/// @param consumerSecret New consumer secret
		/// @param callbackURL New callback URL
		static void setAppTokens(QByteArray consumerKey,
								 QByteArray consumerSecret,
								 QString callbackURL);

		/// @fn void requestToken();
		/// @brief Method for getting a request token
		/// @see https://dev.twitter.com/docs/api/1/post/oauth/request_token
		void requestToken();

		/// @fn void authorize(bool forceLogin = false,
		///					   QString writeLogin = Twitter::FAKE_SCREEN_NAME);
		/// @brief Method for authorizing request Tokens
		/// @param forceLogin Boolean indicating if the user as to sign in to
		/// Twitter to authorize the application. Quite useless in Reyn Tweets.
		/// @brief writeLogin Screen name of the user which want to authorize
		/// the app, in order to write it in the authentication page which will
		/// be returned. Quite useless in Reyn Tweets.
		/// @see https://dev.twitter.com/docs/api/1/get/oauth/authorize
		void authorize(bool forceLogin = false,
					   QString writeLogin = Twitter::FAKE_SCREEN_NAME);

		/// @fn void accessToken(QByteArray verifier = LibRT::FAKE_TOKEN);
		/// @brief Method for getting an access token
		/// @param verifier The OAuth Verifier needed for getting Access tokens.
		/// @see https://dev.twitter.com/docs/api/1/post/oauth/access_token
		void accessToken(QByteArray verifier = LibRT::FAKE_TOKEN);


		//////////////
		// Searches //
		//////////////

		/// @fn void search(QString q);
		/// @brief Method that launch searches
		/// @param q The query
		/// @see https://dev.twitter.com/docs/api/1/get/search
		void search(QString q);


		///////////////
		// Timelines //
		///////////////

		/// @fn void retrieveHomeTimeline(qlonglong sinceID = Twitter::FAKE_TWEET_ID,
		///								  qlonglong maxID = Twitter::FAKE_TWEET_ID,
		///								  bool trimUser = false,
		///								  bool includeEntities = false,
		///								  bool excludeReplies = false,
		///								  int count = Twitter::DEFAULT_TWEETS_COUNT,
		///								  bool contributorsDetails = false);
		/// @brief Retrieving the timeline with the tweets of the user's friends
		/// @param sinceID Minimum tweet ID possible in the timeline
		/// @param maxID Maximum tweet ID possible in the timeline
		/// @param trimUser In tweets, giving only the ID of the author (true).
		/// @param includeEntities Including Tweet Entities in the tweets (true).
		/// @param excludeReplies Excluding the replies
		/// @param count Number of tweets
		/// @param contributorsDetails Including details about contributors
		/// @see https://dev.twitter.com/docs/api/1.1/get/statuses/home_timeline
		void retrieveHomeTimeline(qlonglong sinceID = Twitter::FAKE_TWEET_ID,
								  qlonglong maxID = Twitter::FAKE_TWEET_ID,
								  bool trimUser = false,
								  bool includeEntities = false,
								  bool excludeReplies = false,
								  int count = Twitter::DEFAULT_TWEETS_COUNT,
								  bool contributorsDetails = false);

		/// @fn void retrieveMentionsTimeline(qlonglong sinceID = Twitter::FAKE_TWEET_ID,
		///									  qlonglong maxID = Twitter::FAKE_TWEET_ID,
		///									  bool trimUser = false,
		///									  bool includeEntities = false,
		///									  int count = Twitter::DEFAULT_TWEETS_COUNT,
		///									  bool contributorsDetails = false);
		/// @brief Retrieving the timeline containing the mentions of the user
		/// @param sinceID Minimum tweet ID possible in the timeline
		/// @param maxID Maximum tweet ID possible in the timeline
		/// @param trimUser In tweets, giving only the ID of the author (true).
		/// @param includeEntities Including Tweet Entities in the tweets (true).
		/// @param count Number of tweets
		/// @param contributorsDetails Including details about contributors
		/// @see https://dev.twitter.com/docs/api/1.1/get/statuses/mentions_timeline
		void retrieveMentionsTimeline(qlonglong sinceID = Twitter::FAKE_TWEET_ID,
									  qlonglong maxID = Twitter::FAKE_TWEET_ID,
									  bool trimUser = false,
									  bool includeEntities = false,
									  int count = Twitter::DEFAULT_TWEETS_COUNT,
									  bool contributorsDetails = false);


		////////////
		// Tweets //
		////////////

		/// @fn void destroyTweet(qlonglong tweetID,
		///						  bool trimUser = false);
		/// @brief Destroying (deleting) a tweet
		/// @param tweetID ID of the tweet
		/// @param trimUser Return only user IDs instead of all the values ?
		/// @see https://dev.twitter.com/docs/api/1.1/post/statuses/destroy/%3Aid
		void destroyTweet(qlonglong tweetID,
						  bool trimUser = false);

		/// @fn void retweet(qlonglong tweetID, bool trimUser = false);
		/// @brief Retweeting a tweet
		/// @param tweetID ID of the tweet
		/// @param trimUser Return only user IDs instead of all the values ?
		/// @see https://dev.twitter.com/docs/api/1.1/post/statuses/retweet/%3Aid
		void retweet(qlonglong tweetID, bool trimUser = false);

		/// @fn void showTweet(qlonglong tweetID,
		///					   bool entities = true,
		///					   bool trimUser = false,
		///					   bool includeMyRetweet = true);
		/// @brief Showing a tweet
		/// @param tweetID ID of the tweet
		/// @param entities Include Tweet Entities in th reply ?
		/// @param trimUser Return only user IDs instead of all the values ?
		/// @param includeMyRetweet If set to true and if the user retweeted
		/// the tweet, including the user's retweet ID.
		/// @see https://dev.twitter.com/docs/api/1.1/get/statuses/show/%3Aid
		void showTweet(qlonglong tweetID,
					   bool entities = true,
					   bool trimUser = false,
					   bool includeMyRetweet = true);

		/// @fn void updateTweet(QString tweet,
		///						 qlonglong replyToTweetID = Twitter::FAKE_TWEET_ID,
		///						 float latitude = LibRT::FAKE_LATITUDE,
		///						 float longitude = LibRT::FAKE_LONGITUDE,
		///						 QString reversePlace = Twitter::FAKE_PLACE_ID,
		///						 bool displayCoord = false,
		///						 bool trimUser = false);
		/// @brief Posting a tweet without media
		/// @param tweet Text of the tweet
		/// @param replyToTweetID If the tweet is a reply, this parameter is
		/// the ID of the tweet that this tweet replies to.
		/// @param latitude For geolocation, your longitude.
		/// @param longitude For geolocation, your latitude.
		/// @param reversePlace For geolocation, ID of the place where the tweet
		/// is supposed to be sent
		/// @param displayCoord Displaying the coordonates of the tweet
		/// with a pin on a map
		/// @param trimUser In tweets, giving only the ID of the author (true).
		/// @see https://dev.twitter.com/docs/api/1.1/post/statuses/update
		void updateTweet(QString tweet,
						 qlonglong replyToTweetID = Twitter::FAKE_TWEET_ID,
						 float latitude = LibRT::FAKE_LATITUDE,
						 float longitude = LibRT::FAKE_LONGITUDE,
						 QString reversePlace = Twitter::FAKE_PLACE_ID,
						 bool displayCoord = false,
						 bool trimUser = false);


		///////////
		// Users //
		///////////

		/// @fn void showUser(qlonglong userID, bool entities = true);
		/// @brief Showing a user identified by its ID
		/// @param userID ID of the user
		/// @param entities Include Tweet Entities in th reply ?
		/// @see https://dev.twitter.com/docs/api/1.1/get/users/show
		void showUser(qlonglong userID, bool entities = true);

		/// @fn void void showUser(QString screenName, bool entities = true);
		/// @brief Showing a user identified by its screen name
		/// @param screenName User's screen name
		/// @param entities Include Tweet Entities in th reply ?
		/// @see https://dev.twitter.com/docs/api/1.1/get/users/show
		void showUser(QString screenName, bool entities = true);
};

#endif // REYNTWITTERCALLS_HPP
