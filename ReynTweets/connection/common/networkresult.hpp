/// @file networkresponse.hpp
/// @brief Header of NetworkResponse
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

#ifndef NETWORKRESPONSE_HPP
#define NETWORKRESPONSE_HPP

#include <QNetworkReply>
#include "responseinfos.hpp"
#include "utils/librtconstants.hpp"
#include "utils/httpcode.hpp"

/// @struct NetworkResponse
/// @brief Struct with relevant elements of network reply
class NetworkResponse {
	public:

		/// @fn NetworkResponse(LibRT::HTTPCode httpCode = LibRT::INVALID_HTTP_CODE,
		///						QString httpReason = "",
		///						QByteArray response = "",
		///						QString error = "",
		///						QString repURL = LibRT::FAKE_URL);
		/// @brief Full constructor
		/// @param httpCode Value for httpResponse.code.
		/// @param httpReason Value for httpResponse.message.
		/// @param response Value for responseBody.
		/// @param error Value for requestError.
		/// @param repURL Value for replyURL.
		NetworkResponse(LibRT::HTTPCode httpCode = LibRT::INVALID_HTTP_CODE,
						QString httpReason = "",
						QByteArray response = "",
						QString error = "",
						QString repURL = LibRT::FAKE_URL);

		/// @fn NetworkResponse(QNetworkReply reply);
		/// @brief Building a NetworkResponse with the content of a QNetworkReply.
		/// @param reply the QNetworkReply
		NetworkResponse(QNetworkReply * reply);


		/////////////
		// Getters //
		/////////////

		/// @fn ResponseInfos getHttpResponse();
		/// @brief Getter on httpResponse.
		/// @return httpResponse
		ResponseInfos getHttpResponse();

		/// @fn QByteArray getResponseBody();
		/// @brief Getter on responseBody.
		/// @return responseBody
		QByteArray getResponseBody();

		/// @fn QString getRequestError();
		/// @brief Getter on requestError.
		/// @return requestError
		QString getRequestError();

		/// @fn QString getReplyURL();
		/// @brief Getter on replyURL.
		/// @return replyURL
		QString getReplyURL();

	protected:
		/// @brief HTTP rsponse code and reason
		ResponseInfos httpResponse;

		/// @brief Content of the response
		QByteArray responseBody;

		/// @brief Error which happened in the request
		QString requestError;

		/// @brief Reply URL
		QString replyURL;

		/// @fn ResponseInfos extractHttpStatusesFromNetworkReply(QNetworkReply reply);
		/// @brief Extracting the HTTP code and the HTTP reason from an HTTP reply.
		/// @param reply The QNetworkReply containing the reply of the HTTP request.
		/// @return A ResponseInfos with the code and the reason.
		ResponseInfos extractHttpStatusesFromNetworkReply(QNetworkReply * reply);
};

#endif // NETWORKRESPONSE_HPP
