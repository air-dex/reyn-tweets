/// @file apikeyauthenticator.cpp
/// @brief Implementation of APIKeyAuthenticator
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2013 Romain Ducher
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

#include "apikeyauthenticator.hpp"
#include "../utils/librtconstants.hpp"

// Constructor
APIKeyAuthenticator::APIKeyAuthenticator():
	apiKey(LibRT::FAKE_TOKEN)
{}

// Destructor
APIKeyAuthenticator::~APIKeyAuthenticator() {}

// Getting the API Key
QByteArray APIKeyAuthenticator::getAPIKey() {
	return apiKey;
}

// Setting the API Key
void APIKeyAuthenticator::setAPIKey(QByteArray newAPIKey) {
	apiKey = newAPIKey;
}
