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
#include "../model/configuration/reyntweetssettings.hpp"

class TwitLongerManager {
	public:
		/// @fn TwitLongerManager(QString appName = ReynTweetsSettings::getInstance().getTwitLongerAppName(),
		///						  QByteArray key = ReynTweetsSettings::getInstance().getTwitLongerAPIKey());
		/// @brief Constructor
		/// @param appName Name of the application on TwitLonger
		/// @param key Key of the application on TwitLonger
		TwitLongerManager(QString appName = ReynTweetsSettings::getInstance().getTwitLongerAppName(),
						  QByteArray key = ReynTweetsSettings::getInstance().getTwitLongerAPIKey());

		/// @fn QString getApplicationName();
		/// @brief Getting the application name
		/// @return applicationName
		QString getApplicationName();

		/// @fn QByteArray getAPIKey(bool isClear = true);
		/// @brief Getting the OAuth Token
		/// @param isClear Boolean indicating if the clear value is asked
		/// @return apiKey
		QByteArray getAPIKey(bool isClear = true);

	protected:
		/// @brief Name of the application on TwitLonger
		QString applicationName;

		/// @brief API Key of the application on TwitLonger
		QByteArray apiKey;
};

#endif // TWITLONGERMANAGER_HPP
