/// @file logincontrol.cpp
/// @brief Implementation of LoginControl
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

#include "logincontrol.hpp"
#include <QtQml>

// Constructor
LoginControl::LoginControl() :
	QObject(),
	reyn(this)
{}

// Constructor
LoginControl::~LoginControl() {}

// Constructor
LoginControl::LoginControl(const LoginControl & control) :
	QObject(control.parent()),
	reyn(control.reyn)
{}

const LoginControl & LoginControl::operator=(const LoginControl & control) {
	setParent(control.parent());
	reyn = control.reyn;
	return *this;
}

// Declaring to the QML components
void LoginControl::declareQML() {
	qmlRegisterType<LoginControl>("ReynTweetsControls",
								  0, 2,
								  "LoginControl");
}

// Transmitting the will of authorize
void LoginControl::authorizeReynTweets(QString username, QString password) {
	emit authorize(username, password);
}

// Transmitting the will of deny
void LoginControl::denyReynTweets(QString username, QString password) {
	emit deny(username, password);
}

// Warning the user that the credentials were wrong
void LoginControl::wrongCredentials() {
	emit invalidCredentials();
}
