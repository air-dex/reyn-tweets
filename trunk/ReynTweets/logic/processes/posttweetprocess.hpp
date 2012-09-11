/// @file posttweetprocess.hpp
/// @brief Header of PostTweetProcess
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

#ifndef POSTTWEETPROCESS_HPP
#define POSTTWEETPROCESS_HPP

#include "singletwittercallprocess.hpp"

/// @class PostTweetProcess
/// @brief Process to update a tweet (aka tweeting) without medias.
class PostTweetProcess : public SingleTwitterCallProcess
{
	Q_OBJECT

	public:
		/// @fn PostTweetProcess(QString status,
		///						 QString replyTostatusID = "-1",
		///						 bool userIDonly = true,
		///						 float lat = -361,
		///						 float lon = -361,
		///						 QString place = "",
		///						 bool showCoord = false);
		/// @brief Constructor
		/// @param status Text of the tweet
		/// @param replyTostatusID If the tweet is a reply, this parameter is
		/// the ID of the tweet that this tweet replies to.
		/// @param userIDonly In tweets, giving only the ID of the author (true).
		/// @param withEntities Including Tweet Entities in the tweets (true).
		/// @param lat For geolocation, your longitude.
		/// @param lon For geolocation, your latitude.
		/// @param place For geolocation, ID of the place where the tweet
		/// is supposed to be sent
		/// @param showCoord Displaying the coordonates of the tweet
		/// with a pin on a map
		PostTweetProcess(QString status,
						 QString replyTostatusID = "-1",
						 bool userIDonly = true,
						 float lat = -361,
						 float lon = -361,
						 QString place = "",
						 bool showCoord = false);

		/// @fn PostTweetProcess(QString status,
		///						 qlonglong replyTostatusID = -1,
		///						 bool userIDonly = true,
		///						 float lat = -361,
		///						 float lon = -361,
		///						 QString place = "",
		///						 bool showCoord = false);
		/// @brief Constructor
		/// @param status Text of the tweet
		/// @param replyTostatusID If the tweet is a reply, this parameter is
		/// the ID of the tweet that this tweet replies to.
		/// @param userIDonly In tweets, giving only the ID of the author (true).
		/// @param lat For geolocation, your longitude.
		/// @param lon For geolocation, your latitude.
		/// @param place For geolocation, ID of the place where the tweet
		/// is supposed to be sent
		/// @param showCoord Displaying the coordonates of the tweet
		/// with a pin on a map
		PostTweetProcess(QString status,
						 qlonglong replyTostatusID = -1,
						 bool userIDonly = true,
						 float lat = -361,
						 float lon = -361,
						 QString place = "",
						 bool showCoord = false);



	protected:
		/// @brief Text to post
		QString tweet;

		/// @brief ID of the tweet that this status replies to
		qlonglong replyToTweetID;

		/// @brief Only include the userID in the "user" field of a tweet
		bool trimUser;

		/// @brief Longitude of the tweet
		float longitude;

		/// @brief Latitude of the tweet
		float latitude;

		/// @brief place where the tweet was supposed to be sent
		QString reversePlace;

		/// @brief Displaying coordonates on a map
		bool displayCoord;

		/// @fn void callTwitter();
		/// @brief Updating the tweet
		void callTwitter();
};

#endif // POSTTWEETPROCESS_HPP
