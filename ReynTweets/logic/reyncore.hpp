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
#include "coreresult.hpp"
#include "../model/configuration/reyntweetsconfiguration.hpp"
#include "oauthprocess.hpp"
#include "genericprocess.hpp"
#include "processes/processmanager.hpp"
#include "processes/processwrapper.hpp"

/// @class ReynCore
/// @brief Heart of Reyn Tweets.
///
/// It is the main controller of the application. It is behind the main
/// widget of the program (ReynTweetsWidget).
class ReynCore : public QObject
{
	Q_OBJECT

	//////////////////////////////////
	// Core management of the class //
	//////////////////////////////////

	public:
		/// @fn ReynCore();
		/// @brief Constructor
		ReynCore();

		/// @fn ~ReynCore();
		/// @brief Destructor
		~ReynCore();

	signals:
		/// @fn void sendResult(ProcessWrapper res);
		/// @brief Signal emitted to the QObject that requests the process
		/// @param res Result of a process
		void sendResult(ProcessWrapper res);

	public slots:
		/// @fn void endRequest();
		/// @brief Slot executed when a requester has finished its work
		void endProcess();

	protected:
		/// @brief QObject that asks for the request
		QObject * requestDemander;

		/// @brief Process manager
		static ProcessManager processManager;

		/// @brief Configuration of the program
		static ReynTweetsConfiguration configuration;

	private:
		/// @fn void addProcess(GenericProcess * process);
		/// @brief Adding a requester to the requester manager
		/// @param requester Address of the requester
		void addProcess(GenericProcess * process);

		/// @fn void removeProcess(GenericProcess * process);
		/// @brief Removing a requester of the requester manager
		/// @param requester Address of the requester
		void removeProcess(GenericProcess * process);

		/// @fn ProcessWrapper buildResultSender(GenericProcess * endedProcess);
		/// @brief Method that builds the wrapper of a result
		/// @param endedRequest Ended request that contaons the result
		/// @return The wrapper of the request result
		ProcessWrapper buildResultSender(GenericRequester * endedProcess);

		/// @fn inline void executeProcess(GenericProcess * process);
		/// @brief Inline method for executing requests
		/// @param requester The requester
		inline void executeProcess(GenericProcess * process);


	////////////////////////
	// Actions to realize //
	////////////////////////

	public:
		/// @fn void launchReynTweets();
		/// @brief Launching the app
		void launchReynTweets();

		/// @fn void allowReynTweets();
		/// @brief Allowing Reyn Tweets
		void allowReynTweets();


	//////////
	// Misc //
	//////////

	public:
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

	signals:
		/// @fn void authenticationRequired();
		/// @brief Signal sent if the application has to be authorized again
		/// (in order to get new access tokens, for example).
		void authenticationRequired();

	public slots:
		/// @fn void getUser(ResultWrapper res);
		/// @brief Getting a user after requesting it to Twitter
		/// @param res Result of the request
		void getUser(ResultWrapper res);
};

#endif // REYNCORE_HPP
