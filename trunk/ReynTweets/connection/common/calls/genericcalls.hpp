/// @file genericcalls.hpp
/// @brief Header of GenericCalls
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

#ifndef GENERICCALLS_HPP
#define GENERICCALLS_HPP

#include <QObject>
#include "../requests/genericrequester.hpp"
#include "../../model/resultwrapper.hpp"
#include "requestermanager.hpp"

/// @class GenericCalls
/// @brief Base class for all classes which manage calls to services.
///
/// It contains the methods for the core management of the calls so its derived
/// class can focused on the methods calling a service and not the core management.
class GenericCalls : public QObject
{
	Q_OBJECT

	//////////////////////////////////
	// Core management of the class //
	//////////////////////////////////

	public:
		/// @fn GenericCalls(QObject * requester);
		/// @brief Constructor
		/// @param requester Entity asking for the request
		GenericCalls(QObject * requester);

		/// @fn ~GenericCalls();
		/// @brief Destructor
		~GenericCalls();

	signals:
		/// @fn void sendResult(ResultWrapper res);
		/// @brief Signal emitted to the QObject that sends the request
		/// @param res Result of a request
		void sendResult(ResultWrapper res);

	public slots:
		/// @fn void endRequest();
		/// @brief Slot executed when a requester has finished its work
		void endRequest();

	protected:
		/// @brief QObject that asks for the request
		QObject * requestDemander;

		/// @brief Entity which manages requests that are running
		static RequesterManager requesterManager;

		///////////////////////////
		// Requesters management //
		///////////////////////////

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

		/// @fn void executeRequest(GenericRequester * requester);
		/// @brief Inline method for executing requests
		/// @param requester The requester
		void executeRequest(GenericRequester * requester);
};

#endif // GENERICCALLS_HPP
