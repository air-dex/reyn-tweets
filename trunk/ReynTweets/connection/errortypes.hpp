/// @file errortypes.hpp
/// @brief Header containing the ErrorType enum
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

#ifndef ERRORTYPES_HPP
#define ERRORTYPES_HPP

/// @enum ErrorType
/// @brief Enumeration which indicates if something bad happened during the
/// request. It can takes three values depending on what happened. See the
/// enum values for more details.
enum ErrorType {
	/// @brief Code indicating that there was no error.
	NO_ERROR,

	/// @brief Code for an invalid request result.
	INVALID_RESULT,

	/// @brief Code indicating that there were an error while calling the
	/// Twitter API.
	API_CALL,

	/// @brief Code indicating that Twitter has returned errors.
	TWITTER_ERRORS,

	/// @brief Code indicating that there was an error while parsing results
	/// with <a href="http://qjson.sourceforge.net">QJson</a>.
	QJSON_PARSING,

	/// @brief Code indicating that there was an error while parsing results
	/// under the form <code>arg1=val1&arg2=val2&...&argN=valN</code>.
	OAUTH_PARSING,

	/// @brief Code indicating that there was an error while parsing HTML.
	HTML_PARSING,

	/// @brief Code indicating that there was an error while parsing XML.
	XML_PARSING
};

#endif // ERRORTYPES_HPP
