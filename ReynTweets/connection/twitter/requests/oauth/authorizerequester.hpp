/// @file authorizerequester.hpp
/// @brief Header of AuthorizeRequester
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011 Romain Ducher
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

#ifndef AUTHORIZEREQUESTER_HPP
#define AUTHORIZEREQUESTER_HPP

#include "oauthrequester.hpp"

/// @class AuthorizeRequester
/// @brief Requester for OAuth authentication
class AuthorizeRequester : public OAuthRequester
{
	Q_OBJECT

	public:
		/// @fn AuthorizeRequester(OAuthManager & authManagerr,
		///						   bool forceLog = false,
		///						   QString writeLogin = "");
		/// @brief Constructor
		/// @param authManager Informations for OAuth.
		/// @param forceLog Value for forceLogin
		/// @param writeLogin Value for screenName
		AuthorizeRequester(OAuthManager & authManager,
						   bool forceLog = false,
						   QString writeLogin = "");

	protected:
		/// @brief Boolean indicating if the user as to sign in to
		/// Twitter to authorize the application. Quite useless in Reyn Tweets.
		bool forceLogin;

		/// @brief Screen name of the user which want to authorize the app,
		/// in order to write it in the authentication page which will be
		/// returned. Quite useless in Reyn Tweets.
		QString screenName;

		/////////////////////////////////
		// Override for this requester //
		/////////////////////////////////

		/// @fn void buildGETParameters();
		/// @brief Method building GET Parameters
		void buildGETParameters();

		/// @fn QVariant parseResult(NetworkResponse results,
		///							 bool & parseOK,
		///							 QVariantMap & parsingErrors);
		/// @brief Method that will parse the raw results of the request.
		/// @param results Results to parse. Most of the time the method only
		/// uses the responseBody field.
		/// @param parseOK Boolean whose value will be set to true if there was
		/// no problem while parsing, false otherwise.
		/// @param parsingErrors QVariantMap that may contain information about
		/// errors that may occur while parsing.
		/// @return Parsed results
		QVariant parseResult(NetworkResponse results,
							 bool & parseOK,
							 QVariantMap & parsingErrors);
};

#endif // AUTHORIZEREQUESTER_HPP
