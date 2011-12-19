/// @file requesttype.hpp
/// @brief Header of RequestType
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

#ifndef REQUESTTYPE_HPP
#define REQUESTTYPE_HPP

#include <QString>

/// @enum RequestType
/// @brief Enum indicating the type of the request
enum RequestType {
	GET,
	POST
};

/// @fn QString requestTypeToString(RequestType type)
/// @brief Converting a RequestType into a QString
/// @param type The RequestType
/// @return The corresponding QString
QString requestTypeToString(RequestType type) {
	switch (type) {
		case GET:
			return "GET";
		case POST:
			return "POST";
		default:
			return "";
	}
}

#endif // REQUESTTYPE_HPP
