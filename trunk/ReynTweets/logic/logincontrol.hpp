#ifndef LOGINCONTROL_HPP
#define LOGINCONTROL_HPP

#include <QObject>
#include "reyncore.hpp"

class LoginControl : public QObject
{
		Q_OBJECT
	public:
		/// @fn LoginControl();
		/// @brief Constructor
		LoginControl();


		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

	signals:
		void invalidCredentials();
		void authorize(QString username, QString password);
		void deny(QString username, QString password);

	public slots:
		void wrongCredentials();
		void authorizeReynTweets(QString username, QString password);
		void denyReynTweets(QString username, QString password);

	protected:
		/// @brief Heart of Reyn Tweets
		ReynCore reyn;
};

#endif // LOGINCONTROL_HPP
