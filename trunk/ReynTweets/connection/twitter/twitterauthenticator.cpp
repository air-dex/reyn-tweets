/// @file twitterauthenticator.cpp
/// @brief Implementation of TwitterAuthenticator
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011, 2013 Romain Ducher
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

#include "twitterauthenticator.hpp"

// Constructor
TwitterAuthenticator::TwitterAuthenticator() :
	OAuth10aAuthenticator(),
	OAuth2Authenticator()
{
	// Forces the version to "1.0" to avoid problems with requests authentication
	this->oauthVersion = "1.0";
}

// Destructor
TwitterAuthenticator::~TwitterAuthenticator() {}

// Resetting the tokens.
void TwitterAuthenticator::resetTokens() {
	OAuth10aAuthenticator::resetTokens();
	OAuth2Authenticator::resetTokens();
}
