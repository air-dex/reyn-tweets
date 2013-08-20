/// @file singletwittercallprocess.hpp
/// @brief Header of SingleTwitterCallProcess
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

#ifndef SINGLETWITTERCALLPROCESS_HPP
#define SINGLETWITTERCALLPROCESS_HPP

#include "genericprocess.hpp"
#include "../../connection/twitter/reyntwittercalls.hpp"

/// @class SingleTwitterCallProcess
/// @brief Base class for processes which consists in only one call to Twitter.
///
/// This class is a template method pattern because most of processes have to
/// call Twitter once and transmit results.
class SingleTwitterCallProcess : public GenericProcess
{
	Q_OBJECT

	public:
		/// @fn SingleTwitterCallProcess(ReynTweets::CoreResult rightEnd = ReynTweets::INVALID_END);
		/// @brief Constructor
		/// @brief rightEnd CoreResult if the request was successful
		SingleTwitterCallProcess(ReynTweets::CoreResult rightEnd = ReynTweets::INVALID_END);

		/// @fn void startProcess();
		/// @brief Starting the processes by connecting the process and Twitter
		/// and then calling Twitter via the callTwitter(); method.
		void startProcess();

	public slots:
		/// @fn void callEnded(ResultWrapper res);
		/// @brief Slot executed after the treatment
		/// @param res Result of the Twitter request
		void callEnded(ResultWrapper res);

	protected:
		/// @brief Entity calling Twitter
		ReynTwitterCalls twitter;

		/// @brief CoreResult if the request was successful
		ReynTweets::CoreResult successfullEnd;

		/// @fn virtual void callTwitter() = 0;
		/// @brief Method calling Twitter its code often looks like
		/// "<code>twitter.doSthg();</code>".
		virtual void callTwitter() = 0;

		/// @fn virtual void treatSuccessfulResult(QVariant result);
		/// @brief Default treatment when the request was successful
		/// @param result Result
		virtual void treatSuccessfulResult(QVariant result);

		/// @fn virtual void treatTwitterErrorResult(RequestResult result,
		///											 QString &errorMsg,
		///											 ReynTweets::CoreResult &procEnd);
		/// @brief Default treatment when Twitter says that the request was unsuccessful
		/// @param result Result of the request
		/// @param errorMsg Error message of the process
		/// @param procEnd Reference on the result of the process
		virtual void treatTwitterErrorResult(RequestResult result,
											 QString &errorMsg,
											 ReynTweets::CoreResult &procEnd);

		/// @fn virtual void treatApiCallResult(RequestResult result,
		///                                     QString &errorMsg,
		///										ReynTweets::CoreResult &procEnd);
		/// @brief Default treatment when there was a problem while calling Twitter
		/// @param result Result of the request
		/// @param errorMsg Error message of the process
		/// @param procEnd Reference on the result of the process
		virtual void treatApiCallResult(RequestResult result,
										QString &errorMsg,
										ReynTweets::CoreResult &procEnd);

		/// @fn virtual void treatQjsonParsingResult(ResponseInfos parsingErrors,
		///											 QString &errorMsg,
		///											 ReynTweets::CoreResult &procEnd);
		/// @brief Default treatment when results cannot be parsed
		/// @param parsingErrors Errors that occured while parsing results
		/// @param errorMsg Error message of the process
		/// @param procEnd Reference on the result of the process
		virtual void treatQjsonParsingResult(ResponseInfos parsingErrors,
											 QString &errorMsg,
											 ReynTweets::CoreResult &procEnd);

		/// @fn virtual void treatUnknownResult(QString resultErrorMessage,
		///										QString &errorMsg,
		///                                     ReynTweets::CoreResult & procEnd);
		/// @brief Default treatment when the result was unexpected
		/// @param resultErrorMessage Error message of the request
		/// @param errorMsg Error message of the process
		/// @param procEnd Reference on the result of the process
		virtual void treatUnknownResult(QString resultErrorMessage,
										QString &errorMsg,
										ReynTweets::CoreResult & procEnd);
};

#endif // SINGLETWITTERCALLPROCESS_HPP
