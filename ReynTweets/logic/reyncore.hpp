/// @file reyncore.hpp
/// @brief Header of ReynCore
///
/// Revisions of the file older than r204 are in /trunk/ReynTweets/controls
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

#ifndef REYNCORE_HPP
#define REYNCORE_HPP

#include <QObject>
#include "coreresult.hpp"
#include "../model/configuration/reyntweetsconfiguration.hpp"
#include "processes/genericprocess.hpp"
#include "processes/oauthprocess.hpp"
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
		/// @fn ReynCore(QObject * actionRequester);
		/// @brief Constructor
		/// @param actionRequester Entity which asks the Core to do something
		ReynCore(QObject * actionRequester);

		/// @fn ~ReynCore();
		/// @brief Destructor
		~ReynCore();

		/// @fn ReynCore(const ReynCore & heart);
		/// @brief Copy constructor
		/// @param heart Core to copy
		ReynCore(const ReynCore & heart);

		/// @fn const ReynCore & operator=(const ReynCore & heart);
		/// @brief Affectation operator
		/// @param heart Core to copy
		const ReynCore & operator=(const ReynCore & heart);

	signals:
		/// @fn void sendResult(ProcessWrapper res);
		/// @brief Signal emitted to the QObject that requests the process
		/// @param res Result of a process
		void sendResult(ProcessWrapper res);

	public slots:
		/// @fn void endProcess();
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
		/// @fn void recopie(const ReynCore & heart);
		/// @brief Copying a ReynCore
		/// @param heart Core to copy
		void recopie(const ReynCore & heart);

		/// @fn void addProcess(GenericProcess * process);
		/// @brief Adding a process to the process manager
		/// @param process Address of the process
		void addProcess(GenericProcess * process);

		/// @fn void removeProcess(GenericProcess * process);
		/// @brief Removing a process of the process manager
		/// @param process Address of the process
		void removeProcess(GenericProcess * process);

		/// @fn ProcessWrapper buildResultSender(GenericProcess * endedProcess);
		/// @brief Method that builds the wrapper of a result
		/// @param endedProcess Ended process that contains the result
		/// @return The wrapper of the process result
		ProcessWrapper buildResultSender(GenericProcess * endedProcess);

		/// @fn inline void executeProcess(GenericProcess * process);
		/// @brief Inline method for executing processes
		/// @param process The process
		inline void executeProcess(GenericProcess * process);


	////////////////////////
	// Actions to realize //
	////////////////////////

	public:
		/// @fn void launchReynTweets();
		/// @brief Launching the app
		void launchReynTweets();

		/// @fn void authorizeReynTweets();
		/// @brief Authorizing Reyn Tweets (not saving the configuration after).
		void authorizeReynTweets();

		/// @fn void allowReynTweets();
		/// @brief Allowing Reyn Tweets
		void allowReynTweets();

	protected:
		/// @fn inline void oauthSpecialWiring(OAuthProcess * oauthProcess);
		/// @brief Special wiring of an OAuth process.
		/// @param oauthProcess The process
		inline void oauthSpecialWiring(OAuthProcess * oauthProcess);


	////////////////////
	// Special wiring //
	////////////////////

	signals:
		//////////////////////////////////////////////////////////////
		// OAuth process giving informations about user credentials //
		//////////////////////////////////////////////////////////////

		/// @fn void userCredentialsNeeded();
		/// @brief Transmitting the userCredentialsRequired() signal of
		/// a given OAuthProcess.
		void userCredentialsNeeded();

		/// @fn void credentialsValid(bool credsOK);
		/// @brief Telling the user whether credentials given by it are right.
		/// @param credsOK Boolean indicating if credentials are right (true).
		void credentialsValid(bool credsOK);

		///////////////////////
		// Authorize or deny //
		///////////////////////

		/// @fn void authorize(QString login, QString password);
		/// @brief Slot executed to allow Reyn Tweets to use the Twitter account :).
		/// @param login User login, i.e. its username or its email.
		/// @param password User password
		void authorize(QString login, QString password);

		/// @fn void deny(QString login, QString password);
		/// @brief Slot executed to deny Reyn Tweets to use the Twitter account :(.
		/// @param login User login, i.e. its username or its email.
		/// @param password User password
		void deny(QString login, QString password);

	public slots:
		//////////////////////////////////////////////////////////////
		// OAuth process giving informations about user credentials //
		//////////////////////////////////////////////////////////////

		/// @fn void userCredentialsRequired();
		/// @brief Executed when an OAuthProcess send its
		/// userCredentialsRequired() signal.
		void userCredentialsRequired();

		/// @fn void credentialsOK(bool credsOK);
		/// @brief Telling the user whether credentials given by it are right.
		/// @param credsOK Boolean indicating if credentials are right (true).
		void credentialsOK(bool credsOK);

		///////////////////////
		// Authorize or deny //
		///////////////////////

		/// @fn void authorizeReynTweets(QString login, QString password);
		/// @brief Slot executed to allow Reyn Tweets to use the Twitter account :).
		/// @param login User login, i.e. its username or its email.
		/// @param password User password
		void authorizeReynTweets(QString login, QString password);

		/// @fn void denyReynTweets(QString login, QString password);
		/// @brief Slot executed to deny Reyn Tweets to use the Twitter account :(.
		/// @param login User login, i.e. its username or its email.
		/// @param password User password
		void denyReynTweets(QString login, QString password);
};

#endif // REYNCORE_HPP
