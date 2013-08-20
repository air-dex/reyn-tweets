/// @file twitlongerrequester.cpp
/// @brief Implementation of TwitLongerRequester
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

#include <QDomDocument>
#include <QDomElement>
#include "twitlongerrequester.hpp"
#include "../../../tools/parsers/xmlparser.hpp"

// Constructor
TwitLongerRequester::TwitLongerRequester(HTTPRequestType type,
										 QString url,
										 TwitLongerManager & manager) :
	GenericRequester(type, url, Network::XML_PARSING),
	twitlongerManager(manager)
{}

// Method that will parse the raw results of the request.
QVariant TwitLongerRequester::parseResult(NetworkResponse results,
										  bool &parseOK,
										  QVariantMap &parsingErrors)
{
	XMLParser parser;
	QByteArray rawResponse = results.getResponseBody();
	QString errorMsg;
	int lineMsg;

	QDomElement xmlResults = parser.parse(rawResponse, parseOK, errorMsg, &lineMsg);

	if (!parseOK) {
		// There was a problem while parsing -> fill the parsingErrors map !
		parsingErrors.insert("errorMsg", QVariant(errorMsg));
		parsingErrors.insert("lineError", QVariant(lineMsg));
	}

	QVariantMap resultMap;

	if (!xmlResults.isNull()) {
		QDomElement infoElement = getInfoElement(xmlResults);

		for (QDomNode result = infoElement.firstChild();
			 !result.isNull();
			 result = result.nextSibling())
		{
			QDomElement resultElt = result.toElement();

			resultMap.insert(resultElt.tagName(), QVariant(resultElt.text()));
		}
	}

	return QVariant(resultMap);

}

QList<ResponseInfos> TwitLongerRequester::treatServiceErrors(QVariant parsedResults,
															 NetworkResponse netResponse)
{
	QList<ResponseInfos> serviceErrors;

	QVariantMap resultMap = parsedResults.toMap();

	if (resultMap.contains("error")) {
		ResponseInfos twitLongerError;
		twitLongerError.code = netResponse.getHttpResponse().code;
		twitLongerError.message = resultMap.value("error").toString();
		serviceErrors.append(twitLongerError);
	}

	return serviceErrors;
}

