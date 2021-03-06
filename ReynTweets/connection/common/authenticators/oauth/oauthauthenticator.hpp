/// @file oauthauthenticator.hpp
/// @brief Header of OAuthAuthenticator
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

#ifndef OAUTHAUTHENTICATOR_HPP
#define OAUTHAUTHENTICATOR_HPP

#include "../basicauthenticators.hpp"

/// @class OAuthAuthenticator
/// @brief Base class for Authentication managers related to OAuth.
///
/// It contains the Consumer tokens pair
class OAuthAuthenticator {
	public:
		/// @fn OAuthAuthenticator(QString version = "");
		/// @brief Constructor
		/// @param version Version of OAuth
		OAuthAuthenticator(QString version = "");

		/// @fn virtual ~OAuthAuthenticator();
		/// @brief Destructor
		virtual ~OAuthAuthenticator();

		/////////////////////
		// Getters on data //
		/////////////////////

		/// @fn void setConsumerKey(QByteArray clientKey);
		/// @brief Setter on the consumer key
		/// @param clientKey New consumer key
		void setConsumerKey(QByteArray clientKey);

		/// @fn void setConsumerSecret(QByteArray clientSecret);
		/// @brief Setter on the consumer secret
		/// @param clientSecret New consumer secret
		void setConsumerSecret(QByteArray clientSecret);

	protected:
		/// @brief Consumer tokens
		TokenPair consumerTokens;

		/// @brief Version of the OAuth protocol used for the authentication.
		QString oauthVersion;
};

#endif // OAUTHAUTHENTICATOR_HPP
