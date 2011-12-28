/// @file loginwidget.hpp
/// @brief Header of LoginWidget
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

#ifndef OAUTHWIDGET2_HPP
#define OAUTHWIDGET2_HPP

#include <QWidget>
#include <QVBoxLayout>
#include "loginwidget.hpp"
#include "../../controls/oauthprocess2.hpp"

class OAuthWidget2 : public QWidget
{
		Q_OBJECT
	public:
		/// @fn OAuthWidget(QWidget * parent = 0);
		/// @brief Constructor
		/// @param parent Parent widget
		OAuthWidget2(QWidget *parent = 0);

		/// @fn ~OAuthWidget();
		/// @brief Destructor
		~OAuthWidget2();

		/// @fn void allowReynTweets();
		/// @brief Allowing Reyn Tweets to use your Twitter account
		void allowReynTweets();

	signals:
		/// @fn void authorizeReynTweets(QString login, QString password);
		/// @brief Signal sent to allow Reyn Tweets to use the Twitter account :).
		/// @param login User login, i.e. its username or its email.
		/// @param password User password
		void authorizeReynTweets(QString login, QString password);

		/// @fn void denyReynTweets(QString login, QString password, QString denyString);
		/// @brief Signal sent to deny Reyn Tweets to use the Twitter account :(.
		/// @param login User login, i.e. its username or its email.
		/// @param password User password
		/// @param denyString String indicating that Reyn Tweets is not allowed.
		void denyReynTweets(QString login, QString password, QString denyString);

		/// @fn void authenticationFinished(bool authOK);
		/// @brief Signal sent when the authentication is finished
		/// @param authOK Boolean indicating whether the authentication was
		/// successful. (subject to change)
		void authenticationFinished(bool authOK);

	public slots:
		/// @fn void loginPanelVisible(bool visible);
		/// @brief Slot executing to show (or to hide) the login panel
		/// @param visible Boolean indicating if the login panel has to
		/// be shown or has to be hidden.
		void loginPanelVisible(bool visible);

		/// @fn void errorProcess(bool fatalError, QString errorMsg);
		/// @brief Signal emitted when an error occurs during the process
		/// @param fatalError Boolean indicating if the error is fatal for
		/// the process.
		/// @param errorMsg Message describing the error
		void errorProcess(bool fatalError, QString errorMsg);

		/// @fn void authorizeDemanded(ResultWrapper res);
		/// @brief Slot executing at the end of the authentication. It just
		/// sends the {@link #authenticationFinished(bool)} signal.
		/// @param authOK Boolean indicating whether the authentication was
		/// successful. (subject to change)
		void endAuthentication(bool authOK);

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
		/// @brief OAuth Authentication Flow
		OAuthProcess2 * authenticationFlow;

		/// @brief Login Widget
		LoginWidget loginWidget;

	private:
		/// @brief Layout of the widget
		QVBoxLayout layout;

		/// @fn void killOAuthProcess();
		/// @brief Killing the OAuth Authentication Flow
		void killOAuthProcess();
};

#endif // OAUTHWIDGET2_HPP
