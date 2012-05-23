/// @file twitlongermanager.cpp
/// @brief Implementation of TwitLongerManager
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

#include "twitlongermanager.hpp"

// Constructor
TwitLongerManager::TwitLongerManager() :
	applicationName(""),
	apiKey("")
{}

// Getting the application name
QString TwitLongerManager::getApplicationName() {
	return applicationName;
}

// Setting the application name
void TwitLongerManager::setApplicationName(QString newAppName) {
	applicationName = newAppName;
}

// Getting the API Key
QByteArray TwitLongerManager::getAPIKey(bool isClear) {
	return isClear ? QByteArray::fromBase64(apiKey) : apiKey;
}

// Setting the API Key
void TwitLongerManager::setAPIKey(QByteArray newAPIKey) {
	apiKey = newAPIKey;
}
