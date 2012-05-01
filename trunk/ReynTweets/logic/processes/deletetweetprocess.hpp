/// @file deletetweetprocess.hpp
/// @brief Header of DeleteTweetProcess
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

#ifndef DELETETWEETPROCESS_HPP
#define DELETETWEETPROCESS_HPP

#include "genericprocess.hpp"
#include "../../connection/reyntwittercalls.hpp"
#include "../../model/tweets/tweet.hpp"

/// @class DeleteTweetProcess
/// @brief Processus for deleting a tweet
class DeleteTweetProcess : public GenericProcess
{
	Q_OBJECT

	public:
		/// @fn DeleteTweetProcess(UserInfos & u,
		///						   Tweet statusToDelete,
		///						   bool withEntities = true,
		///						   bool userIDonly = false);
		/// @brief Constructor
		/// @param u User who want to delete the tweet.
		/// @param statusToDelete The tweet to delete
		/// @param withEntities Including Tweet Entities ?
		/// @param userIDonly Omit user details in the reply ?
		DeleteTweetProcess(UserInfos & u,
						   Tweet statusToDelete,
						   bool withEntities = true,
						   bool userIDonly = false);

		/// @fn ~DeleteTweetProcess();
		/// @brief Destructor
		~DeleteTweetProcess();

		/// @fn void startProcess();
		/// @brief Starting the process by determining if the tweet can be deleted.
		void startProcess();


	protected:
		/// @brief Entity calling Twitter
		ReynTwitterCalls twitter;

		/// @brief Configuration
		UserInfos & user;

		/// @brief ID of the tweet to favorite
		Tweet tweetToDelete;

		/// @brief Include Tweet Entities of the tweet in the reply ?
		bool includeEntities;

		/// @brief Only include the userID in the "user" field of a tweet
		bool trimUser;

		/// @brief Indicates if the tweet has to be kept in the timeline
		/// after the deletion.
		bool keepInTimeline;


	/////////////////
	// The process //
	/////////////////

		/// @fn void canDeleteTweet();
		/// @brief Determining if the tweet can be deleted
		void canDeleteTweet();

	signals:
		/// @fn void allowDelete(bool allowToDelete, QString addInfos);
		/// @brief Send after determining if the tweet can be deleted
		/// @param allowToDelete Boolean determining if the tweet can be deleted
		/// (true, false otherwise).
		/// @param addInfos Additionnal informations for the deletion
		/// (ID of the tweet to delete or message explaining why the tweet
		/// won't be destroyed).
		void allowDelete(bool allowToDelete, QString addInfos);

	protected slots:
		/// @fn void searchRetweetIDEnded(RequestResult res);
		/// @brief After searching the ID of the retweet
		/// @param res Result of the request
		void searchRetweetIDEnded(ResultWrapper res);

		/// @fn void deleteTweet(bool allowToDelete, QString addInfos);
		/// @brief Deleting the tweet
		/// @param allowToDelete Boolean determining if the tweet can be deleted
		/// (true, false otherwise).
		/// @param addInfos Additionnal informations for the deletion
		/// (ID of the tweet to delete or message explaining why the tweet
		/// won't be destroyed).
		void deleteTweet(bool allowToDelete, QString addInfos);

		/// @fn void deleteEnded(RequestResult res);
		/// @brief After deleting the tweet
		/// @param res Result of the request
		void deleteEnded(ResultWrapper res);
};

#endif // DELETETWEETPROCESS_HPP
