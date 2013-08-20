/// @file reyntweetsconfiguration.hpp
/// @brief Header of ReynTweetsConfiguration
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011, 2012, 2013 Romain Ducher
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

#ifndef APPCONFIGURATION_HPP
#define APPCONFIGURATION_HPP

#include <QByteArray>
#include <QString>
#include <QStringList>
#include <QVariantMap>
#include "../coreresult.hpp"
#include "../json/jsonobject.hpp"

/// @class ReynTweetsAppConfiguration
/// @brief Class with Reyn Tweets settings.
///
/// The settings are keys, constants and passwords for the following APIs or
/// services :<ul>
/// <li><a href="https://dev.twitter.com/">Twitter API</a></li>
/// <li><a href="http://www.twitlonger.com">TwitLonger</a></li>
/// <li><a href="http://getpocket.com">Pocket</a></li>
/// <li>More to come...</li>
/// </ul>
class AppConfiguration : public JsonObject {
	public:
		/// @fn static AppConfiguration & getReynTweetsConfiguration();
		/// @brief Getting the reference on Reyn Tweets' configuration
		/// @return *REYN_TWEETS_CONFIGURATION
		static AppConfiguration & getReynTweetsConfiguration();

		/// @fn static void unleashReyn();
		/// @brief Deletes the REYN_TWEETS_CONFIGURATION pointer, in order to
		/// avoid memory leaks.
		static void unleashReyn();

		/// @fn void reset();
		/// @brief Resets the configuration to a default value
		void reset();

		/// @fn CoreResult load();
		/// @brief Loading the settings from the settings file.
		/// @return Tag describing what happened
		CoreResult load();

		////////////////////////
		// Getter on settings //
		////////////////////////

		/// @fn QString getErrorLoading();
		/// @brief Getter on the error message after loading the settings
		/// @return errorLoading
		QString getErrorLoading();

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


	protected:
		/////////////////////
		// Core management //
		/////////////////////

		/// @fn ReynTweetsAppConfiguration();
		/// @brief Constructor
		AppConfiguration();

		/// @brief Unique instance of the configuration
		static AppConfiguration * REYN_TWEETS_CONFIGURATION;

		/// @brief Name of the file containing the settings
		static QString SETTINGS_NAMEFILE;

		/// @brief Error while loading the settings
		QString errorLoading;


		/////////////////////
		// JSON conversion //
		/////////////////////

		/// @fn virtual void fillWithVariant(QJsonObject json);
		/// @brief Filling the object with a QJsonObject.
		///
		/// The method is virtual because its implementation depends on the
		/// object type.
		/// @param json The QJsonObject used to fill the JsonObject
		virtual void fillWithVariant(QJsonObject json);

		/// @fn virtual QJsonObject toVariant() const;
		/// @brief Getting a QJsonObject representation of the object
		///
		/// The method is unused. It is here just because it needs to be
		/// implemented.
		/// @return The QJsonObject representation
		virtual QJsonObject toVariant() const;


		//////////////
		// Settings //
		//////////////

		//////////////////////////////
		// Twitter Settings (OAuth) //
		//////////////////////////////

		/// @property consumer_key
		/// @brief Twitter OAuth consumer key
		///
		/// CONSUMER_KEY is the attribute beneath the property.
		Q_PROPERTY(QByteArray consumer_key
				   READ getConsumerKey)

		/// @brief Name of the property consumer_key.
		static QString CONSUMER_KEY_PN;

		/// @brief Twitter OAuth consumer key.
		QByteArray consumerKey;

		/// @property consumer_secret
		/// @brief Twitter OAuth consumer secret
		///
		/// CONSUMER_SECRET is the attribute beneath the property.
		Q_PROPERTY(QByteArray consumer_secret
				   READ getConsumerSecret)

		/// @brief Name of the property consumer_secret.
		static QString CONSUMER_SECRET_PN;

		/// @brief Twitter OAuth consumer secret.
		QByteArray consumerSecret;

		/// @property callback_url
		/// @brief Callback URL for Twitter OAuth authentication
		///
		/// CALLBACK_URL is the attribute beneath the property.
		Q_PROPERTY(QString callback_url
				   READ getCallbackURL)

		/// @brief Name of the property callback_url.
		static QString CALLBACK_URL_PN;

		/// @brief Twitter callback URL
		QString callbackURL;


		////////////////
		// TwitLonger //
		////////////////

		/// @property twitlonger_application_name
		/// @brief Appilcation name in Twitlonger
		///
		/// TWITLONGER_APP_NAME is the attribute beneath the property.
		Q_PROPERTY(QString twitlonger_application_name
				   READ getTwitLongerAppName)

		/// @brief Name of the property twitlonger_application_name.
		static QString TWITLONGER_APP_NAME_PN;

		/// @brief Name of Reyn Tweets in the TwitLonger API
		QString twitlongerAppName;

		/// @property twitlonger_api_key
		/// @brief Twitlonger API key
		///
		/// TWITLONGER_APP_NAME is the attribute beneath the property.
		Q_PROPERTY(QByteArray twitlonger_api_key
				   READ getTwitLongerAPIKey)

		/// @brief Name of the property twitlonger_api_key.
		static QString TWITLONGER_API_KEY_PN;

		/// @brief TwitLonger API key.
		QByteArray twitlongerAPIKey;


		////////////////////////////////////////////////
		// Pocket (formerly known as "Read It Later") //
		////////////////////////////////////////////////

		/// @property pocket_api_key
		/// @brief Pocket API key.
		///
		/// POCKET_API_KEY is the attribute beneath the property.
		Q_PROPERTY(QByteArray pocket_api_key
				   READ getPocketAPIKey)

		/// @brief Name of the property pocket_api_key.
		static QString POCKET_API_KEY_PN;

		/// @brief Pocket API key.
		QByteArray pocketAPIKey;
};

#endif // APPCONFIGURATION_HPP
