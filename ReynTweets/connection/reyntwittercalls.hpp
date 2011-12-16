/// @file reyntwittercalls.hpp
/// @brief Calls to Twitter
/// @author Romain Ducher

/*
Copyright 2011 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef REYNTWITTERCALLS_HPP
#define REYNTWITTERCALLS_HPP

#include <QObject>
#include <QMap>
#include <QUuid>
#include "requests/requests.hpp"
#include "resultwrapper.hpp"
#include "oauthmanager.hpp"

/// @class ReynTwitterCalls
/// @brief ReynTwitterCalls is a class which manages calls to Twitter. It is a
/// singleton. To use it
class ReynTwitterCalls : public QObject
{
	Q_OBJECT

	//////////////////////////////////
	// Core management of the class //
	//////////////////////////////////

	public:
		/// @fn static ReynTwitterCalls & getInstance();
		/// @brief Getter on the unique instance
		/// @return The unique instance
		static ReynTwitterCalls & getInstance();

	signals:
		/// @fn void sendResult(ResultSender res);
		/// @brief Signal emitted to the QObject that sends the request
		/// @param res Result of a request
		void sendResult(ResultWrapper res);

	public slots:
		/// @fn void endRequest();
		/// @brief Slot executed when a requester has finished its work
		void endRequest();

	protected:
		/// @fn ReynTwitterCalls();
		/// @brief Protected constructor
		ReynTwitterCalls();

		/// @brief The unique ReynTwitterCalls object
		static ReynTwitterCalls instance;

		/// @brief Entity which manages requests that are running
		QMap<QUuid, GenericRequester *> requesterManager;

	private:
		/// @fn void addRequester(GenericRequester * requester);
		/// @brief Adding a requester to the requester manager
		/// @param requester Address of the requester
		void addRequester(GenericRequester * requester);

		/// @fn void removeRequester(GenericRequester * requester);
		/// @brief Removing a requester of the requester manager
		/// @param requester Address of the requester
		void removeRequester(GenericRequester * requester);

		/// @fn ResultSender buildResultSender(GenericRequester * endedRequest);
		/// @brief Method that builds the wrapper of a result
		/// @param endedRequest Ended request that contaons the result
		/// @return The wrapper of the request result
		ResultWrapper buildResultSender(GenericRequester * endedRequest);

		/// @fn inline void executeRequest(GenericRequester * requester);
		/// @brief Inline method for executing requests
		/// @param requester The requester
		inline void executeRequest(GenericRequester * requester);


	/////////////////////////////
	// Methods calling Twitter //
	/////////////////////////////
	public:
		/// @fn static void search(QString q);
		/// @brief Method that launch searches
		/// @param requestDemander QObject which asks for the request
		/// @param q The query
		void search(QObject * requestDemander, QString q);
};

#endif // REYNTWITTERCALLS_HPP
