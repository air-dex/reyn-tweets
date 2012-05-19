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

#include "genericcalls.hpp"
#include "../oauthmanager.hpp"

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
        static OAuthManager oauthManager;


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
        /// @see https://api.twitter.com/1/account/verify_credentials.json
        void verifyCredentials(bool entities, bool skipStatus);


        ///////////////
        // Favorites //
        ///////////////

        /// @fn void favoriteTweet(qlonglong id, bool entities = false);
        /// @brief Favoriting a tweet
        /// @param id ID of the tweet to favorite
        /// @param entities Boolean whose value is true if the tweet
        /// in the reply has got its entities
        /// @see https://dev.twitter.com/docs/api/1/post/favorites/create/%3Aid
        void favoriteTweet(qlonglong id, bool entities = false);

        /// @fn void getFavoriteTimeline(qlonglong id = -1,
        ///								 qlonglong sinceID = -1,
        ///								 bool entities = false,
        ///								 int page = 0,
        ///								 int count = 20);
        /// @brief Retrieving the timeline with the favorite tweets of the user
        /// whose ID is id.
        /// @param id ID of the user whose favorites timeline will be
        /// retrieved by the request.
        /// @param count Number of tweets in the timeline
        /// @param sinceID Minimum ID for a tweet possible in the timeline
        /// @param page Number of tweets page
        /// @param entities Boolean whose value is true if the tweets have got
        /// their entities
        /// @see https://dev.twitter.com/docs/api/1/get/favorites
        void getFavoriteTimeline(qlonglong id = -1,
                                 qlonglong sinceID = -1,
                                 bool entities = false,
                                 int page = 0,
                                 int count = 20);

        /// @fn void getFavoriteTimeline(QString id = "",
        ///								 qlonglong sinceID = -1,
        ///								 bool entities = false,
        ///								 int page = 0,
        ///								 int count = 20);
        /// @brief Retrieving the timeline with the favorite tweets of the user
        /// whose screen name is id.
        /// @param id Screen name of the user whose favorites timeline
        /// will be retrieved by the request.
        /// @param count Number of tweets in the timeline
        /// @param sinceID Minimum ID for a tweet possible in the timeline
        /// @param page Number of tweets page
        /// @param entities Boolean whose value is true if the tweets have got
        /// their entities
        /// @see https://dev.twitter.com/docs/api/1/get/favorites
        void getFavoriteTimeline(QString id = "",
                                 qlonglong sinceID = -1,
                                 bool entities = false,
                                 int page = 0,
                                 int count = 20);

        /// @fn void unfavoriteTweet(qlonglong id);
        /// @brief Unavoriting a tweet
        /// @param id ID of the tweet to unfavorite
        /// @see https://dev.twitter.com/docs/api/1/post/favorites/destroy/%3Aid
        void unfavoriteTweet(qlonglong id);


        ///////////
        // OAuth //
        ///////////

        /// @fn static void resetTokens();
        /// @brief Resetting the tokens. A full new OAuth authentication process
        /// has to be launch to get tokens and for authentication in requests
        static void resetTokens();

        /// @fn static void setNewTokens(QByteArray accessToken,
        ///								 QByteArray tokenSecret,
        ///								 QByteArray consumerKey = ReynTweetsSettings::CONSUMER_KEY,
        ///								 QByteArray consumerSecret = ReynTweetsSettings::CONSUMER_SECRET);
        /// @brief Giving new tokens to the oauthManager
        /// @param accessToken New access token
        /// @param tokenSecret New token secret
        /// @param consumerKey New consumer key
        /// @param consumerSecret New consumer secret
        static void setNewTokens(QByteArray accessToken,
                                 QByteArray tokenSecret,
                                 QByteArray consumerKey = ReynTweetsSettings::CONSUMER_KEY,
                                 QByteArray consumerSecret = ReynTweetsSettings::CONSUMER_SECRET);

        /// @fn void requestToken();
        /// @brief Method for getting a request token
        /// @see https://dev.twitter.com/docs/api/1/post/oauth/request_token
        void requestToken();

        /// @fn void authorize();
        /// @brief Method for authorizing request Tokens
        /// @see https://dev.twitter.com/docs/api/1/get/oauth/authorize
        void authorize();

        /// @fn void postAuthorize(QString login,
        ///						   QString password,
        ///						   bool deny);
        /// @brief POST authorize() requests to allow or to deny the application.
        /// @param login User login, i.e. its username or its email
        /// @param password User password
        /// @param deny Boolean indicating if the application must be denied
        /// (true) or authorized (false).
        void postAuthorize(QString login,
                           QString password,
                           bool deny);

        /// @fn void accessToken();
        /// @brief Method for getting an access token
        /// @see https://dev.twitter.com/docs/api/1/post/oauth/access_token
        void accessToken();


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

        /// @fn void retrieveHomeTimeline(qlonglong sinceID = -1,
        ///								  qlonglong maxID = -1,
        ///								  bool trimUser = false,
        ///								  bool includeRTS = false,
        ///								  bool includeEntities = false,
        ///								  bool excludeReplies = false,
        ///								  int page = 0,
        ///								  int count = 20,
        ///								  bool contributorsDetails = false);
        /// @brief Retrieving the timeline with the tweets of the user's friends
        /// @param sinceID Minimum tweet ID possible in the timeline
        /// @param maxID Maximum tweet ID possible in the timeline
        /// @param trimUser In tweets, giving only the ID of the author (true).
        /// @param includeRTS Including retweets
        /// @param includeEntities Including Tweet Entities in the tweets (true).
        /// @param excludeReplies Excluding the replies
        /// @param page Number of pages
        /// @param count Number of tweets
        /// @param contributorsDetails Including details about contributors
        /// @see https://dev.twitter.com/docs/api/1/get/statuses/home_timeline
        void retrieveHomeTimeline(qlonglong sinceID = -1,
                                  qlonglong maxID = -1,
                                  bool trimUser = false,
                                  bool includeRTS = false,
                                  bool includeEntities = false,
                                  bool excludeReplies = false,
                                  int page = 0,
                                  int count = 20,
                                  bool contributorsDetails = false);

        /// @fn void userRetweetsTimeline(qlonglong sinceID = -1,
        ///								  qlonglong maxID = -1,
        ///								  int count = 20,
        ///								  bool trimUser = false,
        ///								  bool includeEntities = false);
        /// @brief Retrieving the timeline with the tweets retweeted by the user
        /// @param sinceID Minimum tweet ID possible in the timeline
        /// @param maxID Maximum tweet ID possible in the timeline
        /// @param count Number of tweets
        /// @param trimUser In tweets, giving only the ID of the author (true).
        /// @param includeEntities Including Tweet Entities in the tweets (true).
        /// @see https://dev.twitter.com/docs/api/1/get/statuses/retweeted_by_me
        void userRetweetsTimeline(qlonglong sinceID = -1,
                                  qlonglong maxID = -1,
                                  int count = 20,
                                  bool trimUser = false,
                                  bool includeEntities = false);


        ////////////
        // Tweets //
        ////////////

        /// @fn void destroyTweet(qlonglong tweetID,
        ///						  bool entities = true,
        ///						  bool trimUser = false);
        /// @brief Destroying (deleting) a tweet
        /// @param tweetID ID of the tweet
        /// @param entities Include Tweet Entities in th reply ?
        /// @param trimUser Return only user IDs instead of all the values ?
        /// @see https://dev.twitter.com/docs/api/1/post/statuses/destroy/%3Aid
        void destroyTweet(qlonglong tweetID,
                          bool entities = true,
                          bool trimUser = false);

        /// @fn void retweet(qlonglong tweetID,
        ///					 bool entities = true,
        ///					 bool trimUser = false);
        /// @brief Retweeting a tweet
        /// @param tweetID ID of the tweet
        /// @param entities Include Tweet Entities in th reply ?
        /// @param trimUser Return only user IDs instead of all the values ?
        /// @see https://dev.twitter.com/docs/api/1/post/statuses/retweet/%3Aid
        void retweet(qlonglong tweetID,
                     bool entities = true,
                     bool trimUser = false);

        /// @fn void showTweet(qlonglong tweetID,
        ///					   bool entities = true,
        ///					   bool trimUser = false);
        /// @brief Showing a tweet
        /// @param tweetID ID of the tweet
        /// @param entities Include Tweet Entities in th reply ?
        /// @param trimUser Return only user IDs instead of all the values ?
        /// @see https://dev.twitter.com/docs/api/1/get/statuses/show/%3Aid
        void showTweet(qlonglong tweetID,
                       bool entities = true,
                       bool trimUser = false);

        /// @fn void updateTweet(QString tweet,
        ///						 qlonglong replyToTweetID,
        ///						 float latitude = -361,
        ///						 float longitude = -361,
        ///						 QString reversePlace = "",
        ///						 bool displayCoord = false,
        ///						 bool trimUser = false,
        ///						 bool includeEntities = false);
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
        /// @param includeEntities Including Tweet Entities in the tweets (true).
        /// @see https://dev.twitter.com/docs/api/1/post/statuses/update
        void updateTweet(QString tweet,
                         qlonglong replyToTweetID = -1,
                         float latitude = -361,
                         float longitude = -361,
                         QString reversePlace = "",
                         bool displayCoord = false,
                         bool trimUser = false,
                         bool includeEntities = false);


        ///////////
        // Users //
        ///////////

        /// @fn void showUser(qlonglong userID, bool entities = true);
        /// @brief Showing a user identified by its ID
        /// @param userID ID of the user
        /// @param entities Include Tweet Entities in th reply ?
        /// @see https://dev.twitter.com/docs/api/1/get/users/show
        void showUser(qlonglong userID, bool entities = true);

        /// @fn void void showUser(QString screenName, bool entities = true);
        /// @brief Showing a user identified by its screen name
        /// @param screenName User's screen name
        /// @param entities Include Tweet Entities in th reply ?
        /// @see https://dev.twitter.com/docs/api/1/get/users/show
        void showUser(QString screenName, bool entities = true);
};

#endif // REYNTWITTERCALLS_HPP
