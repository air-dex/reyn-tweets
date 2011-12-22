/// @file utils.hpp
/// @brief Header with useful methods
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
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef UTILS_HPP
#define UTILS_HPP

#include <QByteArray>
#include <QString>
#include "requesttype.hpp"

/// @class Utils
/// @brief Utilities
class Utils
{
	public:
		/// @fn QString hmacSha1(QByteArray key, QByteArray baseString);
		/// @brief HMAC-SHA1 algorithm for signatures. Its implementation for
		/// Reyn Tweets was found on the <a href="http://developer.qt.nokia.com/">
		/// Qt Developer Network</a> here :
		/// <a href="http://developer.qt.nokia.com/wiki/HMAC-SHA1">
		/// http://developer.qt.nokia.com/wiki/HMAC-SHA1</a>.
		/// @param key Key for signature
		/// @param baseString String that we want to sign
		/// @return The signature
		static QString hmacSha1(QByteArray key, QByteArray baseString);


		/// @fn QString requestTypeToString(RequestType type)
		/// @brief Converting a RequestType into a QString
		/// @param type The RequestType
		/// @return The corresponding QString
		static QString requestTypeToString(RequestType type);
};

#endif // UTILS_HPP
