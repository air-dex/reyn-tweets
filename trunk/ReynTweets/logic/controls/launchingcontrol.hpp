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

	signals:
		/// @fn void launchEnded(bool launchOK,
		///						 QString errorMsg = "",
		///						 bool isFatal = false);
		/// @brief Signal sent after launching
		void launchEnded(bool launchOK,
						 QString errorMsg = "",
						 bool isFatal = false);

		/// @fn void showLoginPopup(bool popupVisible);
		/// @brief Signal sent to modify the visibility of the popup used to
		/// ask the user to give its credentials.
		/// @param popupVisible Boolean indicating if the popup has to be
		/// shown or hidden.
		void showLoginPopup(bool popupVisible);

	public slots:
		/// @fn void launchReynTweets();
		/// @brief Lauching Reyn Tweets
		void launchReynTweets();

		/// @fn void launchOK(ProcessWrapper res);
		/// @brief Slot executed at the end of the launch process
		void launchOK(ProcessWrapper res);

		void validCredentials(bool valid);

		/// @fn void allowOK(ProcessWrapper res);
		/// @brief Slot executed after an authentication, if needed.
		void allowOK(ProcessWrapper res);

		void credentialsNeeded();

	protected:
		/// @brief Core of the application
		ReynCore reyn;

		/// @property loginControl
		/// @brief Control behind the authentication popup
		Q_PROPERTY(LoginControl loginControl
				   READ getLoginControl
				   WRITE setLoginControl)

		/// @brief Launching informations
		LoginControl control;

	private:
		/// @fn void allowWiring();
		/// @brief Wiring for a potential authentication process
		void allowWiring();

		/// @fn void allowUnwiring();
		/// @brief Disconnect what was connected while executing
		/// <code>allowWiring();</code>.
		void allowUnwiring();

		/// @fn void allowReynTweets();
		/// @brief Allowing Reyn Tweets to use a Twitter Account
		void allowReynTweets();
};

#endif // LAUNCHINGCONTROL_HPP
