/// @file logincontrol.hpp
/// @brief Header of LoginControl
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

#ifndef LOGINCONTROL_HPP
#define LOGINCONTROL_HPP

#include <QObject>
#include <QVariant>
#include "../reyncore.hpp"

/// @class LoginControl
/// @brief Control behind a LoginPane
class LoginControl : public QObject
{
    Q_OBJECT

    public:
        /// @fn LoginControl();
        /// @brief Constructor
        LoginControl();

        /// @fn ~LoginControl();
        /// @brief Destructor
        ~LoginControl();

        /// @fn LoginControl(const LoginControl & control);
        /// @brief Copy constructor
        /// @param control Control to copy
        LoginControl(const LoginControl & control);

        /// @fn const LoginControl & operator =(const LoginControl & control);
        /// @brief Affectation
        /// @param control Control to copy
        /// @return The new value of the object
        const LoginControl & operator =(const LoginControl & control);

        /// @fn static void declareQML();
        /// @brief Declaring to the QML system
        static void declareQML();

    signals:
        /// @fn void invalidCredentials();
        /// @brief
        void invalidCredentials();

        /// @fn void authorize(QString username, QString password);
        /// @brief Signal sent by authorizeReynTweets();, when the LoginPane
        /// emits a signal to authorize Reyn Tweets
        /// @param username User login, that is its username or its email
        /// @param password User password
        void authorize(QString username, QString password);

        /// @fn void deny(QString username, QString password);
        /// @brief Signal sent by denyReynTweets();, when the LoginPane
        /// emits a signal to deny Reyn Tweets
        /// @param username User login, that is its username or its email
        /// @param password User password
        void deny(QString username, QString password);

    public slots:
        /// @fn void wrongCredentials();
        /// @brief Slot executed when reyn informs the control that
        /// the user credentials he gave to it were wrong.
        void wrongCredentials();

        /// @fn void authorizeReynTweets(QString username, QString password);
        /// @brief Slot executed when the LoginPane emits its signal
        /// to authorize Reyn Tweets.
        /// @param username User login, that is its username or its email
        /// @param password User password
        void authorizeReynTweets(QString username, QString password);

        /// @fn void denyReynTweets(QString username, QString password);
        /// @brief Slot executed when the LoginPane emits its signal
        /// to deny Reyn Tweets.
        /// @param username User login, that is its username or its email
        /// @param password User password
        void denyReynTweets(QString username, QString password);

    protected:
        /// @brief Heart of Reyn Tweets
        ReynCore reyn;
};

#endif // LOGINCONTROL_HPP
