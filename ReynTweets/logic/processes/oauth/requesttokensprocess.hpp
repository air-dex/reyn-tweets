/// @file requesttokensprocess.hpp
/// @brief Header of RequestTokensProcess
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

#ifndef REQUESTTOKENSPROCESS_HPP
#define REQUESTTOKENSPROCESS_HPP

#include "../genericprocess.hpp"
#include "../../../connection/common/resultwrapper.hpp"
#include "../../../connection/twitter/reyntwittercalls.hpp"

/// @class RequestTokensProcess
/// @brief Process which asks OAuth Request tokens to the Twitter API.
class RequestTokensProcess : public GenericProcess
{
	Q_OBJECT

	public:
		/// @fn RequestTokensProcess();
		/// @brief Constructor
		RequestTokensProcess();

		/// @fn ~RequestTokensProcess();
		/// @brief Destructor
		~RequestTokensProcess();

		/// @fn void startProcess();
		/// @brief Starting the OAuth Authentication flow
		void startProcess();

		/// @fn void resetTokens();
		/// @brief Resetting the tokens. A full new OAuth authentication process
		/// has to be launch to get tokens and for authentication in requests
		void resetTokens();

	private:
		/// @fn void requestToken();
		/// @brief Demanding a Request Token
		void requestToken();

		/// @fn void authorize();
		/// @brief Authorize the request tokens
		void authorize();


	protected slots:
		/////////////////////////
		// Requests to Twitter //
		/////////////////////////

		/// @fn void requestTokenDemanded(ResultWrapper res);
		/// @brief Treatments after the request for Request Tokens
		/// @param res Result of the request
		void requestTokenDemanded(ResultWrapper res);

		/// @fn void authorizeDemanded(ResultWrapper res);
		/// @brief Treatments after the request for authorizing Request Tokens
		/// @param res Result of the request
		void authorizeDemanded(ResultWrapper res);


	protected:
		/// @brief Entity calling Twitter
		ReynTwitterCalls twitter;

		/// @brief Map with results
		QVariantMap tokensMap;
};

#endif // REQUESTTOKENSPROCESS_HPP
