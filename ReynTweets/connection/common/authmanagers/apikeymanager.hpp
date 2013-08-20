/// @file apikeymanager.cpp
/// @brief Header of APIKeyManager
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

#ifndef APIKEYMANAGER_HPP
#define APIKEYMANAGER_HPP

#include <QByteArray>

/// @class APIKeyManager
/// @brief Base class for Authentication managers with needs a simple API key.
class APIKeyManager
{
	public:
		/// @fn APIKeyManager();
		/// @brief Constructor
		APIKeyManager();

		/// @fn QByteArray getAPIKey();
		/// @brief Getting the API key
		/// @return apiKey
		QByteArray getAPIKey();

		/// @fn void setAPIKey(QByteArray newAPIKey);
		/// @brief Setting the API key
		/// @param newAPIKey New value for apiKey
		void setAPIKey(QByteArray newAPIKey);

	protected:
		/// @brief API Key of the application on TwitLonger
		QByteArray apiKey;
};

#endif // APIKEYMANAGER_HPP
