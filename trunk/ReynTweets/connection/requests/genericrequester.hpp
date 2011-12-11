/// @file genericrequester.hpp
/// @brief Generic class for Twitter requests
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

#ifndef GENERICREQUESTER_HPP
#define GENERICREQUESTER_HPP

#include <QObject>
#include <QUuid>
#include "../twittercommunicator.hpp"

/// @class GenericRequest
/// @brief Base class for all the requesters. Parents of such requests are
/// QObjects that demand the request.
class GenericRequester : public QObject
{
	Q_OBJECT

	public:
		/// @fn GenericRequest(QString url = "", QObject * parent = 0);
		/// @brief Constructor. It just calls the parent constructor.
		/// @param requester QObject which asks for this search
		/// @brief url URL called by the requester
		GenericRequester(QObject * requester, QString url);

		/// @fn ~GenericRequester();
		/// @brief Destructor.
		~GenericRequester();

		/// @fn QUuid getUuid();
		/// @brief Getter on the requester's UUID
		/// @return The requester's UUID
		QUuid getUuid();

		/// @fn void executeRequest();
		/// @brief Executing the request
		void executeRequest();

		/// @fn QVariant getParsedResult();
		/// @brief Getting parsed results
		/// @return Parsed results in a QVariant object.
		QVariant getParsedResult();


	signals:
		/// @fn void requestDone(bool ok);
		/// @brief Signal sent when the results of the request received by
		/// the Twitter Communicator have been treated.
		/// @param ok Boolean indicating if the request is ok (true) of if there
		/// was an error (false).
		void requestDone();

	public slots:
		/// @fn void treatResults(bool ok);
		/// @brief Slot that is executed when the Twitter Communicator has just
		/// finished its work.
		/// @param ok Boolean indicating if the Twitter Communicator work is ok
		/// (true) of if therewas an error (false).
		void treatResults(bool ok);

	protected:
		/// @brief UUID of the request
		QUuid uuid;

		/// @brief URL called by the requester
		QString requestURL;

		/// @brief GET parameters that will be passed to the Communicator.
		ArgsMap getParameters;

		/// @fn virtual void buildGETParameters() = 0;
		/// @brief Virtual method building getParameters
		virtual void buildGETParameters() = 0;

		/// @brief POST parameters that will be passed to the Communicator.
		ArgsMap postParameters;

		/// @fn virtual void buildPOSTParameters() = 0;
		/// @brief Virtual method building postParameters
		virtual void buildPOSTParameters() = 0;

		/// @brief Pointer on the Twitter Communicator that will purely execute
		/// the request and get the raw result of it.
		TwitterCommunicator * communicator;

		/// @brief Parsed results of the Twitter Communicator's work
		QVariant parsedResult;

		/// @fn virtual void parseResult() = 0;
		/// @brief Method that will parse the raw results of the request.
		/// @return true if there was no problem while parsing, false otherwise.
		virtual bool parseResult() = 0;	// Maybe not virtual

		/// @fn virtual void treatError() = 0;
		/// @brief Method that will treat errors of the requests made by the
		/// Twitter Communicator.
		virtual void treatError() = 0;	// Maybe not virtual
};

#endif // GENERICREQUESTER_HPP
