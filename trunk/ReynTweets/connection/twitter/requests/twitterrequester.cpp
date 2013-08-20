/// @file twitterrequester.cpp
/// @brief Implementation of TwitterRequester
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2012, 2013 Romain Ducher
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

#include "twitterrequester.hpp"
#include "../../common/utils/parsers/jsonparser.hpp"
#include <QJsonObject>
#include <QJsonArray>
#include <QTextStream>

// Constructor
TwitterRequester::TwitterRequester(LibRT::HTTPRequestType type,
								   QString url,
								   TwitterAuthenticator &authManager,
								   LibRT::NetworkResultType parseError) :
	GenericRequester(type, url, parseError),
	oauthManager(authManager)
{}

///////////////////////////
// Building HTTP Headers //
///////////////////////////

void TwitterRequester::buildHTTPHeaders() {
	// For the Content-Type
	GenericRequester::buildHTTPHeaders();

	// Be careful for update with medias
	headers.insert("Content-Type", "application/x-www-form-urlencoded");

	// Building the OAuth header
	headers.insert("Authorization", this->getAuthorizationHeader());
}

// Building the "Authorization" header needed for Twitter requests
QByteArray TwitterRequester::getAuthorizationHeader() {
	return oauthManager.getAuthorizationHeader(requestType,
											   requestURL,
											   getParameters,
											   postParameters);
}


////////////////////////////
// Network reply tratment //
////////////////////////////

// Workaround for this bug : https://bugreports.qt-project.org/browse/QTBUG-32524
// TODO quand passage à Qt 5.1.2 : remove those 3 #include as soon as the bug is fixed
#include <QJsonValue>
#include <QJsonArray>
#include <QJsonObject>

// Method that will parse the raw results of the request.
QVariant TwitterRequester::parseResult(NetworkResponse results,
									   bool & parseOK,
									   QVariantMap & parsingErrors)
{
	JSONParser parser;
	QString errorMsg;
	int lineMsg;

	// TODO : improve it because of improved JSONParser
	QJsonValue parseval = parser.parse(results.getResponseBody(),
									   &parseOK, &errorMsg,
									   &lineMsg);

	// Workaround for this bug : https://bugreports.qt-project.org/browse/QTBUG-32524
	// TODO quand passage à Qt 5.1.2 : remove it as soon as the bug is fixed
	QVariant result;
	switch (parseval.type()) {
		case QJsonValue::Object: {
			// Is the QJsonObject empty ?
			QJsonObject o = parseval.toObject();
			if (o.isEmpty()) {
				// Buggy case
				QVariantMap varmap;
				result = QVariant::fromValue(varmap);
			} else {
				result = parseval.toVariant();
			}
		} break;

		case QJsonValue::Array: {
			// Is the QJsonArray empty ?
			QJsonArray a = parseval.toArray();
			if (a.isEmpty()) {
				// Buggy case
				QVariantList varlist;
				result = QVariant::fromValue(varlist);
			} else {
				result = parseval.toVariant();
			}
		} break;

		default:
			result = parseval.toVariant();
			break;
	}

	// Normal code (when no bug)
//	QVariant result = parseval.toVariant();

	if (!parseOK) {
		// There was a problem while parsing -> fill the parsingErrors map !
		parsingErrors.insert("errorMsg", QVariant::fromValue(errorMsg));
		parsingErrors.insert("lineError", QVariant::fromValue(lineMsg));
	}

	return result;
}

// Treating parsed results
QList<ResponseInfos> TwitterRequester::treatServiceErrors(QVariant parsedResults,
														  NetworkResponse netResponse)
{
	QList<ResponseInfos> serviceErrors;

	int httpCode = netResponse.getHttpResponse().code;

	// Is the return code expected ?
	switch (httpCode) {
		case 200:
			// If the response code is 200, it is not an error
			return QList<ResponseInfos>();

		// Expected return codes
		case 304:
		case 400:
		case 401:
		case 403:
		case 404:
		case 406:
		case 410:
		case 420:
		case 422:
		case 429:
		case 500:
		case 502:
		case 503:
		case 504:
			break;

		// Unexpected return code
		default: {
			ResponseInfos error;
			error.code = httpCode;
			error.message = TwitterRequester::trUtf8("Unexpected HTTP return code")
					.append(" '")
					.append(QString::number(httpCode))
					.append("'.");

			serviceErrors.append(error);
		} break;
	}


	// Does the parsed results contain Twitter errors ?
	bool areTwitterErrors = false;

	// If there were twitter errors, parsed results are aa QJsonObject
	QJsonValue resval = QJsonValue::fromVariant(parsedResults);

	if (resval.isObject()) {
		// It is a QJsonObject. Does it contain the "errors" JSON Array ?
		QJsonObject resobj = resval.toObject();
		areTwitterErrors = resobj.value("errors").isArray();
	}

	// Fill serviceErrors if there are errors
	if (areTwitterErrors) {
		QJsonArray twitterErrors = resval.toObject().value("errors").toArray();

		for (QJsonArray::Iterator it = twitterErrors.begin();
			 it != twitterErrors.end();
			 ++it)
		{
			QJsonValue twitterError = *it;

			if (twitterError.isObject()) {
				QJsonObject twError = twitterError.toObject();
				ResponseInfos resError;
				resError.code = int(twError.value("code").toDouble());
				resError.message = twError.value("message").toString();

				serviceErrors.append(resError);
			}
		}
	}

	return serviceErrors;
}
