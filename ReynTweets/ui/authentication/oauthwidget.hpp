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
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OAUTHWIDGET_HPP
#define OAUTHWIDGET_HPP

#include <QWidget>
#include <QVBoxLayout>
#include "loginwidget.hpp"
#include "../../controls/oauthprocess.hpp"

/// @class OAuthWidget
/// @brief View for the OAuth process execution
class OAuthWidget : public QWidget
{
		Q_OBJECT
	public:
		/// @fn OAuthWidget(QWidget * parent = 0);
		/// @brief Constructor
		/// @param parent Parent widget
		OAuthWidget(QWidget *parent = 0);

		/// @fn ~OAuthWidget();
		/// @brief Destructor
		~OAuthWidget();

		/// @fn void allowReynTweets();
		/// @brief Allowing Reyn Tweets to use your Twitter account
		void allowReynTweets();

	signals:
		/// @fn void authorizeReynTweets(QString login, QString password);
		/// @brief Signal sent to allow Reyn Tweets to use the Twitter account :).
		/// @param login User login, i.e. its username or its email.
		/// @param password User password
		void authorizeReynTweets(QString login, QString password);

		/// @fn void denyReynTweets(QString login, QString password);
		/// @brief Signal sent to deny Reyn Tweets to use the Twitter account :(.
		/// @param login User login, i.e. its username or its email.
		/// @param password User password
		void denyReynTweets(QString login, QString password);

		/// @fn void authenticationFinished(OAuthProcessResult processResult);
		/// @brief Signal sent when the authentication is finished
		/// @param processResult Value indicating how the OAuth process has ended.
		void authenticationFinished(OAuthProcessResult processResult);

		/// @fn void credentialsOK(bool ok);
		/// @brief Signal sent to show or to hide an error message telling
		/// the user if the credentials he gave were right.
		/// @param ok Boolean indicating if the credentials sent to Twitter
		/// were right.
		void credentialsOK(bool ok);

	public slots:
		/// @fn void loginPanelVisible(bool visible);
		/// @brief Slot executing to show (or to hide) the login panel
		/// @param visible Boolean indicating if the login panel has to
		/// be shown or has to be hidden.
		void loginPanelVisible(bool visible);

		/// @fn void credentialsOK(bool ok);
		/// @brief Signal sent to show or to hide an error message telling
		/// the user if the credentials he gave were right.
		/// @param ok Boolean indicating if the credentials sent to Twitter
		/// were right.
		void rightCredentials(bool ok);

		/// @fn void errorProcess(bool fatalError, QString errorMsg);
		/// @brief Signal emitted when an error occurs during the process
		/// @param fatalError Boolean indicating if the error is fatal for
		/// the process.
		/// @param errorMsg Message describing the error
		void errorProcess(bool fatalError, QString errorMsg);

		/// @fn void endAuthentication(OAuthProcessResult processResult);
		/// @brief Slot executed at the end of the authentication.
		/// @param processResult Value indicating how the OAuth process has ended.
		void endAuthentication(OAuthProcessResult processResult);

	protected slots:
		/////////////////////
		// Launching Slots //
		/////////////////////

		/// @fn void launchAuthorize();
		/// @brief Internal Slot used to send the authorizeReynTweets signal.
		void launchAuthorize();

		/// @fn void launchDeny();
		/// @brief Internal Slot used to send the denyReynTweets signal.
		void launchDeny();

	protected:
		/// @brief OAuth Authentication Flow. It is this object that will
		/// execute the whole authentication process.
		OAuthProcess * authenticationFlow;

		/// @brief Login Widget
		LoginWidget loginWidget;

	private:
		/// @brief Layout of the widget
		QVBoxLayout layout;

		/// @fn void killOAuthProcess();
		/// @brief Killing the OAuth Authentication Flow
		void killOAuthProcess();
};

#endif // OAUTHWIDGET_HPP
