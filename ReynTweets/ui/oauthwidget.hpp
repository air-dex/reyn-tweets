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
#include "../controls/oauthprocess.hpp"

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

		/// @fn ~OAuthWidget();
		/// @brief Destructor
		~OAuthWidget();

		/// @fn void allowReynTweets();
		/// @brief Allowing Reyn Tweets to use your Twitter account
		void allowReynTweets();

	signals:
		/// @fn void startAuthentication();
		/// @brief Signal to send when authentication is started
		void startAuthentication();

		/// @fn void authenticationFinished(bool authOK);
		/// @brief Signal sent when the authentication is finished
		/// @param authOK Boolean indicating whether the authentication was
		/// successful. (subject to change)
		void authenticationFinished(bool authOK);

	public slots:
		/// @fn void browserVisible(bool visible);
		/// @brief Slot executing to show (or to hide) authorizePage
		/// @param visible Boolean indicating authorizePage has to be shown or
		/// has to be hidden.
		void browserVisible(bool visible);

		/// @fn void errorProcess(QString errorMsg, bool fatalError);
		/// @brief Signal emitted when an error occurs during the process
		/// @param errorMsg Message describing the error
		/// @param fatalError Boolean indicating if the error is fatal for
		/// the process.
		void errorProcess(QString errorMsg, bool fatalError);

		/// @fn void authorizeDemanded(ResultWrapper res);
		/// @brief Slot executing at the end of the authentication. It just
		/// sends the {@link #authenticationFinished(bool)} signal.
		/// @param authOK Boolean indicating whether the authentication was
		/// successful. (subject to change)
		void endAuthentication(bool authOK);

	protected:
		/// @brief Embedded Web browser to authorize Reyn Tweets
		QWebView authorizePage;

		/// @brief Entity calling Twitter
		OAuthProcess * oauthAuthenticationFlow;

	private:
		/// @fn void killOAuthProcess();
		/// @brief Killing the OAuth Authentication Flow
		void killOAuthProcess();
};

#endif // OAUTHWIDGET_HPP
