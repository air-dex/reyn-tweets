/// @file oauthrequester.hpp
/// @brief Header of OAuthRequester
/// @author Romain Ducher

/*
Copyright 2011 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OAUTHREQUESTER_HPP
#define OAUTHREQUESTER_HPP

#include "../genericrequester.hpp"

/// @class OAuthRequester
/// @brief Generic requester for requests dealing with OAuth
class OAuthRequester : public GenericRequester
{
	Q_OBJECT

	public:
		/// @fn OAuthRequester(OAuthManager & authManager,
		///					   RequestType type,
		///					   QString url,
		///					   QObject * requester = 0);
		/// @brief Constructor
		/// @param authManager Information for OAuth. The requester takes its
		/// memory address.
		/// @param type Type of the request (GET ou POST).
		/// @param url URL of the request
		/// @param requester QObject which asks for this search.
		OAuthRequester(OAuthManager & authManager,
					   RequestType type,
					   QString url,
					   QObject * requester = 0);
};

#endif // OAUTHREQUESTER_HPP
