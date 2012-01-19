/// @file reyncore.hpp
/// @brief Header of ReynCore
/// @author Romain Ducher

/*
Copyright 2012 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef REYNCORE_HPP
#define REYNCORE_HPP

#include <QObject>
#include "launchresult.hpp"
#include "../connection/reyntwittercalls.hpp"
#include "../model/configuration/reyntweetsconfiguration.hpp"

/// @class ReynCore
/// @brief Heart of Reyn Tweets.
///
/// It is the main controller of the application. It is behind the main
/// widget of the program (ReynTweetsWidget).
class ReynCore : public QObject
{
	Q_OBJECT

	public:
		/// @fn ReynCore();
		/// @brief Constructor
		ReynCore();

		///////////////////////////////
		// Authentication management //
		///////////////////////////////

		/// @fn void checkTokens();
		/// @brief Checks if the access tokens seem legit. If not, it sends an
		/// authenticationRequired(); signal to the ReynTweetsWidget to start
		/// an authentication process.
		void checkTokens();

		//////////////////////////////
		// Configuration management //
		//////////////////////////////

		/// @fn void loadConfiguration();
		/// @brief Loading the configuartion from the configuration file
		void loadConfiguration();

		/// @fn void updateConfAfterAuth(QByteArray accessToken = "",
		///								 QByteArray tokenSecret = "",
		///								 long id,
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
								 long id,
								 QString screenName);

		/// @fn void saveConfiguration();
		/// @brief Saving the configuartion in the configuration file
		void saveConfiguration();

	signals:
		///////////////////////////////
		// Authentication management //
		///////////////////////////////

		/// @fn void authenticationRequired();
		/// @brief Signal sent if the application has to be authorized again
		/// (in order to get new access tokens, for example).
		void authenticationRequired();

		//////////////////////////////
		// Configuration management //
		//////////////////////////////

		/// @fn void launchEnded(LaunchResult authOK);
		/// @brief Signal sent at the end of the authentication to indicate
		/// if it was successful or not.
		/// @param authOK How the launching process ended
		void launchEnded(LaunchResult authOK);

		/// @fn void saveConfEnded(SaveConfResult saveOK);
		/// @brief Signal sent after saving the configuration
		/// @param saveOK How the save process ended
		void saveConfEnded(SaveConfResult saveOK);

	public slots:
		/// @fn void getUser(ResultWrapper res);
		/// @brief Getting a user after requesting it to Twitter
		/// @param res Result of the request
		void getUser(ResultWrapper res);

	protected:
		/// @brief Entity calling Twitter
		ReynTwitterCalls twitter;

		/// @brief Configuration of the program
		ReynTweetsConfiguration configuration;

		/// @fn void fillOAuthManager();
		/// @brief Filling the authentication manager of the ReynTwitterCalls
		/// with the right credentials
		void fillOAuthManager();

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

		/// @fn LaunchResult loadConfigurationPrivate();
		/// @brief Loading the configuartion from the configuration file
		/// @return How the launching process ended
		LaunchResult loadConfigurationPrivate();

		/// @fn SaveConfResult saveConfigurationPrivate();
		/// @brief Saving the configuartion in the configuration file
		/// @return How the save process ended
		SaveConfResult saveConfigurationPrivate();
};

#endif // REYNCORE_HPP
