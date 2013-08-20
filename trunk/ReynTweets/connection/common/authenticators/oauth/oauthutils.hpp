/// @file oauthutils.hpp
/// @brief Utilities for OAuth (header)
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2013 Romain Ducher
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

#ifndef OAUTHUTILS_HPP
#define OAUTHUTILS_HPP

#include <QByteArray>
#include <QString>

/// @fn QString generateNonce();
/// @brief Generates a nonce for a request. To generate a nonce,
/// a random string is generated by taking 32 times one letter in the
/// alphabet. The letter could be in upper case or lower case. The final
/// nonce is the 64 base-encoding of the random string.
/// @return A nonce for a request.
QString generateNonce();

/// @fn QString generateTimestamp();
/// @brief Generates a timestamp for a request. The timestamp is the
/// number of seconds since the Unix Epoch (1/1/1970 at midnight).
/// @return A timestamp corresponding to the current date.
QString generateTimestamp();

/// @fn QByteArray hmacSha1(QByteArray key, QByteArray baseString);
/// @brief HMAC-SHA1 algorithm for signatures.
///
/// Its implementation for Reyn Tweets was found on the
/// <a href="http://qt-project.org">Qt Project website</a> here :
/// <a href="http://qt-project.org/wiki/HMAC-SHA1">
/// http://qt-project.org/wiki/HMAC-SHA1</a>.
/// @param key Key for signature
/// @param baseString String that we want to sign
/// @return The signature
QByteArray hmacSha1(QByteArray key, QByteArray baseString);

#endif // OAUTHUTILS_HPP
