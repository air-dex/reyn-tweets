/// @file genericrequester.hpp
/// @brief Header of GenericRequester
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
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GENERICREQUESTER_HPP
#define GENERICREQUESTER_HPP

#include <QObject>
#include <QUuid>
#include <QVariant>
#include "../twitterurls.hpp"
#include "../requestresult.hpp"
#include "../twittercommunicators/twittercommunicator.hpp"

/// @class GenericRequester
/// @brief Base class for all the requesters.
class GenericRequester : public QObject
{
	Q_OBJECT

	public:
		/// @fn GenericRequester(RequestType type,
		///						 QString url,
		///						 ErrorType parseError = QJSON_PARSING);
		/// @brief Constructor
		/// @param type Type of the request (GET ou POST).
		/// @param url URL called by the requester
		/// @param parseError Error type if an error occurs while parsing. Most
		/// of the time, this value is set to QJSON_PARSING because results are
		/// QJson stream parsed with QJson. However, OAuth requesters use their
		/// own parsing process so they need a special value called OAUTH_PARSING.
		GenericRequester(RequestType type,
						 QString url,
						 ErrorType parseError = QJSON_PARSING);

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

		/// @fn RequestResult getRequestResult();
		/// @brief Getting parsed results
		/// @return Parsed results in a QVariant object.
		RequestResult getRequestResult();

	protected:
		/// @brief UUID of the request
		QUuid uuid;

		/// @brief URL called by the requester
		QString requestURL;

		/// @brief Request type
		RequestType requestType;

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

		/// @brief Pointer on the Twitter Communicator that will purely execute
		/// the request and get the raw result of it.
		TwitterCommunicator * communicator;

		/// @brief Type of parsing error
		ErrorType parsingErrorType;

		/// @fn void setParsingErrorType(ErrorType parseErrorType);
		/// @brief Setting parsingErrorType in classes which inherits from
		/// GenericRequesters.
		/// @param parseErrorType New value for parsingErrorType
		void setParsingErrorType(ErrorType parseErrorType);

	//////////////////////////
	// Treatment of results //
	//////////////////////////

	protected:
		/// @brief Result of the request.
		RequestResult requestResult;

		/// @fn virtual QVariant parseResult(bool & parseOK,
		///									 QVariantMap & parsingErrors);
		/// @brief Method that will parse the raw results of the request.
		/// @param parseOK Boolean whose value will be set to true if there was
		/// no problem while parsing, false otherwise.
		/// @param parsingErrors QVariantMap that may contain information about
		/// errors that may occur while parsing.
		/// @return Parsed results
		virtual QVariant parseResult(bool & parseOK,
									 QVariantMap & parsingErrors);

	public slots:
		/// @fn void treatResults(bool requestOK);
		/// @brief Slot that is executed when the Twitter Communicator has just
		/// finished its work.
		/// @param requestOK Boolean indicating if the Twitter Communicator did
		/// its work successfully.
		void treatResults(bool requestOK);

	signals:
		/// @fn void requestDone();
		/// @brief Signal sent when the results of the request received by
		/// the Twitter Communicator have been treated.
		void requestDone();


	private:
		/// @fn void fillParsedResult(ErrorType errorType,
		///			QVariant parsedResults,
		///			QVariantMap parsingErrors);
		/// @brief Filling parsedResult. Some information such as the
		/// networkError and httpInfos are contained in the Twitter Communicator
		/// son they are not passed as parameters of the method.
		/// @param errorType ErrorType
		/// @param parsedResults Parsed results. If there w
		/// @param parsingErrors Errors that may occur while parsing.
		void fillParsedResult(ErrorType errorType,
							  QVariant parsedResults,
							  QVariantMap parsingErrors);

		/// @fn virtual void initCommunicator();
		/// @brief Initialize the communicator. This a template method because
		/// requests with authentication needs more parameters.
		virtual void initCommunicator();
};

#endif // GENERICREQUESTER_HPP