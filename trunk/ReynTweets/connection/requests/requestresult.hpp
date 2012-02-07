/// @file requestresult.hpp
/// @brief Header of RequestResult
///
/// Revisions older than r242 were in /trunk/ReynTweets/connection
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
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef REQUESTRESULT_HPP
#define REQUESTRESULT_HPP

#include <QNetworkReply>
#include <QVariant>
#include "../errortypes.hpp"

/// @class RequestResult
/// @brief Results of a request
class RequestResult
{
	public:
		/// @fn RequestResult();
		/// @brief Default constructor. It builds an invalid result.
		RequestResult();

		/// @fn RequestResult(ErrorType errorType,
		///					  QVariant parsedResults,
		///					  int httpReturnCode,
		///					  QString httpReturnReason,
		///					  QVariantMap parsingErrorInfos,
		///					  QString errorMsg);
		/// @brief Constructor
		/// @param errorType Code indicating if an error occured.
		/// @param parsedResults Pure results of the request.
		/// @param httpReturnCode HTTP code of the request
		/// @param httpReturnReason HTTP reason
		/// @param parsingErrorInfos Information about potential parsing errors
		/// @param errorMsg Error message
		RequestResult(ErrorType errorType,
					  QVariant parsedResults,
					  int httpReturnCode,
					  QString httpReturnReason,
					  QVariantMap parsingErrorInfos,
					  QString errorMsg);

		/// @fn bool isRequestSuccessful();
		/// @brief Method indicating if the request was successful
		/// @return true if the request was successful, false otherwise.
		bool isRequestSuccessful();

		/// @fn bool isFakeResult();
		/// @brief Method indicating if the request result is fake
		/// @return true if the object is FAKE_REQUEST_RESULT, false otherwise.
		bool isFakeResult();

		/// @fn ErrorType getErrorType();
		/// @brief Getter on requestSuccessful
		/// @return The value of requestSuccessful
		ErrorType getErrorType();

		/// @fn QVariant getParsedResult();
		/// @brief Getter on real results
		/// @return The real results of the request
		QVariant getParsedResult();

		/// @fn int getHttpCode();
		/// @brief Getter on httpCode
		/// @return The HTTP return code
		int getHttpCode();

		/// @fn QString getHttpReason();
		/// @brief Getter on httpReason
		/// @return The value of httpReaso
		QString getHttpReason();

		/// @fn QVariantMap getParsingErrors();
		/// @brief Getter on parsingErrors
		/// @return The value of parsingErrors
		QVariantMap getParsingErrors();

		/// @fn QVariantMap getParsingErrorMessage();
		/// @brief Getter on the parsing error message
		/// @return The parsing error message
		QString getParsingErrorMessage();

		/// @fn QString getErrorMessage();
		/// @brief Getter on the error massage
		/// @return The error message
		QString getErrorMessage();


	protected:
		/// @brief Code indicating whether an error occured during the request.
		ErrorType resultType;

		/// @brief Results of the request parsed by QJson.
		QVariant parsedResult;

		/// @brief HTTP return code.
		int httpCode;

		/// @brief Reason associated to the HTTP return code.
		QString httpReason;

		/// @brief Potential errors that can occur while parsing results.
		QVariantMap parsingErrors;

		/// @brief Error message
		QString errorMessage;
};

#endif // REQUESTRESULT_HPP
