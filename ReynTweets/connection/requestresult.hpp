/// @file requestresult.hpp
/// @brief Header of RequestResult
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
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef REQUESTRESULT_HPP
#define REQUESTRESULT_HPP

#include <QNetworkReply>
#include <QVariant>
#include "errortypes.hpp"

/// @class RequestResult
/// @brief Results of a request
class RequestResult
{
	public:
		/// @fn RequestResult(ErrorType errorType,
		///				QVariant parsedResults,
		///				int httpCode,
		///				QString httpReason,
		///				QNetworkReply::NetworkError netError,
		///				QVariantMap parsingErrorInfos);
		/// @brief Constructor
		/// @param errorType Code indicating if an error occured.
		/// @param parsedResults Pure results of the request.
		/// @param httpCode HTTP code of the request
		/// @param httpReason HTTP reason
		/// @param netError Network error of the QNetworkReply
		/// @param parsingErrorInfos Information about potential parsing errors
		RequestResult(ErrorType errorType,
					  QVariant parsedResults,
					  int httpCode,
					  QString httpReason,
					  QNetworkReply::NetworkError netError,
					  QVariantMap parsingErrorInfos);

		/// @fn bool isRequestSuccessful();
		/// @brief Method indicating if the request was successful
		/// @return true if the request was successful, false otherwise.
		bool isRequestSuccessful();

		/// @fn bool isFakeResult();
		/// @brief Method indicating if the request result is fake
		/// @return true if the object is FAKE_REQUEST_RESULT, false otherwise.
		bool isFakeResult();

		/// @fn ErrorType getRequestSuccessful();
		/// @brief Getter on requestSuccessful
		/// @return The value of requestSuccessful
		ErrorType getRequestSuccessful();

		/// @fn QVariant getParsedResult();
		/// @brief Getter on real results
		/// @return The real results of the request
		QVariant getParsedResult();

		/// @fn QVariantMap getHttpInfos();
		/// @brief Getter on httpInfos
		/// @return The value of httpInfos
		QVariantMap getHttpInfos();

		/// @fn QNetworkReply::NetworkError getNetworkError();
		/// @brief Getter on networkError
		/// @return The value of networkError
		QNetworkReply::NetworkError getNetworkError();

		/// @fn QVariantMap getParsingErrors();
		/// @brief Getter on parsingErrors
		/// @return The value of parsingErrors
		QVariantMap getParsingErrors();

		/// @brief Fake request result
		static RequestResult FAKE_REQUEST_RESULT;

	protected:
		/// @brief Code indicating whether an error occured during the request.
		ErrorType requestSuccessful;

		/// @brief Results of the request parsed by QJson.
		QVariant parsedResult;

		/// @brief Information about the pure http request.
		QVariantMap httpInfos;

		/// @brief Code indicating whether a network error occured during
		/// the request.
		QNetworkReply::NetworkError networkError;

		/// @brief Potential errors that can occur while parsing results.
		QVariantMap parsingErrors;
};

#endif // REQUESTRESULT_HPP
