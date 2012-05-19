/// @file genericrequester.cpp
/// @brief Implementation of GenericRequester
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011 Romain Ducher
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

#include "genericrequester.hpp"
#include "../../tools/parsers/jsonparser.hpp"

// Constructor. It just calls the parent constructor.
GenericRequester::GenericRequester(RequestType type,
                                   QString url,
                                   ErrorType parseError) :
    QObject(),
    uuid(QUuid::createUuid()),
    requestURL(url),
    requestType(type),
    getParameters(),
    postParameters(),
    headers(),
    weblink(0),
    parsingErrorType(parseError),
    requestResult()
{}


// Destructor
GenericRequester::~GenericRequester() {
    // Deleting the communicator
    if (weblink != 0) {
        delete weblink;
        weblink = 0;
    }
}


/////////////
// Getters //
/////////////

// Getting parsed results
RequestResult GenericRequester::getRequestResult() {
    return requestResult;
}

// Getter on the requester's UUID
QUuid GenericRequester::getUuid() {
    return uuid;
}

// Setting parsingErrorType
void GenericRequester::setParsingErrorType(ErrorType parseErrorType) {
    parsingErrorType = parseErrorType;
}


///////////////////////////
// Executing the request //
///////////////////////////

// Building GET Parameters
void GenericRequester::buildGETParameters() {}

// Bbuilding POST Parameters
void GenericRequester::buildPOSTParameters() {}

// Bbuilding HTTP Headers
void GenericRequester::buildHTTPHeaders() {
    // Be careful for update with medias
    #ifndef Q_OS_SYMBIAN
        // Needed for Qt 4.8.x (Windows and Linux) and Symbian version is 4.7.4.
        headers.insert("Content-Type", "application/x-www-form-urlencoded");
    #endif
}

// Executing the request
void GenericRequester::executeRequest() {
    buildGETParameters();
    buildPOSTParameters();
    buildHTTPHeaders();

    // Init the communicator
    weblink = new TwitterCommunicator(requestURL,
                                  requestType,
                                  getParameters,
                                  postParameters,
                                  headers);

    connect(weblink, SIGNAL(requestDone()),
            this, SLOT(treatResults()));

    weblink->executeRequest();
}


//////////////////////////
// Treatment of results //
//////////////////////////

// Slot executed when the Twitter Communicator has just finished its work.
void GenericRequester::treatResults() {
    // Looking the HHTP request
    requestResult.httpResponse = weblink->getHttpResponse();
    requestResult.errorMessage = weblink->getErrorMessage();

    int httpReturnCode = weblink->getHttpResponse().code;

    if (httpReturnCode == 0) {
        // No response => API_CALL
        requestResult.resultType = API_CALL;
    } else {
        // A response to parse
        bool parseOK;
        QVariantMap parseErrorMap;
        requestResult.parsedResult = this->parseResult(parseOK, parseErrorMap);
        requestResult.resultType = parseOK ? NO_ERROR : parsingErrorType;
        requestResult.parsingErrors.code = parseErrorMap.value("lineError").toInt();
        requestResult.parsingErrors.message = parseErrorMap.value("errorMsg").toString();

        if (!parseOK) {
            // Giving the response just in case the user would like to do sthg with it.
            requestResult.parsedResult = QVariant::fromValue(weblink->getResponseBuffer());
        } else {
            // Is it a map with error messages
            switch (httpReturnCode) {
                case 200:
                    break;

                // Uncomment when the following feature is deployed :
                // https://dev.twitter.com/blog/making-api-responses-match-request-content-type
                    /*
                case 404:
                case 500:
                case 503:
                    if (parsingErrorType == QJSON_PARSING
                            && requestResult.parsedResult.type() == QVariant::Map
                        )
                    {
                        // Table error : one row ("errors"; QVariantList)
                        QVariantMap resultMap = requestResult.parsedResult.toMap();

                        if (resultMap.size() == 1
                                && resultMap.contains("errors")
                                && resultMap.value("errors").type() == QVariant::List
                            )
                        {
                            QVariantList errorList = resultMap.value("errors").toList();

                            // Building the list of errors
                            for (QVariantList::Iterator it = errorList.begin();
                                 it != errorList.end();
                                 ++it)
                            {
                                QVariantMap error = it->toMap();
                                ResponseInfos twitterError;
                                twitterError.code = error.value("code").toInt();
                                twitterError.message = error.value("message").toString();
                                requestResult.twitterErrors.append(twitterError);
                            }

                            requestResult.resultType = TWITTER_ERRORS;
                        }
                    }
                    break;
                    //*/

                case 304:
                case 400:
                case 401:
                case 403:
                case 406:
                case 420:
                case 502:
                    if (parsingErrorType == QJSON_PARSING
                            && requestResult.parsedResult.type() == QVariant::Map
                        )
                    {
                        // Table error : two rows called "error" and "request"
                        QVariantMap resultMap = requestResult.parsedResult.toMap();

                        if (resultMap.size() == 2
                                && resultMap.contains("error")
                                && resultMap.contains("request")
                            )
                        {
                            ResponseInfos twitterError;
                            twitterError.code = httpReturnCode;

                            twitterError.message = resultMap.value("error").toString();
                            requestResult.twitterErrors.append(twitterError);

                            twitterError.message = resultMap.value("request").toString();
                            requestResult.twitterErrors.append(twitterError);

                            requestResult.resultType = TWITTER_ERRORS;
                        }
                    }
                    break;

                default:
                    requestResult.resultType = API_CALL;
                    break;
            }
        }
    }

    // Telling the ReynTwitterCalls that the request is finished
    emit requestDone();
}

// Method that will parse the raw results of the request.
QVariant GenericRequester::parseResult(bool & parseOK, QVariantMap & parsingErrors) {
    JSONParser parser;
    QByteArray rawResponse = weblink->getResponseBuffer();
    QString errorMsg;
    int lineMsg;

    // Special treatment for lists because of a QJSON bug while parsing lists
    bool isList = rawResponse.startsWith('[');
    // Truc pour le debug :
    if (isList) {
        rawResponse.prepend("{\"reslist\":");
        rawResponse.append('}');
    }

    QVariant result = parser.parse(rawResponse, parseOK, errorMsg, &lineMsg);

    if (!parseOK) {
        // There was a problem while parsing -> fill the parsingErrors map !
        parsingErrors.insert("errorMsg", QVariant(errorMsg));
        parsingErrors.insert("lineError", QVariant(lineMsg));
    }

    // Retrieveing the list to parse
    if (isList) {
        result = QVariant(result.toMap().value("reslist"));
    }

    return result;
}
