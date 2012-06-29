/// @file headersmap.hpp
/// @brief Header with the definition of ArgsMap and HeadersMap.
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012 Romain Ducher
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

#ifndef HEADERSMAP_HPP
#define HEADERSMAP_HPP

#include <QByteArray>
#include <QMap>
#include <QString>

/// @typedef QMap<QByteArray, QByteArray> ArgsMap
/// @brief Convinience to designate QMaps that contains GET and POST arguments
typedef QMap<QString, QString> ArgsMap;

/// @typedef QMap<QString, QString> HeadersMap
/// @brief Convinience to designate QMaps that contains HTTP headers
typedef QMap<QByteArray, QByteArray> HeadersMap;

#endif // HEADERSMAP_HPP
