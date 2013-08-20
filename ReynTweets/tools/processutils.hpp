/// @file processutils.hpp
/// @brief Useful methods for processes (declaration).
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

#ifndef PROCESSUTILS_HPP
#define PROCESSUTILS_HPP

#include <QString>
#include <QVariant>
#include "../logic/core/coreresult.hpp"
#include "../logic/processes/processresult.hpp"
#include "../connection/common/resultwrapper.hpp"
#include "../connection/common/responseinfos.hpp"

/// @namespace ProcessUtils
/// @brief Namespace with utilities for processes
namespace ProcessUtils {
	//////////////////////////////////////
	// Treating Twitter request results //
	//////////////////////////////////////

	/// @fn void treatSuccessfulResult(QVariant result);
	/// @brief Default treatment when the request was successful
	/// @param result Result
	void treatSuccessfulResult(QVariant result);

	/// @fn void treatTwitterErrorResult(RequestResult result,
	///									 QString &errorMsg,
	///									 CoreResult &issue);
	/// @brief Default treatment when Twitter says that the request was unsuccessful
	/// @param result Result of the request
	/// @param errorMsg Error message of the process
	/// @param issue Reference on the issue of the request
	void treatTwitterErrorResult(RequestResult result,
								 QString &errorMsg,
								 CoreResult &issue);

	/// @fn QString writeTwitterErrors(RequestResult result);
	/// @brief Writing an error message with Twitter errors.
	/// @param result Bad result with errors containing the Twitter errors
	/// (with a code and a message) and the general error message.
	/// @return The corresponding message
	/// @see https://dev.twitter.com/blog/making-api-responses-match-request-content-type
	QString writeTwitterErrors(RequestResult result);

	/// @fn void treatApiCallResult(RequestResult result,
	///								QString &errorMsg,
	///								CoreResult &issue);
	/// @brief Default treatment when there was a problem while calling Twitter
	/// @param result Result of the request
	/// @param errorMsg Error message of the process
	/// @param issue Reference on the issue of the request
	void treatApiCallResult(RequestResult result,
							QString &errorMsg,
							CoreResult &issue);

	/// @fn void treatQjsonParsingResult(ResponseInfos parsingErrors,
	///									 QString &errorMsg,
	///									 CoreResult &issue);
	/// @brief Default treatment when JSON results cannot be parsed by QJSON.
	/// @param parsingErrors Errors that occured while parsing results
	/// @param errorMsg Error message of the process
	/// @param issue Reference on the issue of the request
	void treatQjsonParsingResult(ResponseInfos parsingErrors,
								 QString &errorMsg,
								 CoreResult &issue);

	/// @fn void treatXMLParsingResult(ResponseInfos parsingErrors,
	///								   QString &errorMsg,
	///								   CoreResult &issue);
	/// @brief Default treatment when XML results cannot be parsed.
	/// @param parsingErrors Errors that occured while parsing results
	/// @param errorMsg Error message of the process
	/// @param issue Reference on the issue of the request
	void treatXMLParsingResult(ResponseInfos parsingErrors,
							   QString &errorMsg,
							   CoreResult &issue);

	/// @fn void treatOAuthParsingResult(QString parsingErrorsMsg,
	///									 QString &errorMsg,
	///									 CoreResult &issue);
	/// @brief Default treatment when OAuth results cannot be parsed
	/// @param parsingErrorsMsg Errors that occured while parsing results
	/// @param errorMsg Error message of the process
	/// @param issue Reference on the issue of the request
	void treatOAuthParsingResult(QString parsingErrorsMsg,
								 QString &errorMsg,
								 CoreResult &issue);

	/// @fn void treatUnknownResult(QString resultErrorMessage,
	///								QString &errorMsg,
	///								CoreResult & issue);
	/// @brief Default treatment when the issue was unexpected
	/// @param resultErrorMessage Error message of the request
	/// @param errorMsg Error message of the process
	/// @param issue Reference on the issue of the request
	void treatUnknownResult(QString resultErrorMessage,
							QString &errorMsg,
							CoreResult & issue);
}

#endif // PROCESSUTILS_HPP
