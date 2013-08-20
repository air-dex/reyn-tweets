/// @file networkresulttype.hpp
/// @brief Header containing the Network::NetworkResultType enum
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011, 2012 Romain Ducher
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

#ifndef ERRORTYPES_HPP
#define ERRORTYPES_HPP

namespace Network {
	/// @enum ErrorType
	/// @brief Enumeration which indicates if something bad happened during the
	/// request. It can takes three values depending on what happened. See the
	/// enum values for more details.
	enum NetworkResultType {
		/// @brief Code indicating that there was no error.
		NO_REQUEST_ERROR,

		/// @brief Code for an invalid request result.
		INVALID_RESULT,

		/// @brief Code indicating that there were an error while calling the API.
		API_CALL,

		/// @brief Code indicating that the service (ex. Twitter) has returned errors.
		SERVICE_ERRORS,

		/// @brief Code indicating that there was an error while parsing JSON.
		JSON_PARSING,

		/// @brief Code indicating that there was an error while parsing results
		/// under the form <code>arg1=val1&arg2=val2&...&argN=valN</code>.
		OAUTH_PARSING,

		/// @brief Code indicating that there was an error while parsing HTML.
		HTML_PARSING,

		/// @brief Code indicating that there was an error while parsing XML.
		XML_PARSING,

		/// @brief Code indicating that there is not any parsing.
		NO_PARSING
	};
}

using Network::NetworkResultType;

#endif // ERRORTYPES_HPP
