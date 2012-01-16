/// @file reyntwittercalls.hpp
/// @brief Header of ReynTwitterCalls
/// @author Romain Ducher

/*
Copyright 2011 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef REYNTWITTERCALLS_HPP
#define REYNTWITTERCALLS_HPP

#include <QObject>
#include <QMap>
#include <QUuid>
#include <QWebView>
#include "resultwrapper.hpp"
#include "requestermanager.hpp"
#include "requests/genericrequester.hpp"

/// @class ReynTwitterCalls
/// @brief ReynTwitterCalls is a class which manages calls to Twitter. It is a
/// singleton. To use it
class ReynTwitterCalls : public QObject
{
	Q_OBJECT

	//////////////////////////////////
	// Core management of the class //
	//////////////////////////////////

	public:
		/// @fn ReynTwitterCalls(QObject * requester);
		/// @brief Constructor
		/// @param requester Entity asking for the request
		ReynTwitterCalls(QObject * requester);

		/// @fn ~ReynTwitterCalls();
		/// @brief Destructor
		~ReynTwitterCalls();

	signals:
		/// @fn void sendResult(ResultWrapper res);
		/// @brief Signal emitted to the QObject that sends the request
		/// @param res Result of a request
		void sendResult(ResultWrapper res);

	public slots:
		/// @fn void endRequest();
		/// @brief Slot executed when a requester has finished its work
		void endRequest();

	protected:
		/// @brief QObject that asks for the request
		QObject * requestDemander;

		/// @brief Entity which manages requests that are running
		static RequesterManager requesterManager;

		/// @brief OAuth information
		static OAuthManager oauthManager;

	private:
		/// @fn void addRequester(GenericRequester * requester);
		/// @brief Adding a requester to the requester manager
		/// @param requester Address of the requester
		void addRequester(GenericRequester * requester);

		/// @fn void removeRequester(GenericRequester * requester);
		/// @brief Removing a requester of the requester manager
		/// @param requester Address of the requester
		void removeRequester(GenericRequester * requester);

		/// @fn ResultSender buildResultSender(GenericRequester * endedRequest);
		/// @brief Method that builds the wrapper of a result
		/// @param endedRequest Ended request that contaons the result
		/// @return The wrapper of the request result
		ResultWrapper buildResultSender(GenericRequester * endedRequest);

		/// @fn inline void executeRequest(GenericRequester * requester);
		/// @brief Inline method for executing requests
		/// @param requester The requester
		inline void executeRequest(GenericRequester * requester);


	/////////////////////////////
	// Methods calling Twitter //
	/////////////////////////////

	public:
		//////////////
		// Searches //
		//////////////

		/// @fn void search(QString q);
		/// @brief Method that launch searches
		/// @param q The query
		/// @see https://dev.twitter.com/docs/api/1/get/search
		void search(QString q);


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


		////////////
		// Tweets //
		////////////

		/// @fn void showTweet(long tweetID,
		///					   bool entities = true,
		///					   bool trimUser = false);
		/// @brief Showing a tweet
		/// @param tweetID ID of the tweet
		/// @param entities Include Tweet Entities in th reply ?
		/// @param trimUser Return only user IDs instead of all the values ?
		/// @see https://dev.twitter.com/docs/api/1/get/statuses/show/%3Aid
		void showTweet(long tweetID,
					   bool entities = true,
					   bool trimUser = false);


		///////////
		// Users //
		///////////

		/// @fn void showUser(long userID, bool entities = true);
		/// @brief Showing a user identified by its ID
		/// @param userID ID of the user
		/// @param entities Include Tweet Entities in th reply ?
		/// @see https://dev.twitter.com/docs/api/1/get/users/show
		void showUser(long userID, bool entities = true);

		/// @fn void void showUser(QString screenName, bool entities = true);
		/// @brief Showing a user identified by its screen name
		/// @param screenName User's screen name
		/// @param entities Include Tweet Entities in th reply ?
		/// @see https://dev.twitter.com/docs/api/1/get/users/show
		void showUser(QString screenName, bool entities = true);
};

#endif // REYNTWITTERCALLS_HPP
