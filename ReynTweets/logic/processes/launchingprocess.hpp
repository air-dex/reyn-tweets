#ifndef LAUNCHINGPROCESS_HPP
#define LAUNCHINGPROCESS_HPP

#include "genericprocess.hpp"
#include "../../model/configuration/reyntweetsconfiguration.hpp"
#include "../../connection/reyntwittercalls.hpp"
#include "../coreresult.hpp"
#include "processwrapper.hpp"

/// @class LaunchingProcess
/// @brief Process executed to launch the application
class LaunchingProcess : public GenericProcess
{
	Q_OBJECT

	public:
		/// @fn LaunchingProcess(ReynTweetsConfiguration & conf);
		/// @brief Constructor
		/// @param conf Configuration of Reyn Tweets
		LaunchingProcess(ReynTweetsConfiguration & conf);

		/// @fn void startProcess();
		/// @brief Starting the process
		void startProcess();

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

		/// @fn void authenticationRequired();
		/// @brief Signal sent if the application has to be authorized again
		/// (in order to get new access tokens, for example).
		void authenticationRequired();

		/// @fn void saveConfEnded(CoreResuls saveOK);
		/// @brief Signal sent after saving the configuration
		/// @param saveOK How the save process ended
		void saveConfEnded(CoreResult saveOK);

	public slots:
		/// @fn void loadOK(CoreResult loadRes);
		/// @brief Slot executed after trying to load the configuration.
		/// @param loadRes Enum describing how it ends
		void loadOK(CoreResult loadRes);

		/// @fn void verifyCredentialsEnded(ResultWrapper res);
		/// @brief Slot executed after verifying credentials.
		/// @param res Result of the request
		void verifyCredentialsEnded(ResultWrapper res);

		/// @fn void verifyOK(CoreResult verifyRes);
		/// @brief Slot executed after asking Twitter REST API if the
		/// credentials were right.
		/// @param verifyRes Enum describing how it ends
		void verifyOK(CoreResult verifyRes);

		/// @fn authenticationIssue(ProcessWrapper res);
		/// @brief What happened while authorizing Reyn Tweets
		/// @param res Process result
		void authenticationIssue(ProcessWrapper res);

		/// @fn void retrieveUserEnded(ResultWrapper res);
		/// @brief Getting a user after requesting it to Twitter
		/// @param res Result of the request
		void retrieveUserEnded(ResultWrapper res);

		/// @fn void saveOK(CoreResult saveRes);
		/// @brief Slot executed after trying to save the configuration.
		/// @param saveRes Enum describing how it ends
		void saveOK(CoreResult saveRes);

	protected:
		/// @brief Entity calling Twitter
		ReynTwitterCalls twitter;

		/// @brief Configuration
		ReynTweetsConfiguration & configuration;

	private:
		/// @fn void loadConfiguration();
		/// @brief Loading the configuartion from the configuration file
		void loadConfiguration();

		/// @fn CoreResult loadConfigurationPrivate();
		/// @brief Loading the configuartion from the configuration file
		/// @return How the launching process ended
		CoreResult loadConfigurationPrivate();

		/// @fn void checkTokens();
		/// @brief Checks if the access tokens seem legit. If not, it sends an
		/// authenticationRequired(); signal to the ReynTweetsWidget to start
		/// an authentication process.
		void checkTokens();

		/// @fn void updateConfiguration(QByteArray accessToken = "",
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
		void updateConfiguration(QByteArray accessToken,
								 QByteArray tokenSecret,
								 qlonglong id,
								 QString screenName);

		/// @fn void saveConfiguration();
		/// @brief Saving the configuartion in the configuration file
		void saveConfiguration();

		/// @fn CoreResult saveConfigurationPrivate();
		/// @brief Saving the configuartion in the configuration file
		/// @return How the save process ended
		CoreResult saveConfigurationPrivate();

		/// @fn void buildResult(bool processOK,
		///						 CoreResult issue,
		///						 QString errMsg = "",
		///						 bool isFatal = false);
		/// @brief Building process results
		/// @param processOK Did the process end successfully ?
		/// @param issue Enum value describing how it ended.
		/// @param errMsg Error message
		/// @param isFatal Is the issue fatal (i.e. requiring to abort
		/// the application) ?
		void buildResult(bool processOK,
						 CoreResult issue,
						 QString errMsg = "",
						 bool isFatal = false);

		/// @fn void fillOAuthManager();
		/// @brief Filling the OAuthManager of twitter with configuration tokens
		void fillOAuthManager();
};

#endif // LAUNCHINGPROCESS_HPP
