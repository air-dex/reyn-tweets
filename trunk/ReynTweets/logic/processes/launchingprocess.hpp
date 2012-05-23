/// @file launchingprocess.hpp
/// @brief Header of LaunchingProcess
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
///
/// This file is part of Reyn Tweets.
///
/// Reyn Tweets is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Lesser General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// Reyn Tweets is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU Lesser General Public License for more details.
///
/// You should have received a copy of the GNU Lesser General Public License
/// along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.

#ifndef LAUNCHINGPROCESS_HPP
#define LAUNCHINGPROCESS_HPP

#include "genericprocess.hpp"
#include "../../model/configuration/reyntweetsuserconfiguration.hpp"
#include "../../connection/calls/reyntwittercalls.hpp"
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
		LaunchingProcess(ReynTweetsUserConfiguration & userConf, ReynTweetsAppConfiguration &appConf);

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

	protected:
		/// @brief Entity calling Twitter
		ReynTwitterCalls twitter;

		/// @brief Configuration
		ReynTweetsUserConfiguration & userConfiguration;

		/// @brief Configuration
		ReynTweetsAppConfiguration & appConfiguration;

	private:
		/// @fn void checkSettingsLoad();
		/// @brief Checking if the application settings were loaded successfully.
		void checkSettingsLoad();

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

		/// @fn void fillOAuthAppSettings();
		/// @brief Filling the OAuthManager of twitter with configuration tokens
		void fillTwitterOAuthAppSettings();

		/// @fn void fillOAuthManagerUserSettings();
		/// @brief Filling the OAuthManager of twitter with configuration tokens
		void fillTwitterOAuthUserSettings();

		/// @fn void fillOAuthManager();
		/// @brief Filling the OAuthManager of twitter with configuration tokens
		void fillTwitLongerAppSettings();
};

#endif // LAUNCHINGPROCESS_HPP
