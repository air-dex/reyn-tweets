/// @file unfavoriteprocess.hpp
/// @brief Header of UnfavoriteProcess
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

#ifndef UNFAVORITEPROCESS_HPP
#define UNFAVORITEPROCESS_HPP

#include "genericprocess.hpp"
#include "../../connection/reyntwittercalls.hpp"

class UnfavoriteProcess : public GenericProcess
{
	Q_OBJECT

	public:
		/// @fn explicit UnfavoriteProcess(qlonglong id);
		/// @brief Constructor
		/// @param id ID of the tweet
		explicit UnfavoriteProcess(qlonglong id);

		/// @fn void startProcess() = 0;
		/// @brief Start the process calling twitter to unfavorite the tweet
		void startProcess();

	public slots:
		/// @fn void unfavoriteEnded(ResultWrapper res);
		/// @brief Slot executing after unfavoriting the tweet
		/// @param res Result of the request
		void unfavoriteEnded(ResultWrapper res);

	protected:
		/// @brief Entity calling Twitter
		ReynTwitterCalls twitter;

		/// @brief ID of the tweet to unfavorite
		qlonglong tweetID;

		/// @fn void unfavoriteTweet();
		/// @brief Entry point of the process
		void unfavoriteTweet();

		/// @fn void buildResult(bool processOK,
		///						 CoreResult issue,
		///						 QString errMsg = "",
		///						 bool isFatal = false
		///						 QVariantMap tweetMap = QVariantMap());
		/// @brief Building process results
		/// @param processOK Did the process end successfully ?
		/// @param issue Enum value describing how it ended.
		/// @param errMsg Error message
		/// @param isFatal Is the issue fatal (i.e. requiring to abort
		/// the application) ?
		/// @param tweetMap Request result (Tweet) in a QVariantMap.
		void buildResult(bool processOK,
						 CoreResult issue,
						 QString errMsg,
						 bool isFatal,
						 QVariantMap tweetMap = QVariantMap());
};

#endif // UNFAVORITEPROCESS_HPP
