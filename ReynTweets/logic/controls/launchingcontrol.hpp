/// @file launchingcontrol.hpp
/// @brief Header of LaunchingControl
///
/// Revisions of the file older than r204 are in /trunk/ReynTweets/controls
/// r204 is in /trunk/ReynTweets/logic
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
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

#ifndef LAUNCHINGCONTROL_HPP
#define LAUNCHINGCONTROL_HPP

#include <QObject>
#include "logincontrol.hpp"
#include "../reyncore.hpp"

/// @class LaunchingControl
/// @brief Control behind a LaunchingPane
class LaunchingControl : public QObject
{
	Q_OBJECT

	public:
		/// @fn LaunchingControl();
		/// @brief Constructor
		LaunchingControl();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

		/// @fn LoginControl * getLoginControl();
		/// @brief Reading the login_control property
		/// @return control
		LoginControl * getLoginControl();

		/// @fn void setLoginControl(LoginControl * ctrl);
		/// @brief Writing the login_control property
		/// @param ctrl New value for control
		void setLoginControl(LoginControl * ctrl);


	signals:
		/// @fn void launchEnded(bool launchOK,
		///						 QString errorMsg = "",
		///						 bool isFatal = false);
		/// @brief Signal sent after launching
		/// @param launchOK Did the launching process end successfully ?
		/// @param errorMsg Error message
		/// @param isFatal Did the launching process end with a fatal error ?
		void launchEnded(bool launchOK,
						 QString errorMsg,
						 bool isFatal);

		/// @fn void showLoginPopup(bool popupVisible);
		/// @brief Signal sent to modify the visibility of the popup used to
		/// ask the user to give its credentials.
		/// @param popupVisible Boolean indicating if the popup has to be
		/// shown or hidden.
		void showLoginPopup(bool popupVisible);


	public slots:
		/// @fn void launchReynTweets();
		/// @brief Lauching Reyn Tweets
		void launchReynTweets();

		/// @fn void validCredentials(bool valid);
		/// @brief Slot executed when reyn tells the control if the credentials
		/// given by the user were right.
		/// @param valid Boolean whose value is true if the credentials are OK.
		void validCredentials(bool valid);

		/// @fn void credentialsNeeded();
		/// @brief Slot executed when reyn tells the control that it needs
		/// user credentials.
		void credentialsNeeded();


	protected slots:
		/// @fn void launchOK(ProcessWrapper res);
		/// @brief Slot executed at the end of the launch process
		/// @param res The process result
		void launchOK(ProcessWrapper res);

		/// @fn void allowOK(ProcessWrapper res);
		/// @brief Slot executed after an authentication, if needed.
		/// @param res The process result
		void allowOK(ProcessWrapper res);

	protected:
		/// @brief Core of the application
		ReynCore reyn;

		/// @property loginControl
		/// @brief Control behind the authentication popup
		Q_PROPERTY(LoginControl * loginControl
				   READ getLoginControl
				   WRITE setLoginControl)

		/// @brief Value behind loginControl
		LoginControl * control;

	private:
		/// @fn void allowWiring();
		/// @brief Wiring for a potential authentication process
		void allowWiring();

		/// @fn void allowUnwiring();
		/// @brief Disconnect what was connected while executing
		/// <code>allowWiring();</code>.
		void allowUnwiring();

		/// @fn void allowReynTweets();
		/// @brief Allowing Reyn Tweets to use a Twitter Account
		void allowReynTweets();
};

#endif // LAUNCHINGCONTROL_HPP
