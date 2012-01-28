#include "logincontrol.hpp"
#include <QtDeclarative>

// Constructor
LoginControl::LoginControl() :
	QObject(),
	reyn()
{}

// Declaring to the QML components
void LoginControl::declareQML() {
	qmlRegisterType<LoginControl>("ReynTweetsControls",
									  0, 1,
									  "LoginControl");
}

// Warnig the user that the credentials were wrong
void LoginControl::wrongCredentials() {
	emit invalidCredentials();
}

void LoginControl::authorizeReynTweets(QString username, QString password) {
	emit authorize(username, password);
}

void LoginControl::denyReynTweets(QString username, QString password) {
	emit deny(username, password);
}
