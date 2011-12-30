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
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OAUTHPROCESS_HPP
#define OAUTHPROCESS_HPP

#include <QObject>
#include "oauthprocessresult.hpp"
#include "../connection/reyntwittercalls.hpp"

class OAuthProcess : public QObject
{
	Q_OBJECT

	public:
		/// @fn OAuthProcess(QObject * parent);
		/// @brief Constructor
		/// @param parent Parent object
		OAuthProcess(QObject * parent);

		/// @fn ~OAuthProcess();
		/// @brief Destructor
		~OAuthProcess();

		/// @fn void startAuthentication();
		/// @brief Starting the OAuth authentication flow
		void startAuthentication();

		/// @fn void resetTokens();
		/// @brief Resetting the tokens. A full new OAuth authentication process
		/// has to be launch to get tokens and for authentication in requests
		void resetTokens();


	signals:
		/// @fn void loginPanelVisible(bool visible);
		/// @brief Signal sent to show or to hide the browser
		/// @param visible Boolean indicating if the browser has to be visible.
		void loginPanelVisible(bool visible);

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
		void errorProcess(bool fatalError, QString errorMsg);

		/// @fn void authenticationProcessFinished(OAuthProcessResult processResult);
		/// @brief Signal sent when the authentication process ends.
		/// @param processResult Value indicating how the OAuth process has ended.
		void authenticationProcessFinished(OAuthProcessResult processResult);

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

		/// @fn void authorizeDemanded(ResultWrapper res);
		/// @brief Treatments after the POST authorizing request
		/// @param res Result of the request
		void postAuthorizeDemanded(ResultWrapper res);

		/// @fn void accessTokenDemanded(ResultWrappers res);
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
