/// @file twitlongermanager.hpp
/// @brief Header of TwitLongerManager
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

#ifndef TWITLONGERMANAGER_HPP
#define TWITLONGERMANAGER_HPP

#include <QByteArray>
#include <QString>
#include "../../model/configuration/reyntweetsappconfiguration.hpp"

/// @class TwitLongerManager
/// @brief Entity with all the informations needed for transactions with the
/// TwitLonger API.
class TwitLongerManager {
	public:
		/// @fn TwitLongerManager();
		/// @brief Default constructor. Settings will be filled later.
		TwitLongerManager();

		/// @fn QString getApplicationName();
		/// @brief Getting the application name
		/// @return applicationName
		QString getApplicationName();

		/// @fn void setApplicationName(QString newAppName);
		/// @brief Setting the application name
		/// @param newAppName New value for applicationName
		void setApplicationName(QString newAppName);

		/// @fn QByteArray getAPIKey(bool isClear = true);
		/// @brief Getting the API key
		/// @param isClear Boolean indicating if the clear value is asked
		/// (instead of the encrypted value).
		/// @return apiKey
		QByteArray getAPIKey(bool isClear = true);

		/// @fn void setAPIKey(QByteArray newAPIKey);
		/// @brief Setting the API key
		/// @param newAPIKey New value for apiKey
		void setAPIKey(QByteArray newAPIKey);

	protected:
		/// @brief Name of the application on TwitLonger
		QString applicationName;

		/// @brief API Key of the application on TwitLonger
		QByteArray apiKey;
};

#endif // TWITLONGERMANAGER_HPP
