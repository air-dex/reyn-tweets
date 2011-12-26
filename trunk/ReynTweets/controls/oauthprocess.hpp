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
#include <QWebView>
#include "../connection/reyntwittercalls.hpp"

/// @class OAuthProcess
/// @brief Class executing the OAuth authentication flow
class OAuthProcess : public QObject
{
	Q_OBJECT

	public:
		/// @fn OAuthProcess(QWebView & browser, QObject * parent);
		/// @brief Constructor
		/// @param browser Web view displaying authorization
		/// @param parent Parent object
		OAuthProcess(QWebView & browser, QObject * parent);

		/// @fn void startAuthentication();
		/// @brief Starting the OAuth authentication flow
		void startAuthentication();

		/// @fn void resetTokens();
		/// @brief Resetting the tokens. A full new OAuth authentication process
		/// has to be launch to get tokens and for authentication in requests
		void resetTokens();


	signals:
		/// @fn void browserVisible(bool visible);
		/// @brief Signal sent to show or to hide the browser
		/// @param visible Boolean indicating if the browser has to be visible.
		void browserVisible(bool visible);

		/// @fn void errorProcess(QString errorMsg, bool fatalError);
		/// @brief Signal emitted when an error occurs during the process
		/// @param errorMsg Message describing the error
		/// @param fatalError Boolean indicating if the error is fatal for
		/// the process.
		void errorProcess(QString errorMsg, bool fatalError);

		/// @fn void authenticationProcessFinished(bool authOK);
		/// @brief Signal sent when the authentication process ends.
		/// @param authOK Boolean indicating if the process was successful.
		void authenticationProcessFinished(bool authOK);

	public slots:
		/// @fn void requestTokenDemanded(ResultWrapper res);
		/// @brief Treatments after the request for Request Tokens
		/// @param res Result of the request
		void requestTokenDemanded(ResultWrapper res);

		/// @fn void authorizeDemanded(ResultWrapper res);
		/// @brief Treatments after the request for authorizing Request Tokens
		/// @param res Result of the request
		void authorizeDemanded(ResultWrapper res);

		/// @fn void accessTokenDemanded(ResultWrappers res);
		/// @brief Treatments after the request for Access Tokens
		/// @param res Result of the request
		void accessTokenDemanded(ResultWrapper res);

	protected:
		/// @brief Entity calling Twitter
		ReynTwitterCalls & twitterCalls;

		/// @brief Embedded Web browser to authorize Reyn Tweets
		QWebView & embeddedBrowser;

	private:
		/// @fn void requestToken();
		/// @brief Demanding a Request Token
		void requestToken();

		/// @fn void authorize();
		/// @brief Authorizing Reyn Tweets by displaying the Twitter
		/// authentication page.
		void authorize();

		/// @fn void accessToken();
		/// @brief Demanding an Access Token
		void accessToken();

};

#endif // OAUTHPROCESS_HPP
