#ifndef LAUNCHINGCONTROL_HPP
#define LAUNCHINGCONTROL_HPP

#include <QObject>
#include "logincontrol.hpp"
#include "../reyncore.hpp"

class LaunchingControl : public QObject
{
	Q_OBJECT

	public:
		/// @fn LaunchingControl();
		/// @brief Constructor
		LaunchingControl();

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();

		LoginControl getLoginControl();

		void setLoginControl(LoginControl ctrl);

		void wiring();
		void unwiring();

	signals:
		/// @fn void launchEnded(bool launchOK,
		///						 QString errorMsg = "",
		///						 bool isFatal = false);
		/// @brief Signal sent after launching
		void launchEnded(bool launchOK,
						 QString errorMsg = "",
						 bool isFatal = false);

	public slots:
		/// @fn void launchReynTweets();
		/// @brief Lauching Reyn Tweets
		void launchReynTweets();

		/// @fn void launchOK(ProcessWrapper res);
		/// @brief Slot executed at the end of the launch process
		void launchOK(ProcessWrapper res);

	protected:
		/// @brief Core of the application
		ReynCore reyn;

		Q_PROPERTY(LoginControl loginControl
				   READ getLoginControl
				   WRITE setLoginControl)

		/// @brief Launching informations
		LoginControl control;
};

#endif // LAUNCHINGCONTROL_HPP
