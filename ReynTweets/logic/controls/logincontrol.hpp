#ifndef LOGINCONTROL_HPP
#define LOGINCONTROL_HPP

#include <QObject>
#include <QVariant>
#include "reyncore.hpp"

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

		/// @fn LoginControl();
		/// @brief Constructor
		LoginControl(const LoginControl & control);

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

	signals:
		void showComponent();
		void invalidCredentials();
		void authorize(QString username, QString password);
		void deny(QString username, QString password);

	public slots:
		void credentialsNeeded();
		void validCredentials(bool valid);
		void authorizeReynTweets(QString username, QString password);
		void denyReynTweets(QString username, QString password);

	protected:
		/// @brief Heart of Reyn Tweets
		ReynCore reyn;
};

Q_DECLARE_METATYPE(LoginControl)

#endif // LOGINCONTROL_HPP
