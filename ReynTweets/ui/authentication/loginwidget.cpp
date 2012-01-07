/// @file loginwidget.cpp
/// @brief Implementation of LoginWidget
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

#include "loginwidget.hpp"

LoginWidget::LoginWidget(QWidget *parent) :
	QWidget(parent),
	widgetLayout(),
	credentialsErrorMessage(QObject::trUtf8("<strong style=\"color:red\">Username or password invalid. Try again.</strong>")),
	formLayout(),
	loginLineEdit(),
	passwordLineEdit(),
	passwordCheckBox(QObject::trUtf8("Show password")),
	buttonsLayout(),
	authorizeButton(QObject::trUtf8("Authorize")),
	denyButton(QObject::trUtf8("No thanks"))
{
	// Building the UI
	credentialsErrorMessage.setVisible(false);

	// Password form
	passwordLineEdit.setEchoMode(QLineEdit::Password);
	formLayout.addRow(QObject::trUtf8("Username or email:"), &loginLineEdit);
	formLayout.addRow(QObject::trUtf8("Password:"), &passwordLineEdit);
	passwordCheckBox.setTristate(false);
	formLayout.addRow(&passwordCheckBox);

	// Buttons
	buttonsLayout.addWidget(&authorizeButton);
	buttonsLayout.addWidget(&denyButton);

	// Widget
	widgetLayout.addWidget(&credentialsErrorMessage);
	widgetLayout.addLayout(&formLayout);
	widgetLayout.addLayout(&buttonsLayout);
	setLayout(&widgetLayout);


	// Wiring

	// Showing or hiding the password while writing it.
	connect(&passwordCheckBox, SIGNAL(toggled(bool)),
			this, SLOT(showPassword(bool)));

	// Authorizing or denying the application
	connect(&authorizeButton, SIGNAL(clicked()),
			this, SLOT(authorizeReynTweets()));
	connect(&denyButton, SIGNAL(clicked()),
			this, SLOT(denyReynTweets()));
}

// Destructor
LoginWidget::~LoginWidget() {
	// Unwiring

	// Showing or hiding the password while writing it.
	disconnect(&passwordCheckBox, SIGNAL(toggled(bool)),
			   this, SLOT(showPassword(bool)));

	// Authorizing or denying the application
	disconnect(&authorizeButton, SIGNAL(clicked()),
			   this, SLOT(authorizeReynTweets()));
	disconnect(&denyButton, SIGNAL(clicked()),
			   this, SLOT(denyReynTweets()));
}

// Getter on the login (username or email) written by the user
QString LoginWidget::getLogin() {
	return loginLineEdit.text();
}

// Getter on the password written by the user
QString LoginWidget::getPassword() {
	return passwordLineEdit.text();
}

// Authorize the application
void LoginWidget::authorizeReynTweets() {
	emit authorize();
}

// Deny the application
void LoginWidget::denyReynTweets() {
	emit deny();
}

// Showing or hiding the password
void LoginWidget::showPassword(bool boxChecked) {
	QLineEdit::EchoMode newEchoMode;

	if (boxChecked) {
		newEchoMode = QLineEdit::Normal;
	} else {
		newEchoMode = QLineEdit::Password;
	}

	passwordLineEdit.setEchoMode(newEchoMode);
}

// Showing or hidding the credentials error message.
void LoginWidget::showCredentialsErrorMessage(bool ok) {
	credentialsErrorMessage.setVisible(!ok);
}
