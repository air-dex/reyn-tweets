/// @file utils.hpp
/// @brief Header with useful methods<br/>
/// Revisions older than r120 are in the folder /trunk/ReynTweets/connection/
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
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef UTILS_HPP
#define UTILS_HPP

#include <QByteArray>
#include <QDataStream>
#include <QString>
#include "../connection/requesttype.hpp"

/// @fn QString hmacSha1(QByteArray key, QByteArray baseString);
/// @brief HMAC-SHA1 algorithm for signatures. Its implementation for
/// Reyn Tweets was found on the <a href="http://developer.qt.nokia.com/">
/// Qt Developer Network</a> here :
/// <a href="http://developer.qt.nokia.com/wiki/HMAC-SHA1">
/// http://developer.qt.nokia.com/wiki/HMAC-SHA1</a>.
/// @param key Key for signature
/// @param baseString String that we want to sign
/// @return The signature
QString hmacSha1(QByteArray key, QByteArray baseString);

/// @fn QString requestTypeToString(RequestType type)
/// @brief Converting a RequestType into a QString
/// @param type The RequestType
/// @return The corresponding QString
QString requestTypeToString(RequestType type);

/// @fn ouBien(bool a, bool b);
/// @brief Logical XOR :<code>a XOR b == a && !b || !a && b</code>
/// @param a 1st bool
/// @param b 2nd bool
bool ouBien(bool a, bool b);


////////////////////
// JSON Streaming //
////////////////////

/// @fn static QDataStream & jsonStreamOut(QDataStream & out, const QObject & objectToStream);
/// @brief Output stream operator for JSON serialization
/// @param out The output stream
/// @param objectToStream Object to put in the stream
/// @return The stream with the object
QDataStream & jsonStreamingOut(QDataStream & out, const QObject & objectToStream);

/// @fn static QDataStream & jsonStreamIn(QDataStream & in, QObject & objectToStream);
/// @brief Input stream operator for JSON serialization
/// @param in The input stream
/// @param objectToStream Object to put in the stream
/// @return The stream with the object
QDataStream & jsonStreamingIn(QDataStream & in, QObject & objectToStream);

#endif // UTILS_HPP
