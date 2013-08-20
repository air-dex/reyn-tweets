/// @file twitlongerauthenticator.hpp
/// @brief Header of TwitLongerAuthenticator
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

#ifndef TWITLONGERAUTHENTICATOR_HPP
#define TWITLONGERAUTHENTICATOR_HPP

#include <QString>
#include "../common/authenticators/apikeyauthenticator.hpp"

/// @class TwitLongerAuthenticator
/// @brief Entity with all the informations needed for transactions with the
/// TwitLonger API.
class TwitLongerAuthenticator : public APIKeyAuthenticator
{
	public:
		/// @fn TwitLongerAuthenticator();
		/// @brief Default constructor. Settings will be filled later.
		TwitLongerAuthenticator();

		/// @fn QString getApplicationName();
		/// @brief Getting the application name
		/// @return applicationName
		QString getApplicationName();

		/// @fn void setApplicationName(QString newAppName);
		/// @brief Setting the application name
		/// @param newAppName New value for applicationName
		void setApplicationName(QString newAppName);

	protected:
		/// @brief Name of the application on TwitLonger
		QString applicationName;
};

#endif // TWITLONGERAUTHENTICATOR_HPP
