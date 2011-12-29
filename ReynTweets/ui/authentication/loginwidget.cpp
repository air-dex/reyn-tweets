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
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "loginwidget.hpp"

LoginWidget::LoginWidget(QWidget *parent) :
	QWidget(parent),
	widgetLayout(),
	formLayout(),
	loginLineEdit(),
	passwordLineEdit(),
	passwordCheckBox(QObject::tr("Show password")),
	buttonsLayout(),
	authorizeButton(QObject::tr("Authorize")),
	denyButton(QObject::tr("No thanks"))
{
	// Building the UI

	// Password form
	passwordLineEdit.setEchoMode(QLineEdit::Password);
	formLayout.addRow(QObject::tr("Username or email :"), &loginLineEdit);
	formLayout.addRow(QObject::tr("Password :"), &passwordLineEdit);
	passwordCheckBox.setTristate(false);
	formLayout.addRow(&passwordCheckBox);

	// Buttons
	buttonsLayout.addWidget(&authorizeButton);
	buttonsLayout.addWidget(&denyButton);

	// Widget
	widgetLayout.addLayout(&formLayout);
	widgetLayout.addLayout(&buttonsLayout);
	setLayout(&widgetLayout);


	// Wiring : showing or hiding the password while writing it.
	connect(&passwordCheckBox, SIGNAL(toggled(bool)),
			this, SLOT(showPassword(bool)));
}

// Destructor
LoginWidget::~LoginWidget() {
	disconnect(&passwordCheckBox, SIGNAL(toggled(bool)),
			   this, SLOT(showPassword(bool)));
}

// Getter on the login (username or email) written by the user
QString LoginWidget::getLogin() {
	return loginLineEdit.text();
}

// Getter on the password written by the user
QString LoginWidget::getPassword() {
	return passwordLineEdit.text();
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
