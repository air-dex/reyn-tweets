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

#include "../../common/requests/genericrequester.hpp"
#include "twitterurls.hpp"
#include "../../twitter/oauthmanager.hpp"

/// @class TwitterRequester
/// @brief Base class for requesters that use the Twitter API.
///
/// With the v1.1 Twitter API, all the requests have to be authenticated. As a
/// consequence, this class is merged with its daughter AuthenticationRequester.
class TwitterRequester : public GenericRequester
{
	Q_OBJECT

	public:
		/// @fn TwitterRequester(RequestType type,
		///						 QString url,
		///						 OAuthManager & authManager,
		///						 NetworkResultType parseError = Network::JSON_PARSING,
		///						 bool tokenNeeded = true,
		///						 bool callbackURLNeeded = false,
		///						 bool verifierNeeded = false);
		/// @brief Constructor
		/// @param type Type of the request (GET ou POST).
		/// @param url URL called by the requester
		/// @param authManager Entity with information for OAuth
		/// @param parseError Error type if an error occurs while parsing. Most
		/// of the time, this value is set to JSON_PARSING because results are
		/// written in JSON. However, OAuth requesters use their
		/// own parsing process so they need a special value called OAUTH_PARSING.
		/// @param tokenNeeded Boolean indicating if the oauth_token parameter
		/// is required for authentication.
		/// @param callbackURLNeeded Boolean indicating if the oauth_callback
		/// parameter is required for authentication.
		/// @param verifierNeeded Boolean indicating if the oauth_verifier
		/// parameter is required for authentication.
		TwitterRequester(HTTPRequestType type,
						 QString url,
						 OAuthManager & authManager,
						 NetworkResultType parseError = Network::JSON_PARSING,
						 bool tokenNeeded = true,
						 bool callbackURLNeeded = false,
						 bool verifierNeeded = false);

	protected:
		/// @brief Entity with authentication information
		OAuthManager & oauthManager;

		/// @brief Boolean indicating if the oauth_token parameter is required
		/// for authentication.
		bool oauthTokenNeeded;

		/// @brief Boolean indicating if the oauth_callback parameter
		/// is required for authentication.
		bool oauthCallbackUrlNeeded;

		/// @brief Boolean indicating if the oauth_token parameter is required
		/// for authentication.
		bool oauthVerifierNeeded;

		/// @fn virtual QVariant parseResult(NetworkResponse results,
		///									 bool & parseOK,
		///									 QVariantMap & parsingErrors);
		/// @brief Method that will parse the raw results of the request.
		/// @param results Results to parse. Most of the time the method only
		/// uses the responseBody field.
		/// @param parseOK Boolean whose value will be set to true if there was
		/// no problem while parsing, false otherwise.
		/// @param parsingErrors QVariantMap that may contain information about
		/// errors that may occur while parsing.
		/// @return Parsed results
		virtual QVariant parseResult(NetworkResponse results,
									 bool & parseOK,
									 QVariantMap & parsingErrors);

		/// @fn virtual QList<ResponseInfos> treatServiceErrors(QVariant parsedResults,
		///														NetworkResponse netResponse);
		/// @brief Treating parsed results
		/// @param parsedResults Parsed results to analyse in order to retrieve
		/// service errors.
		/// @param netResponse Other network responce elements, if needed.
		/// @return The list of service errors
		/// @see https://dev.twitter.com/docs/error-codes-responses
		virtual QList<ResponseInfos> treatServiceErrors(QVariant parsedResults,
														NetworkResponse netResponse);

	private:
		/// @fn virtual void buildHTTPHeaders();
		/// @brief Building Content-Type and Authorize headers
		virtual void buildHTTPHeaders();
};

#endif // TWITTERREQUESTER_HPP