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
#include "../../connection/calls/reyntwittercalls.hpp"

/// @class SingleTwitterCallProcess
/// @brief Base class for processes which consists in only one call to Twitter.
///
/// This class is a template method pattern because most of processes have to
/// call Twitter once and transmit results.
class SingleTwitterCallProcess : public GenericProcess
{
    Q_OBJECT

    public:
        /// @fn SingleTwitterCallProcess(CoreResult rightIssue = INVALID_ISSUE);
        /// @brief Constructor
        SingleTwitterCallProcess(CoreResult rightIssue = INVALID_ISSUE);

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

        /// @brief Issue if the request was successful
        CoreResult successfullIssue;

        /// @fn virtual void callTwitter() = 0;
        /// @brief Method calling Twitter its code often looks like
        /// "<code>twitter.doSthg();</code>".
        virtual void callTwitter() = 0;

        /// @fn void buildResult(bool processOK,
        ///						 CoreResult issue,
        ///						 QString errMsg = "",
        ///						 bool isFatal = false);
        /// @brief Building process results for unsuccessful ends
        /// @param processOK Did the process end successfully ?
        /// @param issue Enum value describing how it ended.
        /// @param errMsg Error message
        /// @param isFatal Is the issue fatal (i.e. requiring to abort
        /// the application) ?
        void buildResult(bool processOK,
                         CoreResult issue,
                         QString errMsg,
                         bool isFatal);

        /// @fn void buildResult(QVariant result);
        /// @brief Building process results for successful ends
        /// @param result Request result
        void buildResult(QVariant result);

        /// @fn virtual void treatSuccessfulResult(QVariant result);
        /// @brief Default treatment when the request was successful
        /// @param result Result
        virtual void treatSuccessfulResult(QVariant result);

        /// @fn virtual void treatTwitterErrorResult(RequestResult result,
        ///											 QString &errorMsg,
        ///											 CoreResult &issue);
        /// @brief Default treatment when Twitter says that the request was unsuccessful
        /// @param result Result of the request
        /// @param errorMsg Error message of the process
        /// @param issue Reference on the issue of the request
        virtual void treatTwitterErrorResult(RequestResult result,
                                             QString &errorMsg,
                                             CoreResult &issue);

        /// @fn virtual void treatApiCallResult(RequestResult result,
        ///                                     QString &errorMsg,
        ///										CoreResult &issue);
        /// @brief Default treatment when there was a problem while calling Twitter
        /// @param result Result of the request
        /// @param errorMsg Error message of the process
        /// @param issue Reference on the issue of the request
        virtual void treatApiCallResult(RequestResult result,
                                        QString &errorMsg,
                                        CoreResult &issue);

        /// @fn virtual void treatQjsonParsingResult(ResponseInfos parsingErrors,
        ///											 QString &errorMsg,
        ///											 CoreResult &issue);
        /// @brief Default treatment when results cannot be parsed
        /// @param parsingErrors Errors that occured while parsing results
        /// @param errorMsg Error message of the process
        /// @param issue Reference on the issue of the request
        virtual void treatQjsonParsingResult(ResponseInfos parsingErrors,
                                             QString &errorMsg,
                                             CoreResult &issue);

        /// @fn virtual void treatUnknownResult(QString resultErrorMessage,
        ///										QString &errorMsg,
        ///                                     CoreResult & issue,
        ///										bool & fatal);
        /// @brief Default treatment when the issue was unexpected
        /// @param resultErrorMessage Error message of the request
        /// @param errorMsg Error message of the process
        /// @param issue Reference on the issue of the request
        /// @param fatal Boolean indicating if the request error was fatal or not.
        virtual void treatUnknownResult(QString resultErrorMessage,
                                        QString &errorMsg,
                                        CoreResult & issue,
                                        bool & fatal);
};

#endif // SINGLETWITTERCALLPROCESS_HPP
