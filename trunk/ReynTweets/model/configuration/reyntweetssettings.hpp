/// @file reyntweetssettings.hpp
/// @brief Declaration of the ReynTweetsSettings namespace
///
/// Revisions older than r242 were in /trunk/ReynTweets/connection
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

#ifndef REYNTWEETSSETTINGS_HPP
#define REYNTWEETSSETTINGS_HPP

#include <QDataStream>
#include <QString>
#include <QVariant>
#include "../../logic/coreresult.hpp"
#include "../reyntweetsmappable.hpp"

/// @class ReynTweetsSettings
/// @brief Class with Reyn Tweets settings.
///
/// The settings are keys, constants and passwords for the following APIs or
/// services :<ul>
/// <li><a href="https://dev.twitter.com/">Twitter API</a></li>
/// <li><a href="http://www.twitlonger.com">TwitLonger</a></li>
/// <li><a href="http://getpocket.com">Pocket</a></li>
/// <li>More to come...</li>
/// <ul>
class ReynTweetsSettings {

	public:
		////////////////////////
		// Getter on settings //
		////////////////////////

		/// @fn static ReynTweetsSettings & getInstance()
		/// @brief Getting a reference on the unique instance.
		/// @return A reference on the value contained in the instance pointer.
		static ReynTweetsSettings & getInstance();

		/// @fn QByteArray getConsumerKey();
		/// @brief Getter on the Twitter OAuth consumer key.
		/// @return CONSUMER_KEY
		QByteArray getConsumerKey();

		/// @fn QByteArray getConsumerSecret();
		/// @brief Getter on the Twitter OAuth consumer secret.
		/// @return CONSUMER_SECRET
		QByteArray getConsumerSecret();

		/// @fn QString getCallbackURL();
		/// @brief Getter on the Twitter callback URL.
		/// @return CALLBACK_URL
		QString getCallbackURL();

		/// @fn QString getTwitLongerAppName();
		/// @brief Getter on the TwitLonger application name.
		/// @return TWITLONGER_APP_NAME
		QString getTwitLongerAppName();

		/// @fn QByteArray getTwitLongerAPIKey();
		/// @brief Getter on the TwitLonger API key.
		/// @return TWITLONGER_API_KEY
		QByteArray getTwitLongerAPIKey();

		/// @fn QByteArray getPocketAPIKey();
		/// @brief Getter on the Pocket API key.
		/// @return POCKET_API_KEY
		QByteArray getPocketAPIKey();


	private:
		/////////////////////
		// Core management //
		/////////////////////

		/// @brief Unique instance of the class
		static ReynTweetsSettings * instance;

		/// @fn ReynTweetsSettings();
		/// @brief Private constructor
		ReynTweetsSettings();

		/// @fn CoreResult loadSettings();
		/// @brief Loading the settings from the settings file.
		CoreResult loadSettings();

		/// @brief Name of the file containing the settings
		static QString SETTINGS_NAMEFILE;


	protected:
		//////////////
		// Settings //
		//////////////

		//////////////////////////////
		// Twitter Settings (OAuth) //
		//////////////////////////////

		/// @brief Twitter OAuth consumer key.
		QByteArray CONSUMER_KEY;

		/// @brief Twitter OAuth consumer secret.
		QByteArray CONSUMER_SECRET;

		/// @brief Twitter callback URL
		QString CALLBACK_URL;


		////////////////
		// TwitLonger //
		////////////////

		/// @brief Name of Reyn Tweets in the TwitLonger API
		QString TWITLONGER_APP_NAME;

		/// @brief TwitLonger API key.
		QByteArray TWITLONGER_API_KEY;


		////////////////////////////////////////////////
		// Pocket (formerly known as "Read It Later") //
		////////////////////////////////////////////////

		/// @brief Pocket API key.
		QByteArray POCKET_API_KEY;
};

#endif // REYNTWEETSSETTINGS_HPP
