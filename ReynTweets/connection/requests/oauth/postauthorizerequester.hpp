/// @file postauthorizerequester.hpp
/// @brief Header of PostAuthorizeRequester
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
along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef POSTAUTHORIZEREQUESTER_HPP
#define POSTAUTHORIZEREQUESTER_HPP

#include <QObject>
#include <QVariant>
#include "oauthrequester.hpp"

/// @class PostAuthorizeRequester
/// @brief Request POST authorize(). They send to Twitter user's credentials to
/// authorize the request tokens.
class PostAuthorizeRequester : public OAuthRequester
{
	Q_OBJECT

	public:
		/// @fn PostAuthorizeRequester(QObject * requester,
		///							   OAuthManager & authManager,
		///							   QString pseudo,
		///							   QString pwd,
		///							   bool deny);
		/// @brief Constructor
		/// @param requester QObject asking for the request
		/// @param authManager OAuth informations
		/// @param pseudo User login, i.e. sername or email
		/// @param pwd User password
		/// @param deny Boolean indicating if the application must be denied
		/// (true) or authorized (false).
		PostAuthorizeRequester(QObject * requester,
							   OAuthManager & authManager,
							   QString pseudo,
							   QString pwd,
							   bool deny);

	protected:
		/// @brief User login, i.e. its username or its email
		QString login;

		/// @brief User password
		QString password;

		/// @brief Boolean indicating if the application must be denied (true)
		/// or authorized (false).
		bool denyReynTweets;

		/////////////////////////////////
		// Override for this requester //
		/////////////////////////////////

		/// @fn void buildPOSTParameters();
		/// @brief Building postParameters
		void buildPOSTParameters();

		/// @fn QVariant parseResult(bool & parseOK, QVariantMap & parsingErrors);
		/// @brief Method that will parse the raw results of the request.
		/// @param parseOK Boolean whose value will be set to true if there was
		/// no problem while parsing, false otherwise.
		/// @param parsingErrors QVariantMap that may contain information about
		/// errors that may occur while parsing.
		/// @return Parsed results
		QVariant parseResult(bool & parseOK, QVariantMap & parsingErrors);
};

#endif // POSTAUTHORIZEREQUESTER_HPP
