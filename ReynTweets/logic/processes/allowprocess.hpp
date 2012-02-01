#ifndef ALLOWPROCESS_HPP
#define ALLOWPROCESS_HPP

#include "oauthprocess.hpp"
#include "../../model/configuration/reyntweetsconfiguration.hpp"

/// @brief OAuth Authentication Flow + updating the configuration
class AllowProcess : public OAuthProcess
{
		Q_OBJECT
	public:
		explicit AllowProcess(ReynTweetsConfiguration & conf);

	public slots:

		/// @fn void retrieveUserEnded(ResultWrapper res);
		/// @brief Getting a user after requesting it to Twitter
		/// @param res Result of the request
		void retrieveUserEnded(ResultWrapper res);

	protected:
		bool authEnded;

		/// @brief Configuration of Reyn Tweets
		ReynTweetsConfiguration & configuration;

		void saveConfiguration();

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
