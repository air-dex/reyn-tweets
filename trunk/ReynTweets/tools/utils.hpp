/// @file utils.hpp
/// @brief Header with useful methods
///
/// Revisions older than r120 are in the folder /trunk/ReynTweets/connection/
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

#ifndef UTILS_HPP
#define UTILS_HPP

#include <QByteArray>
#include <QColor>
#include <QDataStream>
#include <QString>
#include "../connection/requests/requesttype.hpp"

///////////////////////
// String convertion //
///////////////////////

/// @fn QString requestTypeToString(RequestType type)
/// @brief Converting a RequestType into a QString
/// @param type The RequestType
/// @return The corresponding QString
QString requestTypeToString(RequestType type);

/// @fn QString boolInString(bool b);
/// @brief Converting a bool into a QString
/// @param b The boolean
/// @return The corresponding QString
QString boolInString(bool b);

/// @fn QColor string2color(QString coloredString);
/// @brief Converting a String into a QColor.
///
/// This function was written because of Twitter which forgets the '#'
/// character before the hexadecimal code under the form 'RRGGBB'.
/// @param coloredString The string with the RRGGBB format.
/// @return The corresponding color : &#135;RRGGBB
QColor string2color(QString coloredString);


////////////////////
// JSON Streaming //
////////////////////

/// @fn QDataStream & jsonStreamingOut(QDataStream & out,
///									   const QObject & objectToStream,
///									   const QStringList & blacklist =
///											QStringList(QString(QLatin1String("objectName"))));
/// @brief Output stream operator for JSON serialization
/// @param out The output stream
/// @param objectToStream Object to put in the stream
/// @param blacklist Properties to ignore while conserting the QObject into
/// a QVariant before serializing.
/// @return The stream with the object
QDataStream & jsonStreamingOut(QDataStream & out,
							   const QObject & objectToStream,
							   const QStringList & blacklist = QStringList(QString(QLatin1String("objectName"))));

/// @fn QDataStream & jsonStreamingIn(QDataStream & in, QObject & objectToStream);
/// @brief Input stream operator for JSON serialization
/// @param in The input stream
/// @param objectToStream Object to put in the stream
/// @return The stream with the object
QDataStream & jsonStreamingIn(QDataStream & in, QObject & objectToStream);


//////////////////
// Miscanellous //
//////////////////

/// @fn QString hmacSha1(QByteArray key, QByteArray baseString);
/// @brief HMAC-SHA1 algorithm for signatures.
///
/// Its implementation for Reyn Tweets was found on the
/// <a href="http://developer.qt.nokia.com/">Qt Developer Network</a> here :
/// <a href="http://developer.qt.nokia.com/wiki/HMAC-SHA1">
/// http://developer.qt.nokia.com/wiki/HMAC-SHA1</a>.
/// @param key Key for signature
/// @param baseString String that we want to sign
/// @return The signature
QString hmacSha1(QByteArray key, QByteArray baseString);

/// @fn bool ouBien(bool a, bool b);
/// @brief Logical XOR : <code>a XOR b == a && !b || !a && b</code>
/// @param a 1st bool
/// @param b 2nd bool
bool ouBien(bool a, bool b);

/// @fn QString formatParam(QString name, QString value, bool putDoubleQuotes = false);
/// @brief Method for formatting parameters in the Authorization header,
/// for GET and POST request parameters, and in the signature.
///
/// The process of how formatting parameters is described
/// <a href="https://dev.twitter.com/docs/auth/authorizing-request">here
/// </a> for the Authorization header and
/// <a href="https://dev.twitter.com/docs/auth/creating-signature">here
/// </a> for the signature. The difference between these two algorithm
/// is that double quotes '"' surrounds the percent encoded value for
/// the Authorization Header and not for the signature.
/// @param name Name of the parameter
/// @param value Value of the parameter
/// @param putDoubleQuotes Boolean indicating if double quotes have to
/// surround the percent encoded value.
/// @return The formatted parameters
QString formatParam(QString name, QString value, bool putDoubleQuotes = false);

#endif // UTILS_HPP
