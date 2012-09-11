/// @file showuserrequester.hpp
/// @brief Header of ShowUserRequester
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

#ifndef SHOWUSERREQUESTER_HPP
#define SHOWUSERREQUESTER_HPP

#include <QString>
#include "../twitterrequester.hpp"
#include "../identificationway.hpp"

/// @class ShowUserRequester
/// @brief Requester for getting details about a user identified by its ID
/// or its screen name.
/// @see https://dev.twitter.com/docs/api/1.1/get/users/show
class ShowUserRequester : public TwitterRequester
{
	public:
		/// @fn ShowUserRequester(OAuthManager & authManager,
		///						  qlonglong id,
		///						  bool entities = true);
		/// @brief Constructor with the user ID
		/// @param authManager OAuthManager for authentication
		/// @param id User ID
		/// @param entities Include entities in the last tweet of the user ?
		ShowUserRequester(OAuthManager & authManager,
						  qlonglong id,
						  bool entities = true);

		/// @fn ShowUserRequester(OAuthManager & authManager,
		///						  QString name,
		///						  bool entities = true);
		/// @brief Constructor with the screen name
		/// @param authManager OAuthManager for authentication
		/// @param name Screen name
		/// @param entities Include entities in the last tweet of the user ?
		ShowUserRequester(OAuthManager & authManager,
						  QString name,
						  bool entities = true);

	protected:
		/// @brief How the user is identified
		IdentificationWay idWay;


		////////////////
		// Parameters //
		////////////////

		/// @brief ID of the user
		qlonglong userID;

		/// @brief Boolean indicating if entities of a tweet have to be included
		/// in the reply
		bool includeEntities;

		/// @brief When this value is set to true, only the id and id_str values
		/// of the user are returned.
		QString screenName;

		/// @fn void buildGETParameters();
		/// @brief Building getParameters
		void buildGETParameters();
};

#endif // SHOWUSERREQUESTER_HPP
