/// @file connectionutils.hpp
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

#ifndef CONNECTIONUTILS_HPP
#define CONNECTIONUTILS_HPP

#include <QByteArray>
#include <QColor>
#include <QDataStream>
#include <QString>
#include "../httprequesttype.hpp"

///////////////////////
// String convertion //
///////////////////////

/// @fn QString requestTypeToString(Network::HTTPRequestType type)
/// @brief Converting a RequestType into a QString
/// @param type The RequestType
/// @return The corresponding QString
QString requestTypeToString(LibRT::HTTPRequestType type);

/// @fn QString boolInString(bool b);
/// @brief Converting a bool into a QString
/// @param b The boolean
/// @return The corresponding QString
QString boolInString(bool b);


//////////////////
// Miscanellous //
//////////////////

/// @fn bool ouBien(bool a, bool b);
/// @brief Logical XOR : <code>a XOR b == a && !b || !a && b</code>
/// @param a 1st bool
/// @param b 2nd bool
/// @returns a XOR b
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

#endif // CONNECTIONUTILS_HPP
