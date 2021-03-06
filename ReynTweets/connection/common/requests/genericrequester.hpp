/// @file genericrequester.hpp
/// @brief Header of GenericRequester
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011 Romain Ducher
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

#ifndef GENERICREQUESTER_HPP
#define GENERICREQUESTER_HPP

#include <QObject>
#include <QUuid>
#include <QVariant>
#include "../requestresult.hpp"
#include "../communicators/twittercommunicator.hpp"
#include "../networkresult.hpp"

/// @class GenericRequester
/// @brief Base class for all the requesters.
class GenericRequester : public QObject
{
	Q_OBJECT

	public:
		/// @fn GenericRequester(Network::HTTPRequestType type,
		///						 QString url,
		///						 LibRT::NetworkResultType parseError = Network::JSON_PARSING);
		/// @brief Constructor
		/// @param type Type of the request (GET ou POST).
		/// @param url URL called by the requester
		/// @param parseError Error type if an error occurs while parsing. Most
		/// of the time, this value is set to JSON_PARSING because results are
		/// written in JSON. However, OAuth requesters use their
		/// own parsing process so they need a special value called OAUTH_PARSING.
		GenericRequester(LibRT::HTTPRequestType type,
						 QString url,
						 LibRT::NetworkResultType parseError = LibRT::JSON_PARSING);

		/// @fn virtual ~GenericRequester();
		/// @brief Destructor.
		virtual ~GenericRequester();

		/// @fn QUuid getUuid();
		/// @brief Getter on the requester's UUID
		/// @return The requester's UUID
		QUuid getUuid();

		/// @fn virtual void executeRequest();
		/// @brief Executing the request. The method is virtual because of the
		/// Authorize step in the OAuth process whose request is quite different
		/// from the other ones.
		virtual void executeRequest();

	protected:
		/// @brief UUID of the request
		QUuid uuid;

		/// @brief URL called by the requester
		QString requestURL;

		/// @brief Request type
		LibRT::HTTPRequestType requestType;

		/// @brief GET parameters that will be passed to the Communicator.
		ArgsMap getParameters;

		/// @fn virtual void buildGETParameters();
		/// @brief Virtual method building getParameters
		virtual void buildGETParameters();

		/// @brief POST parameters that will be passed to the Communicator.
		ArgsMap postParameters;

		/// @fn virtual void buildPOSTParameters();
		/// @brief Virtual method building postParameters
		virtual void buildPOSTParameters();

		/// @brief HTTP headers that will be passed to the Communicator.
		HeadersMap headers;

		/// @fn virtual void buildHTTPHeaders();
		/// @brief Virtual method building headers
		virtual void buildHTTPHeaders();

		/// @brief Pointer on the Twitter Communicator that will purely execute
		/// the request and get the raw result of it.
		TwitterCommunicator weblink;

		/// @brief Type of parsing error
		LibRT::NetworkResultType parsingErrorType;

		/// @fn void setParsingErrorType(LibRT::NetworkResultType parseErrorType);
		/// @brief Setting parsingErrorType in classes which inherits from
		/// GenericRequesters.
		/// @param parseErrorType New value for parsingErrorType
		void setParsingErrorType(LibRT::NetworkResultType parseErrorType);


	//////////////////////////
	// Treatment of results //
	//////////////////////////

	public slots:
		/// @fn void treatResults(NetworkResponse netResponse);
		/// @brief Slot that is executed when the Twitter Communicator has just
		/// finished its work.
		/// @param netResponse Struct with response elements
		void treatResults(NetworkResponse netResponse);

	protected:
		/// @fn virtual QVariant parseResult(NetworkResponse results,
		///									 bool & parseOK,
		///									 QVariantMap & parsingErrors) = 0;
		/// @brief Method that will parse the raw results of the request.
		/// @param results Results to parse. Most of the time the method only
		/// uses the responseBody field.
		/// @param parseOK Boolean whose value will be set to true if there was
		/// no problem while parsing, false otherwise.
		/// @param parsingErrors QVariantMap that may contain information about
		/// errors that may occur while parsing.
		/// @return Parsed results
		virtual QVariant parseResult(NetworkResponse results,
									 bool & parseOK,
									 QVariantMap & parsingErrors) = 0;

		/// @fn virtual QList<ResponseInfos> treatServiceErrors(QVariant parsedResults,
		///														NetworkResponse netResponse) = 0;
		/// @brief Treating parsed results
		/// @param parsedResults Parsed results to analyse in order to retrieve
		/// service errors.
		/// @param netResponse Other network response elements, if needed.
		/// @return The list of service errors
		virtual QList<ResponseInfos> treatServiceErrors(QVariant parsedResults,
														NetworkResponse netResponse) = 0;

	signals:
		/// @fn void requestDone(RequestResult requestResult);
		/// @brief Signal sent when the results of the request received by
		/// the Twitter Communicator have been treated.
		/// @param requestResult Result of the request.
		void requestDone(RequestResult requestResult);
};

#endif // GENERICREQUESTER_HPP
