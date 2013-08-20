/// @file basicauthenticators.hpp
/// @brief Typedefs of BasicAuthenticator and TokenPair
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

#ifndef BASICAUTHENTICATORS_HPP
#define BASICAUTHENTICATORS_HPP

#include <QByteArray>
#include <QPair>
#include <QString>

/// @typedef QPair <QString, QByteArray> BasicAuthenticator;
/// @brief QPair for classic authentications with a login and a pasword :<ul>
/// <li>first : the login.</li>
/// <li>secret : the password.</li></ul>
/// @see TokenPair
typedef QPair<QString, QByteArray> BasicAuthenticator;

/// @typedef QPair<QByteArray, QByteArray> TokenPair;
/// @brief A token pair.
///
/// A token pair is a QPair whose field are:<ul>
/// <li>first : the public key (token).</li>
/// <li>secret : the private key (secret).</li>
/// </ul>
typedef QPair<QByteArray, QByteArray> TokenPair;

#endif // BASICAUTHENTICATORS_HPP
