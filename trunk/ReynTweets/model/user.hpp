/// @file user.hpp
/// @brief Header of User
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

#ifndef USER_HPP
#define USER_HPP

#include <QObject>
#include <QString>
#include <QDate>
#include <QColor>
#include "reyntweetsserializable.hpp"
#include "tweet.hpp"

/// @class User
/// @brief Person who uses Twitter
class User : public ReynTweetsSerializable
{
	Q_OBJECT

	public:
		User(QObject *parent = 0);

	signals:

	public slots:

	protected:
		// User ID

		/// @brief User ID
		int userID;

		/// @brief User ID (String version)
		QString userIDstr;

		// Identity of the user

		/// @brief Screen name ("toto" in "@toto", for example).
		QString screenName;

		/// @brief User's name
		QString name;

		/// @brief Description
		QString description;

		/// @brief URL of the user
		QString userURL;

		/// @brief Location as reported by the user
		QString location;

		// Avatar

		/// @brief Boolean indicating if the profile image is the default image
		bool defaultProfileImage;

		/// @brief URL of the user's avatar.
		QString avatarURL;

		/// @brief URL of the user's avatar (HTTPS version).
		QString avatarURLhttps;

		// User statistics

		/// @brief Number of tweets
		int tweetsCount;

		/// @brief Last tweet posted by the user
		Tweet lastTweet;

		/// @brief Number of friends (people followed by the user)
		int friendsCount;

		/// @brief Number of followers
		int followersCount;

		/// @brief Number of favorites tweets
		int favoritesCount;

		/// @brief Number of lists
		int listsCount;

		// Theme

		/// @brief Is it the default profile ?
		bool defaultProfile;

		/// @brief Boolean indicating if the user has got a background image.
		bool useBackgroundImage;

		/// @brief Is the background repeated as a tile ("mosaïque" in French) ?
		bool backgroundTile;

		/// @brief URL of the user's background.
		QString backgroundURL;

		/// @brief URL of the user's background (HTTPS version).
		QString backgroundURLhttps;

		/// @brief Background color
		QColor backgroundColor;

		/// @brief Color of text in the Twitter Timeline
		QColor textColor;

		/// @brief Color of links in the Twitter Timeline
		QColor linkColor;

		/// @brief Color of sidebar panels. For example, these panels are on
		/// your right when you watch your Twitter parameters online.
		QColor sidebarColor;

		/// @brief Color of the border of sidebar panels.
		QColor sidebarBorderColor;

		// Location

		/// @brief Time zone
		int timezoneOffset;

		/// @brief Name of the user's time zone
		QString timezone;

		// Other parameters

		/// @brief Date when the account was created
		QDate createdAt;

		/// @brief User's idiom
		QString lang;

		/// @brief Boolean indicating if the user protects its account
		bool protectedAccount;

		/// @brief Boolean indicating if the user gives a geolocalisation
		/// by default to its tweets.
		bool geotaggingEnabled;

		/// @brief Boolean indicating if the account is verified
		bool verifiedAccount;

		/// @brief Is the contributors feature enable for the user ?
		/// @see http://blog.twitter.com/2009/12/feature-test-with-businesses.html
		bool contributorsEnabled;

		/// @brief Indicates if the user is a Twitter translator
		bool twitterTranslator;

		// Miscanellous

		/// @brief follow_request_sent
		bool followRequestSent;

		/// @brief show_all_inline_media

		/// @brief Receive notifications from a user (by mobile phone)
		bool notifications;
};

#endif // USER_HPP
