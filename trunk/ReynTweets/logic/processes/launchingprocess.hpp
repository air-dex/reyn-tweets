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
		/// @fn explicit LaunchingProcess(ReynTweetsConfiguration & conf);
		/// @brief Constructor
		/// @param conf Configuration of Reyn Tweets
		explicit LaunchingProcess(ReynTweetsConfiguration & conf);

		/// @fn void startProcess();
		/// @brief Starting the process
		void startProcess();

	signals:
		/// @fn void authenticationRequired();
		/// @brief Signal sent if the application has to be authorized again
		/// (in order to get new access tokens, for example).
		void authenticationRequired();

	public slots:
		/// @fn void verifyCredentialsEnded(ResultWrapper res);
		/// @brief Slot executed after verifying credentials.
		/// @param res Result of the request
		void verifyCredentialsEnded(ResultWrapper res);
/*
		/// @fn authenticationIssue(ProcessWrapper res);
		/// @brief What happened while authorizing Reyn Tweets
		/// @param res Process result
		void authenticationIssue(ProcessWrapper res);
//*/
	protected:
		/// @brief Entity calling Twitter
		ReynTwitterCalls twitter;

		/// @brief Configuration
		ReynTweetsConfiguration & configuration;

	private:
		/// @fn void loadConfiguration();
		/// @brief Loading the configuartion from the configuration file
		void loadConfiguration();

		/// @fn void checkTokens();
		/// @brief Checks if the access tokens seem legit. If not, it sends an
		/// authenticationRequired(); signal to the ReynTweetsWidget to start
		/// an authentication process.
		void checkTokens();

		/// @fn void saveConfiguration();
		/// @brief Saving the configuartion in the configuration file
		void saveConfiguration();

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
