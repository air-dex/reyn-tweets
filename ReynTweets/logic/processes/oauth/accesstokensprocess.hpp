/// @file accesstokensprocess.hpp
/// @brief Header of AccessTokensProcess
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2013 Romain Ducher
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

#ifndef ACCESSTOKENSPROCESS_HPP
#define ACCESSTOKENSPROCESS_HPP

#include <QObject>
#include <QByteArray>
#include "../genericprocess.hpp"
#include "../../../connection/common/resultwrapper.hpp"
#include "../../../connection/twitter/reyntwittercalls.hpp"
#include "../../core/configuration/userconfiguration.hpp"

/// @class AccessTokensProcess
/// @brief Process to get the final tokens to authenticate
class AccessTokensProcess : public GenericProcess
{
	Q_OBJECT

	public:
		/// @fn AccessTokensProcess(QByteArray verifier);
		/// @brief Constructor
		/// @param verifier The OAuth Verifier needed for getting Access tokens.
		AccessTokensProcess(QByteArray verifier);

		/// @fn AccessTokensProcess(QByteArray verifier);
		/// @brief Constructor
		/// @param verifier The OAuth Verifier needed for getting Access tokens.
		AccessTokensProcess(QByteArray verifier, UserConfiguration & conf);

		/// @fn ~AccessTokensProcess();
		/// @brief Destructor
		~AccessTokensProcess();

		/// @fn void startProcess();
		/// @brief Starting the process
		void startProcess();

	protected:
		/// @brief Entity calling the Twitter API
		ReynTwitterCalls twitter;

		/// @brief The OAuth Verifier
		QByteArray oauthVerifier;

		/// @brief Configuration of Reyn Tweets.
		///
		/// It is a pointer because it could be uninitialized
		UserConfiguration * configuration;

		/// @brief Boolean indicating if the process has to update
		/// the user configuration.
		bool updateUserConfiguration;

		/// @brief Map with OAuth's access_tokens results.
		QVariantMap oauthRes;

		/// @fn void accessToken();
		/// @brief Demanding an Access Token
		void accessToken();

		/// @fn void buildOAuthResults(QByteArray accessToken,
		///							   QByteArray tokenSecret,
		///							   qlonglong userID,
		///							   QString screenName);
		/// @brief Building the process result if Reyn Tweets is authorized.
		/// @param accessToken User access token
		/// @param tokenSecret User token secret
		/// @param userID ID of the user who has just authorized the application
		/// @param screenName Screen name of the user who has just authorized
		/// the application.
		virtual void buildOAuthResults(QByteArray accessToken,
									   QByteArray tokenSecret,
									   qlonglong userID,
									   QString screenName);

		/// @fn void saveConfiguration();
		/// @brief
		void saveConfiguration();

		/// @fn void updateConfiguration(QByteArray accessToken,
		///								 QByteArray tokenSecret,
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


	protected slots:
		/////////////////////////
		// Requests to Twitter //
		/////////////////////////

		/// @fn void accessTokenDemanded(ResultWrapper res);
		/// @brief Treatments after the request for Access Tokens
		/// @param res Result of the request
		void accessTokenDemanded(ResultWrapper res);

		/// @fn void retrieveUserEnded(ResultWrapper res);
		/// @brief Getting a user after requesting it to Twitter
		/// @param res Result of the request
		void retrieveUserEnded(ResultWrapper res);

};

#endif // ACCESSTOKENSPROCESS_HPP
