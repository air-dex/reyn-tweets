#ifndef LAUNCHINGCONTROL_HPP
#define LAUNCHINGCONTROL_HPP

#include <QObject>
#include "reyncore.hpp"

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

		/// @fn void launchOK(CoreResult launchOK);
		/// @brief Slot executed at the end of the launch process
		void loadOK(CoreResult loadOK);

		/// @fn void verifyTokensEnded(CoreResults verifyOK);
		/// @brief Slot executed after verifying credentials
		/// @param verifyOK How the verification ended
		void verifyTokensEnded(CoreResult verifyOK);

		/// @fn void saveOK(CoreResult saveOK);
		/// @brief Slot executed after saving the configuration
		void saveOK(CoreResult saveOK);

/*
		void endLaunch(CoreResult res);

		///////////////////////////////
		// Authentication management //
		///////////////////////////////

		/// @fn void authenticationRequired();
		/// @brief Slot executed if an authentication to Twitter is required
		/// for the application
		void authenticationRequired();

		/// @fn void endOAuthAuthenticationFlow(OAuthProcessResult processResult,
		///										QByteArray accessToken = "",
		///										QByteArray tokenSecret = "",
		///										qlonglong userID = -1,
		///										QString screenName = "");
		/// @brief Slot executed after an OAuth Authentication processus
		/// @param processResult Value indicating how the OAuth process has ended.
		/// @param accessToken User access token
		/// @param tokenSecret User token secret
		/// @param userID ID of the user who has just authorized the application
		/// @param screenName Screen name of the user who has just authorized
		/// the application.
		void endOAuthAuthenticationFlow(OAuthProcessResult processResult,
										QByteArray accessToken = "",
										QByteArray tokenSecret = "",
										qlonglong userID = -1,
										QString screenName = "");

		//////////////////////////////
		// Configuration management //
		//////////////////////////////
//*/
	protected:
		/// @brief Core of the application
		ReynCore reyn;

		/// @brief Launching informations
};

#endif // LAUNCHINGCONTROL_HPP
