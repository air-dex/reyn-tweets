/// @file requestermanager.hpp
/// @brief Header of RequesterManager
/// @author Romain Ducher

/*
Copyright 2012 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef REQUESTERMANAGER_HPP
#define REQUESTERMANAGER_HPP

#include <QMap>
#include <QUuid>
#include "requestinfos.hpp"

/// @class RequesterManager
/// @brief Entity storing requests while they are executed. They are indexed
/// with a UUID.
class RequesterManager : protected QMap<QUuid, RequestInfos>
{
	public:
		/// @fn RequesterManager();
		/// @brief Constructs an empty map
		RequesterManager();

		/// @fn RequestInfos & getRequestInfos(QUuid requestUuid);
		/// @brief Getter on request informations
		/// @param requestUuid UUID of the requester
		RequestInfos & getRequestInfos(QUuid requestUuid);

		/// @fn void addRequest(QObject * asker, GenericRequester * requester);
		/// @brief Storing a request
		/// @param asker Entity that asks for the request
		/// @param requester Entity that executing the request
		void addRequest(QObject * asker, GenericRequester * requester);

		/// @fn void removeRequest(QUuid requestUuid);
		/// @brief Removing a request from the manager
		/// @param requestUuid UUID of the requester
		void removeRequest(QUuid requestUuid);
};

#endif // REQUESTERMANAGER_HPP
