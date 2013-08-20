/// @file allowprocess.hpp
/// @brief Header of AllowProcess
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

#ifndef ALLOWPROCESS_HPP
#define ALLOWPROCESS_HPP

#include "oauthprocess.hpp"
#include "../../model/configuration/userconfiguration.hpp"

/// @class AllowProcess
/// @brief OAuth Authentication Flow + updating the configuration
class AllowProcess : public OAuthProcess
{
	Q_OBJECT

	public:
		/// @fn explicit AllowProcess(ReynTweetsUserConfiguration & conf);
		/// @brief Constructor
		/// @param conf Reference on the configuration
		explicit AllowProcess(UserConfiguration & conf);

	public slots:

		/// @fn void retrieveUserEnded(ResultWrapper res);
		/// @brief Getting a user after requesting it to Twitter
		/// @param res Result of the request
		void retrieveUserEnded(ResultWrapper res);

	protected:
		/// @brief Boolean indicating if the OAuth Process has already ended.
		bool authEnded;

		/// @brief Configuration of Reyn Tweets
		UserConfiguration & configuration;

		/// @fn void saveConfiguration();
		/// @brief
		void saveConfiguration();

		/// @fn void endProcess();
		/// @brief Redefinition of <code>GenericProcess::endprocess();</code>
		///
		/// This redefinition is needed because of the extra steps compared to
		/// the OAuthProcess (updating user infos + saving the configuation).
		/// The process must not stop after getting the access tokens.
		void endProcess();

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
};

#endif // ALLOWPROCESS_HPP
