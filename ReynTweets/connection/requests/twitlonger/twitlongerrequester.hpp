/// @file twitlongerrequester.hpp
/// @brief Header of TwitLongerRequester
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

#ifndef TWITLONGERREQUESTER_HPP
#define TWITLONGERREQUESTER_HPP

#include "../genericrequester.hpp"
#include "../../model/managers/twitlongermanager.hpp"
#include "twitlongerurls.hpp"
#include <QDomElement>

/// @class TwitLongerRequester
/// @brief Base requester for all the request to the TwitLonger API.
class TwitLongerRequester : public GenericRequester
{
	Q_OBJECT

	public:
		/// @fn TwitLongerRequester(RequestType type,
		///							QString url,
		///							TwitLongerManager & manager);
		/// @param type Type of the HTTP request (GET or POST)
		/// @param url URL of the request
		/// @param manager Manager with TwitLonger IDs.
		TwitLongerRequester(RequestType type,
							QString url,
							TwitLongerManager & manager);

	protected:
		/// @brief Manager with TwitLonger IDs.
		TwitLongerManager & twitlongerManager;

		/// @fn virtual QVariant parseResult(bool & parseOK,
		///									 QVariantMap & parsingErrors);
		/// @brief Method that will parse the raw results of the request.
		/// @param parseOK Boolean whose value will be set to true if there was
		/// no problem while parsing, false otherwise.
		/// @param parsingErrors QVariantMap that may contain information about
		/// errors that may occur while parsing.
		/// @return Parsed results
		virtual QVariant parseResult(bool & parseOK,
									 QVariantMap & parsingErrors);

		/// @fn virtual void treatParsedResult();
		/// @brief Treating parsed results
		virtual void treatParsedResult();

		/// @fn virtual QDomElement getInfoElement(QDomElement xmlRoot) = 0;
		/// @brief Getting the XML element with all the necessary informations.
		///
		/// TwitLonger replies are XML streams whose root node called
		/// "twitlonger". This node or one of its children contains a node
		/// with all the needed information. For example, the TwitLonger reply
		/// of the request which posts the message to TwitLonger got all what
		/// the application needs in a node called "post" which is the children
		/// of the root "twitlonger" node. That is this "post" node that this
		/// method will return because its children contain crucial informations
		/// just like the message ID and the shortened tweet.
		/// @param xmlRoot Root of the XML reply.
		/// @return The XML element whose children contained the informations.
		virtual QDomElement getInfoElement(QDomElement xmlRoot) = 0;
};

#endif // TWITLONGERREQUESTER_HPP
