/// @file utils.cpp
/// @brief Implementation of the useful methods declared in utils.hpp.
///
/// Revisions older than r120 are in the folder /trunk/ReynTweets/connection/.
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

#include "utils.hpp"
#include <QCryptographicHash>
#include <QVariant>
#include <QMapIterator>
#include <QMetaProperty>
#include <QJsonDocument>
#include <QUrl>

///////////////////////
// String convertion //
///////////////////////

// Converting a RequestType into a QString
QString requestTypeToString(HTTPRequestType type) {
	switch (type) {
		case Network::GET:
			return "GET";
		case Network::POST:
			return "POST";
		default:
			return "";
	}
}

// Converting a bool into a QString
QString boolInString(bool b) {
	return b ? "true" : "false";
}

// Converting a String into a QColor.
QColor string2color(QString coloredString) {
	// Add a '#' at the beginning if not present
	static QChar sharp('#');
	if (!coloredString.startsWith(sharp)) {
		coloredString.prepend(sharp);
	}

	return QColor(coloredString);
}


//////////////////
// Miscanellous //
//////////////////

// Exclusive OR
bool ouBien(bool a, bool b) {
	return  (a && !b) || (!a && b);
}

// Formatting parameters in the Authorization header
QString formatParam(QString name, QString value, bool putDoubleQuotes) {
	QString res = "";
	QByteArray percentEncoded;

	// Percent encoding the name
	percentEncoded = QUrl::toPercentEncoding(name);
	res.append(percentEncoded);

	res.append('=');
	if (putDoubleQuotes) {
		res.append('"');
	}

	// Percent encoding the value
	percentEncoded = QUrl::toPercentEncoding(value);
	res.append(percentEncoded);

	if (putDoubleQuotes) {
		res.append('"');
	}

	return res;
}
