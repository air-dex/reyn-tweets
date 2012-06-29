/// @file requestinfos.hpp
/// @brief Header of RequestInfos
///
/// Revisions older than r242 were in /trunk/ReynTweets/connection
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

#ifndef REQUESTINFOS_HPP
#define REQUESTINFOS_HPP

#include <QObject>
#include "genericrequester.hpp"

/// @class RequestInfos
/// @brief Class containing the entity which asks for the request (the "asker")
/// and the requester that executes the request (the "requester").
class RequestInfos
{
	public:
		/// @fn RequestInfos(QObject * requestAsker = 0,
		///					 GenericRequester * twitterRequest = 0);
		/// @brief Constructor
		/// @param requestAsker The asker
		/// @param twitterRequest The requester
		RequestInfos(QObject * requestAsker = 0,
					 GenericRequester * twitterRequest = 0);

		/// @fn ~RequestInfos();
		/// @brief Destructor
		~RequestInfos();

		/// @fn QObject * getAsker();
		/// @brief Getter on the asker
		QObject * getAsker();

		/// @fn GenericRequester * getRequester();
		/// @brief Getter on the requester
		GenericRequester * getRequester();

	protected:
		/// @brief Entity which asks for the request
		QObject * asker;

		/// @brief Requester that executes the request
		GenericRequester * requester;
};

#endif // REQUESTINFOS_HPP
