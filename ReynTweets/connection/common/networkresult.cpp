/// @file networkresponse.cpp
/// @brief Implementation of extractHttpStatusesFromNetworkReply(QNetworkReply)
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

#include "networkresult.hpp"

// Constructor
NetworkResponse::NetworkResponse(LibRT::HTTPCode httpCode,
								 QString httpReason,
								 QByteArray response,
								 QString error,
								 QString repURL) :
	httpResponse(httpCode, httpReason),
	responseBody(response),
	requestError(error),
	replyURL(repURL)
{}

// Building a NetworkResponse with the content of a QNetworkReply.
NetworkResponse::NetworkResponse(QNetworkReply * reply) :
	httpResponse(extractHttpStatusesFromNetworkReply(reply)),
	responseBody(reply ? reply->readAll() : ""),
	requestError(reply ? reply->errorString() : "null reply"),
	replyURL(reply ? reply->url().toString() : LibRT::FAKE_URL)
{}

// Extracting the HTTP code and the HTTP reason from an HTTP reply.
ResponseInfos NetworkResponse::extractHttpStatusesFromNetworkReply(QNetworkReply * reply) {
	ResponseInfos httpResponse;

	if (reply) {
		QVariant httpStatus;

		// Extract return code
		httpStatus = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
		httpResponse.code = httpStatus.toInt();

		// Extract return reason
		httpStatus = reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute);
		httpResponse.message = QString::fromLatin1(httpStatus.toByteArray());
	}


	return httpResponse;
}

/////////////
// Getters //
/////////////

// httpResponse
ResponseInfos NetworkResponse::getHttpResponse() {
	return httpResponse;
}

// responseBody
QByteArray NetworkResponse::getResponseBody() {
	return responseBody;
}

// requestError
QString NetworkResponse::getRequestError() {
	return requestError;
}

// replyURL
QString NetworkResponse::getReplyURL() {
	return replyURL;
}
