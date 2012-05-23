/// @file twitterrequester.hpp
/// @brief Header of TwitterRequester
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

#ifndef TWITTERREQUESTER_HPP
#define TWITTERREQUESTER_HPP

#include "genericrequester.hpp"

/// @class TwitterRequester
/// @brief Base class for requesters that use the Twitter API.
class TwitterRequester : public GenericRequester
{
	Q_OBJECT

	public:
		/// @fn TwitterRequester(RequestType type,
		///						 QString url,
		///						 ErrorType parseError = QJSON_PARSING);
		/// @brief Constructor
		/// @param type Type of the request (GET ou POST).
		/// @param url URL called by the requester
		/// @param parseError Error type if an error occurs while parsing. Most
		/// of the time, this value is set to QJSON_PARSING because results are
		/// QJson stream parsed with QJson. However, OAuth requesters use their
		/// own parsing process so they need a special value called OAUTH_PARSING.
		TwitterRequester(RequestType type,
						 QString url,
						 ErrorType parseError = QJSON_PARSING);

	protected:
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
};

#endif // TWITTERREQUESTER_HPP
