/// @file showuserrequester.cpp
/// @brief Implementation of ShowUserRequester
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

#include "showuserrequester.hpp"
#include "../../../common/utils/connectionutils.hpp"

// Constructor with the user ID
ShowUserRequester::ShowUserRequester(TwitterAuthenticator & authManager,
									 qlonglong id,
									 bool entities) :
	TwitterRequester(LibRT::GET, Twitter::SHOW_USER_URL, authManager),
	idWay(LibRT::ID),
	userID(id),
	includeEntities(entities),
	screenName()
{}

// Constructor with the screen name
ShowUserRequester::ShowUserRequester(TwitterAuthenticator & authManager,
									 QString name,
									 bool entities) :
	TwitterRequester(LibRT::GET, Twitter::SHOW_USER_URL, authManager),
	idWay(LibRT::SCREEN_NAME),
	userID(),
	includeEntities(entities),
	screenName(name)
{}

// Building getParameters
void ShowUserRequester::buildGETParameters() {
	if (idWay == LibRT::ID) {
		getParameters.insert("id", QString::number(userID));
	}

	getParameters.insert("include_entities", boolInString(includeEntities));

	if (idWay == LibRT::SCREEN_NAME) {
		getParameters.insert("screen_name", screenName);
	}

}
