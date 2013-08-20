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
#include "../core/configuration/appconfiguration.hpp"
#include "../core/configuration/userconfiguration.hpp"
#include "../../connection/twitter/reyntwittercalls.hpp"
#include "../core/coreresult.hpp"
#include "processwrapper.hpp"

/// @class LaunchingProcess
/// @brief Process executed to launch the application
class LaunchingProcess : public GenericProcess
{
	Q_OBJECT

	public:
		/// @fn LaunchingProcess(ReynTweetsUserConfiguration & userConf);
		/// @brief Constructor
		/// @param userConf User configuration
		LaunchingProcess(UserConfiguration & userConf);

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

		/// @brief Configuration related to the user
		UserConfiguration & userConfiguration;

		/// @brief Configuration of Reyn Tweets
		AppConfiguration & appConfiguration;

		/// @brief Boolean indicating if the user configuration was reset
		bool userconfReinit;

	protected:
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

		/// @fn virtual void endProcess(ReynTweets::CoreResult procEnd,
		///								QString errorMessage);
		/// @brief Ending the process.
		///
		/// It is a shortcut for endProcess(procEnd, QVariant(), errorMessage);.
		/// @param procEnd Description on how the process ends.
		/// @param errorMessage Message if an error occurs during the process.
		virtual void endProcess(ReynTweets::CoreResult procEnd,
								QString errorMessage);

		///////////////////////////
		// Filling configuration //
		///////////////////////////

		/// @fn void fillTwitterOAuthAppSettings();
		/// @brief Filling the TwitterAuthenticator of Twitter with consumer tokens
		void fillTwitterOAuthAppSettings();

		/// @fn void fillTwitterOAuthUserSettings();
		/// @brief Filling the TwitterAuthenticator of twitter with access tokens
		void fillTwitterOAuthUserSettings();

		/// @fn void fillTwitLongerAppSettings();
		/// @brief Filling the TwitLongerAuthenticator with the TwitLonger IDs
		/// of the application.
		void fillTwitLongerAppSettings();
};

#endif // LAUNCHINGPROCESS_HPP
