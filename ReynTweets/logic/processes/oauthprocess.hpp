/// @file oauthprocess.hpp
/// @brief Header of OAuthProcess
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

#ifndef OAUTHPROCESS_HPP
#define OAUTHPROCESS_HPP

#include "genericprocess.hpp"
#include "oauthprocessresult.hpp"
#include "../connection/reyntwittercalls.hpp"

/// @class OAuthProcess
/// @brief Controller for the execution of the Twitter's OAuth Authentication Flow
class OAuthProcess : public GenericProcess
{
	Q_OBJECT

	public:
		/// @fn OAuthProcess();
		/// @brief Constructor
		OAuthProcess();

		/// @fn ~OAuthProcess();
		/// @brief Destructor
		~OAuthProcess();

		/// @fn void startProcess();
		/// @brief Starting the OAuth Authentication flow
		void startProcess();

		/// @fn void resetTokens();
		/// @brief Resetting the tokens. A full new OAuth authentication process
		/// has to be launch to get tokens and for authentication in requests
		void resetTokens();


	signals:
		/// @fn void userCredentialsNeeded();
		/// @brief Signal sent when the process requires user credentials
		void userCredentialsRequired();

		/// @fn void loginPanelVisible(bool visible);
		/// @brief Signal sent to show or to hide the browser
		/// @param visible Boolean indicating if the browser has to be visible.
		void loginPanelVisible(bool visible);	// DEPRECATED

		/// @fn void credentialsOK(bool ok);
		/// @brief Signal sent to show or to hide an error message telling
		/// the user if the credentials he gave were right.
		/// @param ok Boolean indicating if the credentials sent to Twitter
		/// were right.
		void credentialsOK(bool ok);

		/// @fn void errorProcess(bool fatalError, QString errorMsg);
		/// @brief Signal emitted when an error occurs during the process
		/// @param fatalError Boolean indicating if the error is fatal for
		/// the process.
		/// @param errorMsg Message describing the error
		void errorProcess(bool fatalError, QString errorMsg);	// DEPRECATED

		/// @fn void authenticationProcessFinished(OAuthProcessResult processResult,
		///										   QByteArray accessToken = "",
		///										   QByteArray tokenSecret = "",
		///										   qlonglong userID = -1,
		///										   QString screenName = "");
		/// @brief Signal sent when the authentication process ends.
		/// @param processResult Value indicating how the OAuth process has ended.
		/// @param accessToken User access token
		/// @param tokenSecret User token secret
		/// @param userID ID of the user who has just authorized the application
		/// @param screenName Screen name of the user who has just authorized
		/// the application.
		void authenticationProcessFinished(OAuthProcessResult processResult,
										   QByteArray accessToken = "",
										   QByteArray tokenSecret = "",
										   qlonglong userID = -1,
										   QString screenName = "");	// DEPRECATED

	private:
		/// @fn void requestToken();
		/// @brief Demanding a Request Token
		void requestToken();

		/// @fn void authorize();
		/// @brief Authorize the request tokens
		void authorize();

		/// @fn void accessToken();
		/// @brief Demanding an Access Token
		void accessToken();

	protected:
		virtual void buildResult(bool processOK,
								 CoreResult issue,
								 QString errMsg = "",
								 bool isFatal = false,
								 QByteArray accessToken = "",
								 QByteArray tokenSecret = "",
								 qlonglong userID = -1,
								 QString screenName = "");


	public slots:
		/////////////////////////
		// Requests to Twitter //
		/////////////////////////

		/// @fn void requestTokenDemanded(ResultWrapper res);
		/// @brief Treatments after the request for Request Tokens
		/// @param res Result of the request
		void requestTokenDemanded(ResultWrapper res);

		/// @fn void authorizeDemanded(ResultWrapper res);
		/// @brief Treatments after the request for authorizing Request Tokens
		/// @param res Result of the request
		void authorizeDemanded(ResultWrapper res);

		/// @fn void postAuthorizeDemanded(ResultWrapper res);
		/// @brief Treatments after the POST authorizing request
		/// @param res Result of the request
		void postAuthorizeDemanded(ResultWrapper res);

		/// @fn void accessTokenDemanded(ResultWrapper res);
		/// @brief Treatments after the request for Access Tokens
		/// @param res Result of the request
		void accessTokenDemanded(ResultWrapper res);


		//////////////////////////
		// OAuthWidget requests //
		//////////////////////////

		/// @fn void authorizeReynTweets(QString login, QString password);
		/// @brief Slot executed to allow Reyn Tweets to use the Twitter account :).
		/// @param login User login, i.e. its username or its email.
		/// @param password User password
		void authorizeReynTweets(QString login, QString password);

		/// @fn void denyReynTweets(QString login, QString password);
		/// @brief Slot executed to deny Reyn Tweets to use the Twitter account :(.
		/// @param login User login, i.e. its username or its email.
		/// @param password User password
		void denyReynTweets(QString login, QString password);


	protected:
		/// @brief Entity calling Twitter
		ReynTwitterCalls twitter;
};

#endif // OAUTHPROCESS_HPP
