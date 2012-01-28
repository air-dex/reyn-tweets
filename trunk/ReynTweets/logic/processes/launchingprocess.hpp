#ifndef LAUNCHINGPROCESS_HPP
#define LAUNCHINGPROCESS_HPP

#include "genericprocess.hpp"
#include "../../model/configuration/reyntweetsconfiguration.hpp"
#include "../../connection/reyntwittercalls.hpp"
#include "../coreresult.hpp"

/// @class LaunchingProcess
/// @brief Process executed to launch the application
class LaunchingProcess : public GenericProcess
{
		Q_OBJECT
	public:
		LaunchingProcess(ReynTweetsConfiguration & conf);

		void startProcess();

		/// @fn void loadConfiguration();
		/// @brief Loading the configuartion from the configuration file
		void loadConfiguration();

		/// @fn void updateConfAfterAuth(QByteArray accessToken = "",
		///								 QByteArray tokenSecret = "",
		///								 qlonglong id,
		///								 QString screenName);
		/// @brief Uploading the configuration after an authentication process
		///
		/// It will consist in updating the user with the id or the screen name
		/// given by the process.
		/// @param accessToken User access token
		/// @param tokenSecret User token secret
		/// @param id ID of the user
		/// @param screenName Screen name of the user
		void updateConfAfterAuth(QByteArray accessToken,
								 QByteArray tokenSecret,
								 qlonglong id,
								 QString screenName);

		/// @fn void saveConfiguration();
		/// @brief Saving the configuartion in the configuration file
		void saveConfiguration();

		/// @fn void checkTokens();
		/// @brief Checks if the access tokens seem legit. If not, it sends an
		/// authenticationRequired(); signal to the ReynTweetsWidget to start
		/// an authentication process.
		void checkTokens();

	signals:

		/// @fn void launchEnded(CoreResult authOK);
		/// @brief Signal sent at the end of the authentication to indicate
		/// if it was successful or not.
		/// @param authOK How the launching process ended
		void loadConfigurationEnded(CoreResult authOK);

		/// @fn void verifyTokensEnded(CoreResult verifyOK);
		/// @brief Signal sent after verifying credentials
		/// @param verifyOK How the verification ended
		void verifyTokensEnded(CoreResult verifyOK);

		/// @fn void saveConfEnded(CoreResuls saveOK);
		/// @brief Signal sent after saving the configuration
		/// @param saveOK How the save process ended
		void saveConfEnded(CoreResult saveOK);

	public slots:
		void loadOK(CoreResult loadRes);

		/// @fn void verifyCredentialsEnded(ResultWrapper res);
		/// @brief Slot executed after verifying credentials.
		/// @param res Result of the request
		void verifyCredentialsEnded(ResultWrapper res);

		void verifyOK(CoreResult verifyRes);

		void saveOK(CoreResult saveRes);

		/// @fn void getUser(ResultWrapper res);
		/// @brief Getting a user after requesting it to Twitter
		/// @param res Result of the request
		void getUser(ResultWrapper res);

		///////////////////////////////
		// Authentication management //
		///////////////////////////////

		/// @fn void allowReynTweets();
		/// @brief Allowing Reyn Tweets
		void allowReynTweets();

	protected:
		/// @brief Entity calling Twitter
		ReynTwitterCalls twitter;

		/// @brief Configuration
		ReynTweetsConfiguration & configuration;

	private:
		///////////////////////////////
		// Authentication management //
		///////////////////////////////

		/// @fn bool isValidToken(QByteArray token);
		/// @brief Determining if a token seems legit
		/// @param token Token to analyze
		/// @return True if the token seems valid, false otherwise
		bool isValidToken(QByteArray token);

		//////////////////////////////
		// Configuration management //
		//////////////////////////////

		/// @fn CoreResult loadConfigurationPrivate();
		/// @brief Loading the configuartion from the configuration file
		/// @return How the launching process ended
		CoreResult loadConfigurationPrivate();

		/// @fn CoreResult saveConfigurationPrivate();
		/// @brief Saving the configuartion in the configuration file
		/// @return How the save process ended
		CoreResult saveConfigurationPrivate();
};

#endif // LAUNCHINGPROCESS_HPP
