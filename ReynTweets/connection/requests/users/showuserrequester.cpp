/// @file showuserrequester.cpp
/// @brief Implementation of ShowUserRequester
/// @author Romain Ducher

/*
Copyright 2012 Romain Ducher

This file is part of Reyn Tweets.

Reyn Tweets is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Reyn Tweets is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#include "showuserrequester.hpp"
#include "../../../tools/utils.hpp"

// Constructor with the user ID
ShowUserRequester::ShowUserRequester(OAuthManager & authManager,
									 long id,
									 bool entities) :
	AuthenticationRequester(GET, TwitterURL::SHOW_USER_URL, authManager),
	idWay(ID),
	userID(id),
	includeEntities(entities),
	screenName()
{}

// Constructor with the screen name
ShowUserRequester::ShowUserRequester(OAuthManager authManager,
									 QString name,
									 bool entities) :
	AuthenticationRequester(GET, TwitterURL::SHOW_USER_URL, authManager),
	idWay(SCREEN_NAME),
	userID(),
	includeEntities(entities),
	screenName(name)
{}

// Building getParameters
void ShowUserRequester::buildGETParameters() {
	if (idWay == ID) {
		getParameters.insert("id", QString::number(userID));
	}

	getParameters.insert("include_entities", boolInString(includeEntities));

	if (idWay == SCREEN_NAME) {
		getParameters.insert("screen_name", screenName);
	}

}
