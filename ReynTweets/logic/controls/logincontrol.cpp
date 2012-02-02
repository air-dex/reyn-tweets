#include "logincontrol.hpp"
#include <QtDeclarative>

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
								  0, 1,
								  "LoginControl");
}

// Warning the user that the credentials were wrong
void LoginControl::wrongCredentials() {
	emit invalidCredentials();
}

void LoginControl::authorizeReynTweets(QString username, QString password) {
	emit authorize(username, password);
}

void LoginControl::denyReynTweets(QString username, QString password) {
	emit deny(username, password);
}
