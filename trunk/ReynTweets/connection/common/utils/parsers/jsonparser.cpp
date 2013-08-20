/// @file jsonparser.cpp
/// @brief Implementation of JSONParser
///
/// Revisions older than r120 (SVN) are in the folder
/// /trunk/ReynTweets/connection/parsers.
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2011, 2013 Romain Ducher
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

#include "jsonparser.hpp"
#include <QJsonDocument>

// Parsing method
QJsonValue JSONParser::parse(QByteArray data,
							 bool *parseOK,
							 QString *parseError,
							 int * lineError,
							 int *)
{
	QJsonParseError jsonParseError;

	// Ensure that datas are encoded with UTF-8
	QString utf8data = QString::fromLatin1(data);
	QJsonDocument jsonDoc = QJsonDocument::fromJson(utf8data.toUtf8(),
													&jsonParseError);

	if (parseOK) {
		*parseOK = jsonParseError.error == QJsonParseError::NoError;
	}

	if (parseError) {
		*parseError = jsonParseError.errorString();
	}

	if (lineError) {
		*lineError = jsonParseError.offset;
	}

	QVariant jsonVar = jsonDoc.toVariant();

	return QJsonValue::fromVariant(jsonVar);
}
