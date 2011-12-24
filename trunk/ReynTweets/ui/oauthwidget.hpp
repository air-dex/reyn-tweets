/// @file oauthwidget.hpp
/// @brief Header of OAuthWidget
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

#ifndef OAUTHWIDGET_HPP
#define OAUTHWIDGET_HPP

#include <QWidget>
#include <QWebView>
#include "../connection/reyntwittercalls.hpp"

/// @class OAuthWidget
/// @brief Widget dealing with OAuth authentication.
class OAuthWidget : public QWidget
{
	Q_OBJECT

	public:
		/// @fn OAuthWidget(QWidget * parent = 0);
		/// @brief Constructor
		/// @param parent Parent widget
		OAuthWidget(QWidget * parent = 0);

		/// @fn void allowReynTweets();
		/// @brief Allowing Reyn Tweets to use your Twitter account
		void allowReynTweets();

	signals:
		/// @fn void authenticationFinished(bool authOK);
		/// @brief Signal sent when the authentication is finished
		/// @param authOK Boolean indicating whether the authentication was
		/// successful. (subject to change)
		void authenticationFinished(bool authOK);

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
		QWebView authorizePage;

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

#endif // OAUTHWIDGET_HPP
