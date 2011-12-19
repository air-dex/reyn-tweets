/// @file authenticaterequester.hpp
/// @brief Header of AuthenticateRequester
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

#ifndef AUTHENTICATEREQUESTER_HPP
#define AUTHENTICATEREQUESTER_HPP

#include "oauthrequester.hpp"

/// @class AuthenticateRequester
/// @brief Requester for OAuth authentication
class AuthenticateRequester : public OAuthRequester
{
		Q_OBJECT
	public:
		AuthenticateRequester(QObject *parent = 0);

	signals:

	public slots:

};

#endif // AUTHENTICATEREQUESTER_HPP
