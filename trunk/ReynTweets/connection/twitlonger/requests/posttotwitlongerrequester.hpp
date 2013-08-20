/// @file posttotwitlongerrequester.hpp
/// @brief Header of PostToTwitLongerRequester
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

#ifndef POSTTOTWITLONGERREQUESTER_HPP
#define POSTTOTWITLONGERREQUESTER_HPP

#include "twitlongerrequester.hpp"

#include "../twitlongerconstants.hpp"

/// @class PostToTwitLongerRequester
/// @brief Posting a long message on TwitLonger and receive a shortened version
/// of this message.
class PostToTwitLongerRequester : public TwitLongerRequester
{
	Q_OBJECT

	public:
		/// @fn PostToTwitLongerRequester(TwitLongerAuthenticator & tlmanager,
		///								  QString longTweet,
		///								  QString userScreenName,
		///								  qlonglong replyToStatusID = TwitLonger::FAKE_TWEET_ID,
		///								  QString replyToUserScreenName = TwitLonger::FAKE_SCREEN_NAME);
		/// @brief Constructor
		/// @param tlmanager Entity with TwitLonger settings.
		/// @param longTweet Text of the tweet
		/// @param userScreenName Screen name of the author of the tweet
		/// @param replyToStatusID If the tweet is a reply, this parameter is
		/// the ID of the tweet that this tweet replies to.
		/// @param replyToUserScreenName If the tweet is a reply, this parameter
		/// is the screen name of the tweet that this tweet replies to.
		PostToTwitLongerRequester(TwitLongerAuthenticator & tlmanager,
								  QString longTweet,
								  QString userScreenName,
								  qlonglong replyToStatusID = TwitLonger::FAKE_TWEET_ID,
								  QString replyToUserScreenName = TwitLonger::FAKE_SCREEN_NAME);

	protected:
		/// @brief Text to post
		QString message;

		/// @brief Screen name of the user who wants to shorten its tweet
		QString username;

		/// @brief ID of the tweet that this status replies to
		qlonglong replyToTweetID;

		/// @brief Screen name of the user that this status replies to
		QString replyToUser;

		/// @fn void buildPOSTParameters();
		/// @brief Building the parameters of the request
		void buildPOSTParameters();

		/// @fn QDomElement getInfoElement(QDomElement xmlRoot);
		/// @brief Getting the XML element with all the necessary informations.
		///
		/// The XML reply of this kind of request get a "twitlonger" root tag
		/// which gets a unique child. This child can get two different names :
		/// <ul>
		/// <li><strong>error</strong>if an error occured. In this case, the
		/// error node only gets a string describing the error and the root node
		/// will be returned.</li>
		/// <li><strong>post</strong>if it was successful. The "post" node's
		/// children containing all the informations needed by the application
		/// (message ID, shortened text, URLs (long and shortened by
		/// <a href="http://is.gd/">is.gd</a>) of the long tweet in TwitLonger.
		/// In this case, the method will return the child of the root.</li>
		/// </ul>
		/// @param xmlRoot Root of the XML reply.
		/// @return The node which contains the informations.
		QDomElement getInfoElement(QDomElement xmlRoot);
};

#endif // POSTTOTWITLONGERREQUESTER_HPP
