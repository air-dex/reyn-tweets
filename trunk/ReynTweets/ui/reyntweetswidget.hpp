/// @file reyntweetswidget.hpp
/// @brief Header of ReynTweetsWidget
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

#ifndef REYNTWEETSWIDGET_HPP
#define REYNTWEETSWIDGET_HPP

#include <QMessageBox>
#include <QVBoxLayout>
#include <QWidget>
#include "ui/launchingwidget.hpp"
#include "ui/authentication/oauthwidget.hpp"
#include "../logic/reyncore.hpp"

/// @class ReynTweetsWidget
/// @brief Main Widget of Reyn Tweets.
class ReynTweetsWidget : public QWidget
{
	Q_OBJECT

	public:
		/// @fn ReynTweetsWidget();
		/// @brief Constructor
		ReynTweetsWidget();

		/// @fn ~ReynTweetsWidget();
		/// @brief Destructor
		~ReynTweetsWidget();

		/// @fn void startReynTweets();
		/// @brief Starting the application
		void startReynTweets();

	signals:

	public slots:
		/// @fn void verifyTokensEnded(CoreResults verifyOK);
		/// @brief Slot executed after verifying credentials
		/// @param verifyOK How the verification ended
		void verifyTokensEnded(CoreResult verifyOK);

		///////////////////////////////
		// Authentication management //
		///////////////////////////////

		/// @fn void authenticationRequired();
		/// @brief Slot executed if an authentication to Twitter is required
		/// for the application
		void authenticationRequired();

		/// @fn void endOAuthAuthenticationFlow(OAuthProcessResult processResult,
		///										QByteArray accessToken = "",
		///										QByteArray tokenSecret = "",
		///										qlonglong userID = -1,
		///										QString screenName = "");
		/// @brief Slot executed after an OAuth Authentication processus
		/// @param processResult Value indicating how the OAuth process has ended.
		/// @param accessToken User access token
		/// @param tokenSecret User token secret
		/// @param userID ID of the user who has just authorized the application
		/// @param screenName Screen name of the user who has just authorized
		/// the application.
		void endOAuthAuthenticationFlow(OAuthProcessResult processResult,
										QByteArray accessToken = "",
										QByteArray tokenSecret = "",
										qlonglong userID = -1,
										QString screenName = "");

		//////////////////////////////
		// Configuration management //
		//////////////////////////////

		/// @fn void launchOK(LaunchResult launchOK);
		/// @brief Slot executed at the end of the launch process
		void launchOK(CoreResult launchOK);

		/// @fn void saveOK(SaveConfResult saveOK);
		/// @brief Slot executed after saving the configuration
		void saveOK(CoreResult saveOK);

	protected:
		/// @brief Main controller
		ReynCore reyn;

		// UI components

		/// @brief Layout of the widget
		QVBoxLayout layout;

		/// @brief Widget for authentication
		OAuthWidget authenticationWidget;

		/// @brief Widget displayed while Reyn Tweets is launched
		LaunchingWidget launchingScreen;

		/// @brief Mock for "a normal execution"
		QLabel mock;

	private:
		/// @fn void criticalPopup(QString title, QString announce, QString problem);
		/// @brief Displaying a QMessageBox announcing a critical problem
		/// @param title Title of the popup
		/// @param announce Announcing what happened
		/// @param problem Description of the problem
		void criticalPopup(QString title, QString announce, QString problem);

		/// @fn QMessageBox::StandardButton questionPopup(QString title,
		///												  QString announce,
		///												  QString question);
		/// @brief Displaying a QMessageBox for asking a question
		/// @param title Title of the popup
		/// @param announce Announcing what happened
		/// @param question Question asked in the popup
		/// @return Yes or No, depending on where the user will click
		QMessageBox::StandardButton questionPopup(QString title,
												  QString announce,
												  QString question);
};

#endif // REYNTWEETSWIDGET_HPP
