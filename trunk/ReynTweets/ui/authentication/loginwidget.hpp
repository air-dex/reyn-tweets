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
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LOGINWIDGET_HPP
#define LOGINWIDGET_HPP

#include <QCheckBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

/// @class LoginWidget
/// @brief Widget asking to the user its name (or email) and its password to
/// authorize request tokens in the OAuth process.
class LoginWidget : public QWidget
{
	Q_OBJECT
	public:
		/// @fn LoginWidget(QWidget *parent = 0);
		/// @brief Constructor
		/// @param parent Parent widget
		LoginWidget(QWidget * parent = 0);

		/// @fn ~LoginWidget();
		/// @brief Destructor
		~LoginWidget();

		/// @fn QString getLogin();
		/// @brief Getter on the login (username or email) written by the user
		/// @return The login
		QString getLogin();

		/// @fn QString getPassword();
		/// @brief Getter on the password written by the user
		/// @return The password
		QString getPassword();

	signals:
		/// @fn void authorize();
		/// @brief Authorize the application
		void authorize();

		/// @fn void deny();
		/// @brief Deny the application
		void deny();

	public slots:
		/// @fn void showCredentialsErrorMessage(bool ok);
		/// @brief Signal sent to show or to hide an error message telling
		/// the user if the credentials he gave were right.
		/// @param ok Boolean indicating if the credentials sent to Twitter
		/// were right.
		void showCredentialsErrorMessage(bool ok);

	protected slots:
		/// @fn void showPassword(bool boxChecked);
		/// @brief Showing or hiding the password
		/// @param boxChecked Boolean indicating if passwordCheckBox is checked.
		void showPassword(bool boxChecked);

		/// @fn void authorizeReynTweets();
		/// @brief Authorize the application
		void authorizeReynTweets();

		/// @fn void denyReynTweets();
		/// @brief Deny the application
		void denyReynTweets();

	protected:
		// GUI Elements
		/// @brief Main layout of the widget
		QVBoxLayout widgetLayout;

		/// @brief Message for bad credentials
		QLabel credentialsErrorMessage;

		// Form for entering the credentials
		/// @brief Layout of the form
		QFormLayout formLayout;

		/// @brief LineEdit for the login field
		QLineEdit loginLineEdit;

		/// @brief LineEdit for the password field
		QLineEdit passwordLineEdit;

		/// @brief Checkbox to see the password while writing it.
		QCheckBox passwordCheckBox;

		// Buttons
		/// @brief Layout for the buttons
		QHBoxLayout buttonsLayout;

		/// @brief Button to authorize
		QPushButton authorizeButton;

		/// @brief Button to deny
		QPushButton denyButton;
};

#endif // LOGINWIDGET_HPP
