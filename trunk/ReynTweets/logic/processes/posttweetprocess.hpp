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
#include "../core/tweets/tweet.hpp"

/// @class PostTweetProcess
/// @brief Process to update a tweet (aka tweeting) without medias.
class PostTweetProcess : public SingleTwitterCallProcess
{
	Q_OBJECT

	public:
		/// @fn PostTweetProcess(Tweet status,
		///						 bool userIDonly = true,
		///						 bool showCoord = false);
		/// @brief Constructor
		/// @param status Tweet to post.
		/// @param userIDonly In tweets, giving only the ID of the author (true).
		/// @param showCoord Displaying the coordonates of the tweet
		/// with a pin on a map
		PostTweetProcess(Tweet status,
						 bool userIDonly = true,
						 bool showCoord = false);

	protected:
		/// @brief Tweet to post. It almost contains all that the Twitter API
		/// needs for updating it.
		Tweet tweet;

		/// @brief Only include the userID in the "user" field of a tweet
		bool trimUser;

		/// @brief Displaying coordonates on a map
		bool displayCoord;

		/// @fn void callTwitter();
		/// @brief Updating the tweet
		void callTwitter();
};

#endif // POSTTWEETPROCESS_HPP
