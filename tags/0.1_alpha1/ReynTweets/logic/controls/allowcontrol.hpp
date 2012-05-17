/// @file allowcontrol.hpp
/// @brief Header of AllowControl
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

#ifndef ALLOWCONTROL_HPP
#define ALLOWCONTROL_HPP

#include "genericcontrol.hpp"
#include "logincontrol.hpp"

/// @class AllowControl
/// @brief Control behind a LoginComponent
class AllowControl : public GenericControl
{
    Q_OBJECT

    public:
        /// @fn AllowControl();
        /// @brief Constructor
        AllowControl();

        /// @fn static void declareQML();
        /// @brief Declaring to the QML system
        static void declareQML();

        /// @fn Q_INVOKABLE void allowReynTweets();
        /// @brief Allowing Reyn Tweets to use a Twitter Account
        Q_INVOKABLE void allowReynTweets();

        /// @fn LoginControl * getLoginControl();
        /// @brief Reading the login_control property
        /// @return control
        LoginControl * getLoginControl();

        /// @fn void setLoginControl(LoginControl * ctrl);
        /// @brief Writing the login_control property
        /// @param ctrl New value for control
        void setLoginControl(LoginControl * ctrl);


    signals:
        /// @fn void showLoginPopup(bool popupVisible);
        /// @brief Signal sent to modify the visibility of the popup used to
        /// ask the user to give its credentials.
        /// @param popupVisible Boolean indicating if the popup has to be
        /// shown or hidden.
        void showLoginPopup(bool popupVisible);


    protected slots:
        /// @fn void validCredentials(bool valid);
        /// @brief Slot executed when reyn tells the control if the credentials
        /// given by the user were right.
        /// @param valid Boolean whose value is true if the credentials are OK.
        void validCredentials(bool valid);

        /// @fn void credentialsNeeded();
        /// @brief Slot executed when reyn tells the control that it needs
        /// user credentials.
        void credentialsNeeded();

        /// @fn void allowOK(ProcessWrapper res);
        /// @brief Slot executed after an authentication, if needed.
        /// @param res The process result
        void allowOK(ProcessWrapper res);

    protected:
        /// @property login_control
        /// @brief Control behind the authentication popup
        Q_PROPERTY(LoginControl * login_control
                   READ getLoginControl
                   WRITE setLoginControl)

        /// @brief Value behind login_control property
        LoginControl * control;

    private:
        /// @fn void allowWiring();
        /// @brief Wiring for authentication process
        void allowWiring();

        /// @fn void allowUnwiring();
        /// @brief Disconnect what was connected while executing
        /// <code>allowWiring();</code>.
        void allowUnwiring();
};

#endif // ALLOWCONTROL_HPP
