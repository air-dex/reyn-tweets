/// @file searchrequest.hpp
/// @brief Requester for searches
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
along with Reyn Tweets.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SEARCHREQUESTER_HPP
#define SEARCHREQUESTER_HPP

#include "genericrequester.hpp"

/// @class SearchRequest
/// @brief Requester for searches
class SearchRequester : public GenericRequester
{
	Q_OBJECT

	public:
		/// @fn SearchRequester(QObject * requester, QString q = "");
		/// @brief Constructor
		/// @param requester QObject which asks for this search
		/// @param q The query
		/// @see https://dev.twitter.com/docs/api/1/get/search
		SearchRequester(QObject * requester, QString q = "");

	protected:
		/// @brief Query made by the user
		QString query;

		/// @fn virtual void buildGETParameters();
		/// @brief Virtual method building getParameters
		void buildGETParameters();

		/// @fn virtual void buildPOSTParameters();
		/// @brief Virtual method building postParameters
		void buildPOSTParameters();

		/// @fn virtual void parseResult();
		/// @brief Method that will parse the raw results of the request.
		/// @return true if there was no problem while parsing, false otherwise.
		/// @sa bool GenericRequester::parseResult();
		bool parseResult();

		/// @fn virtual void treatError() = 0;
		/// @brief Method that will treat errors of the requests made by the
		/// Twitter Communicator.
		void treatError();
};

#endif // SEARCHREQUESTER_HPP
